#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
using namespace std;
class ReadingProblem{
public:
	//constructor
	ReadingProblem();

	vector<string> mComments;
	int mLevel;
	vector<string> mTopicsCovered;
	vector<string> mAuthors;
	vector<string> mCreaters;
	vector<string> mLabels;
	//vector<string> mVariables;
	//vector<string> mGenerator;
	//vector<string> mFields;
	//vector<string> mText;
	vector<string> mProblems;
	unsigned int Pro_Number;

	vector<string> Pro_Option;
	vector<int> Pro_OptionNumber;
	vector<int> Pro_AnswerNumber;
	string** mChoices;

	string Pro_Time;
	string Pro_Type;
	vector<string> Pro_Material;
	string Pro_Comments;
	double Pro_Rating;



	//accessory methods
	int parse(string name);
	void write(string name);

private:
	vector<string> split(string s,const char c);
	void parseOption();
	void buildConstructor(ofstream &fout, string cpp_path_name);
	void buildHeader(ofstream &fout);
	void buildGenerator(ofstream &fout, string fullpath);
	void buildMain(ofstream &fout, string fullpath);
	void buildAnswer(ofstream &fout, string fullpath);

	int generateProblem(string name);
};