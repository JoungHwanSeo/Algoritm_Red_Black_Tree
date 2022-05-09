#include "OSTree.h"

OSTree::OSTree() {
	//Black leafnode를 만들고 해당 사이즈는0, 그리고 root = leaf
	//leaf는 parent가 있으면 안됨... 모두 연결되어 있어서
	leaf = new Node();

	/// <summary>
	/// 이부분 때문에 문제 생길 수도 있을듯... 디버깅시 확인해보기
	leaf->setsize(0); //리프노드는 size 0로 설정
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
		cnode->sizegrow(-1); //DEL과정에서 사용

		if (Current == key) {
			//cnode->sizegrow(1); 
			//자식이 두개인 경우 그 아래에서 다시 find하기 시작함...
			//즉 그대로 빼줘야함
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

/*void OSTree::Connect(Node* pnode, Node* dnode,Node* cnode, bool pleft) { //rep은 이전 위치에서 전부 독립되어 나와야함
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
}*/

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

void OSTree::Rotateright(Node* node) {
	//Rotate Left와 같은 방법으로 구현
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

	while (cnode != leaf) { //삽입할 위치를 찾아가는 과정
		pnode = cnode; 
		//
		cnode->sizegrow(1); //재귀적으로 각 노드의 size 1씩 증가
		//
		int Current = cnode->GetData();
		if (Current == key) {
			printf("Key overalp\n");
			return 0; // 이미 있는 원소일시 0을 return
		}
		if (Current > key) {
			cnode = cnode->getleft();
		}
		else {
			cnode = cnode->getright();
		}
	}
	//이 while loop이 끝나면 삽입하는 쪽의 size는 하나씩 증가됨

	Node* nnode = new Node(key, RED); //삽입할 새로운 노드 생성, 색깔은 RED

	if (pnode == nullptr) { //이번 원소가 처음 들어가는 경우
		nnode->setcolor(BLACK);
		root = nnode;
		//root추가시에도 leaf는 연결해주어야 함
		nnode->setleft(leaf);
		nnode->setright(leaf);
		return key;  //처음 삽입하는 경우는 여기서 바로 종료
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
		InsertHazard(nnode); //삽입시 생기는 문제를 여기서 해결
	
	return key;
}

//InsertHazard는 최소한 root노드가 이미 존재한 상태에서 삽입하는 case 
//재귀적으로 처리하는 case도 있어서 root노드가 올 수도 있음...
//재귀 처리 case때문에 inode가 반드시 마지막 leafnode(정확히는 leaf 바로 위)인 것은 아님
void OSTree::InsertHazard(Node* inode) {
	if (inode == root) {
		//재귀적으로 올라온 경우 처리를 위함!
		inode->setcolor(BLACK);
		return;
	}

	//만약 재귀적으로 올라왔는데 root의 자식인 경우...? 이 경우는 무조건 parent가
	//BLACK이라서 바로 아래의 if에서 처리됨

	if (inode->getparent()->GetColor() == BLACK) {
		//inode->getparent()->sizegrow(1); 이는 필요없음... Insert에서 구현
		//그냥 parent의 size만 증가시키면 문제 해결
	}
	//삽입 노드의 부모가 red인 경우 해당 부모는 절대 root가 아님... root는 BLACK
	else {
		//if (inode->getparent() == root) 이런 경우 없음
		Node* pnode = inode->getparent();
		Node* ppnode = pnode->getparent();
		Node* snode;
		if (inode->getparent()->getparent()->getleft() == inode->getparent()) {
			//삽입노드의 부모노드가 p^2의 왼쪽 자식인 경우
			snode = inode->getparent()->getparent()->getright();

			///case 1 s가 red인 경우 (p와 s가 모두 red) 이 경우 재귀적 해결
			if (snode->GetColor() == RED) {
				pnode->setcolor(BLACK);
				snode->setcolor(BLACK);
				ppnode->setcolor(RED);
				InsertHazard(ppnode); // ppnode에서 재귀적으로 해결
			}
			else {
				//case 2
				if (inode == pnode->getleft()) {
					//삽입 노드가 부모의 left인 경우
					//case 2-1
					Rotateright(ppnode);
					pnode->setcolor(BLACK);
					ppnode->setcolor(RED);
					/*size 조정...
					int ppsize = ppnode->GetSize();
					int size_1 = pnode->getright()->GetSize();
					int size_2 = snode->GetSize();
					pnode->setsize(ppsize);
					ppnode->setsize(size_1 + size_2 + 1);*/
				}
				else {
					//삽입 노드가 부모의 right인 경우
					//case 2-1
					Rotateleft(pnode);
					/*size 조정
					int psize = pnode->GetSize();
					int size_1 = pnode->getleft()->GetSize();
					int size_2 = inode->getleft()->GetSize();
					pnode->setsize(size_1 + size_2 + 1);
					inode->setsize(psize);*/

					//이후 case 2-1의 처리와 동일
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
			//삽입노드의 부모노드가  p^2의 오른쪽 자식인 경우
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

		///추가
		Node* pnode = dnode->getparent();
		///xnode가 leaf로 들어간 경우, parent를 찾을 수 없음...
		///추가

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

			pnode = repnode->getparent();
			//이 경우 pnode는 갱신

			dnode->setdata(repnode->GetData());
			//dnode의 key가 대체노드의 데이터로 대체됨
			//실질적 삭제는 repnode임

			xnode = repnode->getright();

			Connectonly(repnode, repnode->getright());

			dnode = repnode; //rep node가 삭제되어야 함

		}
		delete dnode;
		if (dcolor == BLACK) {
			if (xnode->GetColor() == RED) {
				xnode->setcolor(BLACK);
			}
			else //둘 다 BLACK인 경우만 DeleteHazard 호출
				DeleteHazard(xnode,pnode); //xnode는 leaf일수도 있음
		}

		root->setcolor(BLACK);
		//마지막에 루트 black

		return key;
	}

}

void OSTree::DeleteHazard(Node* xnode, Node* Pnode) {
	//xnode는 leaf일 수도 있음
	//삭제노드와 그 자식이 모두 BLACK인 경우만 호출되므로
	//s는 확실히 leaf가 아니고, l과 r은 leaf일 수 있어도 노드가 존재하긴 함
	Node* pnode = Pnode;

	Node* snode; // x의 형제노드
	Node* lnode;
	Node* rnode;
	while (pnode != nullptr) {

		//Node* pnode = xnode->getparent();
		int pcolor = pnode->GetColor();

		if (xnode == /*xnode->getparent()*/ pnode->getleft()) {
			//x노드가 부모의 왼쪽 자식인 경우


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

				//case 2로 이동

				continue; //xnode는 그대로임
			}
			else if (pcolor == BLACK && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 4
				snode->setcolor(RED);
				xnode = pnode;
				//추가
				pnode = pnode->getparent();
				//추가

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

int OSTree::OSselect(int i) {
	if
}

/*int OSTree::OSDelete(int key) {
	Node* dnode = IsKeyExist_DEL(key);

	//Node* 

	if (dnode == nullptr) {
		return 0; // 해당 키가 존재하지 않음
	}
	else {

		//여기서 Connect까지 하고, 그 뒤의 상황에서 Hazard처리 하기!!!

		if (dnode->getleft() != leaf && dnode->getright() != leaf) {
			//삭제 노드가 두개의 자식을 가지고 있는 경우
			Node* repnode = findmin_DEL(dnode->getright()); 
			// 삭제 노드의 오른쪽 서브트리서 가장 작은 값의 노드 포인터
			dnode->setdata(repnode->GetData());
			//삭제 대상의 노드의 key값만 대체 노드의 data로 대체됨
			//실질적 삭제 대상은 대체노드 repnode임!
			//DeleteHazard(repnode, repnode->getright());
			Connect(repnode->getparent(), repnode, repnode->getright(), true);
			DeleteHazard(repnode->getparent(), repnode->getright(), repnode->GetColor(), true);
			
			//디버깅시 유심히 보기
			delete repnode;

		}
		else {  // 이 경우는 삭제노드의 자식이 1개나 0개
			if (dnode == dnode->getparent()->getleft()) {
				if (dnode->getleft() != leaf) {
					

					Connect(dnode->getparent(), dnode, dnode->getleft(), true);
					DeleteHazard(dnode->getparent(), dnode->getleft(), dnode->GetColor(), true);
					//DeleteHazard(dnode, dnode->getleft(), true);
				}
				else  {  //이 경우는 getright()가 leaf인 경우도 포함됨!!!
					//DeleteHazard(dnode, dnode->getright(), true);
					//여기서 Connect하려면 삭제 노드가 자식을 가지고 있어야 함... 해당 조건 추가하기!!!!
				
					if (dnode->getright() == leaf) { //dnode가 자식을 갖지 않는 경우
						dnode->getparent()->setleft(leaf);
						Node* pnode = dnode->getparent();
						if(pnode == pnode->getparent()->getleft())
					}

					Connect(dnode->getparent(), dnode, dnode->getright(), true);
					DeleteHazard(dnode->getparent(), dnode->getright(), dnode->GetColor(), true);
				}
			}
				//DeleteHazard(dnode, , true);
			else { // 삭제노드가 그 부모노드의 오른쪽 자식
				if (dnode->getleft() != leaf) {
					//DeleteHazard(dnode, dnode->getleft(), false);
					Connect(dnode->getparent(), dnode, dnode->getleft(), false);
					DeleteHazard(dnode->getparent(), dnode->getleft(), dnode->GetColor(), false);
				}
				else {
					Connect(dnode->getparent(), dnode, dnode->getright(), false);
					DeleteHazard(dnode->getparent(), dnode->getright(), dnode->GetColor(), false);
					//DeleteHazard(dnode, dnode->getright(), false);
				}
					
			}
			//디버깅시 유심히 보기
			delete dnode;
				//DeleteHazard(dnode, false);
		}
	}
}

void OSTree::DeleteHazard(Node* pnode, Node* cnode, int dcolor, bool left) {
	if (left) {
		if (dcolor == RED) {
			//아무것도 할필요 없음
		}
		else {
			//삭제노드가 BLACK일시
			if (cnode->GetColor() == RED) {
				cnode->setcolor(BLACK);
			}
			else {
				//삭제노드와 그 자식 모두 BLACK
				Node* pnode = cnode->getparent();
				Node* snode = pnode->getright();
				Node* lnode = snode->getleft();
				Node* rnode = snode->getright();
				int pcolor = pnode->GetColor();
				int scolor = snode->GetColor();
				int lcolor = lnode->GetColor();
				int rcolor = rnode->GetColor();
				if (pcolor == RED && !snode && !lnode && !rnode) {
					//case 1
					//BLACK은 0... P만 red인 경우
					pnode->setcolor(BLACK);
					snode->setcolor(RED);
				}
				else if (scolor == BLACK && rcolor == RED) {
					//case 2
					Rotateleft(pnode);
					pnode->setcolor(scolor);
					snode->setcolor(pcolor);
					rnode->setcolor(BLACK);
				}
				else if (!scolor && lcolor && !rcolor) {
					//case 3
					Rotateright(snode);
					lnode->setcolor(scolor);
					snode->setcolor(lcolor);

					int changedscolor = lcolor;
					int changedlcolor = scolor;

					//여기서는 case 2와 같이 처리
					Rotateleft(pnode);
					pnode->setcolor(changedlcolor);
					lnode->setcolor(pcolor);
					snode->setcolor(BLACK);
				}
				else if (!pcolor && !scolor && !lcolor && !rcolor) {
					//case 4 전부 BLACK
					snode->setcolor(RED);
					//이 경우 dnode의 문제가 pnode로 올라감
					if (pnode == pnode->getparent()->getleft()) {
						//BLACK이어야 실질적 hazard처리가 가능
						DeleteHazard(pnode->getparent(), pnode, BLACK, true);
					}
					else {
						DeleteHazard(pnode->getparent(), pnode, BLACK, false);
					}
				}
				else {
					//case 5
					Rotateleft(pnode);
					pnode->setcolor(scolor);
					snode->setcolor(pcolor);
					//여기서 case1 ~3으로 이동한다.
					/////이게 맞나???
					DeleteHazard(pnode, cnode, BLACK, true);
				}
			}
		}
	}
	//delete 
}*/

/*void OSTree::DeleteHazard(Node* dnode,Node* cnode , bool left) {
	//delete dnode는 맨 마지막에 실행!!!!!!!!!!!
	int COLOR = dnode->GetColor();
	if (left) { //삭제노드가 부모노드의 왼쪽 자식
		Connect(dnode->getparent(), dnode, cnode, true);
		//일단 RB상관 없이 노드 삭제하고 이어줌
		if (COLOR == RED) {
			//아무것도 할 필요가 없음!
		}
		else { //삭제한 노드가 BLACK일시
			if (cnode->GetColor() == RED) {
				cnode->setcolor(BLACK);
			}
			else { //삭제노드와 그 자식노드가 모두 BLACK
				Node* pnode = cnode->getparent();
				Node* snode = pnode->getright();
				Node* lnode = snode->getleft();
				Node* rnode = snode->getright();
				int pcolor = pnode->GetColor();
				int scolor = snode->GetColor();
				int lcolor = lnode->GetColor();
				int rcolor = rnode->GetColor();
				if (pcolor == RED && !snode && !lnode && !rnode) {
					//case 1
					//BLACK은 0... P만 red인 경우
					pnode->setcolor(BLACK);
					snode->setcolor(RED);
				}
				else if (scolor == BLACK && rcolor == RED) {
					//case 2
					Rotateleft(pnode);
					pnode->setcolor(scolor);
					snode->setcolor(pcolor);
					rnode->setcolor(BLACK);
				}
				else if (!scolor && lcolor && !rcolor) {
					//case 3
					Rotateright(snode);
					lnode->setcolor(scolor);
					snode->setcolor(lcolor);
					
					int changedscolor = lcolor;
					int changedlcolor = scolor;

					//여기서는 case 2와 같이 처리
					Rotateleft(pnode);
					pnode->setcolor(changedlcolor);
					lnode->setcolor(pcolor);
					snode->setcolor(BLACK);
				}
				else if (!pcolor && !scolor && !lcolor && !rcolor) {
					//case 4 전부 BLACK
					snode->setcolor(RED);
					//이 경우 dnode의 문제가 pnode로 올라감
					if (pnode == pnode->getparent()->getright()) {

					}
				}
			}
		}
	}

	delete dnode;
}*/