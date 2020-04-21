#ifndef BINHEAP_H_
#define BINHEAP_H_
#include<stdbool.h>
typedef struct Binatyheap
{
	int* p;
	int capacity; //array's capacity
	int size;  //count of elem of array
} Heap, *Binheap;

void createHeap(Binheap* heap); // max-heap
void down_heapify(Binheap* heap, int index); // push an elem,downwards to find it's position
void up_heapify(Binheap* heap, int index);  //upwards to find position
void push(Binheap* heap, int x); //insert x to he heap
void pop(Binheap* heap); // remove the max elem
int getTop(Binheap* heap);  //return max elem
bool isEmpty(Binheap heap);
int getSize(Binheap heap);

void showHeap(Binheap heap);

Binheap buildHeap(int* a, int n);//make a array become a maxheap;

Binheap heapSort(int* a, int n);
#endif
