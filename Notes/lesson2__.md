# Lesson 2

(starting a little later)
The challange of dealing with lots and lots of core is due to memory (an architecture of memory called NUMA). It can get complicated, memory is sometimes shared (ex L3 cache memory, slide 73)

### The Big idea behind GPU programming
I have three arrays (a,b,c) and I sum them up (this is kind of the Hello world for GPU programming). The simple idea in GPU programming: yout turn the body of the loop into a function with a keywork \__global\__. Then a function called _kernel_ which I guess is cudaMalloc (no, it just allocates memory in GPU memory)
vecAdd <<<  index_space >>> (a,b,c,N)

index_space = (N+255)/256 ->

SIMT = single instruction multiple thread. You take ypur code and make a kernel, you define an index space and organize it into blocks
If you look closely on a GPU, you'll see what there's in slide 78. It consist of banks of muktithreaded SIMD processor. There I have 16 blocks, so I can send 16 blocks of memories. I organize the memory around that architecture

Vectorization