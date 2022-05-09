#pragma once
#include "TreeNode.h"
#include "function.h"



class OSTree {
public:
	OSTree();

	int traverse(Node* node,int* val); // val=0�� ���� �־� ��尡 ����� ���

	Node* getroot();
	//Node* IsKeyExist(Node* node,int key);
	Node* IsKeyExist_DEL(int key); //���°�� nullptr return, ������ �ش� ��� ������ return
	//�̴� Delete�������� ����Ͽ� size�� �پ��...
	//void Connect(Node* pnode,Node* dnode,Node* cnode,bool pleft); 
	//dnode�� �����Ǿ� pnode�� cnode�� �̾��� ��
	Node* findmin_DEL(Node* rnode); 
	//�̰͵� Delete�������� ���
	void show(Node* node);
	void Rotateleft(Node* node);
	void Rotateright(Node* node);
	int OSInsert(int key);
	void InsertHazard(Node* node);
	
	int OSDelete(int key);
	//void DeleteHazard(Node* dnode,Node* cnode, bool left = true);

	void Connectonly(Node* dnode, Node* cnode);

	void DeleteHazard(Node* xnode,Node* Pnode);

	int OSselect(Node* node,int i);

	int OSRank(Node* node, int key);
	
	//void DeleteHazard(Node* pnode, Node* cnode,int dcolor ,bool left);
	//left�� true�̸� ���� ��尡 �θ� ����� �����ڽ��� ���
	//cnode�� ������ ����� �ڽ� ���.. ������/�����ϼ��� �����Ƿ� ��������


private:
	Node* root;
	Node* leaf;
 };