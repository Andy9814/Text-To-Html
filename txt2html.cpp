/*
Name :Nripdeep singh
purpose: to convert an txt file to html
Date: july 14, 2017
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<regex>
#include<algorithm>
using namespace std;

// Make a global variables
int noOfBr = 0;
string title;

// function prototype 
string titleHtml(string s);
string txtToHtml(string s);
void putInhtml(istream & in, ostream & out);

int main(int x, char* y[]) {
	// Test the number of args 
	// will through error if argc is < 2 or argc > 4
	if (x < 2 || x > 4) {
		cerr << "Error: Incorrect number of parameters [" << x <<"]"<< endl;
		return EXIT_FAILURE;
	}

	vector<string> v;
	for (auto i = 1; i < x; ++i) {
		v.push_back(y[i]);
	}

	//declare 2 string to store inputfile and outputfile
	string outputfile;
	string inputfile;
	// check there is any .txt file with the help of regex
	regex extension("\\.(txt)$");
	// make a varible infileindex
	unsigned int inFileIndex = 0;
	unsigned int outFileIndex = 0;
	bool inputFound = false;

	for (unsigned i = 0; i < v.size(); ++i) {
		if (regex_search(v[i], extension)) {
			//	cout << "input file is found" << endl;
			inFileIndex = i;
			inputFound = true;
			inputfile = v[i];
			break;
		}
	}

	// if it does not find the .txt file just End the program
	if (inputFound == false) {
		cout <<" ERROR: Input file does not find" << endl;
		return EXIT_FAILURE;
	}

	// Check for .html file. create regex for that
	regex extension1("\\.(html)$");
	for (unsigned i = 0; i < v.size(); ++i)
	{
		if (regex_search(v[i], extension1))
		{
			outFileIndex = i;
			if (inFileIndex < i)
			{
				
				outputfile = v[i];
				break;
			}
			else
			{
				cout << "ERROR: .html file is not in its resepected position" << endl;
				return EXIT_FAILURE;
			}
		}
	}

	//create a ifstream object 
	ifstream infile(inputfile);
	//Test for success
	if (!infile) {
		cerr << "ERROR: Can not open <" << inputfile << "> for input." << endl;

		return EXIT_FAILURE;
	}

	//Create a ofstream object 
	ofstream outfile;
	//To test if user give the outfile name
	if (outputfile == "") {
		outfile.open(txtToHtml(inputfile));
		
		//print erroR mesage
		if (!outfile) {
			cerr << "ERROR: Can not open <" << outputfile << "> for output." << endl;
			return EXIT_FAILURE;
		}

	}
	else {
		outfile.open(outputfile);
		if (outfile.fail())
		{
			//print erro mesage
			cerr << "ERROR: Can not open <" << outputfile << "> for output." << endl;
			return EXIT_FAILURE;
		}
	}
	// create a title for the file 
	title = titleHtml(inputfile);
	
	// put the data from input file to output file
	putInhtml(infile, outfile);
	
	
	bool findSwitch = false;
	// check whether we have any "-r"
	vector<string>::iterator it = find(v.begin(), v.end(), "-r");
	if (it != v.end()) {
		findSwitch = true;
		//v.erase(it);

	}
	// close and reopen the input file again
	
	infile.close();
	infile.open(v[inFileIndex]);

	//report if there is any "-r"
	int countLines = 0;
	string s;
	if (findSwitch == true)
	{

		while (getline(infile, s))
		{
			//cout << "Tesz" << endl;
			countLines++;
		}

		cout << "Output paragraphs processed: " << noOfBr << endl;
		cout << "Input lines processed: " << countLines << endl;
	}
}


/*
Method : txtToHtml
purppse: convert the txt file to html file
*/
string txtToHtml(string s) {

	string w = s.substr(0, s.length() - 4);
	return w + ".html";
}
/*
Method : titleHtml
purppse: remove  the txt file in title

*/
string titleHtml(string s) {

	string w = s.substr(0, s.length() - 4);
	return w;
}


/*
Method : putInHtml
purppse: put some needed commands in html file 
         and put the data from input file to output file

*/
void putInhtml(istream & in, ostream & out) {
	out << "<html xmlns = \"http://www.w3.org/1999/xhtml\" xml:lang = \"en\">" << endl
		<< "<head>" << endl
		<< "<meta http - equiv = \"Content-Type\" content = \"text/html; charset=UTF-8\" / >" << endl
		<< "<title>" << title << "</title>" << endl
		<< "</head>" << endl
		<< "<body>" << endl;

	char ch;

	vector<char> v;
	while (in.get(ch))
	{
		v.push_back(ch);
	}
	for (unsigned i = 0; i < v.size() - 1; ++i)
	{
		// checks if there is two '\n ' frequently
		if ((v[i] == '\n') && (v[i + 1] == '\n'))
		{

			out << "\n<br />";
			noOfBr++;

		}
		else {

			out << v[i];
		}

	}
}
