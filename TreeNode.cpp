#include "TreeNode.h"

TreeNode::TreeNode(int data, int color)
{
	Data = data;
	Color = color; 
	Left = nullptr;
	Right = nullptr;
	Parent = nullptr;
	Size = 1;
}

int TreeNode::GetSize() {
	return Size;
}

int TreeNode::GetColor() {
	return Color;
}

int TreeNode::GetData() {
	return Data;
}

TreeNode* TreeNode::getleft() {
	return Left;
}

TreeNode* TreeNode::getright() {
	return Right;
}

TreeNode* TreeNode::getparent() {
	return Parent;
}

void TreeNode::setleft(TreeNode* left) {
	Left = left;
}

void TreeNode::setright(TreeNode* right) {
	Right = right;
}

void TreeNode::setparent(TreeNode* parent) {
	Parent = parent;
}

void TreeNode::setsize(int size) {
	Size = size;
}

void TreeNode::setcolor(int color) {
	Color = color;
}

void TreeNode::sizegrow(int delta) {
	Size = Size + delta;
}

/*void TreeNode::AddLeft(TreeNode* left) {
	if (Left == nullptr) {
		if (Color == BLACK) {
			Left = left;
		}
		else { //삽입의 부모노드가 RED

		}
	}
}*/