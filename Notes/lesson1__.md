# Lesson 1 (4/11)

Being N agents, you might expect the speedup to be exactly N. But something can go wrong.
There are extra things you should look for when going parallel For example,
1) Load balancing: assuring every agent has a balanced task's load (your algo has finished when every agent has finished)
2) Contention: how to access efficiently a shared resource
3) Parallel overheard: A time/memory overhead that did not exist when going serial (coordination, ...)
4) Problem decomposition is a hard task (you need to be sure every chunh is independent). There is almost always a little bit of task that cannot be done parallel (_serial fraction_)


## Von Neumann architecture
Scientific computing is all about _visible computers_. Python (and virtual-machine operated language) acts as a very abstract language and hides away the detail of implementationn of the underlying hardware. But we want to work near the performance edge of hardware, we want to push the boundaries of performance, therefore we need to make the computer visible, we need to include the hardware in our thinking. 


- ISA (instruction set architecture): the interface to the hardware presented to a programmer
There can be two family of ISA: CISC (intel, e.g: special versions of operator, sometimes over 3500 instructions...) and RISC (ARM, you only operate on register, not on memory! So u dropped some instructions. Easier to implement, but less powerfull. Still, they are smaller (around 350 instructions.))
See the slide on assembly in godbolt
