//STRUCT TNode////////////////////////////////////////////////////

struct TNode
	{
	int Data;
	TNode *Next;
	};


//PROTOTYPE////////////////////////////////////////////////////

void PrintList(TNode *list);
TNode *AddData(TNode *list, int data);
void FreeList(TNode *list);
int GetMax(TNode *list);	
TNode *ReverseList(TNode *list);
void GetOddEven(TNode *&list, TNode *&oddlist, TNode *&evenlist);
int GetListLength(TNode *list); 
bool IsMember(TNode *list,int member);
void CheckOddEven(TNode *&list, TNode *&odd, TNode *&even); //HW #6.c
int CheckInput(int &entry); //HW #6.d

//Unit Test
bool ListOpsTest(void);