#include "OSTree.h"


int main(void) {

	OSTree* tree = new OSTree;
	for (int i = 1; i <= 7; i++) {
		cout << tree->OSInsert(i) << endl;
	}

	tree->show(tree->getroot());

}


