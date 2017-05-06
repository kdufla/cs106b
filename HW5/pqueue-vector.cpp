/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	return myQueue.size();
}

bool VectorPriorityQueue::isEmpty() {
	return myQueue.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	myQueue.add(value);
}

string VectorPriorityQueue::peek() {
	string word=myQueue[0];
	for(int i=1;i<myQueue.size();i++){
		if(myQueue[i]<word)word=myQueue[i];
	}
	return word;
}

string VectorPriorityQueue::dequeueMin() {
	string word=myQueue[0];
	int index=0;
	/* find min*/
	for(int i=1;i<myQueue.size();i++){
		if(myQueue[i]<word){
			word=myQueue[i];
			index=i;
		}
	}
	myQueue.remove(index);
	return word;
}