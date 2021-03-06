#include "OSTree.h"

Node* OSTree::IsKeyExist_DEL(int key) {
	Node* cnode = root;
	while (cnode != leaf) {
		int Current = cnode->GetData();
		cnode->sizegrow(-1); //DEL引舛拭辞 紫遂
		if (Current == key) {
			cnode->sizegrow(1);
			//肢薦 企雌 葛球税 size澗 政走... 嬢託杷 delete吃 葛球績
			return cnode;
		}
		else if (Current < key)
			cnode = cnode->getright();
		else
			cnode = cnode->getleft();
	}
	return nullptr;
}

void OSTree::Connect(Node* pnode, Node* dnode, Node* cnode, bool pleft) { //rep精 戚穿 是帖拭辞 穿採 偽験鞠嬢 蟹人醤敗
	//Node* byenode = dnode;
	if (cnode != leaf) {
		if (pleft) {
			pnode->setleft(cnode);
			cnode->setparent(pnode);
		}
		else {
			pnode->setright(cnode);
			cnode->setparent(pnode);
		}
	}
	else { // dnode亜 叔霜旋 軒覗葛球昔 井酔
		if (pleft) {
			pnode->setleft(leaf);
		}
		else {
			pnode->setright(leaf);
		}
	}
	//delete dnode;
}

Node* OSTree::findmin_DEL(Node* rnode) {
	Node* cnode = rnode;
	Node* pnode = nullptr;
	while (cnode != leaf) {
		cnode->sizegrow(-1); //DEL引舛拭辞 紫遂
		pnode = cnode;
		cnode = cnode->getleft();
	}
	return pnode;
}

//////////////////////////

void OSTree::Connectonly(Node* dnode, Node* cnode) {
	if (cnode != leaf) {  //聡 dnode亜 溌叔備 切縦 馬蟹 亜走澗 井酔
		if (dnode->getparent() == nullptr) //欠闘昔 井酔拭亀 肢薦葛球澗 廃鯵税 切縦幻 亜像....
			root = cnode;
		else if (dnode == dnode->getparent()->getleft())
			dnode->getparent()->setleft(cnode);
		else
			dnode->getparent()->setright(cnode);

		cnode->setparent(dnode->getparent());
	}
	else {
		if (dnode->getparent() == nullptr)
			root = cnode; //焼巷 汽戚斗亀 蒸澗 井酔... 段奄鉢
		else if (dnode == dnode->getparent()->getleft())
			dnode->getparent()->setleft(cnode);
		else
			dnode->getparent()->setright(cnode);
	}
}


int OSTree::OSDelete(int key) {
	Node* dnode = IsKeyExist_DEL(key);

	if (dnode == nullptr) //背雁 徹亜 糎仙馬走 省製
		return 0;
	else {
		int dcolor = dnode->GetColor();

		Node* xnode; 

		///切縦戚 蒸暗蟹 1鯵昔 井酔
		//切縦戚 焼森 蒸澗 井酔澗 xnode研 廃牒 是稽 臣形醤敗
		//焼観牛 せせせせせせ
		//戚係惟 背醤 l引 r亀 leaf亜 焼観 葛球績聖 左舌拝 呪 赤製...
		/////焼艦虞壱 せせせせせせせせせせ

		/*if (dnode->getleft() == leaf && dnode->getright() == leaf) {
			Connectonly(dnode, dnode->getleft());
		}
		else if (dnode->getleft() == leaf && dnode->getright() != leaf) {
			xnode = dnode->getright();
			Connectonly(dnode, dnode->getright());
		}
		else if (dnode->getleft() != leaf && dnode->getright() == leaf) {
			xnode = dnode->getleft();
			Connectonly(dnode, dnode->getleft());
		}
		else {
			//切縦戚 砧鯵昔 井酔
		}*/

		if (dnode->getleft() == leaf) {
			xnode = dnode->getright();
			Connectonly(dnode, dnode->getright());
			//切縦戚 蒸澗 井酔亀 ConnectOnly拭辞 朕獄敗
		}
		else if (dnode->getright() == leaf) {
			xnode = dnode->getleft();
			Connectonly(dnode, dnode->getleft());
		}
		else { // 切縦戚 砧鯵昔 井酔
			Node* repnode; // 叔霜旋 肢薦 企雌 葛球
			repnode = findmin_DEL(dnode->getright());
			dcolor = repnode->GetColor();

			dnode->setdata(repnode->GetData());
			//dnode税 key亜 企端葛球税 汽戚斗稽 企端喫
			//叔霜旋 肢薦澗 repnode績

			xnode = repnode->getright();

			Connectonly(repnode, repnode->getright());

		}
		delete dnode;
		if (dcolor == BLACK) {
			if (xnode->GetColor() == RED) {
				xnode->setcolor(BLACK);
			}
			else //却 陥 BLACK昔 井酔幻 DeleteHazard 硲窒
				DeleteHazard(xnode); //xnode澗 leaf析呪亀 赤製
		}

		root->setcolor(BLACK);
		//原走厳拭 欠闘 black
	}

}

