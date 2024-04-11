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

GoldMine::GoldMine() {

}

GoldMine::~GoldMine() {

}

void GoldMine::SetSize(int s) {
	size = s;
	mine.LoadBitmapByString({ "resources/goldmine1.bmp", "resources/goldmine2.bmp", "resources/goldmine3.bmp" }, RGB(255, 255, 255));
	mine.SetFrameIndexOfBitmap(size-1);
}

double GoldMine::Catch() {
	if (size == 1) {
		return 0.95;
	}
	else if (size == 2) {
		return 0.5;
	}
	else if (size == 3) {
		return 0.8;
	}
	else {
		return 1.0;
	}
}

int GoldMine::Score() {
	if (size == 1) {
		return 10;
	}
	else if (size == 2) {
		return 20;
	}
	else if (size == 3) {
		return 30;
	}
	else {
		return 0;
	}
}

void GoldMine::Show() {
	mine.ShowBitmap();
}

void GoldMine::UnShow() {
	mine.UnshowBitmap();
}

void GoldMine::SetPosition(int x, int y) {
	mine.SetTopLeft(x, y);
}

int GoldMine::GetPositionX() {
	return mine.GetLeft();
}

int GoldMine::GetPositionY() {
	return mine.GetTop();
}

int GoldMine::GetWidth() {
	return mine.GetWidth();
}

int GoldMine::GetHeight() {
	return mine.GetHeight();
}

bool GoldMine::GoldBackHome(int frameindex) {
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (mine.GetTop() <= 75) {//回到一定高度後回收
		mine.SetTopLeft(0, 0);
		return true;
	}
	else {
		//要再乘以速度設定(要跟鉤子的速度一樣
		double x = mine.GetLeft() - 10 * cos(angle);
		double y = mine.GetTop() + 10 * sin(angle);
		mine.SetTopLeft(int(x), int(y));

		return false; //程式繼續執行
	}
}

int GoldMine::GetObjStatus() {
	return obj_status;
}

void GoldMine::SetObjStatus(int value) {
	obj_status = value;
}

// ---------------------Stone----------------------
Stone::Stone() {

}

Stone::~Stone() {

}

void Stone::SetSize(int s) {
	size = s;
	mine.LoadBitmapByString({ "resources/stone1.bmp", "resources/stone2.bmp", "resources/stone3.bmp" }, RGB(255, 255, 255));
	mine.SetFrameIndexOfBitmap(size - 1);
}

int Stone::Score() {
	if (size == 1) {
		return -10;
	}
	else if (size == 2) {
		return -20;
	}
	else if (size == 3) {
		return -30;
	}
	else {
		return 0;
	}
}

void Stone::SetPosition(int x, int y) {
	mine.SetTopLeft(x, y);
}

void Stone::Show() {
	mine.ShowBitmap();
}

void Stone::UnShow() {
	mine.UnshowBitmap();
}

int Stone::GetPositionX() {
	return mine.GetLeft();
}

int Stone::GetPositionY() {
	return mine.GetTop();
}

int Stone::GetWidth() {
	return mine.GetWidth();
}

int Stone::GetHeight() {
	return mine.GetHeight();
}

bool Stone::GoldBackHome(int frameindex) {
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (mine.GetTop() <= 75) {//回到一定高度後回收
		return true;
	}
	else {
		//要再乘以速度設定(要跟鉤子的速度一樣
		double x = mine.GetLeft() - 10 * cos(angle);
		double y = mine.GetTop() + 10 * sin(angle);
		mine.SetTopLeft(int(x), int(y));

		return false; //程式繼續執行
	}
}

int Stone::GetObjStatus() {
	return obj_status;
}

void Stone::SetObjStatus(int value) {
	obj_status = value;
}