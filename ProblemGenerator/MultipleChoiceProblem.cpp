/*********************************************************************************************************
// NAME:        MultipleChoiceProblem.cpp
// AUTHOR:      Chang XU, Zhigang WANG
// DIRECTOR:	Dr. ShuaiCheng Li
// DATE:        27 JAN 2013
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
#include "MultipleChoiceProblem.h"
#include "RandomPackage.h"
#include "TypeDefinition.h"
using namespace std;


//empty constructor
MultipleChoiceProblem::MultipleChoiceProblem(){

}

int 
	MultipleChoiceProblem::parse(string name){
	
	string TxtFileName="../../txtProblem/"+name+".txt";
	ifstream fin(TxtFileName.c_str());

	if(!fin) { 
		cout << "Error-File does not exist or cannot be read\n"; 
		return 1; 
	}
	string mode="";
	char buf[1024];
	bool reading_problem_text=false;//1
	string current_text="";

	while(fin.getline(buf,1024)){
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
			mLevel=atoi(buf); 
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
		else if(mode==("_VARIABLE_"))
		{
			mVariables.push_back(buf);
		}
		else if(mode==("_GENERATOR_"))
		{
			mGenerator.push_back(buf);
		}
		else if(mode==("_OPTION_"))
		{
			Pro_Option=(buf);
			parseOption(Pro_Option);
		}

		else if (mode=="_COMMENT_")
			Pro_Comments=(buf);
		else if (mode=="_RATING_")
			Pro_Rating=(double)(buf[0]);


		else if(mode==("_PROBLEM_"))
		{	int counter=0;

			for(int i=0;buf[i]!=0; i++)
			{	
				if(buf[i]=='$' && (i==0 || buf[i-1]!='\\'))
				{	counter=(counter+1) % 2;
					if (counter==1){
						reading_problem_text=true;
					}
					else {
						reading_problem_text=false;
					}

					if(reading_problem_text)
					{
						mText.push_back(current_text);
					}
					else
					{
						mFields.push_back(current_text);
					}
					current_text="";
					continue;	   
				}	
				else if((buf[i]=='\\' )&& (i==0 || buf[i-1]!='\\'))
				{
					continue;
				}
				current_text+=buf[i];
			}
		}

		if(mode==("_PROBLEM_"))
		{
			if(reading_problem_text)
			{
				mFields.push_back(current_text);
			}
			else
			{
				mText.push_back(current_text);
			} 	
		}
	}
	/************************************************************************/
	/* This place is for updating the database	:)                           */
	/************************************************************************/

	return 0;
}


void 
	MultipleChoiceProblem::parseOption(string option){
		Pro_OptionNumber=0;
		Pro_AnswerNumber=0;

		unsigned int idx=option.find("$$");
		unsigned int pos=0;
		
		string buf0=option.substr(0,idx);
		while(buf0.size()!=0){
			pos=buf0.find_first_of('&');
			if (pos ==buf0.npos){	//cannot find symbol '&'
				mChoices.push_back(buf0);
				Pro_OptionNumber++;
				Pro_AnswerNumber++;
				break;
			}
			mChoices.push_back(buf0.substr(0,pos));
			Pro_OptionNumber++;
			Pro_AnswerNumber++;
			
			buf0=buf0.substr(pos+1,buf0.size());
		}

		string buf=option.substr(idx+2,option.size());
		while(buf.size()!=0){
			pos=buf.find_first_of('&');
			if (pos ==buf.npos){	//cannot find symbol '&'
				mChoices.push_back(buf);
				Pro_OptionNumber++;
				break;
			}
			mChoices.push_back(buf.substr(0,pos));
			Pro_OptionNumber++;
			buf=buf.substr(pos+1,buf.size());
		}
}


void 
	MultipleChoiceProblem::write(string name){
		generateProblem(name);
}


