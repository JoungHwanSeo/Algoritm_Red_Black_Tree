#include "OSTree.h"

OSTree::OSTree() {
	//Black leafnode를 만들고 해당 사이즈는0, 그리고 root = leaf
	//leaf는 parent가 있으면 안됨... 모두 연결되어 있어서
	leaf = new Node();
	leaf->setsize(0); //리프노드는 size 0로 설정
	root = leaf;
}

void OSTree::Rotateleft(Node* node) {
	Node* cnode = node->getright();
	node->setright(cnode->getleft());
	if (cnode->getleft() != leaf) {
		//leaf의 parent는 사실상 여러개 있으므로 leaf의 parent는 연결하면 안됨
		(cnode->getleft())->setparent(node);
	}
	cnode->setparent(node->getparent());
	if (node->getparent() == nullptr) {
		//node가 원래 root였다면 cnode가 root가 됨
		root = cnode;
	}
	else if (node == node->getparent()->getleft()) {
		//만약 node가 원래 parent의 left였다면
		node->getparent()->setleft(cnode);
	}
	else {
		node->getparent()->setright(cnode);
	}
	node->setparent(cnode);
	cnode->setleft(node);
}