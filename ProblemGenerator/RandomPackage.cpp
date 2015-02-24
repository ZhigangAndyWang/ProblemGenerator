#include "RandomPackage.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

//empty constructor
RandomPackage::RandomPackage(){
	srand((unsigned)time(0));
}


//Generate a random Integer 
int
	RandomPackage::RandomInt(int max){
		int a=rand();
		a=a%(max+1);
		return a;
}

//Generate a random Integer
int
	RandomPackage::RandomInt(int min, int max){
		int a=rand();
		a=min+a%(max-min+1);
		return a;
}

//Generate a random Double
double
	RandomPackage::RandomDouble(double max){
		double a=(double)rand()/RAND_MAX;
		a=a*max;
		return a;
}
//Generate a random Double
double
	RandomPackage::RandomDouble(double min,double max){
		double a=(double)rand()/RAND_MAX;
		a=a*(max-min)+min;
		return a;
}


//Generate a random Order Array 
int* 
	RandomPackage::RandomOrderArray(int n){		
		int *array1= new int[n];
		for(int i=0;i<n;i++){
			array1[i]=i;
		}
		 for (int i=n-1;i>0;i--)
		 {
			int idx = rand()%i;
			//if (idx == i) continue;
			int tmp=array1[idx];
			array1[idx] = array1[i];
			array1[i] = tmp;
		 }
		return array1;
}


//Generate a random Integer Array [0,max] with n elements
int* 
	RandomPackage::RandomIntArray(int max, int n){		
		int *array1= new int[n];
		for(int i=0;i<n;i++){
			array1[i]=RandomInt(max);
		}
		return array1;
}


//Generate a random Integer Array [min,max] with n elements
int* 
	RandomPackage::RandomIntArray(int min, int max, int n){		
		int *array1= new int[n];
		for(int i=0;i<n;i++){
			array1[i]=RandomInt(min,max);
		}
		return array1;
}

//Generate a random Integer Array [0,max] with n elements
double* 
	RandomPackage::RandomDoubleArray(double max, int n){		
		double *array1= new double[n];
		for(int i=0;i<n;i++){
			array1[i]=RandomDouble(max);
		}
		return array1;
}


//Generate a random Integer Array [min,max] with n elements
double* 
	RandomPackage::RandomDoubleArray(double min, double max, int n){		
		double *array1= new double[n];
		for(int i=0;i<n;i++){
			array1[i]=RandomDouble(min,max);
		}
		return array1;
}

string
	RandomPackage::VarToString(int a){
	char buf[30];
	sprintf(buf, "%d",a);
	return buf;
}

string
	RandomPackage::VarToString(double a){
	char buf[30];
	sprintf(buf, "%f",a);
	return buf;
}