void 
	MultipleChoiceProblem::buildHeader(ofstream &fout){
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
	MultipleChoiceProblem::buildConstructor(ofstream &fout,string cpp_path_name){
		fout << "void generate();" <<endl <<endl;
};


void 
	MultipleChoiceProblem::buildMain(ofstream &fout, string fullpath){
		fout << "int main(){"<<endl;
		fout << "\t generate();"<<endl;
		fout << "\t return 0;"<<endl;
		fout << "}"<<endl<< endl;
}

vector<string>
	MultipleChoiceProblem::split(string s,const char c){
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
void MultipleChoiceProblem::buildGenerator(ofstream &fout, string fullpath){
	fout << "void generate(){"<<endl;
	fout << "\t RandomPackage r;"<<endl;
	fout << "\t string choice["<<Pro_OptionNumber<<"];"<<endl<<endl;
	
	TypeDefinition t;

	//declare Variables
	for (unsigned int i=0;i<mVariables.size();i++){
		string temp = mVariables[i];
		int index   = temp.find_first_of(" ");
		fout<<("\t"+t.type(temp.substr(0,index))+" "+temp.substr(index+1))<<endl;
	}
	fout<<endl;
	
	//input the content of mGenerator
	for(unsigned int i=0; i<mGenerator.size(); i++)
	{
		string v=mGenerator[i];
		fout<<"\t "<<v<<endl;
	}
	fout<<endl;

	//Construct the choices
	for(unsigned int i=0;i<mChoices.size();i++){
		fout<<"\tchoice["<<i<<"]=";

		vector<string> temp= split(mChoices[i],'$'); // Create vector to hold our words
		string buf="";
		for(unsigned int i=0;i<temp.size();i++){
			if(temp[i].length()==0)
				continue;
			if(temp[i].find_first_not_of(" ")==-1)
				continue;
			if(i!=0)
				buf+="+";
			if(!i&1){	//i is an even number,temp[i] stores text 
				buf+="\""+temp[i]+"\"";
			}
			else	//i is an odd number,temp[i] stores fields 
			{	
					buf+="r.VarToString("+temp[i]+")";			
			}
		}
		buf+=";";
		fout<<buf<<endl;
	}

	fout <<endl;
	fout << "\t int *a_forAnswer=r.RandomOrderArray("<<Pro_OptionNumber<<");" <<endl;
	fout << "\t //generate problem text "<< endl;
	fout << "\t ofstream p1(\"" << fullpath << "\", ios::out);	"<<endl;

	string question="\t p1";
	for(unsigned int i=0; i<mText.size(); i++)
	{
		question+=("<<\" "+mText[i]+" \"");
		if(i<mFields.size())
		{	
			string variable=mFields[i];
			question+=("<<"+mFields[i]);
		} 	
	}
	question+="<<endl;";
	fout<<question<<endl;
	/*
	for(unsigned int i=0; i<mFields.size();i++){
	cout <<"Fields "<<i<<": "<< mFields[i]<<endl;
	}
	for(unsigned int i=0; i<mText.size();i++){
	cout <<"Text "<<i<<": "<< mText[i]<<endl;
	}*/
	
	for(unsigned int i=0;i<Pro_OptionNumber;i++){
		char a='A'+i;
		fout <<"\t p1<<\""<<a<<".\"<<choice[a_forAnswer["<<i<<"]]<<endl;"<<endl;
	}
	fout << "\t p1.close();"<<endl<<endl;

	fout << "\t //generate answer text"<<endl;
	string answer_fullpath=fullpath.insert(fullpath.length()-4,"a"); //construct xxxa.txt
	fout << "\t ofstream p2(\""<< answer_fullpath << "\", ios::out);"<<endl;
	fout << "\t string answer;"<<endl;
	fout << "\t char c_forAnswer=\'A\';"<<endl;


	fout << "\t for(int i=0;i<"<<Pro_OptionNumber<<";i++){"<<endl;
	fout << "\t\t if (a_forAnswer[i]>=0 && a_forAnswer[i]<"<<(Pro_AnswerNumber)<<"){"<<endl;
	fout << "\t\t\t answer+=(c_forAnswer+i);"<<endl;
	fout << "\t\t }\n\t}"<<endl;
	fout << "\t delete[] a_forAnswer;"<<endl<<endl;


	fout << "\t p2<<answer;"<<endl;
	fout << "\t p2.close();"<<endl;
	fout << "}"<<endl;

}


int
	MultipleChoiceProblem::generateProblem(string name){
		string cpp_path_name="../../cProblem/"+name+".cpp";
		ifstream fin(cpp_path_name.c_str());
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

		ofstream fout(cpp_path_name.c_str());
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

		fout.close();
		return 0;

}
