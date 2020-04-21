#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include<stdbool.h>

typedef int Elemtype;
typedef struct Node
{
	Elemtype data;
	struct Node* next;
} Node,*Linklist;

bool GetElem(Linklist l,int i,Elemtype* e);

bool ListInsert(Linklist* l,int i,Elemtype e);

bool ListDelete(Linklist* l,int i,Elemtype* e);

void CreateListByHead(Linklist* l,int n);

void CreatListByTail(Linklist* l,int n);

bool ClearList(Linklist* l);

int lenOfList(Linklist l);

void print(Linklist l);
#endif

