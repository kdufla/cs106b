/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string sub);

int main() {
		string t =getLine("text: ");
		string s =getLine("subsequence: ");
		if(isSubsequence(t,s))cout<<"true"<<endl;
		else cout<<"false"<<endl;
    return 0;
}

bool isSubsequence(string text, string sub){
	if(sub=="")return true;
	if(text=="")return false;
	if(sub[0]==text[0]) return isSubsequence(text.substr(1),sub.substr(1));
	else return isSubsequence(text.substr(1),sub);
}