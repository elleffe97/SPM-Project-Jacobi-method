#include<stdlib.h>
#include<iostream>
#include<vector>

using namespace std;

/*
This file contains the main functions used to generate and print the main matrix A and vector b
*/

vector<vector<float>> matrixgenf(int n);
vector<float> bgenf(int n);

void fprint(vector<vector<float>> M);
void lprint(vector<long> t);



vector<vector<float>> matrixgenf(int n){
	
	vector<vector<float>> M(n, vector<float>(n, 0));
	float sum=0.0;
	
	for (int i=0; i<n; i++){
		sum=0.0;
		for(int j=0; j<n; j++){
			M[i][j]=((float)(rand()%10))/7;
			sum+=M[i][j];
		}
		M[i][i]=((float)2*(sum-M[i][i]));	//strongly diagonal dominant
	}
	return M;
}


void fprint(vector<vector<float>> M){
	for (int i=0; i<M[1].size(); i++){
		for(int j=0; j<M[1].size(); j++)
			cout<<M[i][j]<<"\t";
		cout<<endl;
	}	
}

	
void fprint(vector<float> b){
	for(int i=0; i<b.size(); i++)
		cout<<b[i]<<endl;
}


vector<float> bgenf(int n){
	vector<float> b(n);
	for(int i=0; i<n; i++)
		b[i]=((float)(rand()%10))/7;
	return b;
}

void lprint(vector<long> t){		//time printer
	for(int i=0; i<t.size(); i++)
		cout<<t[i]<<endl;
	return;
}

