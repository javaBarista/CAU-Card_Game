#pragma once
#ifndef PLAYGAME_H
#define PLAYGAME_H
#include "Player.h"
#include <sstream>
#include <ctype.h>


static int battingmoney; //배팅금액을 저장해줄 변수를 정적으로 선언


class PlayGame {
private:
	BlackJack game;	//게임이 진행되면 딜러와 플레이어들의 패를 관리해줄 클래스를 생성
	string name;
	int money[3];	//참가자들이 배팅할 돈을 저장해 줄 배열
	int count;		//참가자의 인원수를 저장해 줄 변수
public:
	PlayGame() {
		battingmoney = 0;	//배팅금 초기화
	}
	void startGame();
};

#endif // !PLAYGAME_H