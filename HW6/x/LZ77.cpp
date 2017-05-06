/*
 * file: LZ77.cpp
 *
 * this is implementation of functions from LZ77.h
 */

#include "LZ77.h"

void encodeLZ(ibstream& infile, obstream& outfile){
	Vector<LZ_out*> vec=buildVec(infile);
	outBinary(vec,outfile);
	deleteVec(vec);
}

void deleteVec(Vector<LZ_out*> vec){
	for(int i=0;i<vec.size();i++)delete vec[i];
}

// write structs in bits
void outBinary(Vector<LZ_out*> vec,obstream& out){
	int pos;
	string posi;
	int len;
	string leng;
	char ch;
	string cha;
	for(int i=0;i<vec.size();i++){
		pos=vec[i]->position;
		len=vec[i]->length;
		ch=vec[i]->next;
		posi=toBinary(pos,SEARCH_LEN);
		leng=toBinary(len,AHAED_LEN+1);
		cha=toBinary(ch,CHAR_LEN);
		for(int i=0;i<SEARCH_LEN;i++){
			if(posi[i]=='1')out.writeBit(1);
			else out.writeBit(0);
		}
		for(int i=0;i<AHAED_LEN+1;i++){
			if(leng[i]=='1')out.writeBit(1);
			else out.writeBit(0);
		}
		for(int i=0;i<CHAR_LEN;i++){
			if(cha[i]=='1')out.writeBit(1);
			else out.writeBit(0);
		}
	}
	// just 0 s because I have exstra codes in len part
	for(int i=0;i<SEARCH_LEN;i++){
		out.writeBit(0);
	}
	/*
	 * I have n+1 size. if len can be 1,2,3 or 4 I can't write it as 00,01,10 and 11 because
	 * len can be 0 too. with n+1 I'm useing only 000,001,010,011 and 100, so 111 (n times 1)
	 * can be like PSEUDO_EOF in huffman.
	 */
	for(int i=0;i<AHAED_LEN+1;i++){
		out.writeBit(1);
	}
}

//return len size string. binary meaning of int number
string toBinary(int number,int len){
    string bin;
    char holder=' ';
    while(number!=0)
    {
        holder=number%2+'0';
        bin=holder+bin;
        number/=2;
    }
	string str;
	while(bin.length()!=len)bin="0"+bin;
	return bin;
}

// bould vector of compressed structs
Vector<LZ_out*> buildVec(ibstream& file){
	Vector<LZ_out*> outputs;
	string search="";
	string lookAhead="";
	char ch;
	LZ_out* output;
	for(int i=0;i<AHEAD_SIZE;i++){
		file.get(ch);
		//cout<<ch;
		lookAhead+=ch;
	}
	//cout<<endl;
	//cout<<search<<endl;
	//cout<<lookAhead<<endl;
	while(file.get(ch)){
		output=findLongestPrefix(ch,search,lookAhead);
		outputs.add(output);
		if(output->length>0){
			for(int i=0;i<output->length;i++){
				lookAhead+=ch;
				search+=lookAhead[0];
				lookAhead=lookAhead.substr(1);
				if(search.length()>SEARCH_SIZE)search=search.substr(1);
				file.get(ch);
			}
		}
		lookAhead+=ch;
		search+=lookAhead[0];
		lookAhead=lookAhead.substr(1);
		if(search.length()>SEARCH_SIZE)search=search.substr(1);
	}
	return outputs;
}

// build struct with longest matching string
LZ_out* findLongestPrefix(char ch,string search,string lookAhead){
	LZ_out* out=new LZ_out;
	int maxLen=0;
	int len;
	int pos=0;
	//cout<<search<<endl;
	for(int i=0;i<search.length();i++){
		len=comLen(search.substr(i),lookAhead);
		//cout<<search[i]<<endl;
		//cout<<len<<endl;
		if(len>maxLen){
			maxLen=len;
			pos=i;
		}
	}
	//cout<<"xxx"<<endl;
	out->length=maxLen;
	if(maxLen>0)out->position=search.length()-pos;
	else out->position=0;
	if(maxLen==8)out->next=ch;
	else out->next=lookAhead[maxLen];
	return out;
}

// common length
int comLen(string st1,string st2){
	int count=0;
	while(st1[count]==st2[count])count++;
	return count;
}

void decodeLZ(ibstream& infile, obstream& outfile){
	int bit;
	int pos;
	int len;
	char ch;
	string str="";
	string dictionary="";
	while(true){
		for(int i=0;i<SEARCH_LEN;i++){
			bit=infile.readBit();
			if(bit==1)str+="1";
			else str+="0";
		}
		pos=binaryStringToInt(str);
		str="";
		for(int i=0;i<AHAED_LEN+1;i++){
			bit=infile.readBit();
			if(bit==1)str+="1";
			else str+="0";
		}
		if(onlyOnes(str))break;
		len=binaryStringToInt(str);
		str="";
		for(int i=0;i<CHAR_LEN;i++){
			bit=infile.readBit();
			if(bit==1)str+="1";
			else str+="0";
		}
		ch=binaryStringToInt(str);
		str="";
		writeText(pos,len,ch,dictionary,outfile);
	}
}

int binaryStringToInt(string str){
	int sum=0;
	int power;
	for(int i=0;i<str.length();i++){
		power=str.length()-i-1;
		if(str[i]==1)sum+=pow(2.0,power);
	}
	return sum;
}

bool onlyOnes(string str){
	for(int i=0;i<str.length();i++){
		if(str[i]==0)return false;
	}
	return true;
}

void writeText(int pos, int len, char ch,string &dictionary, obstream& outfile){
	string word;
	if(pos>0){
		int position=dictionary.length()-pos;
		word=dictionary.substr(position,len);
		for(int i=0;i<len;i++){
			outfile.put(word[i]);
			dictionary+=word[i];
			if(dictionary.length()==SEARCH_SIZE+1)dictionary=dictionary.substr(1);
		}
	}
	outfile.put(ch);
	dictionary+=ch;
	if(dictionary.length()==SEARCH_SIZE+1)dictionary=dictionary.substr(1);
}