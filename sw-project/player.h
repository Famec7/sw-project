#pragma once
#define MAX_HP 14		//플레이어의 최대 채력		//player hp is full <= 14글자임
#define MAX_SHIELD	 6	//플레이어의 최대 실드 게이지 //shield <= 6글자임

int HP = MAX_HP;					//HP 초기화
int shield = MAX_SHIELD;		//실드 초기화
int curPosX;								//현재 위치 X좌표
int curPosY;								//현재 위치 Y좌표

int bulletNum = 1;					//

int isShield_Flag = 0;

typedef struct bullet {
	int x;
	int y;

};

//화면에 Player 상태 출력
void TextPlayer() {

}
void UseShield() {
	isShield_Flag = 1;

}
void MoveLeft() {

}
void MoveRight() {

}
void MoveUp() {

}
void MoveDown() {

}
void Attack(char input) {

}

