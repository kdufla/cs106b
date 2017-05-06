/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"
#include "strlib.h"

HeapPriorityQueue::HeapPriorityQueue() {
	efSize=0;
	alSize=4;
	myQueue=new string[alSize];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] myQueue;
}

int HeapPriorityQueue::size() {
	return efSize;
}

bool HeapPriorityQueue::isEmpty() {
	return efSize==0;
}

void HeapPriorityQueue::enqueue(string value) {
	/* double size of array */
	if(efSize+1==alSize){
		alSize*=2;
		string *temp=new string[alSize];
		for(int i=0;i<efSize;i++)temp[i]=myQueue[i];
		delete[] myQueue;
		myQueue=temp;
	}
	/* enqueue value */
	myQueue[efSize]=value;
	bubbleUp(efSize);
	efSize++;
}

string HeapPriorityQueue::peek() {
	if(efSize==0)error("");
	return myQueue[0];
}

string HeapPriorityQueue::dequeueMin() {
	if(efSize==0)error("");
	string name=myQueue[0];
	substitute(0,efSize-1);
	efSize--;
	bubbleDown(0);
	return name;
}

void HeapPriorityQueue::substitute(int n1,int n2){
	string t=myQueue[n1];
	myQueue[n1]=myQueue[n2];
	myQueue[n2]=t;
}

void HeapPriorityQueue::bubbleUp(int n){
	if(n!=0){
		int up;
		/* instead of rounded n/2, I'm useing (n-2)/2 and (n-1)/2 */
		if(n%2==0)up=(n-2)/2;
		else up=(n-1)/2;
		if(myQueue[n]<myQueue[up]){
			substitute(up,n);
			bubbleUp(up);
		}
	}
}

void HeapPriorityQueue::bubbleDown(int n){
	if(2*n+2>efSize)return; // make shure that lower value exists
	int down;
	if(myQueue[2*n+1]<myQueue[2*n+2]||2*n+2==efSize)down=2*n+1;
	else down=2*n+2;
	if(myQueue[down]<myQueue[n]){
		substitute(n,down);
		bubbleDown(down);
	}
}