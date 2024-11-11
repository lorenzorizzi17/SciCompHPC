#include <omp.h>
#include <iostream>

static long num_steps = 100000000;
double step;

#define NUM_THREADS 8
#define PAD 8 //based on my knowledge on L1 cache. This is called zero padding an array

int main() {
    int i, nthreads;
    double pi;
    double partial_sum = 0;
    step = 1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        int i,id, numthrds;
        double x; double sum;
        id = omp_get_thread_num();
        numthrds = omp_get_num_threads();
        if(id == 0 ) {
            nthreads=numthrds;
        }
        for (i = id; i < num_steps; i=i+numthrds)
        {
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
        }
        #pragma omp critical 
            partial_sum += sum*step;
    
        
    }

    std::cout << omp_get_wtime() - start << " " << partial_sum;
}




// omp_set_num_threads(int)