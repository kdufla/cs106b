/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "strlib.h"
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int WORD_LEN=4;
const double PAUSE_TIME=3000.00;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void letterCubes(Grid<char> &gr);
void shuffle(Vector<string> &shake,int n);
void boardConfiguration(Vector<char> &chars,Vector<string> &shake,int n);
void chooseGridSize(Vector<string> &shake,int &n);
void playerTurn(Grid<char> &gr,Lexicon &used,Lexicon &eng);
bool canBeFormed(string word, Grid<char> &gr);
bool tryToForm(string word, int x,int y,Grid<char> &gr, Grid<bool> &backtracking);
void highlight(Grid<bool> &backtracking);
void computersTurn(Grid<char> &gr,Lexicon &used,Lexicon &eng);
void findAllWords(Grid<char> &gr,Lexicon &used,int x,int y,string word,Grid<bool> &backtracking,Lexicon &eng);

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
	while(true){
		Grid<char> gr;
		Lexicon eng("EnglishWords.dat");//import list of words program can use
		Lexicon used;
		letterCubes(gr);
		playerTurn(gr,used,eng);
		computersTurn(gr,used,eng);
		cout<<"do you want to play again?"<<endl;
		if(getLine()!="yes")break;
	}
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}
/*
 * initialization of the game: choose board size, shuffle grid and draw it
 */

void letterCubes(Grid<char> &gr){
	Vector<string> shake;
	int n;
	chooseGridSize(shake,n);
	int x=sqrt((double)n);
	drawBoard(x,x);
	Vector<char> chars;
	boardConfiguration(chars,shake, n);
	gr.resize(x,x);
	int count=0;
	//draw chars on board
	for(int i=0;i<x;i++){
		for(int j=0;j<x;j++){
			labelCube(i,j,chars[count]);
			gr.set(i,j,chars[count]);
			count++;
		}
	}
}
/*
 * choose size of grid
 */
void chooseGridSize(Vector<string> &shake,int &n){
	cout<<endl;
	cout<<"you can choose standard Boggle (4x4 grid)"<<endl;
	cout<<"or Big Boggle (5x5 grid)"<<endl;
	cout<<"would you like Big Buggle?"<<endl;
	if(getLine()=="yes"){
		n=25;
		for(int i=0;i<n;i++){
			shake.add(BIG_BOGGLE_CUBES[i]);
		}
	}else{
		n=16;
		for(int i=0;i<n;i++){
			shake.add(STANDARD_CUBES[i]);
		}
	}
}

/*
 * choose board configuration. random charachters or charachters from
 * string entered bu human. result is Vector<char> which will be used
 * on board.
 */
void boardConfiguration(Vector<char> &chars,Vector<string> &shake,int n){
	cout<<endl;
	cout<<"would you like to force board configuration?"<<endl;
	if(getLine()=="yes"){
		string line;
		while(true){
			cout<<"enter string: ";
			line=toUpperCase(getLine());
			cout<<endl;
			if(line.length()<n)cout<<"not enough charachters"<<endl;
			else break;
		}
		for(int i=0;i<n;i++)chars.add(line[i]);
	}else{
		shuffle(shake,n);
		string str;
		char ch;
		for(int i=0;i<n;i++){
			str=shake[i];
			ch=str[randomInteger(0, str.size()-1)];
			chars.add(ch);
		}
	}
}
/*
 * shuffle strings. change their positions randomly.
 */
void shuffle(Vector<string> &shake,int n){
	for(int i=0;i<n;i++){
		int r = randomInteger(i, n-1);
		string s=shake[i];
		shake[i]=shake[r];
		shake[r]=s;
	}
}
/*
 * the human player's turn: get word, check it's size, if it's used, if it's english
 * word and most important - if it's on the board.
 */
void playerTurn(Grid<char> &gr,Lexicon &used,Lexicon &eng){
	string word;
	cout<<endl;
	while(true){
		cout<<"enter a word: ";
		word=toUpperCase(getLine());
		if(word=="")break;
		cout<<endl;
		if(word.length()>=WORD_LEN&&eng.contains(word)&&!used.contains(word)&&canBeFormed(word,gr)){
			recordWordForPlayer(word,HUMAN);
			used.add(word);
		}else cout<<"wrong! ";
		if(word.length()<WORD_LEN)cout<<"too short.";
		cout<<endl<<endl;
	}
}
/*
 * initialization for recursion and backtracking, find word on board and highlight it.
 * return true if word is on board.
 */
