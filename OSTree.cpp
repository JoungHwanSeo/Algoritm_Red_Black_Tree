#include "OSTree.h"

OSTree::OSTree() {
	//Black leafnode�� ����� �ش� �������0, �׸��� root = leaf
	//leaf�� parent�� ������ �ȵ�... ��� ����Ǿ� �־
	leaf = new Node();

	leaf->setsize(0); //�������� size 0�� ����
	/// </summary>
	root = leaf;
}

int OSTree::traverse(Node* node, int* val) {
	Node* cnode = node;
	if (cnode == leaf)
		return *val;
	traverse(cnode->getleft(), val);
	(*val)++;
	traverse(cnode->getright(), val);
	return *val;
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
			//cnode->sizegrow(1); 
			//�ڽ��� �ΰ��� ��� �� �Ʒ����� �ٽ� find�ϱ� ������...
			//�� �״�� �������
			//cout << "Key " << cnode->GetColor() << "  " << cnode->GetData() << endl;
			return cnode;
		}
		else if (Current < key)
			cnode = cnode->getright();
		else
			cnode = cnode->getleft();
	}
	//cout << "Not Found" << endl;
	return nullptr;
}

/*void OSTree::Connect(Node* pnode, Node* dnode,Node* cnode, bool pleft) { //rep�� ���� ��ġ���� ���� �����Ǿ� ���;���
	//Node* byenode = dnode;
	if (cnode != leaf) {
		if (pleft) {
			pnode->setleft(cnode);
			cnode->setparent(pnode);
		}
		else {
			pnode->setright(cnode);
			cnode->setparent(pnode);
		}
	}
	else { // dnode�� ������ ��������� ���
		if (pleft) {
			pnode->setleft(leaf);
		}
		else {
			pnode->setright(leaf);
		}
	}
	//delete dnode;
}*/

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

	bool InsertSucess = true;

	//�켱 �����Ͱ� �̸� �ִ��� Ȯ��

	//cnode�� leaf, �� �ƹ� �����͵� ���� ��� InsertSucess�� true��.
	while (cnode != leaf) { //������ ��ġ�� ã�ư��� ����
		pnode = cnode;
		//
		//cnode->sizegrow(1); //��������� �� ����� size 1�� ����
		//
		int Current = cnode->GetData();
		if (Current == key) {
			//printf("Key overalp\n");
			//return 0; // �̹� �ִ� �����Ͻ� 0�� return
			InsertSucess = false;
			break;
		}
		else if (Current > key) {
			cnode = cnode->getleft();
		}
		else {
			cnode = cnode->getright();
		}
	}

	cnode = root;
	pnode = nullptr;

	if (!InsertSucess)
		return 0; // �ߺ��� ���� ����
	else {
		while (cnode != leaf) { //������ ��ġ�� ã�ư��� ����
			pnode = cnode;
			//
			cnode->sizegrow(1); //��������� �� ����� size 1�� ����
			//
			int Current = cnode->GetData();
			//�ش� else�� ������ Current == key�� ���� ����
			if (Current > key) {
				cnode = cnode->getleft();
			}
			else {
				cnode = cnode->getright();
			}
		}
	}

	while (cnode != leaf) { //������ ��ġ�� ã�ư��� ����
		pnode = cnode; 
		//
		cnode->sizegrow(1); //��������� �� ����� size 1�� ����
		//
		int Current = cnode->GetData();
		if (Current == key) {
			//printf("Key overalp\n");
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
	
	return key; //���� �� ������ Tree�� �ƹ��͵� ������ 
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

void OSTree::Connectonly(Node* dnode, Node* cnode) {
	if (cnode != leaf) {  //�� dnode�� Ȯ���� �ڽ� �ϳ� ������ ���
		if (dnode->getparent() == nullptr) //��Ʈ�� ��쿡�� �������� �Ѱ��� �ڽĸ� ����....
			root = cnode;
		else if (dnode == dnode->getparent()->getleft())
			dnode->getparent()->setleft(cnode);
		else
			dnode->getparent()->setright(cnode);

		cnode->setparent(dnode->getparent());
	}
	else {
		if (dnode->getparent() == nullptr)
			root = cnode; //�ƹ� �����͵� ���� ���... �ʱ�ȭ
		else if (dnode == dnode->getparent()->getleft())
			dnode->getparent()->setleft(cnode);
		else
			dnode->getparent()->setright(cnode);

	}
}

int OSTree::OSDelete(int key) {

	bool DeleteSuccess = false;

	Node* tmpnode = root;

	while (tmpnode != leaf) {
		int Current = tmpnode->GetData();

		if (Current == key) {
			DeleteSuccess = true; // key�� ã�ƾ� ��μ� true
			break;
		}
		else if (Current < key)
			tmpnode = tmpnode->getright();
		else
			tmpnode = tmpnode->getleft();
	}
	//cout << "Not Found" << endl;

	Node* dnode;

	if (!DeleteSuccess) //���� ����� ���� ���
		return 0;
	else {  //���� ����� �ִ� ���
		dnode = IsKeyExist_DEL(key);  //�̰ɷ� size������
		if (dnode == nullptr) //�ش� Ű�� �������� ����
			return 0;  //��� ����� ���� ���� ����..
		else {
			int dcolor = dnode->GetColor();

			Node* xnode;

			///�߰�
			Node* pnode = dnode->getparent();
			///xnode�� leaf�� �� ���, parent�� ã�� �� ����...

			if (dnode->getleft() == leaf) {
				xnode = dnode->getright();
				Connectonly(dnode, dnode->getright());
				//�ڽ��� ���� ��쵵 ConnectOnly���� Ŀ����
			}
			else if (dnode->getright() == leaf) {
				xnode = dnode->getleft();
				Connectonly(dnode, dnode->getleft());
			}
			else { // �ڽ��� �ΰ��� ���
				Node* repnode; // ������ ���� ��� ���
				repnode = findmin_DEL(dnode->getright());
				dcolor = repnode->GetColor();

				pnode = repnode->getparent();
				//�� ��� pnode�� ����

				dnode->setdata(repnode->GetData());
				//dnode�� key�� ��ü����� �����ͷ� ��ü��
				//������ ������ repnode��

				xnode = repnode->getright();

				Connectonly(repnode, repnode->getright());

				dnode = repnode; //rep node�� �����Ǿ�� ��

			}
			delete dnode;
			if (dcolor == BLACK) {
				if (xnode->GetColor() == RED) {
					xnode->setcolor(BLACK);
				}
				else //�� �� BLACK�� ��츸 DeleteHazard ȣ��
					DeleteHazard(xnode, pnode); //xnode�� leaf�ϼ��� ����
			}

			root->setcolor(BLACK);
			//�������� ��Ʈ black

			return key;
		}
	}
		
	
}

void OSTree::DeleteHazard(Node* xnode, Node* Pnode) {
	//xnode�� leaf�� ���� ����
	//�������� �� �ڽ��� ��� BLACK�� ��츸 ȣ��ǹǷ�
	//s�� Ȯ���� leaf�� �ƴϰ�, l�� r�� leaf�� �� �־ ��尡 �����ϱ� ��
	Node* pnode = Pnode;

	Node* snode; // x�� �������
	Node* lnode;
	Node* rnode;
	while (pnode != nullptr) {

		//Node* pnode = xnode->getparent();
		int pcolor = pnode->GetColor();

		if (xnode == /*xnode->getparent()*/ pnode->getleft()) {
			//x��尡 �θ��� ���� �ڽ��� ���


			//snode = xnode->getparent()->getright();
			snode = pnode->getright();
			lnode = snode->getleft();
			rnode = snode->getright();
			//pnode = xnode->getparent();
			int scolor = snode->GetColor();
			int lcolor = lnode->GetColor();
			int rcolor = rnode->GetColor();
			//int pcolor = pnode->GetColor();


			if (pcolor == RED && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 1
				pnode->setcolor(BLACK);
				snode->setcolor(RED);
				break;
			}
			else if (scolor == BLACK && rcolor == RED) {
				//case 2
				Rotateleft(pnode);
				pnode->setcolor(scolor);
				snode->setcolor(pcolor);
				rnode->setcolor(BLACK);
				break;
			}
			else if (scolor == BLACK && lcolor == RED && rcolor == BLACK) {
				//case 3
				Rotateright(snode);
				lnode->setcolor(BLACK);
				snode->setcolor(RED);

				//case 2�� �̵�

				continue; //xnode�� �״����
			}
			else if (pcolor == BLACK && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 4
				snode->setcolor(RED);
				xnode = pnode;
				//�߰�
				pnode = pnode->getparent();
				//�߰�

				//��� �ݺ�... �̹��� pnode�� ����
				continue;
			}
			else {
				Rotateleft(pnode);
				pnode->setcolor(RED);
				snode->setcolor(BLACK);

				continue;
			}
		}
		else {
			//x��尡 �θ��� ������ �ڽ��� ���


			//snode = xnode->getparent()->getleft();
			snode = pnode->getleft();
			lnode = snode->getleft();
			rnode = snode->getright();
			//pnode = xnode->getparent();
			int scolor = snode->GetColor();
			int lcolor = lnode->GetColor();
			int rcolor = rnode->GetColor();

			if (pcolor == RED && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 1
				pnode->setcolor(BLACK);
				snode->setcolor(RED);
				break;
			}
			else if (scolor == BLACK && lcolor == RED) {
				//case 2
				Rotateright(pnode);
				pnode->setcolor(scolor);
				snode->setcolor(pcolor);
				lnode->setcolor(BLACK);
				break;
			}
			///�����غ��� ��Ī�� ��� l�� r�� ���� ���ǵ� �ٲ��� �ϳ� ����
			else if (scolor == BLACK && rcolor == RED && lcolor == BLACK) {
				//case 3
				Rotateleft(snode);
				rnode->setcolor(BLACK);
				snode->setcolor(RED);
				//�������� ������ x
				continue;
			}
			else if (pcolor == BLACK && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 4
				snode->setcolor(RED);
				xnode = pnode;

				pnode = pnode->getparent();

				continue;
			}
			else {
				//case 5
				Rotateright(pnode);
				pnode->setcolor(RED);
				snode->setcolor(BLACK);
				continue;
			}
		}
	}
}

int OSTree::OSselect(Node* node,int i) {
	if (node->GetSize() < i)
		return 0;
	else {
		//i�� tree�� �ִ� �������� ���� ������ ��
		int order = node->getleft()->GetSize() + 1;
		//�ش� ���(����Ʈ���� ��Ʈ)�� Ʈ������ ���°�� ������
		if (i == order)
			return node->GetData();
		else if (i < order)
			return OSselect(node->getleft(), i);
		else
			return OSselect(node->getright(), i - order);
	}
}

int OSTree::OSRank(Node* node, int key) {
	Node* fnode = IsKeyExist(node, key);
	if (fnode == nullptr)
		return 0;
	else {
		int order = fnode->getleft()->GetSize() + 1;
		Node* tmpnode = fnode;
		while (tmpnode != root) {
			if (tmpnode == tmpnode->getparent()->getright())
				order = order + tmpnode->getparent()->getleft()->GetSize() + 1;
			tmpnode = tmpnode->getparent();
		}
		return order;
	}
}
