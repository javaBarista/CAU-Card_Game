#include "Playgame.h"


//입력 예외처리를 위한 함수
void exceptionError() {
	cin.clear();
	cin.ignore(100, '\n');
}

void PlayGame:: startGame() {
	game.rule();
	cin.get();
	system("cls");

	while (1) {
		cout << "몇명의 플레이어로 시작 하시겠습니까?(딜러 제외 최소 1인, 최대 3인)";
		cin >> count;
		if ((int)count > 0 && (int)count < 4) break;
		exceptionError();
		cout << "딜러 제외 최소 1인, 최대 3인 입니다." << endl;
	}

	Player *player = new Player[count];

	exceptionError();
	cout << "당신의 이름을 입력해 주세요 : ";
	getline(cin, name);
	player[0].setName(name);
	for (int i = 1; i < count; i++) {
		ostringstream o;					//ostream을 이용해 플레이어의 이름은 따로 입력받지 않고 int타입을 스트링으로 변경해 저장
		o << i;
		name = o.str() + " 번째 플레이어";
		player[i].setName(name);
	}


	while (true) {
		int *sum = new int[count];			//사용자들의 합계를 입력받을 벡터
		int dsum;					//딜러의 합계를 저장할 변수
		battingmoney = 0;			//정적으로 선언한 배팅금을 매번 게임이 돌 때마다 0으로 초기화
		while (1) {
			cout << player[0].getName() << "님의 보유 금액은 " << player[0].getMoney() << "입니다." << endl;
			cout << player[0].getName() << "님 얼마를 배팅하시겠습니까?(최소배팅금액은 만원) : ";
			cin >> money[0];
			if (money[0] < 10000) continue;		//배팅금은 10000원을 넘겨야 한다.

			if (money[0] <= player[0].getMoney()) {
				battingmoney += money[0];		//총 배팅금에 내가 배팅한 돈만큼 더해준다
				player[0].setMoney(money[0]);	//배팅한 돈 만큼 자본금에서 빼준다.
				break;
			}

			cout << "보유한 금액보다 많은 금액입니다." << endl;
			exceptionError();
		}

		//다른 플레이어들은 난수를 이용해 적절한 금액을 배팅해 준다.
		for (int i = 1; i < count; i++) {
			money[i] = rand() % 1000 * 5;
			if (money[i] < 100) money[i] *= 25;
			else money[i] *= 20;
			battingmoney += money[i];
			player[i].setMoney(money[i]);
		}

		putchar('\n');
		cout << "최종 배팅 금액은: " << battingmoney << endl;

		exceptionError();
		putchar('\n');
		cout << "최초 2장의 카드가 지급됩니다.(enter입력시 시작)";
		cin.get();

		BlackJack game;	//게임이 진행되면 딜러와 플레이어들의 패를 관리해줄 클래스를 생성

		system("cls");
		cout << "=====딜러의 카드=====" << endl;
		game.dealerCardShow();														//딜러의 카드를 보여주고
		game.decshape();																	//덱모양을 보여준 뒤
		for (int i = count - 1; i > 0; i--) {										//나를 제외한 플레이어들의 카드를 보여준다				
			cout << player[i].getName() << " 님의 현재 보유 카드 입니다." << endl;
			game.orherCardShow(i);
			putchar('\n');
		}
		cout << player[0].getName() << " 님의 현재 보유 카드 입니다." << endl;		//마지막으로 내 카드를 출력
		game.myCardShow();

		char choice;

		//처음 지급 후엔 계속해서카드를 받는 Hit를할지 더 이상 카드를 받지 않는 stand를 할지를 선택 하기위한 반복문
		while (1) {
			cout << "카드를 받으시겠습니까 ?(h: Hit, s: Stand)";
			cin >> choice;
			if (sizeof(choice) != sizeof(char)) {		//한글이 입력되면 예외처리
				exceptionError();
				continue;
			}

			game.needdealerCard();						//딜러가 카드가 더 필요한지 호출
			for (int i = count - 1; i > 0; i--) {		//다른 플레이어들이 카드가 더 필요한지 호출
				game.needOtherCard(i);
			}

			if (choice == 'h' || choice == 'H') {
				game.addMyCard();						//사용자가 카드를 더 받기를 원하므로 카드지급
				system("cls");
				cout << "=====딜러의 카드=====" << endl;
				game.dealerCardShow();
				game.decshape();
				for (int i = count - 1; i > 0; i--) {
					cout << player[i].getName() << " 님의 현재 보유 카드 입니다." << endl;
					game.orherCardShow(i);
					putchar('\n');
				}
				cout << player[0].getName() << " 님의 현재 보유 카드 입니다." << endl;
				game.myCardShow();
			}

			else if (choice == 's' || choice == 'S') {
				dsum = game.dealerScore();		//딜러의 점수 저장
				sum[0] = game.myScore();			//내 점수를 저장 
				for (int i = 1; i < count; i++) {
					sum[i] = game.otherScore(i);	//다른 플레이어들의 점수도 차례로 저장
				}

				system("cls");
				cout << "=====딜러의 카드=====" << endl;
				game.dealerOpenCard();					//딜러의 모든 카드를 오픈
				cout << "딜러의 점수: " << dsum << endl;
				game.decshape();
				//각 플레이어의 카드와 점수를 출력해준다.
				for (int i = count - 1; i > 0; i--) {
					cout << player[i].getName() << " 님의 현재 보유 카드 입니다." << endl;
					game.orherCardShow(i);
					putchar('\n');
					cout << player[i].getName() << "님 점수: " << sum[i] << endl;
					cout << "---------------------------------------------------" << endl;
				}
				//내 점수와 카드도 출력해준다.
				cout << player[0].getName() << " 님의 현재 보유 카드 입니다." << endl;
				game.myCardShow();
				cout << "내 점수의 합계: " << sum[0] << endl << endl;

				//딜러가 black jack으로 이길때
				if (dsum > 20 && dsum < 22) {
					cout << "딜러가 BLACK JACk이 나왔습니다.!!!!!!!!!" << endl;
					cout << "다른 모든 참가자는 패배입니다." << endl;
					cout << "배팅금 : " << battingmoney << "의 1.5배인 " << battingmoney * 1.5 << "를 얻는다." << endl;
					break;
				}

				//참가자가 나 한명일때
				if (count == 1) {
					//딜러와 나 둘다 21을 오버했을때
					if (sum[0] > 21 && dsum > 21) {
						cout << "모두 21을 넘겨 비겼습니다." << endl;
						cout << "배팅금은 원래대로 지급됩니다." << endl;
						player[0].winmoney(money[0]);
					}
					//딜러와 내 점수가 같을때
					else if (sum[0] == dsum) {
						cout << "같은 점수가 나왔습니다." << endl;
						cout << "배팅금은 원래대로 지급됩니다." << endl;
						player[0].winmoney(money[0]);
					}
					//딜러의 점수만 21을 넘겼을때
					else if (dsum > 21) {
						//내 점수가 21보다 작기만 하면 내 승리
						if (sum[0] < 22) {
							cout << player[0].getName() << "님이 이겼습니다!!!!!" << endl;
							cout << "배팅금 : " << battingmoney << "의 2배인 ";
							player[0].winmoney(battingmoney * 2);
							cout << battingmoney * 2 << "를 얻는다." << endl;

						}
					}
					//내가 21을 넘겼을 때
					else if (sum[0] > 21) {
						//딜러 점수가 21보다 작기만 하면 내 승리
						if (dsum < 22) {
							cout << "딜러의 승리!!!!!!!!!" << endl;
							cout << "배팅금 : " << battingmoney << "의 1.5배인 " << battingmoney * 1.5 << "를 얻는다." << endl;
						}
					}
					//둘다 21이하의 점수일 때
					else {
						//딜러의 점수가 내 점수 보다 크면 딜러의 승리 
						if (dsum > sum[0]) {
							cout << "딜러의 승리!!!!!!!!!" << endl;
							cout << "배팅금 : " << battingmoney << "의 1.5배인 " << battingmoney * 1.5 << "를 얻는다." << endl;
						}
						//내점수가 더 크면 내승리
						else {
							cout << player[0].getName() << "님이 이겼습니다!!!!!" << endl;
							cout << "배팅금 : " << battingmoney << "의 2배인 ";
							player[0].winmoney(battingmoney * 2);
							cout << battingmoney * 2 << "를 얻는다." << endl;
						}
					}
					goto onemoregame;
				}

				//참가자가 여러명일때
				else {
					//딜러가 BLACK JACK이 아닐때 참가자 중 같은 값으로 비긴 참가자가 있는지 판단.
					int samecount = 0;
					int samescore;
					for (int i = 0; i < count; i++) {
						if (dsum < 22 && sum[i] < 22) {
							if (dsum == sum[i]) {
								samecount++;
								samescore = dsum;
							}
						}
						if (sum[i] < 22 && sum[i + 1] < 22) {
							if (sum[i] == sum[i + 1]) {
								samecount++;
								samescore = sum[i];
							}
						}
					}
					if (sum[0] < 22 && sum[2] < 22) {
						if (sum[0] == sum[2]) {
							samecount++;
							samescore = sum[0];
						}
					}
					//같은 점수를 가진 참가자가 있다면 무효게임
					if (samecount > 0) {
						cout << samescore << " 점으로 같은 점수가 나왔습니다." << endl;
						cout << "배팅금은 원래대로 지급됩니다." << endl;
						for (int i = 0; i < count; i++) {
							player[i].winmoney(money[i]);
						}
						break;
					}

					//참가자들의 점수는 전부 다르고 그중에 BLACK JACK으로 이기는 경우
					else {
						for (int i = 0; i < count; i++) {
							if (sum[i] > 20 && sum[i] < 22) {
								cout << player[i].getName() << "님의 BLACK JACK!!!!!!!!!!!!!!!!!!!" << endl << endl;
								cout << "배팅금 : " << battingmoney << "의 2배인 ";
								player[i].winmoney(battingmoney * 2);
								cout << battingmoney * 2 << "를 얻는다." << endl;
								goto onemoregame;
							}
						}
					}

					//참가자들의 점수중 21을 넘기는 사람이 몇명인지 카운트
					int over21 = 0;
					for (int i = 0; i < count; i++) {
						if (sum[i] > 21) {
							over21++;
						}
					}

					//모든 참가자가 21을 넘겼을 때
					if (over21 == (count - 1)) {
						//딜러 마저 21을넘기면 모든 사람들이 같이 패배
						if (dsum > 21) {
							cout << "모두 21을 넘겨 비겼습니다." << endl;
							cout << "배팅금은 원래대로 지급됩니다." << endl;
							for (int i = 0; i < count; i++) {
								player[i].winmoney(money[i]);
							}
							break;
						}
						//딜러는 21을 넘기지 않았다면 딜러의 승리
						else {
							cout << "딜러의 승리!!!!!!!!!" << endl;
							cout << "배팅금 : " << battingmoney << "의 1.5배인 " << battingmoney * 1.5 << "를 얻는다." << endl;
							break;
						}
					}
					//참가자중 한명이라도 21을 넘지 않았다면
					else {
						int winner;									//승자의 번호를 저장할 변수
						int max;
						if (dsum < 21)	max = dsum;				//딜러의 카드 합계가 20이하 이면 max에 우선 딜러의 합계를 저장
						else {										//딜러의 합계가 21을 넘으면 사용자 중 21을 넘지 않는 사람의 합계를 저장
							for (int i = 0; i < count; i++) {
								if (sum[i] < 21) {
									max = sum[i];
									winner = i;
									break;
								}
							}
						}
						for (int i = 0; i < count; i++) {
							if (sum[i] < 21 && sum[i] > max) {		//플레이어들의 카드 합계 중 21보다 작으면서 현재 max보다 크면 max를 해당 값으로 바꿔준다
								max = sum[i];
								winner = i;
							}
						}

						if (dsum != max) {										//딜러승리가 아니면 이긴 플레이어에게 배팅금의 2배를 지급
							cout << player[winner].getName() << "님의 승리 !!!!!!!!!!!!!!!!!!!" << endl << endl;
							cout << "배팅금 : " << battingmoney << "의 2배인 ";
							player[winner].winmoney(battingmoney * 2);
							cout << battingmoney * 2 << "를 얻는다." << endl;
							break;
						}
						else {							//max에 있는값이 딜러의 합계이면 딜러의 승리
							cout << "딜러의 승리!!!!!!!!!" << endl;
							cout << "배팅금 : " << battingmoney << "의 1.5배인 " << battingmoney * 1.5 << "를 얻는다." << endl;
							break;
						}

					}
				}
			}
		}

		//추가 게임을 진행할 것인지 물어보고 선택에 따라 명령을 실행
	onemoregame:
		while (1) {
			cout << "한게임 더 하시겠습니까?? (y = yes, n = NO)";
			cin >> choice;
			if (isalpha(choice) == false || sizeof(choice) != sizeof(char)) {	//입력한 값이 한글인지 확인 후 한글이면 버퍼를 비우너준다
				exceptionError();
				continue;
			}
			if (choice == 'y' || choice == 'Y') {
				if (player[0].getMoney() < 10000) {		//사용자가 추가 게임을 요청해도 자산이 만원이 안되면 게임을 진행 할 수 없도록 설정
					system("cls");
					cout << player[0].getName() << "님의 돈이 만원을 넘지 못하여 자동으로 종료 됩니다." << endl;
					return;
				}
				game.newdec();
				system("cls");
				break;
			}
			else if (choice == 'n' || choice == 'N')	//사용자가 더 이상의 게임을 원하지 않으면 게임 종료
				return;
		}
	}
}