#include "OSTree.h"

OSTree::OSTree() {
	//Black leafnode�� ����� �ش� �������0, �׸��� root = leaf
	//leaf�� parent�� ������ �ȵ�... ��� ����Ǿ� �־
	leaf = new Node();

	/// <summary>
	/// �̺κ� ������ ���� ���� ���� ������... ������ Ȯ���غ���
	leaf->setsize(0); //�������� size 0�� ����
	/// </summary>
	root = leaf;
}

Node* OSTree::getroot() {
	return root;
}

Node* OSTree::IsKeyExist_DEL(int key) {
	Node* cnode = root;
	while (cnode != leaf) {
		int Current = cnode->GetData();
		cnode->sizegrow(-1); //DEL�������� ���
		if (Current == key) {
			cnode->sizegrow(1); 
			//���� ��� ����� size�� ����... ������ delete�� �����
			return cnode;
		}
		else if (Current < key)
			cnode = cnode->getright();
		else
			cnode = cnode->getleft();
	}
	return nullptr;
}

void OSTree::Connect(Node* del, Node* rep) { //rep�� ���� ��ġ���� ���� �����Ǿ� ���;���
	if (del->getparent() == nullptr) {
		
	}
	/////////////

}

Node* OSTree::findmin_DEL(Node* rnode) {
	Node* cnode = rnode;
	Node* pnode = nullptr;
	while (cnode != leaf) {
		cnode->sizegrow(-1); //DEL�������� ���
		pnode = cnode;
		cnode = cnode->getleft();
	}
	return pnode;
}

void OSTree::show(Node* node) {
	if (node == leaf)
		return;
	show(node->getleft());
	int Color = node->GetColor();
	if (Color == BLACK)
		cout << "Black " << node->GetData() << endl;
	else
		cout << "Red " << node->GetData() << endl;
	show(node->getright());
}

