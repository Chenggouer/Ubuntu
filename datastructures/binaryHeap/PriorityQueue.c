#include<stdio.h>
#include "BinHeap.h"
#define INT_MXA 65535

Binheap createpQueue(int* a, int n)
{
	Binheap head;
	head = buildHeap(a, n);
	return head;
}
void push_pQueue(Binheap* head, int x)
{
	push(head, x);
}
int pop_pQueue(Binheap* head)
{
	if((*head)->size == 0)
	{
		printf("pQueue is empty!\n");
		return INT_MXA;
	}
	(*head)->size--;
	int temp = *((*head)->p);
	*((*head)->p) = *((*head)->p + ((*head)->size));
	*((*head)->p + ((*head)->size)) = temp;
	
	(*head)->size--;
	down_heapify(head, 0);
	(*head)->size++;
	return temp;
}
void showpQueue(Binheap p)
{
	showHeap(p);
}int main()
{
	Binheap pQueue;
	int a[] = {1,2,5,3,4};
	int len = sizeof(a)/sizeof(a[0]);
	pQueue = createpQueue(a, len);
	showpQueue(pQueue);
	push_pQueue(&pQueue, 10);

	showpQueue(pQueue);
	int top = pop_pQueue(&pQueue);
	showpQueue(pQueue);
	printf("top = %d\n",top);

	return 0;
}
