#pragma once
#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Card.h"

//CardDec�� ��ӹ޴� BlackJackŬ���� �ۼ� �������� ������ ����� ī�� ����� ����ϴ� Ŭ�����̴�.
class BlackJack : public CardDec {
private:
	int sum;
	int key;
	int size;
	int drand;		//������ ���� ���� ���庯��
public:
	BlackJack();
//mycard ����--------------
	int myScore();		//�� ������ �հ踦 ������ �ش�.

	void addMyCard();	//ī�带 ���� ���޹޴´�.

	void myCardShow();	//���� ���� ������ ī�带 ����� �����ش�.

//dealerī�� ����---------------
	int dealerScore();		//������ ���ھ� ���

	void needdealerCard();	//������ ī�尡 �� �ʿ����� üũ�ϰ� �� �ʿ��ϸ� ������ �ִ� �Լ�

	void addDealerCard();	//�������� ī�带 ���� �� �����Ѵ�.

	void dealerCardShow();	//������ ī�带 �����ش�.(������ ������ �޸�ǥ��)

	void dealerOpenCard();	//������ ī�带 ���� �����ش�.(�޸�ī�嵵 ����)

//otherplayerī�� ����-------------------
	int otherScore(int i);		//�ٸ� �����ڵ��� ���ھ� ���

	void needOtherCard(int i);	//�ٸ� �÷��̾���� ī�尡 �� �ǿ����� üũ�ϰ� �ʿ��ϸ� ������ �ִ� �Լ� 

	void addotherCard(int i);	//�ٸ� �÷��̾���� ī�带 ������ �ִ� �Լ�

	void orherCardShow(int i);	//�ٸ� �÷��̾���� ī�带 ����� �����ִ� �Լ�
};

#endif // !BLACKJACK_H