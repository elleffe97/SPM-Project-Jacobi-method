# SPM-Project-Jacobi-method
Implementation of Jacobi method using `C++` threads and Fast Flow
library. 

## The method ##
The Jacobi method is an iterative way to solve linear systems such as
$Ax=b$. In each $k + 1$ iteration an $x^{k+1}$ is produced with the closed
formula:

$$x_i^{k+1} = { {1 \over {A_{i i}}} b_i \sum_{j=1, j \ne i}^n { A_{i j} x_j^k } }$$

The only hypothesis required for the convergence of the method regards
the matrix $A$ that must be *row strictly diagonal dominant*. 

## How to use it? ##
To run the code you need to download and install the Fast Flow library
at https://github.com/fastflow/fastflow. \
Then, to compile you must use a compiler which supports `C++` (because of the
`Barrier` objects).\
The compilation must contains the flags:

-   `-pthread`

-   `-O3`

-   `-std=c++20`

-   `- ../fastflow/`

<<<<<<< Updated upstream
-   `-I`

So, using `g++`: `g++ -std=c++20 -O3 -I ../fastflow/ -pthread main.cpp -o main`
=======
So, using `g++`: `g++ -C++20 -pthread -O3 main.cpp -o main` insert
fastflow flag\
>>>>>>> Stashed changes
Then you just need to execute it, to do that you need to give in input:

-   number of threads: integer $> = 1$ (default $4$ )

-   system size: integer $> 1$ (default $1000$ )

-   number of iterations: integer $> 1$ (default $500$ )

So, an example of execution is: `.\main 5 5000 500 `\
\
The program will print on screen the execution time of the serial
algorithm, of the parallel algorithm with both 1 and the given number of
C++ threads and of the FastFlow `parallel_for` approach again for both 1
and given number of threads. Then, all the statistics of SpeedUp,
Efficiency and Scalability are printed. 

In the end it will be asked if you want the print of the computed vector
$X$ together with the real number of
iterations computed due to the stopping condition (fixed at
$10^{-11}$) and you answer could be only 'Y' or 'N'.\
\
Here you can find the [report](Report_Jacobi.pdf) of the entire project with all the
considerations and the numerical experiments.
