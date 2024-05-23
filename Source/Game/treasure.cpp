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
	if (this->GetTop() <= 75) {//�^��@�w���׫�^��
		this->SetTopLeft(0, 0);
		return true;
	}
	else if (obj_status == 2) {
		//�n�A���H�t�׳]�w(�n��_�l���t�פ@��
		double x = this->GetLeft() + 10 * cos(angle);
		double y = this->GetTop() + 10 * sin(angle);
		this->SetTopLeft(int(x), int(y));
	}
	return false; //�{���~�����
}

int Treasure::GetObjStatus() {
	return obj_status;
}

void Treasure::SetObjStatus(int value) {
	obj_status = value;
}

void Treasure::Move() {

}