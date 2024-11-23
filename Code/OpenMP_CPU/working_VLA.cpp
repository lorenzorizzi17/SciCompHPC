#include <iostream>


int main(int argc, char* argv[]) {
	std::cout << __cplusplus;
	  int NUM_THREADS;
      	  std::cin >> NUM_THREADS;	
          //int NUM_THREADS = std::stoi(argv[1]);

          double sum[NUM_THREADS];
          
	  for(int i = 0; i < NUM_THREADS; i++){
                  sum[i] = i;
          }
 	  
	 
	  for (int i = 0; i < NUM_THREADS; i++){
	  	std::cout << sum[i] << " ";
	  };
}
