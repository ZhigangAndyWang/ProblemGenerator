/*********************************************************************************************************
// NAME:        ReadingProblem.cpp
// AUTHOR:      Chang XU, Zhigang WANG
// DIRECTOR:	Dr. ShuaiCheng Li
// DATE:        27 FEB 2013
// PRODUCT:     Problem Class version 1.0
//
// DESCRIPTION: This is the implementation file for the class 
//              Problem.
// 
// CHANGES:		
// 
// NOTES:
//
// COPYRIGHT:  
//
********************************************************************************************************/
#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
//#include <windows.h>
#include <sstream>
#include "ReadingProblem.h"
#include "RandomPackage.h"
#include "TypeDefinition.h"
using namespace std;


//empty constructor
ReadingProblem::ReadingProblem(){

}

int 
	ReadingProblem::parse(string name){
	
	string TxtFileName="../../txtProblem/"+name+".txt";
	ifstream fin(TxtFileName.c_str());

	if(!fin) { 
		cout << "Error-File does not exist or cannot be read\n"; 
		return 1; 
	}
	string mode="";
	char buf[8192];
	//bool reading_problem_text=false;//1
	//string current_text="";

	while(fin.getline(buf,8192)){
		if (buf[0]==0){	//empty line
			continue;
		}
		if(buf[0]=='_'){
			mode=buf;
			continue;
		}
		else if(buf[0]=='#')
		{	string temp=buf;
			temp=temp.substr(1);
			mComments.push_back(buf);
			continue;
		}
		else if(mode=="_TYPE_"){
			Pro_Type=(buf);
		}
		else if(mode=="_LEVEL_")
		{
			mLevel=(long)(buf); 
		} 
		else if(mode==("_COVERAGE_"))//we assume one line per topic
		{
			mTopicsCovered.push_back(buf);
		}
		else if(mode=="_TIME_"){
			Pro_Time=(buf);
		}
		else if(mode=="_AUTHOR_"){
			mAuthors.push_back(buf);
		}
		else if(mode=="_CREATER_"){
			mCreaters.push_back(buf);
		}
		else if(mode=="_LABEL_"){
			mLabels.push_back(buf);
		}
		/*else if(mode==("_VARIABLE_"))
		{	
		mVariables.push_back(buf);
		}
		else if(mode==("_GENERATOR_"))
		{
		mGenerator.push_back(buf);
		}*/
		else if(mode==("_OPTION_"))
		{	
			Pro_Option.push_back(buf);
		}
		else if (mode=="_MATERIAL_")
			Pro_Material.push_back(buf);

		else if (mode=="_COMMENT_")
			Pro_Comments=(buf);
		else if (mode=="_RATING_")
			Pro_Rating=(double)(buf[0]);
		else if(mode==("_PROBLEM_"))
		{	
			Pro_Number=0;
			string pbs=buf;
			unsigned int idx=0;

			while(pbs.size()!=0){
				idx=pbs.find_first_of("$_$");
				if (idx ==pbs.npos){	//cannot find symbol '&'
					break;
				}
				mProblems.push_back(pbs.substr(0,idx));
				Pro_Number++;

				pbs=pbs.substr(idx+3,pbs.size());
			}
		}
	}

	//subsequently dealing with options
	mChoices = new string*[Pro_Option.size()];
	for(unsigned int i=0;i<Pro_Option.size();i++){
		mChoices[i]=new string[10];
	}
	parseOption();
	/************************************************************************/
	/* This place is for updating the database	:)                           */
	/************************************************************************/

	return 0;
}


