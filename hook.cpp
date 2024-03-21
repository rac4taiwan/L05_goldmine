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

void hookcpp::Show() {
	mine.ShowBitmap();
}

void hookcpp::UnShow() {
	mine.UnshowBitmap();
}

void hookcpp::SetPosition(int x, int y) {
	mine.SetTopLeft(x, y);
}

void hookcpp::LoadTheTab() {
	mine.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", "resources/hook_3.bmp",
		"resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", "resources/hook_7.bmp",
		"resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", "resources/hook_11.bmp",
		"resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp" , "resources/hook_13.bmp",
		"resources/hook_12.bmp","resources/hook_11.bmp", "resources/hook_10.bmp", "resources/hook_9.bmp",
		"resources/hook_8.bmp", "resources/hook_7.bmp",	"resources/hook_6.bmp", "resources/hook_5.bmp",
		"resources/hook_4.bmp", "resources/hook_3.bmp", "resources/hook_2.bmp", "resources/hook_1.bmp" }, RGB(255, 255, 255));
	mine.SetTopLeft(375, 75);
}

void hookcpp::LoadHook() {
	mine.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", "resources/hook_3.bmp",
		"resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", "resources/hook_7.bmp",
		"resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", "resources/hook_11.bmp",
		"resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp" }, RGB(255, 255, 255));
	mine.SetTopLeft(400, 75);
}

void hookcpp::SetHook(int frameindex) {
	mine.SetFrameIndexOfBitmap(frameindex);
}



int hookcpp::GetPositionX() {
	return mine.GetLeft();
}

int hookcpp::GetPositionY() {
	return mine.GetTop();
}

int hookcpp::GetFrameIndex() {
	return mine.GetFrameIndexOfBitmap();
}

void hookcpp::SetAnimate(int delay, bool once) {
	mine.SetAnimation(delay, once);
}

//-----------------------------

void hookcpp::ReleaseTab(int frameindex)
{
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;
	if (mine.GetLeft() + 150 > 900 || mine.GetLeft() < 0 || mine.GetTop() + 100 > 600) {
		hook_status = 2;//�_�l�쩳�F �^�a�a
	}
	else {//�_�l�~��
		x = mine.GetLeft() + 10 * cos(angle);
		y = mine.GetTop() - 10 * sin(angle);
		mine.SetTopLeft(int(x), int(y));
	}
	
	if (obj_status == 1) {//�q���y�����A�ˬd�_�l�q���O�_���|
		//���C���q���gfor�j��Ggold[i]�Bobj_status[i]
		if (IsOverlap(390, 300)) {
			obj_status = 2;//���A�G�I���^�a���W
			hook_status = 2;
		}
		//�j�鵲��
	}
	
}

void hookcpp::RollTab(int frameindex)
{
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (mine.GetTop() <= 75) {//�^��@�w���׫�^��
		hook_status = 0;
		mine.SetTopLeft(400, 75);
	}
	else {
		//�n�A���H�t�׳]�w
		x = mine.GetLeft() - 10 * cos(angle);
		y = mine.GetTop() + 10 * sin(angle);
		mine.SetTopLeft(int(x), int(y));
	}	
}

bool hookcpp::IsOverlap(int a, int b){
	if (mine.GetTop() > b && mine.GetTop() < b + 72) {
		if (mine.GetLeft() > a && mine.GetLeft() < a + 81) {
			return true;
		}
	}
	return false;
}