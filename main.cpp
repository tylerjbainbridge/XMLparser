/*
* Tyler Bainbridge
* UMass Lowell
* Tyler_Bainbridge@student.uml.edu
* Assignment 3
* (c) UMass Lowell 2015
* created 9/8/15
* last edited 9/25/15 at 11PM
*/
#include "element.h"

using namespace std;

string getOpen(string line); //get the name of the opening tag
string getClosed(string line); //get the name of the closing tag

void parseFile(string fileName); //the workhorse of the program, orgranizes all the utilities to complete the task

void printOpenElement(element tag); //prints the info on an opening tag
void printClosedElement(element tag); //prints the info on a closing tag
void printCompleteElement(string line, int lineNumber); //print the complete tag
void printStack(stack<element> songstack); //prints the contents of the stack without modifying the original

int main(int argc, char** argv) {

	parseFile("test.xml"); //goes through the file and parses each line

	cout << "Done." << endl;
	return 0;
}

void parseFile(string fileName)
{
	ifstream inFile(fileName.c_str()); //setting the filename
	string line, finalTag, initialTag; //strings for different stages of the parsing stages
	element* tag; //element pointer for creating new elements
	stack<element> songstack; //stack for opening tags
	int startPos, endPos,lineNumber=1;

	while(getline(inFile, line))
	{
		if(line.at(0)=='<' && line.at(1)=='?')
		{
			cout << lineNumber << "    " << getOpen(line) << " is an attribute, not an open tag." << endl; 
		}

		if(line.find("<!--")!=string::npos) //looking comments
		{
			cout<< lineNumber <<"    Starting comment: " << line << endl; //shows the first part of the comment
			lineNumber++; 
			getline(inFile, line); //gets next line
			while(line.find("-->")==string::npos) //searching for the end of the comment
			{
				lineNumber++;
				cout << lineNumber << "    Comment: " << line << endl;
				getline(inFile, line); //gets next line
			}
			cout<< lineNumber << "    Ending comment: " << line << endl<<endl;
			getline(inFile, line); //gets next line
			lineNumber++; //counts the line again
		}
		if(line.at((line.find("<"))+1)!='/') //if it is not a closing tag, then proceed to see if its closed inline
		{
			int backSlash = line.find('/'); //checks if there is a slash to then see if it is a closing tag
			if(backSlash!= string::npos&&line.at(backSlash-1)=='<') //checking for complete elements
			{
				printCompleteElement(line, lineNumber); //prints the full line, and the content between tags
			}
		}

		if(line.at((line.find("<"))+1)!='/'&&!ispunct(line.at((line.find("<"))+1))&&line.at((line.find(">"))-1)!='/') //if the character proceeding the opening bracket is not a backslash or punct (to get rid of closing tags and other tags) and there is no slash before the closing tags(self closing)
		{
			tag = new element(getOpen(line), lineNumber); //creates a new Element with the line number and tagName
			int backSlash = line.find('/'); //checks if there is a slash to then see if it is a closing tag

			if(backSlash!= string::npos&&line.at(backSlash-1)!='<') //safeguard for tags that have forward slashes but are not for closing tags
			{
				songstack.push(*tag); //pushes the tag onto the stack
				printOpenElement(songstack.top()); //prints the tag's info
				printStack(songstack); //displayes the stack's contents
			}

			if(backSlash == string::npos)//if there is no slash aka it is an open tag
			{
				songstack.push(*tag); //pushes the tag onto the stack
				printOpenElement(songstack.top()); //prints the tag's info
				printStack(songstack); //displays the stack's contents
			}

			//song.push_back(*tag); //adds onto a vector
		}else if(line.at((line.find("<"))+1)!='/'&&ispunct(line.at((line.find("<"))+1))) //xml
		{

		}else if(line.at((line.find("<"))+1)!='/'&&!ispunct(line.at((line.find("<"))+1))&&line.at((line.find(">"))-1)=='/') //self closing tags
		{
			cout << lineNumber << "   " << getOpen(line) << " is a self closing tag, not adding to stack. " << endl;
		}

		if(line.at((line.find("<"))+1)=='/') //if the character proceeding the opening bracket is a backslash (to find closing tags)
		{
			tag = new element(getClosed(line), lineNumber); //creates a new Element with the line number and tagName

			if(songstack.top().getName() ==  tag->getName()){
				//checks if the top of the stack is equal to the closing tag found first
				printClosedElement(*tag); //prints info
				songstack.pop(); //pops the stack
				printStack(songstack); //displayes the stack's contents
			}
		}
		lineNumber++; //counting lines
	}
}

