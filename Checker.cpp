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

	int instnum = 0; // 명령어 개수
	int* arr; // 사용할 array

	while (1) {
		inifs >> func;
		inifs >> val;
		if (func == "I")
			instnum++;
		if (inifs.eof())
			break;
		outifs >> ofunc;
		outifs >> oval;
		
		//instnum++; //명령어 개수 많아봤자 최대 Insert명령어개수
	}

	arr = new int[instnum]; //
	int datanum = 0; // 트리에 존재하는 data개수

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
			if (oval == 0) {  //중복 Insert 발생
				if (nptr != nullptr)
					result = T;
				else
					result = F;
				checktree->OSInsert(val);
			}
			else { //중복이 없었던 경우
				if (nptr == nullptr) {
					checktree->OSInsert(val);
					if (IsKeyExist(checktree->getroot(), val) != nullptr) {
						result = T;
						datanum++; //Insert가 정상적으로 진행된 경우만 개수 증가
					}
						
					//실제로 삽입 뒤에 해당 값이 존재하는지까지 확인
				}
				else {
					result = F;
					checktree->OSInsert(val);
				}
			}
		}
		else if (func == "D") {  //Delete
			nptr = IsKeyExist(checktree->getroot(), val);
			if (oval == 0) {  //val이라는 값이 없어 삭제 실패했다고 나옴
				if (nptr == nullptr)
					result = T;
				else
					result = F;
				checktree->OSDelete(val);
			}
			else { //val값 있어서 삭제 성공했다고 나옴
				if (nptr != nullptr) //값을 찾았음
				{
					checktree->OSDelete(val);
					if (IsKeyExist(checktree->getroot(), val) == nullptr) {
						result = T;
						datanum--;// 삭제 실제로 성공
					}
					//삭제한 뒤에 실제로 값이 없어졌는지까지 확인
				}
				else {  //값을 못찾았음
					result = F;
					checktree->OSDelete(val);
				}
			}
		}
		else if (func == "S") { //Select
			if (oval == 0) { //val이 트리의 데이터 수보다 크다고 나옴
				sum = 0;
				//트리의 노드 개수를 travers방식으로 한번 더 체크
				if (val > checktree->traverse(checktree->getroot(), &sum))
					result = T;
				else
					result = F;
			}
			else {  //oval이 트리에서 val번째 작은 수라고 나옴

			}
		}
		else {  // Rank인 경우
			if (oval == 0) {  //val이 트리에 존재하지 않음
				nptr = IsKeyExist(checktree->getroot(), val);
				if (nptr == nullptr) //실제로 val이 존재하지 않음
					result = T;
				else
					result = F;
			}
			else { //val이 tree에서 oval번째 작은 수라고 나옴

			}
		}

		ofs <<"연산 : "<<func << " " << val << " 결과 : " << oval << " check 결과 : " << result << endl;
		
	}

	delete[] arr;
	inifs.close();
	outifs.close();
	ofs.close();
}