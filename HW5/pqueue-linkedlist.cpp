/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"
#include "strlib.h"



LinkedListPriorityQueue::LinkedListPriorityQueue() {
	listLen=0;
	start=NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	if(listLen!=0){
		member *p=start;
		member *t=NULL;
		while(p->link!=NULL){
			t=p->link;
			delete p;
			p=t;
		}
	}
}

int LinkedListPriorityQueue::size() {
	return listLen;
}

bool LinkedListPriorityQueue::isEmpty() {
	return listLen==0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	member *m=new member;
	m->name=value;
	member *temp=NULL;
	if(listLen==0){
		member *p=new member;
		p->link=NULL;
		p->name=value;
		start=p;
		listLen++;
	}else{
		int count=0; // to see if value is the smallest
		for(member *p=start;p!=NULL;p=p->link){
			if(p->name>value){
				m->link=p;
				if(count==0)start=m;
				else temp->link=m;
				listLen++;
				break;
			}
			/* if value is the largest so every other name in list is smaller than value */
			if(p->link==NULL){
				m->link=NULL;
				p->link=m;
				listLen++;
				break;
			}
			temp=p;
			count++;
		}
	}
}

string LinkedListPriorityQueue::peek() {
	if(listLen==0)error("");
	return start->name;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(listLen==0)error("");
	string name=start->name;
	if(listLen>1){
		member *t=start->link;
		delete start;
		start=t;
	}
	else start=NULL;
	listLen--;
	return name;
}

