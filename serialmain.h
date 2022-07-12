#include<stdlib.h>
#include<iostream>
#include<vector>

#include "utimer.h"
#include "measures.h"


using namespace std;

/*
File of the main function of the sequential implementation of the Jacobi method
*/

vector<float> serial(vector<int> argv, vector<vector<float>> A, vector<float> b, long * time);

vector<float> serial(vector<int> argv, vector<vector<float>> A, vector<float> b, long * time){
	
	int n=argv[1];
	
	int N=argv[2];
		
	vector<float> x0(n,0);
	vector<float> x1(n,0);
	
	{
		utimer seq("Elapsed sequencial time = ", time);
		
		for(int k=0; k<N; k++){
			for (int i=0; i<n; i++){
				float sum=0;
				for(int j=0; j<i; j++)
					sum+=A[i][j]*x0[j];
				for(int j=i+1; j<n; j++)
					sum+=A[i][j]*x0[j];
				
				x1[i]=(b[i]-sum)/A[i][i];
			}
			if(difference(x0, x1))			//stopping condition
				break;
			else
				x0=x1;
		}
	}
	
	return(x1);
}
		

