#pragma once
#include "TreeNode.h"
#include "function.h"



class OSTree {
public:
	OSTree();

	int traverse(Node* node,int* val); // val=0인 값을 넣어 노드가 몇개인지 계산

	Node* getroot();
	//Node* IsKeyExist(Node* node,int key);
	Node* IsKeyExist_DEL(int key); //없는경우 nullptr return, 있으면 해당 노드 포인터 return
	//이는 Delete과정에서 사용하여 size가 줄어듦...
	//void Connect(Node* pnode,Node* dnode,Node* cnode,bool pleft); 
	//dnode가 삭제되어 pnode와 cnode가 이어질 때
	Node* findmin_DEL(Node* rnode); 
	//이것도 Delete과정에서 사용
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
	//left가 true이면 삭제 노드가 부모 노드의 왼쪽자식인 경우
	//cnode는 삭제할 노드의 자식 노드.. 오른쪽/왼쪽일수도 있으므로 지정해줌


private:
	Node* root;
	Node* leaf;
 };