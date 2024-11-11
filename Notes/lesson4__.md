# Lesson 4

N.B. OpenMP is a multiprocessing model, an API

How do we define performance in parallel programming?
If we have N independent task on P processing elements, there's still some serial overhead (loading data, consuimg results) -> Ideally, I'd want a speedup which is simply multiplicative, simply lienar

See the definition for Speedip S(P), 
So if S = P, then its simply multiplicative, lineare (P the number of processors). Very important concept: if
$$
T_{P}(P) = (serial\_fraction + \frac{parallel\_fraction}{P})*Time_{seq}
$$
Basically you can show that the maximum speedup i $1 /\alpha$, where $\alpha$ is the serial fraction of your program, independently of $P$. Whats the take home message? Well, there's an asymptotic limit. No need to go with huge number of threads. 


On padding. The first method is working but is not readable, so it is not ok (rot thing to do)

## Synchronization
The threads are always concurrent. They are unordered. You need to make sure that everthinh still works: when having shared data, you need to put a synchro mechanism. A lot of options of synchro: we'll talk about the easiests,

### Critical
Basically a principle of mutual exclusion ( or critical section/critical region). One thread doing it, if other threads tries to do it, they will get blocked essentially. Slide 49. 'float' is outside parallel scope (SPMD is the name of this style). When finished the big_SPMD_job, I call a function that will modify stuff and update the result. SO i want to be sure that only one thread at a time does that. That adds a lot of overhead (but still, is it contended? = lots of threads try to access the critical region at thr same time. If function B takes a lot of time and ctitical function doesnt, then less probability that two threads simulataneosly invokes critical function). Still, try to make the critical section as small as possible

### Barrier:
All of the threads have to arrive at this breakpoint for the program to keep running (slide 50: name of the pattern SPMD) and execute, for example in slide 50, the functions 'really_big_and_ugly'


## Omp for
Basically every compiler converts to omp pragma for directive into a omp pragma parallel directive as the one written in slide 58. But doing the omp for, you lose control of the thread division and let the compiler do whatever it wants to do

N.B OpenMP will make the for index (i) a private index for every thread, so no risk of race condition! Just a single copy of i for each thread. But this does not apply for j, for example. For j, it is better to declare and define. I could have not declared j outside the for paraller lopp, otherwise I would have encounterd a race condition
 
## Reduction (slide 61)
reduction(operator:) syntax -> create a local copy of each variable in the list f0r each thread. Those copies will mask the original variables. It will initianalize them as the identity for that specific operator. There's an implied barrier at the end of the loop, theyre getting recombined 



## Load balancing
Ideally, every single thread should have the same quantity of load, of work

The optimal choice is to overdecompose. Chanches are I'll deliver the work in a statistical way that really balance the load

There's a collection of clauses that'll do those stuff for me (static or dynamic). The default of static is one chunk per thread. Think about why is chunk size one a bad idea

## Nowait clause

At the end of a for loop, it is always implied a barrier (the default behaviour has to be safe). But sometimes theres no reason to put a barrier at the end of a for loop. Skippable by means of nowait (see slide 76, for example) 