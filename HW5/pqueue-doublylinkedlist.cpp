/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include "strlib.h"


DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	listLen=0;
	first=NULL;
	last=NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	if(listLen!=0){
		member *p=first;
		member *t=NULL;
		while(p->next!=NULL){
			t=p->next;
			delete p;
			p=t;
		}
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return listLen;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return listLen==0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	member *m=new member;
	m->name=value;
	if(listLen==0){ //first member
		m->prev=NULL;
		m->next=NULL;
		first=m;
		last=m;
	}else{
		m->prev=last;
		last->next=m;
		m->next=NULL;
		last=m;
	}
	listLen++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(listLen==0)error("");
	member *p=first;
	string name=p->name;
	int count=0;
	for(int i=1;i<listLen;i++){
		p=p->next;
		count++;
		if(name>p->name){
			name=p->name;
			count=0;
		}
	}
	return name;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(listLen==0)error("");
	member *p=first;
	string name=p->name;
	int count=0;
	for(int i=1;i<listLen;i++){
		p=p->next;
		count++;
		if(name>p->name){
			name=p->name;
			count=0;
		}
	}
	p=last;
	for(int i=0;i<count;i++){
		p=p->prev;
	}
	// get ready to remove member
	if(p->prev==NULL&&p->next==NULL){
		first=NULL;
		last=NULL;
	}else if(p->prev==NULL){
		first=p->next;
		(p->next)->prev=NULL;
	}else if(p->next==NULL){
		last=p->prev;
		(p->prev)->next=NULL;
	}else{
		(p->prev)->next=p->next;
		(p->next)->prev=p->prev;
	}
	delete p;
	listLen--;
	return name;
}