void OSTree::DeleteHazard(Node* xnode) {
	//xnode澗 leaf析 呪亀 赤製
	//肢薦葛球人 益 切縦戚 乞砧 BLACK昔 井酔幻 硲窒鞠糠稽
	//s澗 溌叔備 leaf亜 焼艦壱, l引 r精 leaf析 呪 赤嬢亀 葛球亜 糎仙馬延 敗
	Node* snode; // x税 莫薦葛球
	Node* lnode;
	Node* rnode;
	while (xnode != root) {

		Node* pnode = xnode->getparent();
		int pcolor = pnode->GetColor();

		if (xnode == xnode->getparent()->getleft()) {
			//x葛球亜 採乞税 図楕 切縦昔 井酔


			snode = xnode->getparent()->getright();
			lnode = snode->getleft();
			rnode = snode->getright();
			//pnode = xnode->getparent();
			int scolor = snode->GetColor();
			int lcolor = lnode->GetColor();
			int rcolor = rnode->GetColor();
			//int pcolor = pnode->GetColor();


			if (pcolor == RED && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 1
				pnode->setcolor(BLACK);
				snode->setcolor(RED);
				break;
			}
			else if (scolor == BLACK && rcolor == RED) {
				//case 2
				Rotateleft(pnode);
				pnode->setcolor(scolor);
				snode->setcolor(pcolor);
				rnode->setcolor(BLACK);
				break;
			}
			else if (scolor == BLACK && lcolor == RED && rcolor == BLACK) {
				//case 3
				Rotateright(snode);
				lnode->setcolor(BLACK);
				snode->setcolor(RED);

				//case 2稽 戚疑

				continue; //xnode澗 益企稽績
			}
			else if (pcolor == BLACK && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 4
				snode->setcolor(RED);
				xnode = pnode;
				//仙瑛 鋼差... 戚腰殖 pnode亜 庚薦
				continue;
			}
			else {
				Rotateleft(pnode);
				pnode->setcolor(RED);
				snode->setcolor(BLACK);

				continue;
			}
		}
		else {
			//x葛球亜 採乞税 神献楕 切縦昔 井酔


			snode = xnode->getparent()->getleft();
			lnode = snode->getleft();
			rnode = snode->getright();
			//pnode = xnode->getparent();
			int scolor = snode->GetColor();
			int lcolor = lnode->GetColor();
			int rcolor = rnode->GetColor();

			if (pcolor == RED && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 1
				pnode->setcolor(BLACK);
				snode->setcolor(RED);
				break;
			}
			else if (scolor == BLACK && rcolor == RED) {
				//case 2
				Rotateright(pnode);
				pnode->setcolor(scolor);
				snode->setcolor(pcolor);
				rnode->setcolor(BLACK);
				break;
			}
			else if (scolor == BLACK && lcolor == RED && rcolor == BLACK) {
				//case 3
				Rotateleft(snode);
				lnode->setcolor(BLACK);
				snode->setcolor(RED);
				//庚薦葛球澗 食穿備 x
				continue;
			}
			else if (pcolor == BLACK && scolor == BLACK && lcolor == BLACK && rcolor == BLACK) {
				//case 4
				snode->setcolor(RED);
				xnode = pnode;
				continue;
			}
			else {
				//case 5
				Rotateright(pnode);
				pnode->setcolor(RED);
				snode->setcolor(BLACK);
				continue;
			}
		}
	}
}