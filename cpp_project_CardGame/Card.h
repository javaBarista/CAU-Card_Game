#pragma once
#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
//각 모양을 매크로로 숫자에 정의하여 개발 과정에서 오류를 줄여준다
#define spade 0
#define hart 1
#define dia 2
#define clover 3
using namespace std;

class CardDec {
protected:
	int dec[52];		//카드덱을 저장할 변수 
	vector <int> mycard;	//벡터를 이용해 내가 보유한 카드를 저장
	vector <int> dealercard;	//딜러의 카드를 동적으로 저장할 벡터
	vector<vector<int>> othercard;		//2차원 벡터를 이용해 다른 플레이어의 카드를 저장
	string up;			//카드의 윗쪽 테두리
	string shape[4];	//카드의 무늬모양
	string number[13];	//카드의 숫자모양
	string down;		//카드의 아랫쪽 테두리
public:
	CardDec();
	int makecard();

	void newdec() {
		for (int i = 0; i < 52; i++) {
			dec[i] = i;
		}
	}

	//엎어져있는 덱 모양을 보여주는 함수
	void decshape();

	//기본적인 룰을 보여주는 함수
	void rule();
};
#endif // !CARD_H