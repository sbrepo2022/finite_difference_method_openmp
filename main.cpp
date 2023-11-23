/*
    Performance comparison of single-threaded and multithreaded calculation implementation
    of the dynamics of the thermal conductivity of the plate.
    ---

    Sergey Borisov (c) 2023
    borisov123.sergey@yandex.ru

    License: MIT [https://mit-license.org/]
*/

#include <omp.h>

#include "single_thread.h"
#include "multi_thread.h"


int main()
{
    double t_start, t_end;

    t_start = omp_get_wtime();
    single_thread::process_calculation();
    t_end = omp_get_wtime();
    std::cout << "Single-thread execution: " << t_end - t_start << " sec remains\n";

    t_start = omp_get_wtime();
    multi_thread::process_calculation();
    t_end = omp_get_wtime();
    std::cout << "Multithread execution: " << t_end - t_start << " sec remains\n";

    return 0;
}
