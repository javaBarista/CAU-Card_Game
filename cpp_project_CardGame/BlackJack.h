#pragma once
#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Card.h"

//CardDec을 상속받는 BlackJack클래스 작성 전반적인 게임의 진행과 카드 출력을 담당하는 클래스이다.
class BlackJack : public CardDec {
private:
	int sum;
	int key;
	int size;
	int drand;		//딜러를 위한 난수 저장변수
public:
	BlackJack();
//mycard 관련--------------
	int myScore();		//내 점수의 합계를 리턴해 준다.

	void addMyCard();	//카드를 한장 지급받는다.

	void myCardShow();	//내가 현재 보유한 카드를 출력해 보여준다.

//dealer카드 관련---------------
	int dealerScore();		//딜러의 스코어 계산

	void needdealerCard();	//딜러가 카드가 더 필요한지 체크하고 더 필요하면 지급해 주는 함수

	void addDealerCard();	//딜러에게 카드를 한장 더 지급한다.

	void dealerCardShow();	//딜러의 카드를 보여준다.(딜러는 한장은 뒷면표시)

	void dealerOpenCard();	//딜러의 카드를 전부 보여준다.(뒷면카드도 오픈)

//otherplayer카드 관련-------------------
	int otherScore(int i);		//다른 참가자들의 스코어 계산

	void needOtherCard(int i);	//다른 플레이어들이 카드가 더 피요한지 체크하고 필요하면 지급해 주는 함수 

	void addotherCard(int i);	//다른 플레이어들의 카드를 에드해 주는 함수

	void orherCardShow(int i);	//다른 플레이어들의 카드를 출력해 보여주는 함수
};

#endif // !BLACKJACK_H