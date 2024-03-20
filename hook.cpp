#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Source/Game/mygame.h"
#include "Source/Game/mytreasure.h"
#include <cmath>

using namespace game_framework;

hookcpp::hookcpp() {

}

hookcpp::~hookcpp() {

}

void hookcpp::SetPosition(int x, int y) {
	mine.SetTopLeft(x, y);
}

int hookcpp::GetPositionX() {
	return mine.GetLeft();
}

int hookcpp::GetPositionY() {
	return mine.GetTop();
}

void hookcpp::ReleaseTab(hookcpp hook, int frameindex)
{
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (hook.GetPositionX() + 150 > 900 || hook.GetPositionX()  < 0 || hook.GetTop() +100 > 600) {
		status = 2;//�_�l�쩳�F �^�a�a
	}
	else {//�_�l�~��
		x = hook.GetPositionX() + 10 * cos(angle);
		y = hook.GetPositionY() - 10 * sin(angle);
		hook.SetPosition(int(x), int(y));
	}
}

void hookcpp::RollTab(hookcpp hook, int frameindex)
{
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (hook.GetPositionY() <= 75) {//�^��@�w���׫�^��
		status = 0;
		hook.SetPosition(400, 75);
	}
	else {
		//�n�A���H�t�׳]�w
		x = hook.GetPositionX() - 10 * cos(angle);
		y = hook.GetPositionY() + 10 * sin(angle);
		hook.SetPosition(int(x), int(y));
	}	
}

bool hookcpp::IsOverlap(hookcpp hook, int a, int b){
	if (hook.GetPositionY() == b) {
		if (hook.GetPositionX() == a) {
			return true;
		}
	}
	return false;
}
/*if (hook.GetPositionY() > bmp.GetPositionY() && hook.GetPositionY() < bmp.GetPositionY() + 85) {
	if (hook.GetPositionX() > bmp.GetPositionX() && hook.GetPositionX() < bmp.GetPositionX() + 150) {
		return true;
	}
}*/


bool hookcpp::GoldBackHome(GoldMine bmp, int frameindex) {
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;
	
	if (bmp.GetPositionY() <= 75) {//�^��@�w���׫�^��
		/*int v1 = Score_number[2].GetFrameIndexOfBitmap() + gold.Score() % 10;
		int v2 = Score_number[1].GetFrameIndexOfBitmap() + gold.Score() / 10 + v1 / 10;
		int v3 = Score_number[0].GetFrameIndexOfBitmap() + v2 / 10;
		Score_number[0].SetFrameIndexOfBitmap(v3);
		Score_number[1].SetFrameIndexOfBitmap(v2);
		Score_number[2].SetFrameIndexOfBitmap(v1);*/
		return true;
	}
	else {
		//�n�A���H�t�׳]�w(�n��_�l���t�פ@��
		x = bmp.GetPositionX() - 10 * cos(angle);
		y = bmp.GetPositionY() + 10 * sin(angle);
		bmp.SetPosition(int(x), int(y));

		return false; //�{���~�����
	}
}