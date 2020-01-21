#include "Playgame.h"


//�Է� ����ó���� ���� �Լ�
void exceptionError() {
	cin.clear();
	cin.ignore(100, '\n');
}

void PlayGame:: startGame() {
	game.rule();
	cin.get();
	system("cls");

	while (1) {
		cout << "����� �÷��̾�� ���� �Ͻðڽ��ϱ�?(���� ���� �ּ� 1��, �ִ� 3��)";
		cin >> count;
		if ((int)count > 0 && (int)count < 4) break;
		exceptionError();
		cout << "���� ���� �ּ� 1��, �ִ� 3�� �Դϴ�." << endl;
	}

	Player *player = new Player[count];

	exceptionError();
	cout << "����� �̸��� �Է��� �ּ��� : ";
	getline(cin, name);
	player[0].setName(name);
	for (int i = 1; i < count; i++) {
		ostringstream o;					//ostream�� �̿��� �÷��̾��� �̸��� ���� �Է¹��� �ʰ� intŸ���� ��Ʈ������ ������ ����
		o << i;
		name = o.str() + " ��° �÷��̾�";
		player[i].setName(name);
	}


	while (true) {
		int *sum = new int[count];			//����ڵ��� �հ踦 �Է¹��� ����
		int dsum;					//������ �հ踦 ������ ����
		battingmoney = 0;			//�������� ������ ���ñ��� �Ź� ������ �� ������ 0���� �ʱ�ȭ
		while (1) {
			cout << player[0].getName() << "���� ���� �ݾ��� " << player[0].getMoney() << "�Դϴ�." << endl;
			cout << player[0].getName() << "�� �󸶸� �����Ͻðڽ��ϱ�?(�ּҹ��ñݾ��� ����) : ";
			cin >> money[0];
			if (money[0] < 10000) continue;		//���ñ��� 10000���� �Ѱܾ� �Ѵ�.

			if (money[0] <= player[0].getMoney()) {
				battingmoney += money[0];		//�� ���ñݿ� ���� ������ ����ŭ �����ش�
				player[0].setMoney(money[0]);	//������ �� ��ŭ �ں��ݿ��� ���ش�.
				break;
			}

			cout << "������ �ݾ׺��� ���� �ݾ��Դϴ�." << endl;
			exceptionError();
		}

		//�ٸ� �÷��̾���� ������ �̿��� ������ �ݾ��� ������ �ش�.
		for (int i = 1; i < count; i++) {
			money[i] = rand() % 1000 * 5;
			if (money[i] < 100) money[i] *= 25;
			else money[i] *= 20;
			battingmoney += money[i];
			player[i].setMoney(money[i]);
		}

		putchar('\n');
		cout << "���� ���� �ݾ���: " << battingmoney << endl;

		exceptionError();
		putchar('\n');
		cout << "���� 2���� ī�尡 ���޵˴ϴ�.(enter�Է½� ����)";
		cin.get();

		BlackJack game;	//������ ����Ǹ� ������ �÷��̾���� �и� �������� Ŭ������ ����

		system("cls");
		cout << "=====������ ī��=====" << endl;
		game.dealerCardShow();														//������ ī�带 �����ְ�
		game.decshape();																	//������� ������ ��
		for (int i = count - 1; i > 0; i--) {										//���� ������ �÷��̾���� ī�带 �����ش�				
			cout << player[i].getName() << " ���� ���� ���� ī�� �Դϴ�." << endl;
			game.orherCardShow(i);
			putchar('\n');
		}
		cout << player[0].getName() << " ���� ���� ���� ī�� �Դϴ�." << endl;		//���������� �� ī�带 ���
		game.myCardShow();

		char choice;

		//ó�� ���� �Ŀ� ����ؼ�ī�带 �޴� Hit������ �� �̻� ī�带 ���� �ʴ� stand�� ������ ���� �ϱ����� �ݺ���
		while (1) {
			cout << "ī�带 �����ðڽ��ϱ� ?(h: Hit, s: Stand)";
			cin >> choice;
			if (sizeof(choice) != sizeof(char)) {		//�ѱ��� �ԷµǸ� ����ó��
				exceptionError();
				continue;
			}

			game.needdealerCard();						//������ ī�尡 �� �ʿ����� ȣ��
			for (int i = count - 1; i > 0; i--) {		//�ٸ� �÷��̾���� ī�尡 �� �ʿ����� ȣ��
				game.needOtherCard(i);
			}

			if (choice == 'h' || choice == 'H') {
				game.addMyCard();						//����ڰ� ī�带 �� �ޱ⸦ ���ϹǷ� ī������
				system("cls");
				cout << "=====������ ī��=====" << endl;
				game.dealerCardShow();
				game.decshape();
				for (int i = count - 1; i > 0; i--) {
					cout << player[i].getName() << " ���� ���� ���� ī�� �Դϴ�." << endl;
					game.orherCardShow(i);
					putchar('\n');
				}
				cout << player[0].getName() << " ���� ���� ���� ī�� �Դϴ�." << endl;
				game.myCardShow();
			}

			else if (choice == 's' || choice == 'S') {
				dsum = game.dealerScore();		//������ ���� ����
				sum[0] = game.myScore();			//�� ������ ���� 
				for (int i = 1; i < count; i++) {
					sum[i] = game.otherScore(i);	//�ٸ� �÷��̾���� ������ ���ʷ� ����
				}

				system("cls");
				cout << "=====������ ī��=====" << endl;
				game.dealerOpenCard();					//������ ��� ī�带 ����
				cout << "������ ����: " << dsum << endl;
				game.decshape();
				//�� �÷��̾��� ī��� ������ ������ش�.
				for (int i = count - 1; i > 0; i--) {
					cout << player[i].getName() << " ���� ���� ���� ī�� �Դϴ�." << endl;
					game.orherCardShow(i);
					putchar('\n');
					cout << player[i].getName() << "�� ����: " << sum[i] << endl;
					cout << "---------------------------------------------------" << endl;
				}
				//�� ������ ī�嵵 ������ش�.
				cout << player[0].getName() << " ���� ���� ���� ī�� �Դϴ�." << endl;
				game.myCardShow();
				cout << "�� ������ �հ�: " << sum[0] << endl << endl;

				//������ black jack���� �̱涧
				if (dsum > 20 && dsum < 22) {
					cout << "������ BLACK JACk�� ���Խ��ϴ�.!!!!!!!!!" << endl;
					cout << "�ٸ� ��� �����ڴ� �й��Դϴ�." << endl;
					cout << "���ñ� : " << battingmoney << "�� 1.5���� " << battingmoney * 1.5 << "�� ��´�." << endl;
					break;
				}

				//�����ڰ� �� �Ѹ��϶�
				if (count == 1) {
					//������ �� �Ѵ� 21�� ����������
					if (sum[0] > 21 && dsum > 21) {
						cout << "��� 21�� �Ѱ� �����ϴ�." << endl;
						cout << "���ñ��� ������� ���޵˴ϴ�." << endl;
						player[0].winmoney(money[0]);
					}
					//������ �� ������ ������
					else if (sum[0] == dsum) {
						cout << "���� ������ ���Խ��ϴ�." << endl;
						cout << "���ñ��� ������� ���޵˴ϴ�." << endl;
						player[0].winmoney(money[0]);
					}
					//������ ������ 21�� �Ѱ�����
					else if (dsum > 21) {
						//�� ������ 21���� �۱⸸ �ϸ� �� �¸�
						if (sum[0] < 22) {
							cout << player[0].getName() << "���� �̰���ϴ�!!!!!" << endl;
							cout << "���ñ� : " << battingmoney << "�� 2���� ";
							player[0].winmoney(battingmoney * 2);
							cout << battingmoney * 2 << "�� ��´�." << endl;

						}
					}
					//���� 21�� �Ѱ��� ��
					else if (sum[0] > 21) {
						//���� ������ 21���� �۱⸸ �ϸ� �� �¸�
						if (dsum < 22) {
							cout << "������ �¸�!!!!!!!!!" << endl;
							cout << "���ñ� : " << battingmoney << "�� 1.5���� " << battingmoney * 1.5 << "�� ��´�." << endl;
						}
					}
					//�Ѵ� 21������ ������ ��
					else {
						//������ ������ �� ���� ���� ũ�� ������ �¸� 
						if (dsum > sum[0]) {
							cout << "������ �¸�!!!!!!!!!" << endl;
							cout << "���ñ� : " << battingmoney << "�� 1.5���� " << battingmoney * 1.5 << "�� ��´�." << endl;
						}
						//�������� �� ũ�� ���¸�
						else {
							cout << player[0].getName() << "���� �̰���ϴ�!!!!!" << endl;
							cout << "���ñ� : " << battingmoney << "�� 2���� ";
							player[0].winmoney(battingmoney * 2);
							cout << battingmoney * 2 << "�� ��´�." << endl;
						}
					}
					goto onemoregame;
				}

				//�����ڰ� �������϶�
				else {
					//������ BLACK JACK�� �ƴҶ� ������ �� ���� ������ ��� �����ڰ� �ִ��� �Ǵ�.
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
					//���� ������ ���� �����ڰ� �ִٸ� ��ȿ����
					if (samecount > 0) {
						cout << samescore << " ������ ���� ������ ���Խ��ϴ�." << endl;
						cout << "���ñ��� ������� ���޵˴ϴ�." << endl;
						for (int i = 0; i < count; i++) {
							player[i].winmoney(money[i]);
						}
						break;
					}

					//�����ڵ��� ������ ���� �ٸ��� ���߿� BLACK JACK���� �̱�� ���
					else {
						for (int i = 0; i < count; i++) {
							if (sum[i] > 20 && sum[i] < 22) {
								cout << player[i].getName() << "���� BLACK JACK!!!!!!!!!!!!!!!!!!!" << endl << endl;
								cout << "���ñ� : " << battingmoney << "�� 2���� ";
								player[i].winmoney(battingmoney * 2);
								cout << battingmoney * 2 << "�� ��´�." << endl;
								goto onemoregame;
							}
						}
					}

					//�����ڵ��� ������ 21�� �ѱ�� ����� ������� ī��Ʈ
					int over21 = 0;
					for (int i = 0; i < count; i++) {
						if (sum[i] > 21) {
							over21++;
						}
					}

					//��� �����ڰ� 21�� �Ѱ��� ��
					if (over21 == (count - 1)) {
						//���� ���� 21���ѱ�� ��� ������� ���� �й�
						if (dsum > 21) {
							cout << "��� 21�� �Ѱ� �����ϴ�." << endl;
							cout << "���ñ��� ������� ���޵˴ϴ�." << endl;
							for (int i = 0; i < count; i++) {
								player[i].winmoney(money[i]);
							}
							break;
						}
						//������ 21�� �ѱ��� �ʾҴٸ� ������ �¸�
						else {
							cout << "������ �¸�!!!!!!!!!" << endl;
							cout << "���ñ� : " << battingmoney << "�� 1.5���� " << battingmoney * 1.5 << "�� ��´�." << endl;
							break;
						}
					}
					//�������� �Ѹ��̶� 21�� ���� �ʾҴٸ�
					else {
						int winner;									//������ ��ȣ�� ������ ����
						int max;
						if (dsum < 21)	max = dsum;				//������ ī�� �հ谡 20���� �̸� max�� �켱 ������ �հ踦 ����
						else {										//������ �հ谡 21�� ������ ����� �� 21�� ���� �ʴ� ����� �հ踦 ����
							for (int i = 0; i < count; i++) {
								if (sum[i] < 21) {
									max = sum[i];
									winner = i;
									break;
								}
							}
						}
						for (int i = 0; i < count; i++) {
							if (sum[i] < 21 && sum[i] > max) {		//�÷��̾���� ī�� �հ� �� 21���� �����鼭 ���� max���� ũ�� max�� �ش� ������ �ٲ��ش�
								max = sum[i];
								winner = i;
							}
						}

						if (dsum != max) {										//�����¸��� �ƴϸ� �̱� �÷��̾�� ���ñ��� 2�踦 ����
							cout << player[winner].getName() << "���� �¸� !!!!!!!!!!!!!!!!!!!" << endl << endl;
							cout << "���ñ� : " << battingmoney << "�� 2���� ";
							player[winner].winmoney(battingmoney * 2);
							cout << battingmoney * 2 << "�� ��´�." << endl;
							break;
						}
						else {							//max�� �ִ°��� ������ �հ��̸� ������ �¸�
							cout << "������ �¸�!!!!!!!!!" << endl;
							cout << "���ñ� : " << battingmoney << "�� 1.5���� " << battingmoney * 1.5 << "�� ��´�." << endl;
							break;
						}

					}
				}
			}
		}

		//�߰� ������ ������ ������ ����� ���ÿ� ���� ����� ����
	onemoregame:
		while (1) {
			cout << "�Ѱ��� �� �Ͻðڽ��ϱ�?? (y = yes, n = NO)";
			cin >> choice;
			if (isalpha(choice) == false || sizeof(choice) != sizeof(char)) {	//�Է��� ���� �ѱ����� Ȯ�� �� �ѱ��̸� ���۸� �����ش�
				exceptionError();
				continue;
			}
			if (choice == 'y' || choice == 'Y') {
				if (player[0].getMoney() < 10000) {		//����ڰ� �߰� ������ ��û�ص� �ڻ��� ������ �ȵǸ� ������ ���� �� �� ������ ����
					system("cls");
					cout << player[0].getName() << "���� ���� ������ ���� ���Ͽ� �ڵ����� ���� �˴ϴ�." << endl;
					return;
				}
				game.newdec();
				system("cls");
				break;
			}
			else if (choice == 'n' || choice == 'N')	//����ڰ� �� �̻��� ������ ������ ������ ���� ����
				return;
		}
	}
}