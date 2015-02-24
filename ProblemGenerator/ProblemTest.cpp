#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include "RandomPackage.h"
using namespace std;

string choice[4];

int  main(){
	srand((unsigned)time(0));

	RandomPackage r1;
	cout<< "RandomInt(5)\t" <<r1.RandomInt(5)<<endl;
	return 0;
}
