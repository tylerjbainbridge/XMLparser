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
#include "element.h"

using namespace std;


element::element(string finalTag, int lineNumber)
{
	elementName = finalTag;
	lineNum = lineNumber;
}

string element::getName(){
	return elementName;
}

int element::getlineNum(){
	return lineNum;
}

	