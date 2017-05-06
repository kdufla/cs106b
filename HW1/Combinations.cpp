/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int combination(int n, int k);

int main() {
    cout<<combination(8, 5)<<endl;
    return 0;
}

int combination(int n,int k){
	if(k==n||k==0){
		return 1;
	}else{
		return combination(n-1, k-1)+combination(n-1, k);
	}
}
