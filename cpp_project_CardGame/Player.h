#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "BlackJack.h"

//플레이어의 이름과 자산을 담아줄 함수를 만든다.
class Player {
private:
	string name;
	int money;
public:
	//기본형 함수를 포함해 getter와 setter들만 있어서 이너클래스로 작성(속도향상을 위해)
	Player() {
		name = "무명";
		money = 1000000;
	}

	string getName() {	return name;}	//이름을 리턴해 주는 getter

	void setName(string name) {	this->name = name;}		//이름을 새롭게 설정해 주는 setter

	int getMoney() {return money;}			//현재 자본을 리턴해 주는 getter

	void setMoney(int money) {	this->money -= money;}		//현재 돈에서 배팅후의 돈을 설정해 주는 setter
	
	void winmoney(int money) { this->money += money; }		//새로들어오는 머니값을 업데이트 해주는 setter

};

#endif // !PLAYER_H