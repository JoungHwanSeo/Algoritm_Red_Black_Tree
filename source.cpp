#include "OSTree.h"


int main(void) {

	OSTree* tree = new OSTree;
	for (int i = 1; i <= 7; i++) {
		cout << tree->OSInsert(i) << endl;
	}

	//cout << tree->findmin(tree->getroot())->GetData();

}



Node* OSTree::IsKeyExist(int key) {
	Node* cnode = root;
	while (cnode != leaf) {
		int Current = cnode->GetData();
		if (Current == key)
			return cnode;
		else if (Current < key)
			cnode = cnode->getright();
		else
			cnode = cnode->getleft();
	}
	return nullptr;
}