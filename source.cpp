#include "OSTree.h"
#include "fstream"
#include "string"
#include "Checker.h"

int main(void) {

	ifstream ifs("input.txt");
	ofstream ofs("output.txt");

	OSTree* tree = new OSTree;

	string read;
	int val;
	while (!ifs.eof()) {
		ifs >> read;
		ifs >> val;
		if (ifs.eof())
			break;
		ofs << read << " " << val << endl;
	}

	ifs.close();

	ifs.open("input.txt");

	while (!ifs.eof()) {  
		ifs >> read;
		ifs >> val;
		if (ifs.eof())
			break;
		if (read == "I")
			ofs << (tree->OSInsert(val)) << endl;
		else if (read == "D")
			ofs << (tree->OSDelete(val)) << endl;
		else if (read == "S")
			ofs << (tree->OSselect(tree->getroot(), val)) << endl;
		else
			ofs << (tree->OSRank(tree->getroot(), val)) << endl;
	}

	Checker("input.txt", "output.txt");

	ifs.close();
	ofs.close();


	/*for (int i = 1; i <= 100; i++) {
		//cout << tree->OSInsert(i) << endl;
		tree->OSInsert(i);
	}
	//tree->show(tree->getroot());

	for (int i = 11; i <= 20; i++) {
		tree->OSDelete(i);
		//tree->show(tree->getroot());
		//cout << "--------------------------" << endl << endl;

	}*/

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



