#include "multi_thread.h"

namespace multi_thread
{

void process_calculation()
{
    std::vector<std::vector<double>> T;     // Temperatures on last step
    std::vector<std::vector<double>> Tn;    // New temperatures
    resize_vectors(T, Tn);

    // Write zeros, but not in first column
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            // Boundary conditions of first kind
            T[i][j] = 0.0;
            if (j == 0) T[i][j] = 20.0;
        }
    }

#ifdef PRINTING
    // Open file to write
    std::ofstream ofile("output/output_multi_thread.txt", std::ios::out);

    if (!ofile.is_open()) {
        std::cerr << "Cannot open file to write.\n" << std::endl;
        return;
    }
#endif

    // Integration of differential equation
    double t_cur = 0;
    while (t_cur < t_max)
    {
        calc_central_nodes(T, Tn);
        calc_left_column(T, Tn);
        calc_top_row(T, Tn);
        calc_bottom_row(T, Tn);
        calc_right_column(T, Tn);
#ifdef PRINTING
        print_to_stream(ofile, Tn);
#endif

        T.swap(Tn);
        t_cur += dt;
    }

#ifdef PRINTING
    ofile.close();
#endif
}


void calc_central_nodes(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn)
{
    #pragma omp parallel for 
    for (size_t i = 1; i < height - 1; i++)
    {
        for (size_t j = 1; j < width - 1; j++)
        {
            // Differential equation for central nodes
            Tn[i][j] = a * dt * ((T[i][j+1] - 2 * T[i][j] + T[i][j-1]) / (dx*dx) + (T[i+1][j] - 2 * T[i][j] + T[i-1][j]) / (dy*dy)) + T[i][j];
        }
    }
}


void calc_left_column(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn)
{
    size_t j = 0;

    for (size_t i = 0; i < height; i++)
    {
        // Boundary conditions of first kind
        T[i][j] = 20.0; 
    }
}


void calc_top_row(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn)
{
    size_t i = 0;
    
    for (size_t j = 0; j < width; j++)
    {
        // Boundary conditions of third kind
        Tn[i][j] = (100 * dy + Tn[i+1][j]) / (dy + 1);
    }
}


void calc_bottom_row(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn)
{
    size_t i = height - 1;

    for (size_t j = 0; j < width; j++)
    {
        // Boundary conditions of second kind
        Tn[i][j] = 10*dy + Tn[i-1][j];
    }
}


void calc_right_column(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn)
{
    size_t j = width - 1;

    for (size_t i = 0; i < height; i++)
    {
        // Boundary conditions of second kind (zero flow)
        Tn[i][j] = Tn[i][j-1];
    }
}


void print_to_stream(std::ostream &out, const std::vector<std::vector<double>> &Tn)
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            // Write frame
            out << Tn[i][j] << " ";
        }
        out << std::endl;
    }
    out << std::endl;
}


void resize_vectors(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn)
{
    T.resize(height);
    Tn.resize(height);
    for (size_t i = 0; i < height; i++)
    {
        T[i].resize(width);
        Tn[i].resize(width);
    }
}

}
