/*
Michael Bekesz
CS162 AI
Dr. Devi
Knight's Tour
v.1 100408S1900
*/

/////////////////////////////////////////////////

#include <cstdio>
#include <assert.h>
#include "KnightsTour.h"

/////////////////////////////////////////////////

AIStateNode *GOpenList;
AIStateNode *GClosedList;

/////////////////////////////////////////////////

AIStateNode *NodeCreate(void)
{
	AIStateNode *newnode;
	newnode= new AIStateNode;
	if(newnode==NULL)
	{
		printf("Unable to alloc memory %s(%d)\n",__FILE__,__LINE__);
		return NULL;
	}

	int i,j;
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			newnode->Board[i][j]=false;
		}
	}

	newnode->CurrentPosX=0;
	newnode->CurrentPosY=0;
	newnode->Next=NULL;

	return newnode;
}

/////////////////////////////////////////////////

AIStateNode *GetChildren(AIStateNode *node)
{
	if(node==NULL)
	{
		printf("Bad NULL Node passed %s(%d)",__FILE__,__LINE__);
		return NULL;
	}
	int posx=node->CurrentPosX;
	int posy=node->CurrentPosY;

	AIStateNode *childlist=NULL;

	childlist=AddPosToList(childlist,node,-2,-1);
	childlist=AddPosToList(childlist,node,+2,-1);
	childlist=AddPosToList(childlist,node,+2,+1);
	childlist=AddPosToList(childlist,node,-2,+1);
	childlist=AddPosToList(childlist,node,-1,-2);
	childlist=AddPosToList(childlist,node,+1,-2);
	childlist=AddPosToList(childlist,node,+1,+2);
	childlist=AddPosToList(childlist,node,-1,+2);

	return childlist;
}

/////////////////////////////////////////////////

AIStateNode *NodeCreateCopy(AIStateNode *node,int newposx, int newposy)
{
	assert(node!=NULL);
	AIStateNode *newnode=NodeCreate();

	int i,j;
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			newnode->Board[i][j]=node->Board[i][j];
		}
	}
	newnode->Board[newposx][newposy]=true;
	newnode->CurrentPosX=newposx;
	newnode->CurrentPosY=newposy;

	return newnode;
}

/////////////////////////////////////////////////

AIStateNode *AddPosToList(AIStateNode *childlist,AIStateNode *node, int deltax, int deltay)
{
	assert(node!=NULL);

	int posx=node->CurrentPosX;
	int posy=node->CurrentPosY;

	AIStateNode *tmpnode;

	if(IsOnBoard(posx+deltax,posy+deltay)==true && IsOccupied(node,posx+deltax,posy+deltay)==false)
	{
		tmpnode=NodeCreateCopy(node,posx+deltax,posy+deltay);
		tmpnode->Next=childlist;
		childlist=tmpnode;
	}
	return childlist;
}

/////////////////////////////////////////////////

AIStateNode *AddList(AIStateNode *list1,AIStateNode *list2)
{
	AIStateNode *p;
	AIStateNode *next;
	for(p=list2;p!=NULL;p=next)
	{
		next=p->Next;
		p->Next=list1;
		list1=p;
	}
	return list1;
}

/////////////////////////////////////////////////

bool IsOnBoard(int posx,int posy)
{
	if(posx<0) {return false;}
	if(posx>=ROWS) {return false;}
	if(posy<0) {return false;}
	if(posy>=COLS) {return false;}

	return true;

}

/////////////////////////////////////////////////

bool IsOccupied (AIStateNode *node, int posx, int posy)
{
	if(node==NULL)
	{
		printf("Bad NULL Node passed %s(%d)",__FILE__,__LINE__);
		return true;
	}

	if(node->Board[posx][posy]==true) {return true;}

	return false;

}

/////////////////////////////////////////////////

bool IsEndState(AIStateNode *node)
{
	assert(node!=NULL);

	int x,y;
	for(x=0;x<ROWS;x++)
	{
		for(y=0;y<COLS;y++)
		{
			if(node->Board[x][y]==false) {return false;}
		}
	}
	return true;
}

/////////////////////////////////////////////////

bool PrintState(AIStateNode *node)
{
	int i,j;
	printf("+");
	for(i=0;i<COLS;i++)
	{
		printf("-");
	}
	printf("+\n");
	
	for(i=0;i<ROWS;i++)
	{
		printf("|");
		for(j=0;j<COLS;j++)
		{
			bool occupied=node->Board[i][j];
			if(occupied)
			{printf("X");}
			else
			{printf(" ");}
		}
		printf("|\n");
	}
	printf("+");
	for(i=0;i<COLS;i++)
	{printf("-");}
	printf("+\n");

	return true;
}

/////////////////////////////////////////////////

bool KnightsTour(void)
{
	AIStateNode *node=NodeCreate();
	if(node==NULL)
	{
		printf("Node allocation error %s(%d)\n",__FILE__,__LINE__);
		return false;
	}

	GOpenList=node;
	GClosedList=NULL;

	while(GOpenList!=NULL)
	{
		AIStateNode *current;
		current=GOpenList;
		GOpenList=GOpenList->Next;
		PrintState(current);
		if(IsEndState(current)==true)
		{
			return true;
		}

		AIStateNode *children;
		children=GetChildren(current);

		delete current;

		GOpenList=AddList(GOpenList,children);
	}
	return false;
}