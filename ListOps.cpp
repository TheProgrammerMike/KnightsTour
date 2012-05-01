#include <iostream>
#include <cstdio>
#include "ListOps.h"

using namespace std;

//////////////////////////////////////////////////////

void PrintList(TNode *list)
	{
		cout<<"List: \n";
	TNode *p;
	for(p=list;p!=0;p=p->Next)
		{
		cout<<p->Data<<" "<<endl;
		}
	}

//////////////////////////////////////////////////////

TNode *AddData(TNode *list, int data)
	{
	TNode *newnode=new TNode;
	if(newnode==NULL)
		{
		printf("Could not allocate space in AddData- %s(%d) \n",__FILE__,__LINE__);
		return list;
		}
	newnode->Data=data;
	newnode->Next=list;
	return newnode;
	}

//////////////////////////////////////////////////////

void FreeList(TNode *list)
{
	TNode *p;
	TNode *next;
	for(p=list;p!=NULL;p=next)
	{
		next=p->Next;
		delete p;	
	}
	if(p)
	{
		printf("Error clearing list in: FreeList-%s(%d) \n",__FILE__,__LINE__);	//HW #6.a
	}
}

//////////////////////////////////////////////////////

int GetMax(TNode *list)
{
	TNode *p;
	if(list==NULL)
	{
		printf("No Max, No List in: GetMax-%s(%d) \n",__FILE__,__LINE__); //HW #6.b
		return 0;
	}
	int max=list->Data;

	for(p=list->Next;p!=0;p=p->Next)
		{
		if(p->Data>max)
		max=p->Data;
		}
	return max;
}

//////////////////////////////////////////////////////

TNode *ReverseList(TNode *list)
{
		if(list==0)
		{
			return NULL;
		}
		TNode *newlist=NULL;
		TNode *p;
		TNode *next;
		for(p=list;p!=NULL;p=next)
		{
			next=p->Next;
			p->Next=newlist;
			newlist=p;
		}
		return newlist;
}


///////////////////////////////////////////////////////////////

void GetOddEven(TNode *&list, TNode *&oddlist, TNode *&evenlist)
{
	oddlist=NULL;
	evenlist=NULL;
	TNode *p;
	for(p=list;p!=NULL;p=p->Next)
	{
		if(p->Data%2)
			oddlist=AddData(oddlist,p->Data);
		else
			evenlist=AddData(evenlist,p->Data);
	}
}
//////////////////////////////////////////////////////////////////////
int GetListLength(TNode *list)
{
	TNode *p;
	int counter=0;
	for(p=list;p!=0;p=p->Next)
	{
		counter++;
	}
	return counter;
}
//Unit Tests////////////////////////////////////////////////////////////////////////////

bool ListOpsTest(void)
{
	//Test 1
	TNode *mylist=NULL;
	int i;
	for(i=1;i<=100;i++)
	{
		mylist=AddData(mylist,i);
		if(GetListLength(mylist)!=i)
		{
			printf("Error in list length %s (%d) ",__FILE__,__LINE__);
			return false;
		}
	}

	for(i=1;i<=100;++i)
	{
		if(IsMember(mylist,i)==false)
		{
			printf("Error- Member missing - %s(%d)",__FILE__,__LINE__);
			return false;
		}
	}

	for(i=-1;i>=-100;--i);
	{
		if(IsMember(mylist,i)==true)
		{
			printf("Error- Member should not be in list - %s(%d)",__FILE__,__LINE__);
			return false;
		}
	}

	return true;
}
//Is number requested a member
bool IsMember(TNode *list,int member)
{
	TNode *p;
	for(p=list;p!=NULL;p=p->Next)
	{
		if(p->Data == member)
			{return true;}

	}
	return false;
}
void CheckOddEven(TNode *&list, TNode *&odd, TNode *&even) //HW #6.c
{
	TNode *p, *next;
	odd=NULL;
	even=NULL;
	for(p=list;p!=NULL;p=next)
	{
		next=p->Next;
		if(p->Data%2==0)
		{
			p->Next=even;
			even=p;
		}
		else
		{
			p->Next=odd;
			odd=p;
		}
	}
	list=NULL;
	return;
}

int CheckInput(int &entry) //HW #6.d
{
	char x;
	if(entry>':'||entry<0)
	{
		printf("Error- Entry out of bounds - %s(%d)",__FILE__,__LINE__);
		//return 0;		No sence in returnin value an continuning, 1st pass->no list
		exit(1);
	}
	else if (x=getchar())
	{
		if(x>';')
		{
			printf("Error- Entry out of bounds - %s(%d)\nList is now closed\n",__FILE__,__LINE__);
			return 0;
		}
		else
		{
			return entry;
		}
	}
	else 
	{
		return entry;
	}

}

