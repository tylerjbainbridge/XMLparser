/*
* Tyler Bainbridge
* UMass Lowell
* Tyler_Bainbridge@student.uml.edu
* Assignment 3
* (c) UMass Lowell 2015
* created 9/8/15
* last edited 9/25/15 at 11PM
*/
#ifndef ELEMENT_H
#define ELEMENT_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <iomanip>
#include <stack>

using namespace std;

class element{
public:
	element();
	element(string finalTag, int lineNumber); //creates a new element
	string getName(); //returns element name
	int getlineNum(); //returns the line number

private:
	string elementName; //name of the tag
	int lineNum; //line number its found on
};

#endif