void OSTree::Rotateleft(Node* node) {
	Node* cnode = node->getright();

	int size = node->GetSize();
	int size_1 = node->getleft()->GetSize();
	int size_2 = cnode->getleft()->GetSize();
	node->setsize(size_1 + size_2 + 1);
	cnode->setsize(size);


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

void OSTree::Rotateright(Node* node) {
	//Rotate Left�� ���� ������� ����
	Node* cnode = node->getleft();

	int size = node->GetSize();
	int size_1 = node->getright()->GetSize();
	int size_2 = cnode->getright()->GetSize();

	node->setsize(size_1 + size_2 + 1);
	cnode->setsize(size);

	node->setleft(cnode->getright());
	if (cnode->getright() != leaf) {
		(cnode->getright())->setparent(node);
	}
	cnode->setparent(node->getparent());
	if (node->getparent() == nullptr) {
		root = cnode;
	}
	else if (node == node->getparent()->getleft()) {
		node->getparent()->setleft(cnode);
	}
	else {
		node->getparent()->setright(cnode);
	}
	node->setparent(cnode);
	cnode->setright(node);
}

int OSTree::OSInsert(int key) {
	Node* cnode = root;
	Node* pnode = nullptr; 

	while (cnode != leaf) { //������ ��ġ�� ã�ư��� ����
		pnode = cnode; 
		//
		cnode->sizegrow(1); //��������� �� ����� size 1�� ����
		//
		int Current = cnode->GetData();
		if (Current == key) {
			printf("Key overalp\n");
			return 0; // �̹� �ִ� �����Ͻ� 0�� return
		}
		if (Current > key) {
			cnode = cnode->getleft();
		}
		else {
			cnode = cnode->getright();
		}
	}
	//�� while loop�� ������ �����ϴ� ���� size�� �ϳ��� ������

	Node* nnode = new Node(key, RED); //������ ���ο� ��� ����, ������ RED

	if (pnode == nullptr) { //�̹� ���Ұ� ó�� ���� ���
		nnode->setcolor(BLACK);
		root = nnode;
		//root�߰��ÿ��� leaf�� �������־�� ��
		nnode->setleft(leaf);
		nnode->setright(leaf);
		return key;  //ó�� �����ϴ� ���� ���⼭ �ٷ� ����
	}
	else if (key < (pnode->GetData())) {
		pnode->setleft(nnode);
		///
		nnode->setparent(pnode);
		nnode->setleft(leaf);
		nnode->setright(leaf);
		////////
		////////////
	}
	else {
		pnode->setright(nnode);

		nnode->setparent(pnode);
		nnode->setleft(leaf);
		nnode->setright(leaf);
	}

	if (pnode->getparent() == nullptr)
		return key;
	else
		InsertHazard(nnode); //���Խ� ����� ������ ���⼭ �ذ�
	
	return key;
}

//InsertHazard�� �ּ��� root��尡 �̹� ������ ���¿��� �����ϴ� case 
//��������� ó���ϴ� case�� �־ root��尡 �� ���� ����...
//��� ó�� case������ inode�� �ݵ�� ������ leafnode(��Ȯ���� leaf �ٷ� ��)�� ���� �ƴ�
void OSTree::InsertHazard(Node* inode) {
	if (inode == root) {
		//��������� �ö�� ��� ó���� ����!
		inode->setcolor(BLACK);
		return;
	}

	//���� ��������� �ö�Դµ� root�� �ڽ��� ���...? �� ���� ������ parent��
	//BLACK�̶� �ٷ� �Ʒ��� if���� ó����

	if (inode->getparent()->GetColor() == BLACK) {
		//inode->getparent()->sizegrow(1); �̴� �ʿ����... Insert���� ����
		//�׳� parent�� size�� ������Ű�� ���� �ذ�
	}
	//���� ����� �θ� red�� ��� �ش� �θ�� ���� root�� �ƴ�... root�� BLACK
	else {
		//if (inode->getparent() == root) �̷� ��� ����
		Node* pnode = inode->getparent();
		Node* ppnode = pnode->getparent();
		Node* snode;
		if (inode->getparent()->getparent()->getleft() == inode->getparent()) {
			//���Գ���� �θ��尡 p^2�� ���� �ڽ��� ���
			snode = inode->getparent()->getparent()->getright();

			///case 1 s�� red�� ��� (p�� s�� ��� red) �� ��� ����� �ذ�
			if (snode->GetColor() == RED) {
				pnode->setcolor(BLACK);
				snode->setcolor(BLACK);
				ppnode->setcolor(RED);
				InsertHazard(ppnode); // ppnode���� ��������� �ذ�
			}
			else {
				//case 2
				if (inode == pnode->getleft()) {
					//���� ��尡 �θ��� left�� ���
					//case 2-1
					Rotateright(ppnode);
					pnode->setcolor(BLACK);
					ppnode->setcolor(RED);
					/*size ����...
					int ppsize = ppnode->GetSize();
					int size_1 = pnode->getright()->GetSize();
					int size_2 = snode->GetSize();
					pnode->setsize(ppsize);
					ppnode->setsize(size_1 + size_2 + 1);*/
				}
				else {
					//���� ��尡 �θ��� right�� ���
					//case 2-1
					Rotateleft(pnode);
					/*size ����
					int psize = pnode->GetSize();
					int size_1 = pnode->getleft()->GetSize();
					int size_2 = inode->getleft()->GetSize();
					pnode->setsize(size_1 + size_2 + 1);
					inode->setsize(psize);*/

					//���� case 2-1�� ó���� ����
					Rotateright(ppnode);
					inode->setcolor(BLACK);
					ppnode->setcolor(RED);

					/*int ppsize = ppnode->GetSize();
					int size_3 = inode->getright()->GetSize();
					int size_4 = snode->GetSize();
					inode->setsize(ppsize);
					ppnode->setsize(size_3 + size_4 + 1);*/
					
				}
			}
		}
		else {
			//���Գ���� �θ��尡  p^2�� ������ �ڽ��� ���
			snode = ppnode->getleft();
			if (snode->GetColor() == RED) {
				pnode->setcolor(BLACK);
				snode->setcolor(BLACK);
				ppnode->setcolor(RED);
				InsertHazard(ppnode);
			}
			else if (snode->GetColor() == BLACK) {
				if (inode == pnode->getright()) {
					Rotateleft(ppnode);
					pnode->setcolor(BLACK);
					ppnode->setcolor(RED);
				}
				else {
					Rotateright(pnode);

					Rotateleft(ppnode);
					inode->setcolor(BLACK);
					ppnode->setcolor(RED);
				}
			}
		}

		

		
	}


}

int OSTree::OSDelete(int key) {
	Node* dnode = IsKeyExist_DEL(key);

	//Node* 

	if (dnode == nullptr) {
		return 0; // �ش� Ű�� �������� ����
	}
	else {
		if (dnode->getleft() != leaf && dnode->getright() != leaf) {
			//���� ��尡 �ΰ��� �ڽ��� ������ �ִ� ���
			Node* repnode = findmin_DEL(dnode->getright()); 
			// ���� ����� ������ ����Ʈ���� ���� ���� ���� ��� ������
			dnode->setdata(repnode->GetData());
			//���� ����� ����� key���� ��ü ����� data�� ��ü��
			//������ ���� ����� ��ü��� repnode��!
			DeleteHazard(repnode, repnode->getright());
		}
		else {  // �� ���� ��������� �ڽ��� 1���� 0��
			if (dnode == dnode->getparent()->getleft()) {
				if (dnode->getleft() != leaf) {
					DeleteHazard(dnode, dnode->getleft(), true);
				}
				else  {  //�� ���� getright()�� leaf�� ��쵵 ���Ե�!!!
					DeleteHazard(dnode, dnode->getright(), true);
				}
			}
				//DeleteHazard(dnode, , true);
			else { // ������尡 �� �θ����� ������ �ڽ�
				if (dnode->getleft() != leaf) {
					DeleteHazard(dnode, dnode->getleft(), false);
				}
				else
					DeleteHazard(dnode, dnode->getright(), false);
			}
				//DeleteHazard(dnode, false);
		}
	}
}

void OSTree::DeleteHazard(Node* dnode,Node* cnode , bool left) {
	if (left) { //������尡 �θ����� ���� �ڽ�
		if (dnode->GetColor() == RED) {

		}
	}
}