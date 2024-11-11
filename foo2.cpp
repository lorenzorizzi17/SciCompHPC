#include <omp.h>
#include<iostream>

static long num_steps = 100000000;

#define NUM_THREADS 8

int main() {
    int i, nthreads;
    double pi = 0;
    double step = 1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:pi)
    for(int i = 0; i < num_steps; i++ ) {
        double x  = (i+0.5)*step;
        pi += 4.0/(1.0+x*x)*(step);
    }
    std::cout << pi << " " << omp_get_wtime() - start;
}
