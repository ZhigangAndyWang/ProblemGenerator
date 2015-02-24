/*********************************************************************************************************
// NAME:        ReadingGenerator.cpp
// AUTHOR:      Chang XU, Zhigang WANG
// DIRECTOR:	Dr. ShuaiCheng Li
// DATE:        5 Feb 2013
// PRODUCT:     ReadingGenerator version 1.0
//
// DESCRIPTION: This is the file to generate reading problems
// 
// CHANGES:		
// 
// NOTES:
//
// COPYRIGHT:  
//
********************************************************************************************************/
#include <iostream>
#include <string>
//#include <windows.h>
#include <fstream>
#include "stdio.h"
#include "stdlib.h"
#include "ReadingGenerator.h"
#include "ReadingProblem.h"
using namespace std;

//empty constructor
ReadingGenerator::ReadingGenerator(){

}

int
	ReadingGenerator::generateProblem(string name){

		ReadingProblem p;
		//parse the text file and convert it into cpp file
		p.parse(name);
		p.write(name);
		return 0;
}
