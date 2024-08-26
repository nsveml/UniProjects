#include "deq.h"

int DeleteMax(Deque a){
	int b=a->size;
	int c=0, max=0;
	for(int i=0; i<b; i++){
		c=PopBack(a);
		if(c>max) max=c;
		PushFront(a, c);
	}
	for(int i=0; i<b; i++){
		c=PopBack(a);
		if(c!=max) PushFront(a, c); else break;
	}
	return(max);
}

void Sort(Deque a){
	int c, b=a->size;
	Deque deq=NewDeq();
	for(int i=0; i<b; i++){
		c=DeleteMax(a);
		PushFront(deq, c);
	}
	*a=*deq;
}