bool canBeFormed(string word, Grid<char> &gr){
	Grid<bool> backtracking(gr.numRows(),gr.numCols());
	for(int i=0;i<gr.numRows();i++){
		for(int j=0;j<gr.numCols();j++){
			backtracking[i][j]=false;
		}
	}
	for(int i=0;i<gr.numRows();i++){
		for(int j=0;j<gr.numCols();j++){
			if(gr[i][j]==word[0]){
				if(tryToForm(word,i,j,gr,backtracking)){
					highlight(backtracking);
					return true;
				}
			}
		}
	}
	return false;
}
/*
 * base case 1: if every leter is in sequence last word is nothing.
 * base case 2: word can't be outside of boarders
 * base case 3: two chars of word can't be on same place
 * check same things on every neighbour
 */
bool tryToForm(string word, int x,int y,Grid<char> &gr, Grid<bool> &backtracking){
	if(word=="")return true;
	if(x<0||y<0||x==gr.numRows()||y==gr.numCols())return false;
	if(backtracking[x][y])return false;
	if(word[0]!=gr[x][y])return false;
	else{
		backtracking[x][y]=true;
		bool form=tryToForm(word.substr(1),x-1,y-1,gr,backtracking)||tryToForm(word.substr(1),x-1,y,gr,backtracking)
		||tryToForm(word.substr(1),x-1,y+1,gr,backtracking)||tryToForm(word.substr(1),x,y-1,gr,backtracking)
		||tryToForm(word.substr(1),x,y+1,gr,backtracking)||tryToForm(word.substr(1),x+1,y-1,gr,backtracking)
		||tryToForm(word.substr(1),x+1,y,gr,backtracking)||tryToForm(word.substr(1),x+1,y+1,gr,backtracking);
		if(!form)backtracking[x][y]=false;
		return form;
	}
	return true;
}
/* 
 * This function is used to highlight a cube which is currently being used
 * to form a word.
 */
void highlight(Grid<bool> &backtracking){
	for(int i=0;i<backtracking.numRows();i++){
		for(int j=0;j<backtracking.numCols();j++){
			if(backtracking[i][j])highlightCube(i,j,true);
		}
	}
	pause(PAUSE_TIME);
	for(int i=0;i<backtracking.numRows();i++){
		for(int j=0;j<backtracking.numCols();j++){
			if(backtracking[i][j])highlightCube(i,j,false);
		}
	}
}
/*
 * this is computer's turn. using two "for" it can find every word for
 * every coordinate on game board.
 */
void computersTurn(Grid<char> &gr,Lexicon &used,Lexicon &eng){
	Grid<bool> backtracking(gr.numRows(),gr.numCols());
	for(int i=0;i<gr.numRows();i++){
		for(int j=0;j<gr.numCols();j++){
			backtracking[i][j]=false;
		}
	}
	string word="";
	for(int i=0;i<gr.numRows();i++){
		for(int j=0;j<gr.numCols();j++){
			findAllWords(gr,used,i,j,word,backtracking,eng);
		}
	}
}
/*
 * base case: in first four cases check coordinates are within boaders. then see if
 * coordinates were already used and finally check if prefix of word is prefix of
 * any real word from lexicon.
 * if "word" is real word write it on board. then add neighbour characters to word
 * and see if new word is real. 
 */
void findAllWords(Grid<char> &gr,Lexicon &used,int x,int y,string word,Grid<bool> &backtracking,Lexicon &eng){
	if(x<0||y<0||x==gr.numRows()||y==gr.numCols()||backtracking[x][y]||!eng.containsPrefix(word))return;
	else{
		backtracking[x][y]=true;
		if(word.length()>=WORD_LEN&&!used.contains(word)&&eng.contains(word)){
			recordWordForPlayer(word,COMPUTER);
			used.add(word);
		}
		for(int i=-1;i<2;i++){
			for(int j=-1;j<2;j++){
				findAllWords(gr,used,x+i,y+j,word+gr[x][y],backtracking,eng);
			}
		}
		backtracking[x][y]=false;
	}
}