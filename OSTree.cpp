#include "OSTree.h"

OSTree::OSTree() {
	//Black leafnode�� ����� �ش� �������0, �׸��� root = leaf
	//leaf�� parent�� ������ �ȵ�... ��� ����Ǿ� �־
	leaf = new Node();
	leaf->setsize(0); //�������� size 0�� ����
	root = leaf;
}

void OSTree::Rotateleft(Node* node) {
	Node* cnode = node->getright();
	node->setright(cnode->getleft());
	if (cnode->getleft() != leaf) {
		//leaf�� parent�� ��ǻ� ������ �����Ƿ� leaf�� parent�� �����ϸ� �ȵ�
		(cnode->getleft())->setparent(node);
	}
	cnode->setparent(node->getparent());
	if (node->getparent() == nullptr) {
		//node�� ���� root���ٸ� cnode�� root�� ��
		root = cnode;
	}
	else if (node == node->getparent()->getleft()) {
		//���� node�� ���� parent�� left���ٸ�
		node->getparent()->setleft(cnode);
	}
	else {
		node->getparent()->setright(cnode);
	}
	node->setparent(cnode);
	cnode->setleft(node);
}