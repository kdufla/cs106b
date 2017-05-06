/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

int main() {
	int countHeads=0;
	int count=0;
	while(true){
		if(countHeads==3){
			cout<<"it took "<<count<<" flips to get 3 consecutive heads"<<endl;
			break;
		}else{
			if(randomChance(0.5)){
				cout<<"heads"<<endl;
				countHeads++;
			}else{
				cout<<"tails"<<endl;
				countHeads=0;
			}
		}
		count++;
	}
    return 0;
}
