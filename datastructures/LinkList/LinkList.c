#include<stdio.h>
#include "LinkList.h"
#include<stdlib.h>
#include<stdbool.h>

bool GetElem(Linklist l,int i,Elemtype* e)
{
	int j=1;
	Linklist p=l->next;

	while(p && j<i)
	{
		p=p->next;
		++j;
	}
	if(!p || j>i)
	  return false;
	*e=p->data;

	return true;
}

bool ListInsert(Linklist* l,int i,Elemtype e)
{
	int j=1;
	Linklist p,s;

	p=(*l);
	while(p && j < i)
	{
		p=p->next;
		++j;
	}
	if(!p || j>i)
	  return false;
	
	s=(Linklist)malloc(sizeof(Node));
	s->data=e;
	s->next=p->next;
	p->next=s;
	
	return true;
}

bool ListDelete(Linklist* l,int i,Elemtype* e)
{
	int j=1;
	Linklist p,q;

	p=(*l);

	while(p->next && j<i)
	{
		p=p->next;
		j++;
	}
	if(!(p->next) || j>i)
		return false;
	q=p->next;
	p->next=q->next;
	*e=q->data;
	free(q);
	return true;
}

void CreateListByHead(Linklist* l,int n)
{
	Linklist p;
	int i;
	(*l)=(Linklist)malloc(sizeof(Node));
	(*l)->next=NULL;

	for(i=0;i<n;i++)
	{
		p=(Linklist)malloc(sizeof(Node));
		p->data=i+1;
		p->next=(*l)->next;
		(*l)->next=p;
	}
}

void CreatListByTail(Linklist* l,int n)
{
	Linklist p,r;
	int i;
	(*l)=(Linklist)malloc(sizeof(Node));
	r=(*l);

	for(i=0;i<n;i++)
	{
		p=(Node*)malloc(sizeof(Node));
		p->data=i+1;
		r->next=p;
		r=p;
	}
	r->next=NULL;
}

bool ClearList(Linklist* l)
{
	Linklist p,q;
	p=(*l)->next;

	while(p)
	{
		q=p->next;
		free(p);
		p=q;
	}

	(*l)->next=NULL;

	return true;
}
int lenOfList(Linklist l)
{
	int i=0;
	Linklist p;
	p=l->next;

	while(p)
	{
		i++;
		p=p->next;
	}

	return i;
}
void print(Linklist l)
{
	Linklist p;
	int i;
	int n=lenOfList(l);

	p=l->next;
	for(i=1;i<=n;i++)
	{
		printf("%d  ",p->data);
		p=p->next;
		if(i%5==0)
		  printf("\n");
	}
	printf("\n");
}





