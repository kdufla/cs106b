/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include <ctime>
using namespace std;

//prototypes
string findLedder(Queue<Vector<string> > &ledderCollection, string lastWord, Lexicon &used,Lexicon &words);

int main() {
	Lexicon eng("EnglishWords.dat");//import list of words program can use
	while(true){
		Queue<Vector<string> > ledderCollection;
		Lexicon used; //used word can't be in shortest ledder so I'm not useing tham twice
		string word=""; //first word
		string lastWord=""; //last word
		while(true){
			word=getLine("? first word: ");
			lastWord=getLine("? last word: ");
			if(word.length()==lastWord.length())break;
		}
		Vector<string> ledder;
		ledder.add(word);
		used.add(word);
		ledderCollection.enqueue(ledder);//add first word(with vector) in queue
		int asa=0;

		//start clock
		clock_t start;
		start = std::clock();
		double duration = 0.0;

		//main procces
		cout<<"shortest ladder is:"<<endl;
		cout<<findLedder(ledderCollection,lastWord,used,eng)<<endl;
		
		//end clock
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		cout << "Duration: " <<duration<<endl;
		if(getLine("again? ")!="yes")break;
	}
    return 0;
}

/*
* this method can find the shortest ledder between words
* first check every word with changeing one letter and add new words in queue
* than do same with new words in queue. eventually after checking every possible word
* there will be nothing to add in queue and loop will stop, or before that program will find ledder.
* first ledder is less or equal than second smallest.
*/
string findLedder(Queue<Vector<string> > &ledderCollection, string lastWord, Lexicon &used,Lexicon &words){
	while(!ledderCollection.isEmpty()){
		Vector<string> ledder=ledderCollection.dequeue();
		string ww=ledder[ledder.size()-1];//last word in ledder
		string backup=ww;
		// replace every char with letters from a to z for
		for(char ch='a';ch<='z';ch++){
			for(int i=0;i<ww.length();i++){
				ww[i]=ch;
				//if never used and in lexicon
				if(!used.contains(ww)&&words.contains(ww)){
					Vector<string> v1;
					v1.add(ww);
					Vector<string> v2=ledder+v1;
					ledderCollection.enqueue(v2);
					used.add(ww);
					// return shortest ledder
					if(lastWord==ww){
						return v2.toString();
					}
				}
				ww=backup;
			}
		}
	}
	return "impissible"; // there is no ledder between these two
}

