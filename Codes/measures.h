#pragma once
#include<stdlib.h>
#include<cmath>

/*
This file contains the functions used to compute the statistics of the methods and to evaluate the stopping condition
*/

double epsilon=1e-11;		//tolerance for the stopping contition

bool difference(vector<float> x0, vector<float> x1);
float speedup(long tseq, long tpar);
float efficiency(long tseq, long tpar, int n);
float scalability(long tpar1, long tparn);

float speedup(long tseq, long tpar){		//Speedup
	return ((float)(tseq)/tpar);
}

float efficiency(long tseq, long tpar, int n){		//Efficiency
	return ((float)(tseq)/(n *tpar));
}

float scalability(long tpar1, long tparn){		//Scalability
	return ((float)(tpar1)/tparn);
}

bool difference(vector<float> x0, vector<float> x1){		//to determine if the stopping condition holds this function compute the norm 1 of the 
	float norm=0;											// vectors x0 and x1 (the solution vector x in two consecutive iteration) doing a 
	for(int i=0; i<x0.size(); i++)							//for loop on all their components
		norm+=std::abs(x0[i]-x1[i]);
	norm=norm/(float(x0.size()));
	if (norm<=epsilon)
		return true;
	else
		return false;
}

bool difference(float norm){								//This version of the function difference simply compares two float values
	if (norm<=epsilon)
		return true;
	else
		return false;
}
	