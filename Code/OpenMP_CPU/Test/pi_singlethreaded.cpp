#include<iostream>
#include<omp.h>

int main(int argc, char* argv[]) {

        int num_steps = 100000000;
        double step = 1.0/(double)num_steps;
        double pi = 0.0;

        double start = omp_get_wtime();
        {
                double x;
                double sum;
                for(int i = 0; i < num_steps; i++) {
                        x = (i+ 0.5)*step;
                        sum += 4.0/(1.0+x*x);  //every thread will have its internal copy of i that is not interfering with others              
                }
                pi += sum*step;
        }
	std::cout << pi << " ";
        std::cout << omp_get_wtime()-start;
}

