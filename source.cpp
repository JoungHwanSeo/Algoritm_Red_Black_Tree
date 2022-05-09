#include "OSTree.h"


int main(void) {

	OSTree* tree = new OSTree;
	for (int i = 1; i <= 10; i++) {
		cout << tree->OSInsert(i) << endl;
	}
	//tree->show(tree->getroot());

	for (int i = 4; i <= 7; i++) {
		tree->OSDelete(i);
		//tree->show(tree->getroot());
		//cout << "--------------------------" << endl << endl;

	}

	tree->show(tree->getroot());

	/*for (int i = 3; 3 <= 5; i++) {
		tree->OSDelete(i);
	}
	tree->show(tree->getroot());*/

	//cout << tree->findmin(tree->getroot())->GetData();

}



