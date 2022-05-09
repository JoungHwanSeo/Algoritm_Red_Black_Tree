#include "OSTree.h"

Node* OSTree::IsKeyExist_DEL(int key) {
	Node* cnode = root;
	while (cnode != leaf) {
		int Current = cnode->GetData();
		cnode->sizegrow(-1); //DEL과정에서 사용
		if (Current == key) {
			cnode->sizegrow(1);
			//삭제 대상 노드의 size는 유지... 어차피 delete될 노드임
			return cnode;
		}
		else if (Current < key)
			cnode = cnode->getright();
		else
			cnode = cnode->getleft();
	}
	return nullptr;
}

void OSTree::Connect(Node* pnode, Node* dnode, Node* cnode, bool pleft) { //rep은 이전 위치에서 전부 독립되어 나와야함
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
	else { // dnode가 실질적 리프노드인 경우
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
		cnode->sizegrow(-1); //DEL과정에서 사용
		pnode = cnode;
		cnode = cnode->getleft();
	}
	return pnode;
}

//////////////////////////

void OSTree::Connectonly(Node* dnode, Node* cnode) {
	if (cnode != leaf) {  //즉 dnode가 확실히 자식 하나 가지는 경우
		if (dnode->getparent() == nullptr) //루트인 경우에도 삭제노드는 한개의 자식만 가짐....
			root = cnode;
		else if (dnode == dnode->getparent()->getleft())
			dnode->getparent()->setleft(cnode);
		else
			dnode->getparent()->setright(cnode);

		cnode->setparent(dnode->getparent());
	}
	else {
		if (dnode->getparent() == nullptr)
			root = cnode; //아무 데이터도 없는 경우... 초기화
		else if (dnode == dnode->getparent()->getleft())
			dnode->getparent()->setleft(cnode);
		else
			dnode->getparent()->setright(cnode);
	}
}


int OSTree::OSDelete(int key) {
	Node* dnode = IsKeyExist_DEL(key);

	if (dnode == nullptr) //해당 키가 존재하지 않음
		return 0;
	else {
		int dcolor = dnode->GetColor();

		Node* xnode; 

		///자식이 없거나 1개인 경우
		//자식이 아예 없는 경우는 xnode를 한칸 위로 올려야함
		//아닌듯 ㅋㅋㅋㅋㅋㅋ
		//이렇게 해야 l과 r도 leaf가 아닌 노드임을 보장할 수 있음...
		/////아니라고 ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ

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
			//자식이 두개인 경우
		}*/

		if (dnode->getleft() == leaf) {
			xnode = dnode->getright();
			Connectonly(dnode, dnode->getright());
			//자식이 없는 경우도 ConnectOnly에서 커버함
		}
		else if (dnode->getright() == leaf) {
			xnode = dnode->getleft();
			Connectonly(dnode, dnode->getleft());
		}
		else { // 자식이 두개인 경우
			Node* repnode; // 실질적 삭제 대상 노드
			repnode = findmin_DEL(dnode->getright());
			dcolor = repnode->GetColor();

			dnode->setdata(repnode->GetData());
			//dnode의 key가 대체노드의 데이터로 대체됨
			//실질적 삭제는 repnode임

			xnode = repnode->getright();

			Connectonly(repnode, repnode->getright());

		}
		delete dnode;
		if (dcolor == BLACK) {
			if (xnode->GetColor() == RED) {
				xnode->setcolor(BLACK);
			}
			else //둘 다 BLACK인 경우만 DeleteHazard 호출
				DeleteHazard(xnode); //xnode는 leaf일수도 있음
		}

		root->setcolor(BLACK);
		//마지막에 루트 black
	}

}

void OSTree::DeleteHazard(Node* xnode) {
	//xnode는 leaf일 수도 있음
	//삭제노드와 그 자식이 모두 BLACK인 경우만 호출되므로
	//s는 확실히 leaf가 아니고, l과 r은 leaf일 수 있어도 노드가 존재하긴 함
	Node* snode; // x의 형제노드
	Node* lnode;
	Node* rnode;
	while (xnode != root) {

		Node* pnode = xnode->getparent();
		int pcolor = pnode->GetColor();

		if (xnode == xnode->getparent()->getleft()) {
			//x노드가 부모의 왼쪽 자식인 경우


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

				//case 2로 이동

				continue; //xnode는 그대로임
			}
			else if (pcolor == BLACK && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 4
				snode->setcolor(RED);
				xnode = pnode;
				//재귀 반복... 이번엔 pnode가 문제
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
			//x노드가 부모의 오른쪽 자식인 경우


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
				//문제노드는 여전히 x
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