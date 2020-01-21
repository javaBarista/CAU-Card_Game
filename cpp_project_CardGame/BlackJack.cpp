#include "BlackJack.h"

//BlackJack의 기본 생성자에서 우선 각 플레이어에게 카드를 두장씩 할당
BlackJack::BlackJack():CardDec() {
	for (int j = 0; j < 3; j++) {
		vector <int> temp;			//임시로 값을 입력받을 벡터를 만들어 카드를 두장 넣어주고 
		for (int i = 0; i < 2; i++) {
			temp.push_back(makecard());
		}
		othercard.push_back(temp);		//해당 벡터를 2차원 벡터에 넣어준다
	}
	for (int i = 0; i < 2; i++) {		//내가 보유한 카드와 딜러의 카드도 두개씩 할당
		mycard.push_back(makecard());
		dealercard.push_back(makecard());
	}
	drand = rand() % 2;			//딜러가 ace카드를 가지고있을때를 위해 미리 난수 생성
}

//mycard 관련-----------------------------------------
void BlackJack::addMyCard() {
	mycard.push_back(makecard());	//함수가 호출되면 벡터의 마지막에 makecard() 를 호출해 새로운 값을 넣어준다.
}

int BlackJack::myScore() {
	size = mycard.size();			//벡터의 크기를 저장
	sum = 0;						//합계를 0으로 세팅
	for (int i = 0; i < size; i++) {
		key = (mycard[i] % 13);
		if (key > 10 || key == 0) key = 10;		//카드의 숫자가 J, Q, K 중 하나이면 key에 10을 저장

		else if (key == 1) {		//카드의 숫자가 ace일 경우
			int choice;					//선택문을 통해 1과 11중 어느값으로 사용할지 선택
			while(1) {
				cout << "ACE카드를 1과 11중 어느 것으로 사용하겠습니까? ";
				cin >> choice;
				if (choice == 11 || choice == 1) {
					key = choice;
					break;
				}	
			}
		}
		sum += key;
	}
	return sum;		//합을 리턴해준다
}

void BlackJack::myCardShow() {
	size = mycard.size();		//벡터의 크기를 저장해놓은 뒤 반복문을 통해 카드를 출력
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

//dealer카드 관련--------------------------------------------------
int BlackJack::dealerScore() {
	size = dealercard.size();
	sum = 0;
	for (int i = 0; i < size; i++) {
		key = (dealercard[i] % 13);
		if (key > 10 || key == 0) key = 10;
		else if (key == 1) {
			if (sum == 10) key == 11;		//딜러의 카드의 합이 10인데 ace을 가지고 있다면 11로 사용가능
			else if (drand == 1) key = 1;	//딜러의 합계가 10을 만족하지 못한 상태에서 ace를 가지고 있다면 랜덤수로 사용
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
	if (dealerScore() < 17) addDealerCard();		//딜러카드 합계가 17보다 작으면 카드를 추가로 받는다
}

void BlackJack::dealerCardShow() {
	size = dealercard.size();
	for (int i = 0; i < size; i++) {
		cout << up << "  ";
	}
	putchar('\n');
	cout << "│ ▼│" << "  ";		    //딜러는 카드의 첫장이 뒤집어져야 하기에 카드의 뒷모양 출력
	for (int i = 1; i < size; i++) {	//따라서 반복문이 1(두번째 카드)부터 시작
		key = dealercard[i];
		cout << shape[key / 13] << "  ";
	}
	putchar('\n');
	cout << "│ △│" << "  ";		
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

//otherplayer카드 관련-----------------------------------------------------------
int BlackJack::otherScore(int i) {	//몇번째 플레이어인지 알기 위해 i를 넘겨 받는다 
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
	if (otherScore(i) < 15) addotherCard(i);	//다른 플레이어들은 15보다 적을 시 카드 드로우
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