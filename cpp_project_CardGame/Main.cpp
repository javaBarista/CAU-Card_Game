/*
파일명 : BlackJack.h, BlackJack.cpp, Card.h, Card.cpp, Player.h, Playgame.h, Playgame.cpp, Main.cpp
프로그램 설명: 이 프로그램은 블랙잭 게임으로 주어진 규칙에 따라 게임이 진행된다.(간락한 설명 자세한 내용은 보고서)
			  1. 사용자를 입력받는다.
			  2. 플레이어가 둘 이상의 경우 ostream을 이용해 추가 플레이어의 별칭을 만들어준다(실 세계에서 도박할때 다른 사람이름을 아는경우X)
			  3. 사용자가 배팅할 돈을 입력받는다.
			  4. 나머지 플레이어의 배팅금을 난수를 통해 입력받는다.
			  5. BlackJack 클래스를 호출해 기본 생성자를 통해 딜러와 각 플레이어들이 사용할 벡터에 Card 클래스에 makeCard()함수를 통해 카드를 생성
			  6. 추가로 카드가 필요하면 각 add함수를 통해 카드를 분배
			  7. 각 플레이어들의 합계를 구해 조건문으로 승자를 가려준다.
			  8. 반복문으로 추가게임을 할지 여부 선택
입력: 사용자의 이름과 배팅할 돈, ACE카드를 가지고 있을때 1과 11중 어느것으로 사용할지 여부, HIT혹은 STAND여부, 추가 게임을 진행할지 여부
출력: 배팅된 금액의 합계, 각 플레이어들의 카드, 카드의 합계 점수, 합계를 비교한 결과
날짜: 2018년 12월 07일
작성자: 20166439 강석민
*/
#include "Playgame.h"

int main() {
	PlayGame playgame;

	playgame.startGame();
}