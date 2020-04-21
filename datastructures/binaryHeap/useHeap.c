#include<stdio.h>
#include "BinHeap.h"

int main()
{
	Binheap head;
	createHeap(&head);

	push(&head, 9);
	push(&head, 10);
	int a = getSize(head);
	printf("size of heap is %d\n",a);
	showHeap(head);
	push(&head,11);
	showHeap(head);
	pop(&head);
	showHeap(head);
	int arr[5] = {1,2,5,3,4};
	int len = sizeof(arr)/sizeof(arr[0]);
	//Binheap mhead = buildHeap(arr, len);
	//showHeap(mhead);

	Binheap hs = heapSort(arr, len);
	printf("after heapsort: \n");
	showHeap(hs);
	return 0;
}
