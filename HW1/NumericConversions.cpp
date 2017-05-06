/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
	cout<<stringToInt("-8")<<endl;
    return 0;
}

string intToString(int n){
	string sign="";
	if(n<0){
		n=-n;
		sign="-";
	}
	if(n<10){
		char ch = '0' + n;
		string str=string()+ch;
		return sign+str;
	}else{
		return sign+intToString(n/10)+intToString(n%10);
	}
}





int stringToInt(string str){
	int sign=1;
	if(str[0]=='-'){
		sign=-1;
		str=str.substr(1);
	}
	if(str.length()==1){
		int i=str[0]-48;
		return sign*i;
	}else{
		return sign*(10*stringToInt(str.substr(0,str.length()-1))+stringToInt(str.substr(str.length()-1,1)));
	}
}