#include "OSTree.h"


int main(void) {

	OSTree* tree = new OSTree;
	for (int i = 1; i <= 7; i++) {
		cout << tree->OSInsert(i) << endl;
	}

	for (int i = 3; 3 <= 5; i++) {
		tree->OSDelete(i);
	}
	tree->show(tree->getroot());

	//cout << tree->findmin(tree->getroot())->GetData();

}



