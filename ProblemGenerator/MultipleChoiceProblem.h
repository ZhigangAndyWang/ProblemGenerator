#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
using namespace std;
class MultipleChoiceProblem{
public:
	//constructor
	MultipleChoiceProblem();

	vector<string> mComments;
	int mLevel;
	vector<string> mTopicsCovered;
	vector<string> mAuthors;
	vector<string> mCreaters;
	vector<string> mLabels;
	vector<string> mVariables;
	vector<string> mGenerator;
	vector<string> mFields;
	vector<string> mText;

	string Pro_Option;
	unsigned int Pro_OptionNumber;
	unsigned int Pro_AnswerNumber;
	vector<string> mChoices;

	string Pro_Time;
	string Pro_Type;
	string Pro_Comments;
	double Pro_Rating;



	//accessory methods
	int parse(string name);
	void write(string name);

private:
	vector<string> split(string s,const char c);
	void parseOption(string option);
	void buildConstructor(ofstream &fout, string cpp_path_name);
	void buildHeader(ofstream &fout);
	void buildGenerator(ofstream &fout, string fullpath);
	void buildMain(ofstream &fout, string fullpath);
	int generateProblem(string name);
};