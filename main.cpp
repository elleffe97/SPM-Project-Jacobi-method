#include <iostream>
#include<stdlib.h>
#include <thread>
#include <chrono>
#include<vector>

#include "generation.h"
#include "serialmain.h"
#include "threadmain.h"
#include "measures.h"
#include "fflow.h"

/*
Main function of the project.

	Input:
	- nthread: number of threads
	
	- n: matrix dimension
	
	- N: number of iterations to be performed
	
	It performs the execution of the Jacobi method in several version:
	
	1) Sequential
	
	2) Parallelized with nthread threads
	
	3) Parallelized with Fast Flow parallel_for and nthread workers
	
	4) Parallelized with 1 thread
	
	5) Parallelized with Fast Flow parallel_for and 1 worker
	
	Then the overhead is computed for the parallelization algorithm with nthread threads.
	
	In the end the statistics of Speedup, Scalability and Efficiency are printed for the algorithms.
	
*/

int main(int argc, char * argv[]){
	
	vector<int> arg(3,0);
	arg[0]=atoi(argv[1]);		//number of threads
	arg[1]=atoi(argv[2]);		//matrix dimension
	arg[2]=atoi(argv[3]);		//number of iterations
	
	long tseq;					//variable for sequential time
	long tparn;					//variable for threads time	(nthread>1)
	long tff;					//variable for fast flow time
	long tpar1;					//variable for 1 threads time
	long tff1;					//variable for 1 worker with fast flow
	
	
	cout<<endl<<"Matrix and vector generation"<<endl<<endl;
	
	vector<vector<float>> A(arg[1], vector<float>(arg[1],0));		//main matrix
	vector<float> b(arg[1]);										//main vector
	A=matrixgenf(arg[1]);
	b=bgenf(arg[1]);
	
	
	cout<<"Sequential execution"<<endl<<endl;
	vector<float> xser=serial(arg, A, b, &tseq);			//result of sequential algorithm
	
	cout<<"Threads execution"<<endl<<endl;
	vector<float> xparn=parallel(arg, A, b, &tparn);		//result of parallel algorithm with nthread threads
	
	cout<<"ParallelFor execution"<<endl<<endl;
	vector<float> xff=fflow(arg, A, b, &tff);				//result of parallel algorithm with fast flow
	
	long timeo=Overhead(arg);						//overhead for parallel thread computation
	
	arg[0]=1;
	
	vector<float> xpar1=parallel(arg, A, b, &tpar1);		//result of thread algorithm with 1 thread
	
	vector<float> xff1=fflow(arg, A, b, &tff1);				//result of fast flow algorithm with 1 worker
	
	float SpUppar=speedup(tseq, tparn);						//speedup of the thread algorithm
	float Sclpar=scalability(tpar1, tparn);					//scalability of the thread algorithm
	float Effpar=efficiency(tseq, tparn, atoi(argv[1]));	//efficiency of the thread algorithm
	
	float SpUpff=speedup(tseq, tff);						//speedup of the fastflow algorithm
	float Sclff=scalability(tff1, tff);						//scalability of the fastflow algorithm
	float Effff=efficiency(tseq, tff, atoi(argv[1]));		//efficiency of the fastflow algorithm
	
	cout<<endl<<"Threads statistics:"<<endl<<endl;
	
	cout<< "Speedup = "<< SpUppar<<endl<< "Scalability = "<< Sclpar<<endl<<"Efficiency = "<<Effpar<<endl;
	
	cout<<endl<<"Fast Flow statistics:"<<endl<<endl;
	
	cout<< "Speedup = "<< SpUpff<<endl<< "Scalability = "<< Sclff<<endl<<"Efficiency = "<<Effff<<endl<<endl;
	
	cout<< "Overhead="<< timeo <<endl;
	
	
	
	return (0);
}
	
	
