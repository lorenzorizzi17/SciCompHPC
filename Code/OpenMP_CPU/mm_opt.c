/*
**  function: Matrix Multiplication ... three loop, ijk case
**            where ijk defines the order of the loops
**
**  HISTORY: Written by Tim Mattson, July 2012. 
*/
#include "mm_utils.h"
#include <math.h>

/* void mm_opt(int Ndim, int Mdim, int Pdim, TYPE *A, TYPE *B, TYPE *C){
  
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
} */

int MIN(int a, int b){
   if(a<b){ return a;}
   else {return b;}
}

#define MAX_PAGE 4096



void mm_opt(int Ndim, int Mdim, int Pdim, TYPE *A, TYPE *B, TYPE *C){ 
   
   ////////////////////////////////////////////////////////////////
   ////     First things first, transpose the matrix B.
   ////     This way, when performing the matrix multiplication
   ////     every row of A gets multiplied by a row of B,
   ////     assuring cache locality (rows are continguous in memory)
   /////////////////////////////////////////////////////////////////
   
   //Calculate tile_size (page size)
   int tile_size_i = sqrt(Mdim*MAX_PAGE / (double)(Pdim*sizeof(TYPE)));
   int tile_size_j = sqrt(Pdim*MAX_PAGE / (double)(Mdim*sizeof(TYPE)));
   
   //Effectively transpose B using tiles
   TYPE* Bt = (TYPE*) malloc(Pdim*Mdim*sizeof(TYPE));
   for (int i=0; i<Pdim; i+=tile_size_i) {
      for (int j=0; j<Mdim; j+=tile_size_j) {
         for (int it=i; it< MIN(Pdim,i+tile_size_i); it++){
            for (int jt=j; jt< MIN(Mdim,j+tile_size_j);jt++){
               *(Bt+it+Pdim*jt) = *(B+jt+Mdim*it);
            }
         }
      }
   }

   omp_set_num_threads(8);
   int nthreads;

   #pragma omp parallel
   {
      int id = omp_get_thread_num();

      if (id == 0){ nthreads = omp_get_num_threads();}

      //i cycle
      for (int i=id; i < Ndim; i+= nthreads){         
         //j cycle
         for (int j=i; j < Mdim; j++){
            TYPE tmp = 0; 
               // Vectorization using 512-bit registers?
               // Something like AVX512, I'm not sure whether my computer have those 
               // but I've noticed quite a performance boost when going from 4 sums to 8 sums
               for(int k=0;k<Pdim; k=k+8){
                  TYPE tmp1 = *(A+(i*Pdim+k+0)) *  *(Bt+(j*Pdim+k+0));  
                  TYPE tmp2 = *(A+(i*Pdim+k+1)) *  *(Bt+(j*Pdim+k+1));
                  TYPE tmp3 = *(A+(i*Pdim+k+2)) *  *(Bt+(j*Pdim+k+2));   
                  TYPE tmp4 = *(A+(i*Pdim+k+3)) *  *(Bt+(j*Pdim+k+3));
                  TYPE tmp5 = *(A+(i*Pdim+k+4)) *  *(Bt+(j*Pdim+k+4));  
                  TYPE tmp6 = *(A+(i*Pdim+k+5)) *  *(Bt+(j*Pdim+k+5));
                  TYPE tmp7 = *(A+(i*Pdim+k+6)) *  *(Bt+(j*Pdim+k+6));  
                  TYPE tmp8 = *(A+(i*Pdim+k+7)) *  *(Bt+(j*Pdim+k+7)); 
                  tmp += tmp1+tmp2+tmp3+tmp4+tmp5+tmp6+tmp7+tmp8;
               }
               *(C+(i*Mdim+j)) += tmp;
         }
         for (int j=0; j < i; j++){
               TYPE tmp = 0.0;
               // Vectorization using 512-bit registers?
               // Something like AVX512, I'm not sure whether my computer have those 
               // but I've noticed quite a performance boost when going from 4 sums to 8 sums
               for(int k=0;k<Pdim; k=k+8){
                  TYPE tmp1 = *(A+(i*Pdim+k+0)) *  *(Bt+(j*Pdim+k+0));  
                  TYPE tmp2 = *(A+(i*Pdim+k+1)) *  *(Bt+(j*Pdim+k+1));
                  TYPE tmp3 = *(A+(i*Pdim+k+2)) *  *(Bt+(j*Pdim+k+2));   
                  TYPE tmp4 = *(A+(i*Pdim+k+3)) *  *(Bt+(j*Pdim+k+3));
                  TYPE tmp5 = *(A+(i*Pdim+k+4)) *  *(Bt+(j*Pdim+k+4));  
                  TYPE tmp6 = *(A+(i*Pdim+k+5)) *  *(Bt+(j*Pdim+k+5));
                  TYPE tmp7 = *(A+(i*Pdim+k+6)) *  *(Bt+(j*Pdim+k+6));  
                  TYPE tmp8 = *(A+(i*Pdim+k+7)) *  *(Bt+(j*Pdim+k+7)); 
                  tmp += tmp1+tmp2+tmp3+tmp4+tmp5+tmp6+tmp7+tmp8;
               }
               *(C+(i*Mdim+j)) += tmp;
         }
      }
   }


}