void
	ReadingProblem::parseOption(){
		for (unsigned int i=0;i<Pro_Option.size();i++)
		{
			string option=Pro_Option[i];
			int ith_ProOption_Number=0;
			int ith_ProAnswer_Number=0;
			int j=0;

			unsigned int idx=option.find("$$");
			unsigned int pos=0;

			string buf0=option.substr(0,idx);
			while(buf0.size()!=0){
				pos=buf0.find_first_of('&');
				if (pos ==buf0.npos){	//cannot find symbol '&'
					mChoices[i][j]=(buf0);
					j++;
					ith_ProOption_Number++;
					ith_ProAnswer_Number++;
					break;
				}
				mChoices[i][j++]=(buf0.substr(0,pos));
				ith_ProOption_Number++;
				ith_ProAnswer_Number++;

				buf0=buf0.substr(pos+1,buf0.size());
			}

			string buf=option.substr(idx+2,option.size());
			while(buf.size()!=0){
				pos=buf.find_first_of('&');
				if (pos ==buf.npos){	//cannot find symbol '&'
					mChoices[i][j++]=(buf);
					ith_ProOption_Number++;
					break;
				}
				mChoices[i][j++]=(buf.substr(0,pos));
				ith_ProOption_Number++;
				buf=buf.substr(pos+1,buf.size());
			}

			Pro_OptionNumber.push_back(ith_ProOption_Number);
			Pro_AnswerNumber.push_back(ith_ProAnswer_Number);
		}
}


void 
	ReadingProblem::write(string name){
		generateProblem(name);
		for(unsigned int  m=0;m<Pro_Option.size();m++)   
			delete[]   mChoices[m];   
		delete[]   mChoices;
}


void 
	ReadingProblem::buildHeader(ofstream &fout){
		fout << "/* The problem is automatically generated. ";	   
	
      int counter=0;  
      
      for(unsigned int i=0; i<mComments.size(); i++)
      {
        string s=(string)mComments[i];
        for(unsigned int j=0; j<s.length(); j++)
        	{
        		if(s[j]=='/') 
					continue;
        		fout << s[j];
        		counter++;
        		if(counter%80==0)
					fout << endl; 
        	}		
      }
      fout << "*/" <<endl;
	  fout << "#include <iostream>" << endl;
	  fout << "#include <fstream>" << endl;
	  fout << "#include <string>" << endl;
	  fout << "#include <time.h>" << endl;
	  fout << "#include <stdlib.h>" << endl;
	  fout << "#include \"/Users/andywang/Documents/csPro/ProblemGenerator/ProblemGenerator/RandomPackage.h\"" << endl;
	  
	  /***************************************************************************************/
	  /* This place is reserved for declaring including some updated head files in the future*/
	  /***************************************************************************************/

	  fout << "using namespace std;"<<endl<<endl;

}

void 
	ReadingProblem::buildConstructor(ofstream &fout,string cpp_path_name){
		fout << "void generate();" <<endl;
		fout << "string getAnswer(int* a,int b,int c);;" <<endl <<endl;
};


void 
	ReadingProblem::buildMain(ofstream &fout, string fullpath){
		fout << "int main(){"<<endl;
		fout << "\t generate();"<<endl;
		fout << "\t return 0;"<<endl;
		fout << "}"<<endl<< endl;
}

