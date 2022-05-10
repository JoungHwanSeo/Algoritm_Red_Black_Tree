#include "Checker.h"

void Checker(string inputfile, string outputfile) {
	ifstream inifs(inputfile);
	ifstream outifs(outputfile);
	ofstream ofs("checker.txt");

	set<int> container;

	string func;
	string ofunc;
	int val;
	int oval;

	string result;
	string T = "True";
	string F = "False";

	OSTree* checktree = new OSTree;

	//int instnum = 0; // ��ɾ� ����
	//int* arr; // ����� array

	while (1) {
		inifs >> func;
		inifs >> val;
		//if (func == "I")
		//	instnum++;
		if (inifs.eof())
			break;
		outifs >> ofunc;
		outifs >> oval;
		
		//instnum++; //��ɾ� ���� ���ƺ��� �ִ� Insert��ɾ��
	}

	//arr = new int[instnum]; //
	//int datanum = 0; // Ʈ���� �����ϴ� data����

	inifs.close();
	inifs.open(inputfile);

	//Node* nptr;
	//int sum = 0;
	set<int>::iterator itr;
	int size;
	int count;

	while (1) {
		inifs >> func;
		inifs >> val;
		outifs >> oval;
		if (outifs.eof())
			break;
		if (func == "I") {  //Insert
			itr = container.find(val);
			if (oval == 0) {  //�ߺ� Insert �߻�
				if (itr == container.end()) //�����غ��� �ش� val�� ������.. 
					result = F;
				else //������ �̹� val�� ��������
					result = T;
			}
			else { //�ߺ��� ������ ���
				if(itr == container.end()){ //�ش� val�� ������ ����
					result = T;
				}
				else {
					result = F;
				}
			}
			container.insert(val); //�������� �ϴ� insert...
		}
		else if (func == "D") {  //Delete
			itr = container.find(val);
			if (oval == 0) {  //val�̶�� ���� ���� ���� �����ߴٰ� ����
				if (itr == container.end()) //������ ������
					result = T;
				else //��� ã�ƺ��� �־���
					result = F;
			}
			else { //val�� �־ ���� �����ߴٰ� ����
				if (itr != container.end()) //ã����
				{
					result = T;
				}
				else
					result = F;
			}
			container.erase(val);
		}
		else if (func == "S") { //Select
			size = container.size();
			if (oval == 0) { //val�� Ʈ���� ������ ������ ũ�ٰ� ����
				if (size < val) //������ val�� ������ �������� ŭ
					result = T;
				else
					result = F;
			}
			else {  //oval�� Ʈ������ val��° ���� ����� ����
				count = 0;
				for (itr = container.begin(); itr != container.end(); itr++) {
					if (*itr == oval) { //oval�� ����� �ִ��� Ȯ���Ͽ� check
						count++;
						break;
					}
					else
						count++;
				}
				if (count == val)
					result = T;
				else
					result = F;
			}
		}
		else {  // Rank�� ���
			if (oval == 0) {  //val�� Ʈ���� �������� ����
				itr = container.find(val);
				if (itr == container.end()) //������ �������� ����
					result = T;
				else
					result = F;
			}
			else { //val�� tree���� oval��° ���� ����� ����
				itr = container.begin();
				for (int i = 1; i < oval; i++)
					itr++;
				if (*itr == val)
					result = T;
				else
					result = F;
			}
		}

		ofs << "���� : " << func << " " << val << " ��� : " << oval << " check ��� : " << result << endl;
	}


	/*while (1) {
		inifs >> func;
		inifs >> val;
		outifs >> oval;
		if (outifs.eof())
			break;
		//cout << func << "  " << val << "  " << oval << endl;
		if (func == "I") {  //Insert
			nptr = IsKeyExist(checktree->getroot(), val);
			if (oval == 0) {  //�ߺ� Insert �߻�
				if (nptr != nullptr)
					result = T;
				else
					result = F;
				checktree->OSInsert(val);
			}
			else { //�ߺ��� ������ ���
				if (nptr == nullptr) {
					checktree->OSInsert(val);
					if (IsKeyExist(checktree->getroot(), val) != nullptr) {
						result = T;
						//datanum++; //Insert�� ���������� ����� ��츸 ���� ����
					}
						
					//������ ���� �ڿ� �ش� ���� �����ϴ������� Ȯ��
				}
				else {
					result = F;
					checktree->OSInsert(val);
				}
			}
			container.insert(val);
		}
		else if (func == "D") {  //Delete
			nptr = IsKeyExist(checktree->getroot(), val);
			if (oval == 0) {  //val�̶�� ���� ���� ���� �����ߴٰ� ����
				if (nptr == nullptr)
					result = T;
				else
					result = F;
				checktree->OSDelete(val);
			}
			else { //val�� �־ ���� �����ߴٰ� ����
				if (nptr != nullptr) //���� ã����
				{
					checktree->OSDelete(val);
					if (IsKeyExist(checktree->getroot(), val) == nullptr) {
						result = T;
						//datanum--;// ���� ������ ����
					}
					//������ �ڿ� ������ ���� �������������� Ȯ��
				}
				else {  //���� ��ã����
					result = F;
					checktree->OSDelete(val);
				}
			}
		}
		else if (func == "S") { //Select
			if (oval == 0) { //val�� Ʈ���� ������ ������ ũ�ٰ� ����
				sum = 0;
				//Ʈ���� ��� ������ travers������� �ѹ� �� üũ
				if (val > checktree->traverse(checktree->getroot(), &sum))
					result = T;
				else
					result = F;
			}
			else {  //oval�� Ʈ������ val��° ���� ����� ����

			}
		}
		else {  // Rank�� ���
			if (oval == 0) {  //val�� Ʈ���� �������� ����
				nptr = IsKeyExist(checktree->getroot(), val);
				if (nptr == nullptr) //������ val�� �������� ����
					result = T;
				else
					result = F;
			}
			else { //val�� tree���� oval��° ���� ����� ����

			}
		}

		ofs <<"���� : "<<func << " " << val << " ��� : " << oval << " check ��� : " << result << endl;
		
	}*/

	//delete[] arr;
	inifs.close();
	outifs.close();
	ofs.close();
}