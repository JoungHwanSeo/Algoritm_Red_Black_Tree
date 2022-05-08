#pragma once
#include "TreeNode.h"



class OSTree {
public:
	OSTree();
	Node* getroot();
	void show(Node* node);
	void Rotateleft(Node* node);
	void Rotateright(Node* node);
	int OSInsert(int key);
	void InsertHazard(Node* node);


private:
	Node* root;
	Node* leaf;
 };