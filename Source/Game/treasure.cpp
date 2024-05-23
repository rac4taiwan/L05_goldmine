#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "mytreasure.h"

using namespace game_framework;

Treasure::Treasure() {

}

Treasure::~Treasure() {

}

double Treasure::Catch() {
	return 0.9;
}

int Treasure::Score() {
	return 0;
}

int Treasure::Time() {
	return 0;
}

bool Treasure::GoldBackHome(double angle) {
	if (this->GetTop() <= 75) {//回到一定高度後回收
		this->SetTopLeft(0, 0);
		return true;
	}
	else if (obj_status == 2) {
		//要再乘以速度設定(要跟鉤子的速度一樣
		double x = this->GetLeft() + 10 * cos(angle);
		double y = this->GetTop() + 10 * sin(angle);
		this->SetTopLeft(int(x), int(y));
	}
	return false; //程式繼續執行
}

int Treasure::GetObjStatus() {
	return obj_status;
}

void Treasure::SetObjStatus(int value) {
	obj_status = value;
}

void Treasure::Move() {

}