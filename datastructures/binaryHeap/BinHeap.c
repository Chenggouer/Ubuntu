#include<stdio.h>
#include<stdlib.h>
#include "BinHeap.h"
#define INT_MIN -999999
void createHeap(Binheap* heap)
{
	(*heap) = (Binheap)malloc(sizeof(Heap));
	(*heap)->capacity = 1;
	(*heap)->p = (int*)malloc((*heap)->capacity*sizeof(int));
	(*heap)->size = 0;
}

void up_heapify(Binheap* heap, int index)
{
	int parent = (index-1)/2;
	if(parent < 0) return;
	if(*((*heap)->p + index) > (*(*heap)->p + parent))
	{
		int temp = *((*heap)->p + index);
		*((*heap)->p + index) = *((*heap)->p + parent);
		*((*heap)->p +parent) = temp;
		up_heapify(heap, parent);
	}
}
void down_heapify(Binheap* heap, int index)
{
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int lagest = index;
	if(left <= (*heap)->size - 1 && *((*heap)->p + left) > *((*heap)->p + index) )
	  lagest = left;
	if(right <= (*heap)->size - 1 && *((*heap)->p + right) > *((*heap)->p + lagest))
	  lagest = right;

	//printf(" lagest = %d\n",lagest);
	if(lagest != index)
	{
		int temp = *((*heap)->p + lagest);
		*((*heap)->p + lagest) = *((*heap)->p + index);
		*((*heap)->p + index) = temp;
		down_heapify(heap, lagest); //continue downwards to find position
	}
}

void push(Binheap* heap, int x)
{
	if((*heap)->size >= (*heap)->capacity) return;
	*((*heap)->p + ((*heap)->size)) = x;
	(*heap)->size++;
	if(4 * ((*heap)->size) >= 3 * ((*heap)->capacity))
	{
		(*heap)->capacity *= 2;
		(*heap)->p = (int*)realloc((*heap)->p, ((*heap)->capacity) * sizeof(int) );
	}
	up_heapify(heap, (*heap)->size - 1);
}

void pop(Binheap* heap)
{
	if((*heap)->size == 0) return;
	(*heap)->size--;
	int temp = *(((*heap)->p) + ((*heap)->size));
	*((*heap)->p + ((*heap)->size)) =*((*heap)->p);
	*((*heap)->p) = temp;

	if(4 * ((*heap)->size) < (*heap)-> capacity)
	{
		(*heap)->capacity /= 2;
		(*heap)->p = (int*)realloc((*heap)->p, ((*heap)->capacity)*sizeof(int));
	}
}

int getTop(Binheap* heap)
{
	if((*heap)->size != 0) return *((*heap)->p);
	else
	  return INT_MIN;
}
bool isEmpty(Binheap heap)
{
	if(heap->size != 0)
	  return true;
	else
	  return false;
}

int getSize(Binheap heap)
{
	return heap->size;
}

void showHeap(Binheap heap)
{
	for(int i = 0; i < heap->size; i++)
	{
		printf("%d  ",(heap->p[i]));
	}
	printf("\n");
}

Binheap buildHeap(int* a, int n)
{
	int len = n;
	Binheap head = (Heap*)malloc(sizeof(Heap));
	head->capacity = len + 2; // (push:size < capacity)
	head->size = len;
	head->p = (int*)malloc((head->size) * sizeof(int));
	//printf("original heap is:\n");
	for(int i = 0; i < len; i++)
	{
		*(head->p + i) = a[i];
		//printf("%d  ",*(head->p + i));
	}
	for(int i = 0; i < len / 2; i++)
	{
		down_heapify(&head,i);
	}
	//printf("after down_heapify:\n");
	return head;
}

Binheap heapSort(int* a, int n)
{
	Binheap head = buildHeap(a,n);
	int len = head->size;
	for(int i = head->size - 1; i > 0; i--)
	{
		int temp = *(head->p + i);
		*(head->p + i) = *(head->p);
		*(head->p) = temp;
		printf("%d\n",*(head->p + i));
		head->size--;
		down_heapify(&head, 0);
	}
	head->size = len;
	return head;
}
