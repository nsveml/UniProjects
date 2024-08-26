#include "deq.h"

Deque NewDeq(){
	Deque a=(Deque)malloc(sizeof(deque));
	a->size=0;
	a->key=NULL;
	return(a);
}

void print(Deque a){
	for(int i=0; i<a->size; i++){
		printf("%d ",a->key[i]);
	}
	printf("\n");
}

int IsEmpty(Deque a){
	int b=0;
	if(a->size==0) b=1;
	return(b);
}

void PushBack(Deque a, int b){
	if(a->key==NULL){
		a->key=(int*)malloc(sizeof(int));
		a->key[0]=b;
	}else{
		int *c=(int*)malloc((a->size+1)*sizeof(int));
		c[a->size]=b;
		for(int i=0; i<a->size; i++){
			c[i]=a->key[i];
		}
		free(a->key);
		a->key=c;
	}
	a->size++;
}

void PushFront(Deque a, int b){
	if(a->key==NULL){
		a->key=(int*)malloc(sizeof(int));
		a->key[0]=b;
	}else{
		int *c=(int*)malloc((a->size+1)*sizeof(int));
		c[0]=b;
		for(int i=1; i<=a->size; i++){
			c[i]=a->key[i-1];
		}
		free(a->key);
		a->key=c;
	}
	a->size++;
}

int PopBack(Deque a){
	int b=0;
	if(a->size>0){
		b=a->key[a->size-1];
		int*c=(int*)malloc((a->size-1)*sizeof(int));
		for(int i=0; i<a->size-1; i++){
			c[i]=a->key[i];
		}
		free(a->key);
		a->key=c;
		a->size--;
	}
	if (a->size==0){
		a->size=0;
		a->key=NULL;
	}
	return(b);
}

int PopFront(Deque a){
	int b=0;
	if(a->size>0){
		b=a->key[0];
		int*c=(int*)malloc((a->size-1)*sizeof(int));
		for(int i=0; i<a->size-1; i++){
			c[i]=a->key[i+1];
		}
		free(a->key);
		a->key=c;
		a->size--;
	}
	if (a->size==0){
		a->size=0;
		a->key=NULL;
	}
	return(b);
}

void Clear(Deque a){
	a->size=0;
	free(a->key);
	a->key=NULL;
}
