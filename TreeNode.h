#pragma once

#define BLACK 0
#define RED 1

#include <iostream>

class TreeNode
{
public:
	TreeNode(int data = 0, int color = BLACK); //dafault�� black

	int GetSize();
	int GetColor();
	int GetData();
	TreeNode* getleft();
	TreeNode* getright();
	TreeNode* getparent();
	//���⼭�� �ܼ��� �ٿ��ִ� ���길 ����! ��Ÿ ������ OSTree���� �Ұ���
	void setleft(TreeNode* left);
	void setright(TreeNode* right);
	void setparent(TreeNode* parent);
	void setsize(int size);
	void setcolor(int color);

	void sizegrow(int delta);
	//void AddLeft(TreeNode* left); //���Գ��� RED
private:
	int Color;
	int Data;
	TreeNode* Parent;
	TreeNode* Left;
	TreeNode* Right;
	int Size;

};

typedef TreeNode Node;