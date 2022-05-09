#include "function.h"

Node* IsKeyExist(Node* node, int key) {
	Node* cnode = node;

	while (cnode->GetSize() != 0) {
		int current = cnode->GetData();
		if (current == key)
			return cnode;
		else if (current < key)
			cnode = cnode->getright();
		else
			cnode = cnode->getleft();
	}

	return nullptr; // 찾지 못한 경우
}