#include <iostream>
#include <fstream>
#include <vector>

#include "constants.h"


namespace single_thread
{

    void process_calculation();

    void calc_central_nodes(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn);

    void calc_left_column(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn);

    void calc_top_row(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn);

    void calc_bottom_row(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn);

    void calc_right_column(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn);

    void print_to_stream(std::ostream &out, const std::vector<std::vector<double>> &Tn);

    void resize_vectors(std::vector<std::vector<double>> &T, std::vector<std::vector<double>> &Tn);

}
