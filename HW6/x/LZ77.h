/*
 * file: LZ77.h
 *
 * this is header file for Lempel-Ziv 1977 compression
 */

#ifndef My_LZ77
#define My_LZ77

#include "LZ77_Types.h"
#include "bstream.h"
#include "Vector.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>

//encode
void encodeLZ(ibstream& infile, obstream& outfile);
// bould vector of compressed structs
Vector<LZ_out*> buildVec(ibstream& file);
// write structs in bits
void outBinary(Vector<LZ_out*> vec,obstream& out);
//return len size string. binary meaning of int number
string toBinary(int number,int len);
//delete structures
void deleteVec(Vector<LZ_out*> vec);
// build struct with longest matching string
LZ_out* findLongestPrefix(char ch,string search,string lookAhead);
// common length
int comLen(string st1,string st2);

//decode
void decodeLZ(ibstream& infile, obstream& outfile);
//binary code to int
int binaryStringToInt(string str);
//check if it's end
bool onlyOnes(string str);

void writeText(int pos, int len, char ch,string &dictionary, obstream& outfile);


#endif