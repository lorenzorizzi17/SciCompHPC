/*
**  function: Matrix Multiplication ... three loop, ijk case
**            where ijk defines the order of the loops
**
**  HISTORY: Written by Tim Mattson, July 2012. 
*/
#include "mm_utils.h"

void mm_ijk(int Ndim, int Mdim, int Pdim, TYPE *A, TYPE *B, TYPE *C){
   int i, j, k;
   TYPE tmp;

   for (i=0; i < Ndim; i++){
      for (j=0; j<Mdim; j++){
            tmp = 0.0;
            // formally, C_ij = A_ik B_kj, where k goes from 1 to P
            for(k=0;k<Pdim;k++){
               tmp += *(A+(i*Pdim+k)) *  *(B+(k*Mdim+j));   //accessing the A_ik, B_kj
            }
            *(C+(i*Mdim+j)) += tmp;
      }
   }
}

//optimized version
void mm_ijk_opt(int Ndim, int Mdim, int Pdim, TYPE *A, TYPE *B, TYPE *C){
  

  omp_set_num_threads(8);
  int nthreads;
  
  #pragma omp parallel 
  {
      
      int id = omp_get_thread_num();

      if(id == 0){
         nthreads = omp_get_num_threads();
      }

      int i, j, k;
      TYPE tmp;

      for (i=0; i < Ndim; i++){
         for (j=id; j < Mdim;j+=nthreads){
               tmp = 0.0;
               // formally, C_ij = A_ik B_kj, where k goes from 1 to P
               for(k=0; k<Pdim; k++){
                  tmp += *(A+(i*Pdim+k)) *  *(B+(k*Mdim+j));   //accessing the A_ik, B_kj
               }
               #pragma omp critical
               {
                  *(C+(i*Mdim+j)) += tmp;
               }
         }
      }
  }
}
