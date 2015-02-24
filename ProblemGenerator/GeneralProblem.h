#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
using namespace std;
class GeneralProblem{
public:
	//constructor
	GeneralProblem();

	//accessories
	int parse(string name);
	int generateProblem();

	string name;	//name of the problem to be generated
	string type;	//type of the problem to be generated


	
};