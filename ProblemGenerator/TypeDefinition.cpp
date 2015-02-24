#include <iostream>
#include "TypeDefinition.h"
#include <string>
using namespace std;

//empty constructor
TypeDefinition::TypeDefinition(){

};

string
	TypeDefinition::type(string name){

		if (name=="integer"){
			return "int";
		}
		else if (name=="double"){
			return "double";
		}
		else if (name=="string"){
			return "string";
		}
		else if (name=="char"){
			return "char";
		}
		else if (name=="integerArray"){
			return "integer*";
		}
		else if (name=="stringArray"){
			return "string*";
		}
		else if (name=="doubleArray"){
			return "double*";
		}
		//else if (name=="DGraph"){
		//	return "DGraph";
		//}
		//else if (name=="UDGraph"){
		//	return "UDGraph";
		//}

		/************************************************************************/
		/* This place is reserved for updating the Type used	:)              */
		/************************************************************************/
		else {
			return "Object";
		}
};


