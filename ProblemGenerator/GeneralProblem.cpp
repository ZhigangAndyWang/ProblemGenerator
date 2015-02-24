/*********************************************************************************************************
// NAME:        GeneralProblem.cpp
// AUTHOR:      Chang XU, Zhigang WANG
// DIRECTOR:	Dr. ShuaiCheng Li
// DATE:        4 Feb 2013
// PRODUCT:     Problem Class version 1.0
//
// DESCRIPTION: This is the implementation file for the class 
//              GeneralProblem.
// 
// CHANGES:		
// 
// NOTES:
//
// COPYRIGHT:  
//
********************************************************************************************************/
#include "GeneralProblem.h"
#include <string>
#include <iostream>
#include <fstream> 
//#include <windows.h>
#include "MultipleChoiceGenerator.h"
#include "ReadingGenerator.h"
using namespace std;

//empty constructor
GeneralProblem::GeneralProblem(){

}

//initiate the general problem and set its name and type
int
GeneralProblem::parse(string name1){
	string txtFileName="../../txtProblem/"+name1+".txt";
	ifstream fin(txtFileName.c_str());

	if(!fin) { 
		cout << "Error-File does not exist or cannot be read\n"; 
		return 1; 
	}
	string mode="";
	char buf[1024];

	while(fin.getline(buf,1024)){
		if(buf[0]=='_'){
			mode=buf;
		}
		if(mode=="_TYPE_"){
			fin.getline(buf,1024);
			type=(buf);
			break;
		}
	}
	name=name1;
	return 0;
		
}

//generate the specific problem using the specific type generator
int
GeneralProblem::generateProblem(){
	if (type=="MultipleChoice"){
		MultipleChoiceGenerator mc;
		return mc.generateProblem(name);
	}
	else if (type=="Reading"){
		ReadingGenerator rc;
		return rc.generateProblem(name);
	}

	return 0;
		


}

