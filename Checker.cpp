#include "Checker.h"

void Checker(string inputfile, string outputfile) {
	ifstream inifs(inputfile);
	ifstream outifs(outputfile);
	ofstream ofs("checker.txt");

	string func;
	string ofunc;
	int val;
	int oval;

	string result;
	string T = "True";
	string F = "False";

	OSTree* checktree = new OSTree;

	int instnum = 0; // ��ɾ� ����
	int* arr; // ����� array

	while (1) {
		inifs >> func;
		inifs >> val;
		if (func == "I")
			instnum++;
		if (inifs.eof())
			break;
		outifs >> ofunc;
		outifs >> oval;
		
		//instnum++; //��ɾ� ���� ���ƺ��� �ִ� Insert��ɾ��
	}

	arr = new int[instnum]; //
	int datanum = 0; // Ʈ���� �����ϴ� data����

	inifs.close();
	inifs.open(inputfile);

	Node* nptr;
	int sum = 0;

	while (1) {
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
						datanum++; //Insert�� ���������� ����� ��츸 ���� ����
					}
						
					//������ ���� �ڿ� �ش� ���� �����ϴ������� Ȯ��
				}
				else {
					result = F;
					checktree->OSInsert(val);
				}
			}
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
						datanum--;// ���� ������ ����
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
		
	}

	delete[] arr;
	inifs.close();
	outifs.close();
	ofs.close();
}