vector<string>
	ReadingProblem::split(string s,const char c){
		vector<string> result;
		istringstream ss(s);
		while (!ss.eof())
		{
			string x;               // here's a nice, empty string
			getline(ss, x, c);  // try to read the next field into x
			result.push_back(x);
		}
		return result;
}
void ReadingProblem::buildGenerator(ofstream &fout, string fullpath){
	fout << "void generate(){"<<endl;
	fout << "\t RandomPackage r;"<<endl;
	fout << "\t string choice["<<Pro_Number<<"]["<<10<<"];"<<endl<<endl;
	fout << "\t string answer;"<<endl<<endl;
	TypeDefinition t;

	//Construct the choices
	for(unsigned int i=0;i<Pro_Number;i++){
		for(unsigned int j=0;j<Pro_OptionNumber[i];j++)
		fout<<"\tchoice["<<i<<"]["<<j<<"]=\""<<mChoices[i][j]<<"\";"<<endl;
	}

	fout <<endl;
	fout << "\t int *a_forAnswer;"<<endl;
	fout << "\t //generate problem text "<< endl;
	fout << "\t ofstream p1(\"" << fullpath << "\", ios::out);	"<<endl;
	for(unsigned int i=0;i<Pro_Material.size();i++)
		fout << "\t p1<<\""<<Pro_Material[i]<<"\"<<endl;"<<endl;
	fout<<endl;
	
	for(unsigned int n=0;n<Pro_Number;n++){
		fout << "\t a_forAnswer=r.RandomOrderArray("<<Pro_OptionNumber[n]<<");" <<endl;
		fout<<"\t p1<<\""<<mProblems[n]<<"\"<<endl;"<<endl;
		for(unsigned int i=0;i<Pro_OptionNumber[n];i++){
			char a='A'+i;
			fout <<"\t p1<<\""<<a<<".\"<<choice["<<n<<"][a_forAnswer["<<i<<"]]<<endl;"<<endl;
		}
		fout<<"\t answer+=getAnswer(a_forAnswer,"<<Pro_OptionNumber[n]<<","<<Pro_AnswerNumber[n]<<");"<<endl<<endl;
	}


	fout << "\t p1.close();"<<endl<<endl;

	fout << "\t //generate answer text"<<endl;
	string answer_fullpath=fullpath.insert(fullpath.length()-4,"a"); //construct xxxa.txt
	fout << "\t ofstream p2(\""<< answer_fullpath << "\", ios::out);"<<endl;

	fout << "\t delete[] a_forAnswer;"<<endl<<endl;

	fout << "\t p2<<answer;"<<endl;
	fout << "\t p2.close();"<<endl;
	fout << "}"<<endl;

}

void ReadingProblem::buildAnswer(ofstream &fout, string fullpath){
	fout <<endl<<"string getAnswer(int* a_forAnswer,int a,int b){"<<endl;
	fout << "\t string result;" <<endl;
	fout << "\t for(int i=0;i<a;i++){" <<endl;
	fout << "\t\t if (a_forAnswer[i]>=0 && a_forAnswer[i]<b){" <<endl;
	fout << "\t\t\t result+=('A'+i); " <<endl;
	fout << "\t\t }"<<endl<<"\t }"<<endl;
	fout << "\t result+=\"\\n\";" <<endl;
	fout << "\t return result; " <<endl;
	fout << "}" <<endl;
}
int
	ReadingProblem::generateProblem(string name){
		string cpp_path_name="../../cProblem/"+name+".cpp";
		ifstream fin(cpp_path_name);
		if(fin){
			cout << "Error -This problem's cpp file exists."<<endl;
			return 1;
		}
		fin.close();

		//create the folder if needed
//////		int idx=cpp_path_name.find_last_of('/');
//////		string directory_name=cpp_path_name.substr(0,idx);
//////		while (directory_name[directory_name.length()-1]=='/')
//////		{	directory_name=directory_name.substr(0,directory_name.length()-1);
//////		}
//////		DWORD ftyp = GetFileAttributesA(directory_name.c_str());
//////		if(ftyp & FILE_ATTRIBUTE_DIRECTORY){			//The directory does not exists
//////			if (ftyp == INVALID_FILE_ATTRIBUTES){	
//////				if(CreateDirectory(directory_name.c_str(),NULL))
//////					cout <<directory_name <<" Created!"<<endl;
//////				else
//////					cout <<"ERROR-Create Directory Failed for: " << directory_name <<endl;
//////			}
//////		}

		ofstream fout(cpp_path_name);
		if(!fout){
			cout << "Error -Cannot Write File: " << cpp_path_name <<endl;
			return 1;
		}
		
		
		//string fullPath="D:/Desktop/Year1.B/CS/workplace/temp/"+name+".txt";
		int id2=name.find_last_of('/');
		string fullpath="../../../temp/"+name.substr(id2+1,name.length())+".txt";

		//read in the text file
		buildHeader(fout);

		//build constructors, and other methods in a similar way   
		buildConstructor(fout, cpp_path_name);
		buildMain(fout,fullpath);
		buildGenerator(fout,fullpath);
		buildAnswer(fout,fullpath);

		fout.close();
		return 0;

}
