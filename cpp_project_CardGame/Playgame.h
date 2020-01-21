#pragma once
#ifndef PLAYGAME_H
#define PLAYGAME_H
#include "Player.h"
#include <sstream>
#include <ctype.h>


static int battingmoney; //���ñݾ��� �������� ������ �������� ����


class PlayGame {
private:
	BlackJack game;	//������ ����Ǹ� ������ �÷��̾���� �и� �������� Ŭ������ ����
	string name;
	int money[3];	//�����ڵ��� ������ ���� ������ �� �迭
	int count;		//�������� �ο����� ������ �� ����
public:
	PlayGame() {
		battingmoney = 0;	//���ñ� �ʱ�ȭ
	}
	void startGame();
};

#endif // !PLAYGAME_H