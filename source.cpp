#include "OSTree.h"


int main(void) {

	OSTree* tree = new OSTree;
	for (int i = 1; i <= 100; i++) {
		//cout << tree->OSInsert(i) << endl;
		tree->OSInsert(i);
	}
	//tree->show(tree->getroot());

	for (int i = 11; i <= 20; i++) {
		tree->OSDelete(i);
		//tree->show(tree->getroot());
		//cout << "--------------------------" << endl << endl;

	}

	//cout << tree->OSselect(tree->getroot(), 45);
	//for (int i = 1; i <= 20; i++)
	//	cout << tree->OSRank(tree->getroot(), i) << endl << endl;

	//tree->show(tree->getroot());

	/*for (int i = 3; 3 <= 5; i++) {
		tree->OSDelete(i);
	}
	tree->show(tree->getroot());*/

	//cout << tree->findmin(tree->getroot())->GetData();

}



