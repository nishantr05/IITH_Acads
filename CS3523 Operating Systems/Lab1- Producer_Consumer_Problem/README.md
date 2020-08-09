## Solving the Produce Consumer problem

File includes two multi-threaded C programs (without Semaphores and with Semaphores) to solve the Producer-Consumer Problem.
The programs take as cmd args **'p'** (no. of producers), **'c'** (no. of Consumers), **'N'** (Buffer Size).

### Program-1 (no semaphores) can be executed by :
- Compiling the code:  `gcc -pthread ES18BTECH11013_lab1_nosem.c`
- Running the code : `./a.out p c N`

### Program-2 (with semaphores) can be executed by :
- Compiling the code:  `gcc -pthread ES18BTECH11013_lab1_sem.c`
- Running the code : `./a.out p c N`
