#include "OSTree.h"
using namespace std;

int main(void) {
	OSTree* tree = new OSTree;
	for (int i = 0; i < 10; i++) {
		cout << tree->OSInsert(i) << endl;
	}

}