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

void OSTree::Connect(Node* del, Node* rep) { //rep은 이전 위치에서 전부 독립되어 나와야함
	if (del->getparent() == nullptr) {
		
	}
	/////////////

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

int OSTree::OSDelete(int key) {
	Node* dnode = IsKeyExist_DEL(key);

	//Node* 

	if (dnode == nullptr) {
		return 0; // 해당 키가 존재하지 않음
	}
	else {
		if (dnode->getleft() != leaf && dnode->getright() != leaf) {
			//삭제 노드가 두개의 자식을 가지고 있는 경우
			Node* repnode = findmin_DEL(dnode->getright()); 
			// 삭제 노드의 오른쪽 서브트리서 가장 작은 값의 노드 포인터
			dnode->setdata(repnode->GetData());
			//삭제 대상의 노드의 key값만 대체 노드의 data로 대체됨
			//실질적 삭제 대상은 대체노드 repnode임!
			DeleteHazard(repnode, repnode->getright());
		}
		else {  // 이 경우는 삭제노드의 자식이 1개나 0개
			if (dnode == dnode->getparent()->getleft()) {
				if (dnode->getleft() != leaf) {
					DeleteHazard(dnode, dnode->getleft(), true);
				}
				else  {  //이 경우는 getright()가 leaf인 경우도 포함됨!!!
					DeleteHazard(dnode, dnode->getright(), true);
				}
			}
				//DeleteHazard(dnode, , true);
			else { // 삭제노드가 그 부모노드의 오른쪽 자식
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
	if (left) { //삭제노드가 부모노드의 왼쪽 자식
		if (dnode->GetColor() == RED) {

		}
	}
}