#pragma once

#define BLACK 0
#define RED 1

#include <iostream>

class TreeNode
{
public:
	TreeNode(int data = 0, int color = BLACK); //dafault는 black

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