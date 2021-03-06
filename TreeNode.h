#pragma once

#define BLACK 0
#define RED 1

#include <iostream>

using namespace std;

class TreeNode
{
public:
	TreeNode(int data = 0, int color = BLACK); //dafault는 black
	//~TreeNode(); //이 경우 TreeNode*는 여기서 new해주는 것이 아니라 다른데서 생긴 걸
	//받아오므로 굳이 Destructor필요 x

	int GetSize();
	int GetColor();
	int GetData();
	TreeNode* getleft();
	TreeNode* getright();
	TreeNode* getparent();
	//여기서는 단순히 붙여주는 연산만 진행! 기타 연산은 OSTree에서 할거임
	void setleft(TreeNode* left);
	void setright(TreeNode* right);
	void setparent(TreeNode* parent);
	void setsize(int size);
	void setcolor(int color);
	void setdata(int data);

	void sizegrow(int delta);
	//void AddLeft(TreeNode* left); //삽입노드는 RED
private:
	int Color;
	int Data;
	TreeNode* Parent;
	TreeNode* Left;
	TreeNode* Right;
	int Size;

};

typedef TreeNode Node;