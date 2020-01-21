#pragma once
#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
//�� ����� ��ũ�η� ���ڿ� �����Ͽ� ���� �������� ������ �ٿ��ش�
#define spade 0
#define hart 1
#define dia 2
#define clover 3
using namespace std;

class CardDec {
protected:
	int dec[52];		//ī�嵦�� ������ ���� 
	vector <int> mycard;	//���͸� �̿��� ���� ������ ī�带 ����
	vector <int> dealercard;	//������ ī�带 �������� ������ ����
	vector<vector<int>> othercard;		//2���� ���͸� �̿��� �ٸ� �÷��̾��� ī�带 ����
	string up;			//ī���� ���� �׵θ�
	string shape[4];	//ī���� ���̸��
	string number[13];	//ī���� ���ڸ��
	string down;		//ī���� �Ʒ��� �׵θ�
public:
	CardDec();
	int makecard();

	void newdec() {
		for (int i = 0; i < 52; i++) {
			dec[i] = i;
		}
	}

	//�������ִ� �� ����� �����ִ� �Լ�
	void decshape();

	//�⺻���� ���� �����ִ� �Լ�
	void rule();
};
#endif // !CARD_H