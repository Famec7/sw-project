#pragma once

struct TimeStruct {
	double time;	// 게임의 총 시간 저장
	double deltaTime;
};

extern TimeStruct Time;

void InitTime();
void UpdateTime();