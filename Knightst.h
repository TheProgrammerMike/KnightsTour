#define ROWS		5
#define COLS		4

struct AIStateNode
{
	bool Board[ROWS][COLS];
	int CurrentPosX;
	int CurrentPosY;
	AIStateNode *Next;
};

AIStateNode *NodeCreate(void);
AIStateNode *GetChildren(AIStateNode *node);
AIStateNode *NodeCreateCopy(AIStateNode *node, int newposx, int newposy);
AIStateNode *AddPosToList(AIStateNode *childlist, AIStateNode *parent, int deltax, int deltay);
AIStateNode *AddList(AIStateNode *list1, AIStateNode *list2);
bool IsOnBoard(int posx, int posy);
bool IsOccupied(AIStateNode *node, int posx, int posy);
bool IsEndState(AIStateNode *node);
bool PrintState(AIStateNode *node);
bool KnightsTour(void);
