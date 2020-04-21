#include<stdio.h>
#include "LinkList.h"

int main()
{
	Linklist l1,l2;
	puts("Initializeing...");


	CreateListByHead(&l1,10);
	CreatListByTail(&l2,10);

	print(l1);
	print(l2);

	Elemtype e1,e2;
	puts("get l1's second elemtens:");
	GetElem(l1,2,&e1);
	puts("Delete l1's second elem:");
	ListDelete(&l1,2,&e2);

	print(l1);

	puts("Insert l1 in second posiong with11");
	ListInsert(&l1,2,11);
	print(l1);

	return 0;
}
