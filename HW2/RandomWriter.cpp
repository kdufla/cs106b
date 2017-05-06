/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "map.h"
#include "vector.h"
#include "simpio.h"
#include "random.h"
using namespace std;

//prototypes
void openFile(ifstream &stream);
void analyse(Map<string,Vector<char> > &map,ifstream &stream,int k,string &mostUsed);
void generateText(Map<string,Vector<char> > &map,string &mostUsed,int k);

int main() {
	Map<string,Vector<char> > map;//storage for analysed characteristic patterns
	ifstream stream;
    openFile(stream);
	int k=getInteger("choose order: ");//order number
	string mostUsed="";

	//main procces
	analyse(map,stream,k,mostUsed);
	generateText(map,mostUsed,k);

	stream.close();
    return 0;
}

void openFile(ifstream &stream){
	string file;
	while(true){
		file=getLine("enter file name: ");
		stream.open(file.c_str());
		if(stream.fail()){
			cout<<"invalid name"<<endl;
			stream.clear();
		}else break;
	}
}

/*
* this method anlyses every character (excluding first ones) in text
* first skip few characters and add them in string
* than for every other character save k chars as string in map
* string before char as key and char in vector as value.
* string with the longest vector is the most used one
*/
void analyse(Map<string,Vector<char> > &map,ifstream &stream,int k,string &mostUsed){
	//init:
	int maxNum=0;
	char ch;
	string str="";
	for(int i=0;i<k;i++){
		ch=stream.get();
		str+=ch;
	}
	//analyse:
	while(stream.get(ch)){
		if(map.containsKey(str)){
			map[str].add(ch);
		}else{
			Vector<char> v;
			v.add(ch);
			map.put(str,v);
		}
		if(map[str].size()>maxNum&&str.find(' ') == string::npos){
			mostUsed=str;
			maxNum=map[str].size();
		}
		str=str.substr(str.length()-k+1,k-1)+ch;
	}
}

/*
* this method uses result of analyse to generate random text.
* first put most used sting as fisrt word and than based on that string generate random character
* from value (vactor) in map. than remove first char of string and add generated char as last one
* and add chat to full (generated) text.
*/
void generateText(Map<string,Vector<char> > &map,string &mostUsed,int k){
	string str=mostUsed;
	string totalStr=mostUsed;
	for(int i=0;i<2000;i++){
		int g=map[str].size()-1;
		int n = randomInteger(0, g);
		char ch=map.get(str).get(n);
		totalStr+=ch;
		str=str.substr(str.length()-k+1,k-1)+ch;
	}
	cout<<totalStr<<endl;
}