void printOpenElement(element tag)
{
	int nameWidth = 30; //width of the name
	int numWidth = 5; //width of the number
	char separator = ' '; //using the i/o manipulation library adding spaces to fill the rest of the width

	cout << left << setw(numWidth) << setfill(separator) <<  tag.getlineNum(); //line number
	cout << left << setw(nameWidth) << setfill(separator) << "Opened Element: "+tag.getName()<< endl; //prints the element opened
}

void printClosedElement(element tag)
{
	int nameWidth = 30; //width of the name
	int numWidth = 5; //width of the number
	char separator = ' '; //using the i/o manipulation library adding spaces to fill the rest of the width

	cout << left << setw(numWidth) << setfill(separator) <<  tag.getlineNum(); //line number
	cout << left << setw(nameWidth) << setfill(separator) << "Closed Element: "+tag.getName()<< endl; //prints the element closed
	cout << endl;
}

void printCompleteElement(string line, int lineNumber)
{
	int nameWidth = 30; //width of the name
	int numWidth = 5; //width of the number
	int startPos, endPos; //start and end pos for substr
	string fullLine; //for the full line without XML indentation
	string elementContent; //for what is between the tags

	char separator = ' '; //using the i/o manipulation library adding spaces to fill the rest of the width

	startPos = line.find("<");
	endPos = line.find("/n ",startPos+1); //getting the full line without spacing from XML
	fullLine = line.substr(startPos, (endPos - startPos) - 1); //getting the line with no spacing

	startPos = line.find(">"); 
	endPos = line.find("<",startPos+1); //getthing what's between the tags aka Content
	elementContent = line.substr(startPos+1, (endPos - startPos) - 1); //getting content

	cout << left << setw(numWidth) << setfill(separator) <<  lineNumber; //prints the name
	cout << left << setw(nameWidth) << setfill(separator) << "Complete Element: "+fullLine<< endl; //prints the complete line
	cout << left << setw(numWidth) << setfill(separator) << " "; //spacing for next line
	cout << left << setw(nameWidth) << setfill(separator) << "Element Name: "+ getOpen(fullLine)<< endl; //prints what is between the tags
	cout << left << setw(numWidth) << setfill(separator) << " "; //spacing for next line
	cout << left << setw(nameWidth) << setfill(separator) << "Element Content: "+ elementContent<< endl; //prints what is between the tags
	cout << endl;
}
void printStack(stack<element> songstack)
{
	cout << "     Vector containts: ";
	while(songstack.size()!=0) //if the stack isn't empty pop and print
	{
		cout<<songstack.top().getName()<<" ";
		songstack.pop(); 
	}
	cout << endl; //spacing for neatness
	cout << endl;
}

string getClosed(string line)
{
	int startPos; //where to start the substr
	int endPos; //where to end the substr
	string finalTag;

	startPos = line.find("/"); //to get tagname without slash
	endPos = line.find(">",startPos+1); //sets end pos to the closing bracket
	finalTag = line.substr(startPos+1, (endPos-startPos)-1); //creates a new string that is the closing tag

	return finalTag;
}


string getOpen(string line)
{

	int startPos; //where to start the substr
	int endPos; //where to end the substr
	string initialTag, finalTag;

	startPos = line.find("<");
	endPos = line.find(">",startPos+1); //goes through "line" and finds what's in the brackets

	initialTag = line.substr(startPos+1, (endPos-startPos)-1); //creates a new string that is just what's in the brackets
	startPos = initialTag.find("<");
	endPos = initialTag.find(">",startPos+1); //resets end positions to correspond with the new string

	if(initialTag.find(" ", startPos+1)!=string::npos) //checks if there is a space in the string (ids, etc)
	{
		if(ispunct(initialTag.at(startPos+1))) //to avoid random punct.
		{
			startPos++;
		}
		endPos = initialTag.find(" ", startPos+1); //sets the endPos to where the first instance of the space is
		finalTag = initialTag.substr(startPos+1,(endPos-startPos)-1); //get's rid of what is after the space and stores in finalTag
	}

	if (initialTag.find(" ", startPos + 1) == string::npos) //if there is no space in the tag
	{
		if(ispunct(initialTag.at(startPos+1))) //to avoud random punct.
		{
			startPos++;
		}
		finalTag = initialTag.substr(startPos + 1, (endPos - startPos) - 1); //getting the finalTag
	}

	return finalTag;
}