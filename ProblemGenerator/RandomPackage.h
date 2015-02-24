/**********************************************************************************/
/*This package is used to generate random specific integer, array or double number*/
/**********************************************************************************/
#include <string>
using namespace std;
class RandomPackage{

public:
	RandomPackage();

	
	//Generate a random Integer 
	int RandomInt(int max);             //[0,max]
	int RandomInt(int min, int max);	//[min,max]

	//Generate a random Double 
	double RandomDouble(double max);             //[0,max]
	double RandomDouble(double min, double max);             //[0,max]

	//Generate a random Order Array
	int* RandomOrderArray(int n);             //Example[1,0,2,3] when n=4


	//Generate a random Integer Array
	int* RandomIntArray(int max, int n);		//[0,max] with n elements
	int* RandomIntArray(int min, int max, int n);		//[min,max] with n elements


	//Generate a random Double Array
	double* RandomDoubleArray(double max, int n);		//[0,max] with n elements
	double* RandomDoubleArray(double min, double max, int n);		//[min,max] with n elements

	//convert the variable(int,double) to string
	string VarToString(int a);
	string VarToString(double a);

private:

};
