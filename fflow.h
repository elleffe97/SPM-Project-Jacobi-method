#include<stdlib.h>
#include<iostream>
#include<vector>
#include <ff/parallel_for.hpp>

#include "utimer.h"
#include "measures.h"

/*
File of the main function for the computation of Jacobi method using a parallelization based on fast flow parallel_for
*/


using namespace std;

vector<float> fflow(vector<int> argv, vector<vector<float>> A, vector<float> b, long * time);

vector<float> fflow(vector<int> argv, vector<vector<float>> A, vector<float> b, long * time){
	
	int nthread=argv[0];
	
	int n=argv[1];
	
	int N=argv[2];
		
	vector<float> x0(n,0);
	vector<float> x1(n,0);
	
	ff::ParallelFor pf(nthread);			//declaration of a ParalleFor object with nthread workers
	
	{
		utimer ff("Elapsed parallel_for time = ", time);	// start of time computing
		
		for(int k=0; k<N; k++){

			pf.parallel_for(0, n, 1, 0, [&](const long i){
				float sum=0;
				for(int j=0; j<i; j++)
					sum+=A[i][j]*x0[j];
				for(int j=i+1; j<b.size(); j++)
					sum+=A[i][j]*x0[j];
				
				x1[i]=(b[i]-sum)/A[i][i];				//update x1(i)
				
				}, 
				nthread);
			if(difference(x0, x1))					//stopping condition
				break;
			else
				x0=x1;
		}
	}
	
	return(x1);
}
		

