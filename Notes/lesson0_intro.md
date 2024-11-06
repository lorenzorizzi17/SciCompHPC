# Lesson 1 (28/10)

### Introduction:
Logistic stuff: no textbook
Grades: 40% on the participation (doing exercise, being there, ...). 60 % is actually a project (that may fail so on't worry about). Pick a theme that you like from the course syllabus/what weve done in the class.  Ok for individual work, presentation up to 10 min. 

OpenMP is the most known model of parallel computing (still running on the CPU, though). We'll move on to the GPU and then cloud computing, massive supercomputers

### Scientific computing
Kind at the crossover of science, math and computing. Theory of third pillar of the foundation of science? 
Claim: AI is not actual science since it is not explainable. It might be a nice tool though. Ai doesn't give insights about the physical world; it just finds patterns and fills in "blanks". It gives answers, not explaination

See the slide on the Master Algorithm, the conceptual classification between ML approaches

(See this list to find a cool subject for the final exam)
- Dense linear algebra: For ex, find $: Ax = b$. There exist a set of fundamental blocks that should be wired to the hardware called BLAS, kinda like an API I guess. A set of routines that can factorize every algebra problem (and then performa a separation of concern: high levele and low level, the latter optimized). Densa: I have to treat all of the elements
- Sparse lineare algebra: also linear algebra, but this time most of the matrix elements are null (>90%) (like an adjacent matrix in a graph: the world is sparse! ) \[flops = floating point operation, FLOPS = /per second \]. 
- Spectral methods: given a differential equation. Basically it concerns the decomposition of complex functions into basis functions to easily solve a differential equation and turn it into an algebraic problem (e.g.: Fourier transform (which basically decomposes on a exp basis, buy you can also use a Laguerre pol basis, ...)). FT is a typical algo in this class (or Fast FT, FFT)
- N-body methods: A set of agents that interact through a pair-wise force. It parallelize well (but large summation may kinda be a problem... ) (fast multipole method)
- Structured grid: diff equations become difference finite equation (see the example on heat equation: relaxation method, which we'll be parallelizing, the one with the 1d rod in between two thermal sink)
- Unstructured grid: something with nukes. Adaptive mesh refinement
- Monte Carlo methods: all about random sampling. Can be used to integrate functions (with a rate of convergence of $O(\sqrt N)$, or run simulation as a source of sample data (even more: evaluate the value of $\pi$, for example). Still, when going multi-dimensional, MC metheods are the best and can assure great robustness

