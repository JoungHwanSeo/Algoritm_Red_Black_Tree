#include <filesystem>
#include "OSTree.h"
#include "fstream"
#include "string"
#include "Checker.h"


int main(void) {



	string inputf = "input.txt";

	ifstream ifs(inputf);
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

	ifs.open(inputf);

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

	Checker(inputf, "output.txt");

	ifs.close();
	ofs.close();
	delete tree;

}



