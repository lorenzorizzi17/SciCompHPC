#include<iostream>
#include<omp.h>

int main(int argc, char* argv[]) {

	int NUM_THREADS = std::stoi(argv[1]);
	int num_steps = 100000000;
	double step = 1.0/(double)num_steps;
	double pi = 0.0;
	double start = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel for reduction (+:pi)
	for(int i = 0; i < num_steps; i++){
		double x = (i+0.5)*step;
		pi += 4.0/(1.0+x*x);
	}

	pi*=step;
	std::cout << omp_get_wtime()-start;
}
