#include "BlackJack.h"

//BlackJack�� �⺻ �����ڿ��� �켱 �� �÷��̾�� ī�带 ���徿 �Ҵ�
BlackJack::BlackJack():CardDec() {
	for (int j = 0; j < 3; j++) {
		vector <int> temp;			//�ӽ÷� ���� �Է¹��� ���͸� ����� ī�带 ���� �־��ְ� 
		for (int i = 0; i < 2; i++) {
			temp.push_back(makecard());
		}
		othercard.push_back(temp);		//�ش� ���͸� 2���� ���Ϳ� �־��ش�
	}
	for (int i = 0; i < 2; i++) {		//���� ������ ī��� ������ ī�嵵 �ΰ��� �Ҵ�
		mycard.push_back(makecard());
		dealercard.push_back(makecard());
	}
	drand = rand() % 2;			//������ aceī�带 �������������� ���� �̸� ���� ����
}

//mycard ����-----------------------------------------
void BlackJack::addMyCard() {
	mycard.push_back(makecard());	//�Լ��� ȣ��Ǹ� ������ �������� makecard() �� ȣ���� ���ο� ���� �־��ش�.
}

int BlackJack::myScore() {
	size = mycard.size();			//������ ũ�⸦ ����
	sum = 0;						//�հ踦 0���� ����
	for (int i = 0; i < size; i++) {
		key = (mycard[i] % 13);
		if (key > 10 || key == 0) key = 10;		//ī���� ���ڰ� J, Q, K �� �ϳ��̸� key�� 10�� ����

		else if (key == 1) {		//ī���� ���ڰ� ace�� ���
			int choice;					//���ù��� ���� 1�� 11�� ��������� ������� ����
			while(1) {
				cout << "ACEī�带 1�� 11�� ��� ������ ����ϰڽ��ϱ�? ";
				cin >> choice;
				if (choice == 11 || choice == 1) {
					key = choice;
					break;
				}	
			}
		}
		sum += key;
	}
	return sum;		//���� �������ش�
}

void BlackJack::myCardShow() {
	size = mycard.size();		//������ ũ�⸦ �����س��� �� �ݺ����� ���� ī�带 ���
	for (int i = 0; i < size; i++) {
		cout << up << "  ";
	}
	putchar('\n');

	for (int i = 0; i < size; i++) {
		key = mycard[i];
		cout << shape[key / 13] << "  ";
	}
	putchar('\n');
	for (int i = 0; i < size; i++) {
		key = mycard[i];
		cout << number[key % 13] << "  ";
	}
	putchar('\n');
	for (int i = 0; i < size; i++) {
		cout << down << "  ";
	}
	putchar('\n');
}

//dealerī�� ����--------------------------------------------------
int BlackJack::dealerScore() {
	size = dealercard.size();
	sum = 0;
	for (int i = 0; i < size; i++) {
		key = (dealercard[i] % 13);
		if (key > 10 || key == 0) key = 10;
		else if (key == 1) {
			if (sum == 10) key == 11;		//������ ī���� ���� 10�ε� ace�� ������ �ִٸ� 11�� ��밡��
			else if (drand == 1) key = 1;	//������ �հ谡 10�� �������� ���� ���¿��� ace�� ������ �ִٸ� �������� ���
			else key = 11;	
		}
		sum += key;
	}
	return sum;
}

void BlackJack::addDealerCard() {
	dealercard.push_back(makecard());
}

void BlackJack::needdealerCard() {
	if (dealerScore() < 17) addDealerCard();		//����ī�� �հ谡 17���� ������ ī�带 �߰��� �޴´�
}

void BlackJack::dealerCardShow() {
	size = dealercard.size();
	for (int i = 0; i < size; i++) {
		cout << up << "  ";
	}
	putchar('\n');
	cout << "�� �妢" << "  ";		    //������ ī���� ù���� ���������� �ϱ⿡ ī���� �޸�� ���
	for (int i = 1; i < size; i++) {	//���� �ݺ����� 1(�ι�° ī��)���� ����
		key = dealercard[i];
		cout << shape[key / 13] << "  ";
	}
	putchar('\n');
	cout << "�� �⦢" << "  ";		
	for (int i = 1; i < size; i++) {
		key = dealercard[i];
		cout << number[key % 13] << "  ";
	}
	putchar('\n');
	for (int i = 0; i < size; i++) {
		cout << down << "  ";
	}
	putchar('\n');
}

void BlackJack::dealerOpenCard() {
	size = dealercard.size();
	for (int i = 0; i < size; i++) {
		cout << up << "  ";
	}
	putchar('\n');
	for (int i = 0; i < size; i++) {
		key = dealercard[i];
		cout << shape[key / 13] << "  ";
	}
	putchar('\n');
	for (int i = 0; i < size; i++) {
		key = dealercard[i];
		cout << number[key % 13] << "  ";
	}
	putchar('\n');
	for (int i = 0; i < size; i++) {
		cout << down << "  ";
	}
	putchar('\n');
}

//otherplayerī�� ����-----------------------------------------------------------
int BlackJack::otherScore(int i) {	//���° �÷��̾����� �˱� ���� i�� �Ѱ� �޴´� 
	size = othercard[i].size();
	sum = 0;
	for (int j = 0; j < size; j++) {
		key = (othercard[i][j] % 13);
		if (key > 10 || key == 0) key = 10;
		
		sum += key;
	}
	return sum;
}

void BlackJack::needOtherCard(int i) {
	if (otherScore(i) < 15) addotherCard(i);	//�ٸ� �÷��̾���� 15���� ���� �� ī�� ��ο�
}

void BlackJack::addotherCard(int i) {
	othercard[i].push_back(makecard());
}

void BlackJack::orherCardShow(int i) {
	size = othercard[i].size();
	for (int j = 0; j < size; j++) {
		cout << up << "  ";
	}
	putchar('\n');

	for (int j = 0; j < size; j++) {
		key = othercard[i][j];
		cout << shape[key / 13] << "  ";
	}
	putchar('\n');
	for (int j = 0; j < size; j++) {
		key = othercard[i][j];
		cout << number[key % 13] << "  ";
	}
	putchar('\n');
	for (int j = 0; j < size; j++) {
		cout << down << "  ";
	}
	putchar('\n');
}