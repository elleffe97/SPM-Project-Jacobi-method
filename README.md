# SPM-Project-Jacobi-method
Implementation of Jacobi method using C++ threads and Fast Flow library.

To run the codes you need to download and install the Fast Flow library at https://github.com/fastflow/fastflow.
Then to compile must use a compiler which supports C++11* (because of the Barrier objects).

The compilation must contains the flags:
-pthread
-o3
-g++20*

So, e.g using g++: g++ -C++20 -pthread -o3 main.cpp -o main

Then you just need to execute it, to do that you need to give in input:
-number of threads: integer >=1 (default 4)
-system size: integer > 1 (default 1000)
-number of iterations: integer >1 (default 500)

So, an example of execution is: .\main 5 5000 500

The program will print on screen the execution time of the serial algorithm,  of the parallel algorithm with both 1 and the given number of C++ threads and of the FastFlow parallel_for approach againg for both 1 and given number of threads.

In the end it will be asked if you want the print of the computed vector $x$ and you answer could be only 'Y' or 'N'.

Here you can find the report of the entire project with all the considerations and the numerical experiments.
