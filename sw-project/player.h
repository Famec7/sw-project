#pragma once
#include "Cursor.h"
#define MAX_HP 14		//플레이어의 최대 채력		//player hp is full <= 14글자임
#define MAX_SHIELD	 6	//플레이어의 최대 실드 게이지 //shield <= 6글자임

int HP = MAX_HP;					//HP 초기화
int shield = MAX_SHIELD;		//실드 초기화
COORD mainCharacterCurPos;

int bulletNum = 1;					//

int isShield_Flag = 0;

int 

void PlayerShowModel() {

}
void PlayerDeleteModel() {

}
void PlayerDetectedCollision() {

}
void PlayerShiftLeft() {

}
void PlayerShiftRight() {

}
void PlayerShiftUp() {

}
void PlayerShiftDown() {

}
//화면에 Player 상태 출력
void PlayerStatOutput() {

}
void ProcessKeyInput() {

}
void UseShield() {
	isShield_Flag = 1;

}
void Attack(char input) {

}

