#pragma once
#include "TreeNode.h"



class OSTree {
public:
	OSTree();
	void Rotateleft(Node* node);
	void Rotateright(Node* node);
	int OSInsert(int key);
	void InsertHazard(Node* node);


private:
	Node* root;
	Node* leaf;
 };