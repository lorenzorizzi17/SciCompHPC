#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include<math.h>
#include <string.h> 
// 
// This program traverses a linked list carrying out
// a compute-intensive computation for each element 
// of the list.  The computations are independent and
// don't matter at all for the purposes of this exercise.
// 
// The goal is to process the traversal of the list in 
// parllel, not the computation carried out for each 
// node in the list.
//
// Therefore, go to main() and stick to work in main 
// for this exercise.
// 

// N is the length of the list
#ifndef N
#define N 15
#endif

// Start computing fibonacci numbers from the FS'th element in
// the sequence during the process-work step in this program.
#ifndef FS
#define FS 30
#endif

#define NTHREADS 8

// definition of a node in the list
struct node {
   int data;
   int fibdata;
   struct node* next;
};

// recurrsively compute a number in the fibonacci sequence
int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fib(n - 1);
      y = fib(n - 2);
	  return (x + y);
   }
}

// compute the member in the fibonnacci sequence given
// by the value of data in the list of nodes
void processwork(struct node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

// initialize the list
struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = (struct node*) malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i=0; i< N; i++) {
       temp  =  malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}

struct node* advance(struct node** p, int i){
   for(int j = 0; j< i; j++){
            *p = (*p)->next;
            if(*p == NULL){return NULL;}
   }
}




int main(int argc, char *argv[]) {
   double start, end;
   struct node *p=NULL;
   struct node *temp=NULL;
   struct node *head=NULL;
     
   //printf("Process linked list of length %d\n",N);
   //printf("Each node will be processed by function 'processwork()'\n");
   //printf("We will compute fibonacci numbers starting at %d\n",FS);
 
   p = init_list(p);
   head = p;

   // traverse the list process work for each node
   start = omp_get_wtime();
   omp_set_num_threads(NTHREADS);
   int nthreads;
   #pragma omp parallel
   {
        //assign an id to each thread
        int id = omp_get_thread_num();

        if (id == 0) {nthreads = omp_get_num_threads();}

        // every thread will cover a portion of the linked list
        // Thread with id = i will start processing from element i in the linked list
        // advance is a simple function that takes in a pointer to a struct node sp and an int j
        // and returns a pointer to the node which is j element away from sp (traversing the list)
        struct node* sp = head;
        advance(&sp,id);

        //now the thread can start processing element traversing the linked list
        // from sp = head + id, every thread jumps then to sp += nthreads
        for(int j = 0; j < N; j++){
            if(sp == NULL){break;}
            processwork(sp);
            //increment sp by going nthread element away
            advance(&sp, nthreads);
        }

      
      
   }
   end = omp_get_wtime();

   // traverse the list releasing memory allocated for the list
    p = head;
    while (p != NULL) {
       //printf("%d : %d\n",p->data, p->fibdata);
       temp = p->next;
       free (p);
       p = temp;
    }  
    free (p);
    printf("%f", end - start);
    return 0;
}

