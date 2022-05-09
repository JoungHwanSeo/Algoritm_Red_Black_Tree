#include "OSTree.h"

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

void OSTree::Connect(Node* pnode, Node* dnode, Node* cnode, bool pleft) { //rep�� ���� ��ġ���� ���� �����Ǿ� ���;���
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

//////////////////////////

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
	Node* dnode = IsKeyExist_DEL(key);

	if (dnode == nullptr) //�ش� Ű�� �������� ����
		return 0;
	else {
		int dcolor = dnode->GetColor();

		Node* xnode; 

		///�ڽ��� ���ų� 1���� ���
		//�ڽ��� �ƿ� ���� ���� xnode�� ��ĭ ���� �÷�����
		//�ƴѵ� ������������
		//�̷��� �ؾ� l�� r�� leaf�� �ƴ� ������� ������ �� ����...
		/////�ƴ϶�� ��������������������

		/*if (dnode->getleft() == leaf && dnode->getright() == leaf) {
			Connectonly(dnode, dnode->getleft());
		}
		else if (dnode->getleft() == leaf && dnode->getright() != leaf) {
			xnode = dnode->getright();
			Connectonly(dnode, dnode->getright());
		}
		else if (dnode->getleft() != leaf && dnode->getright() == leaf) {
			xnode = dnode->getleft();
			Connectonly(dnode, dnode->getleft());
		}
		else {
			//�ڽ��� �ΰ��� ���
		}*/

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

			dnode->setdata(repnode->GetData());
			//dnode�� key�� ��ü����� �����ͷ� ��ü��
			//������ ������ repnode��

			xnode = repnode->getright();

			Connectonly(repnode, repnode->getright());

		}
		delete dnode;
		if (dcolor == BLACK) {
			if (xnode->GetColor() == RED) {
				xnode->setcolor(BLACK);
			}
			else //�� �� BLACK�� ��츸 DeleteHazard ȣ��
				DeleteHazard(xnode); //xnode�� leaf�ϼ��� ����
		}

		root->setcolor(BLACK);
		//�������� ��Ʈ black
	}

}

void OSTree::DeleteHazard(Node* xnode) {
	//xnode�� leaf�� ���� ����
	//�������� �� �ڽ��� ��� BLACK�� ��츸 ȣ��ǹǷ�
	//s�� Ȯ���� leaf�� �ƴϰ�, l�� r�� leaf�� �� �־ ��尡 �����ϱ� ��
	Node* snode; // x�� �������
	Node* lnode;
	Node* rnode;
	while (xnode != root) {

		Node* pnode = xnode->getparent();
		int pcolor = pnode->GetColor();

		if (xnode == xnode->getparent()->getleft()) {
			//x��尡 �θ��� ���� �ڽ��� ���


			snode = xnode->getparent()->getright();
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


			snode = xnode->getparent()->getleft();
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
			else if (scolor == BLACK && rcolor == RED) {
				//case 2
				Rotateright(pnode);
				pnode->setcolor(scolor);
				snode->setcolor(pcolor);
				rnode->setcolor(BLACK);
				break;
			}
			else if (scolor == BLACK && lcolor == RED && rcolor == BLACK) {
				//case 3
				Rotateleft(snode);
				lnode->setcolor(BLACK);
				snode->setcolor(RED);
				//�������� ������ x
				continue;
			}
			else if (pcolor == BLACK && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 4
				snode->setcolor(RED);
				xnode = pnode;
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