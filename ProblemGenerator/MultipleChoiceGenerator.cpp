/*********************************************************************************************************
// NAME:        MultipleChoiceGenerator.cpp
// AUTHOR:      Chang XU, Zhigang WANG
// DIRECTOR:	Dr. ShuaiCheng Li
// DATE:        5 Feb 2013
// PRODUCT:     MultipleChoice1Generator version 1.0
//
// DESCRIPTION: This is the file to generate multiple choice problems
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
#include "MultipleChoiceGenerator.h"
#include "MultipleChoiceProblem.h"
using namespace std;

//empty constructor
MultipleChoiceGenerator::MultipleChoiceGenerator(){

}

int
	MultipleChoiceGenerator::generateProblem(string name){

		MultipleChoiceProblem p;
		//parse the text file and convert it into cpp file
		p.parse(name);
		p.write(name);
		return 0;

}
