#ifndef DEQ_H
#define DEQ_H

#pragma once

#include<stdio.h>
#include<stdlib.h>

typedef struct deque deque;
typedef struct deque *Deque;

struct deque{
	int *key;
	int size;
};

Deque NewDeq();

void print(Deque);

int Isempty(Deque);

void PushBack(Deque, int);

void PushFront(Deque, int);

int PopBack(Deque);

int PopFront(Deque);

void Clear(Deque);

int DeleteMax(Deque);

void Sort(Deque);

int IsEmpty(Deque);

#endif
