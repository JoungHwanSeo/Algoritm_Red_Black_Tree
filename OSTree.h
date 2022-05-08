#pragma once
#include "TreeNode.h"



class OSTree {
public:
	OSTree();
	bool OSInsert(int key);
	void Rotateleft(Node* node);
private:
	Node* root;
	Node* leaf;
 };