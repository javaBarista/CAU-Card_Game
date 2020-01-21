#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "BlackJack.h"

//�÷��̾��� �̸��� �ڻ��� ����� �Լ��� �����.
class Player {
private:
	string name;
	int money;
public:
	//�⺻�� �Լ��� ������ getter�� setter�鸸 �־ �̳�Ŭ������ �ۼ�(�ӵ������ ����)
	Player() {
		name = "����";
		money = 1000000;
	}

	string getName() {	return name;}	//�̸��� ������ �ִ� getter

	void setName(string name) {	this->name = name;}		//�̸��� ���Ӱ� ������ �ִ� setter

	int getMoney() {return money;}			//���� �ں��� ������ �ִ� getter

	void setMoney(int money) {	this->money -= money;}		//���� ������ �������� ���� ������ �ִ� setter
	
	void winmoney(int money) { this->money += money; }		//���ε����� �Ӵϰ��� ������Ʈ ���ִ� setter

};

#endif // !PLAYER_H