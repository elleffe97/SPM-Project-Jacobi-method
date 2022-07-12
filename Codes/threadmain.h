
#include <iostream>
#include<stdlib.h>
#include<functional>
#include<mutex>
#include <thread>
#include <chrono>
#include <atomic>
#include<vector>

#include <barrier>

#include "utimer.h"
#include "measures.h"

/*
File of the main funtion of the algorithm for Jacobi method implemented with standar C++ threads. 
It also contains a function for the compiutation of the overhead.
*/

using namespace std;

vector<float> parallel(vector<int> argv, vector<vector<float>> A, vector<float> b, long *time);
long Overhead(vector<int> argv);


vector<float> parallel(vector<int> argv, vector<vector<float>> A, vector<float> b, long *time) {

	int nthread = argv[0]; 
  
	int n=argv[1];

	int N=argv[2];
	
	vector<float> x0(n,0);
	
	vector<float> x1(n,0);
	
	int NrIter=N;
	
	float Norm=0;
	
	vector<float> norm(nthread, 0);		//vector of the partial norms
	
	barrier Barr(nthread, [&](){for(int y=0;y<nthread; y++){			//barrier objec with its labda function 
									Norm+=norm[y];
									norm[y]=0;
									}
								Norm=Norm/((float)(n));
								if(difference(Norm))		//fianl stopping condition
									NrIter=0;
								else{
									NrIter--;
									x0=x1;
									Norm=0;}
								return;});
	
	auto sum=[&](int m, int M, int T)	//lambda function for the vìbody of each thread
	{
		while(NrIter>0){
			for (int h=m; h<M; h++){
				float sum=0;
				for(int j=0; j<h; j++)
					sum+=A[h][j]*x0[j];
				for(int j=h+1; j<b.size(); j++)
					sum+=A[h][j]*x0[j];
				
				x1[h]=(b[h]-sum)/A[h][h];
				
				norm[T]+=abs(x0[h]-x1[h]);		//computation of the partial norm
			}
			Barr.arrive_and_wait();		//call to the Barrier object
		}	
	};
		
			
	thread * t[nthread]; 
	
	int mean;				//Chunks dimension computation:
	
	if (n%nthread==0)
		mean=n/nthread; 
	else
		mean=n/nthread+1;
		
	int M=mean;
	int m=0;
	
	{														//main loop
		utimer threadtime("Elapsed thread time = ", time);
		
		for(int T=0; T<nthread; T++){
			
			t[T] = new thread(sum, m, std::min(M, n), T);
			m=M;
			M=M+mean;	
		}
		
		for(int i=0; i<nthread; i++)
			t[i]->join();
			
	}	
	
	return(x1);
}


long Overhead(vector<int> argv){
	
	int nthread = argv[0]; 
  
	int n=argv[1];

	int N=argv[2];
	
	long time;
	
	auto over=[&](){return;};	//void lambda function for the overhead computation
	
	thread * t[nthread]; 
	
	int mean;				//chunks dimension computation:
	
	if (n%nthread==0)
		mean=n/nthread; 
	else
		mean=n/nthread+1;
		
	int M=mean;
	int m=0;
	
	//main loop
	
	{
		utimer overheadtime("Overhead = ", &time);
		
		for(int T=0; T<nthread; T++){
			
			t[T] = new thread(over);
			m=M;
			M=M+mean;	
		}
		
		for(int i=0; i<nthread; i++)
			t[i]->join();
			
	}	
	return (time);
}
	
