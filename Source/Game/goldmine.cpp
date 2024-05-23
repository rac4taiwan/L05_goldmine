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

GoldMine::GoldMine(int s, int x, int y) {
	size = s;
	this->LoadBitmapByString({ "resources/goldmine1.bmp", "resources/goldmine2.bmp", "resources/goldmine3.bmp" }, RGB(255, 255, 255));
	this->SetFrameIndexOfBitmap(size - 1);
	this->SetTopLeft(x, y);
}

GoldMine::GoldMine() {

}

GoldMine::~GoldMine() {

}

/*void GoldMine::SetSize(int s) {
	//size = s;
	Size(s);
	LoadBitmapByString({ "resources/goldmine1.bmp", "resources/goldmine2.bmp", "resources/goldmine3.bmp" }, RGB(255, 255, 255));
	SetFrameIndexOfBitmap(size-1);
}

void GoldMine::Size(int s) {
	size = s;
}*/

double GoldMine::Catch() {
	if (size == 1) {
		return 0.95;
	}
	else if (size == 2) {
		return 0.65;
	}
	else if (size == 3) {
		return 0.3;
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

bool GoldMine::GoldBackHome(double angle) {

	if (this->GetTop() <= 75) {//回到一定高度後回收
		SetTopLeft(0, 0);
		return true;
	}
	else if (obj_status == 2) {
		//要再乘以速度設定(要跟鉤子的速度一樣
		double x, y;
		if (size == 1) {
			x = GetLeft() + 10 * cos(angle) * 0.95;
			y = GetTop() + 10 * sin(angle) * 0.95;
		}
		else if (size == 2) {
			x = GetLeft() + 10 * cos(angle) * 0.65;
			y = GetTop() + 10 * sin(angle) * 0.65;
		}
		else {
			x = GetLeft() + 10 * cos(angle) * 0.3;
			y = GetTop() + 10 * sin(angle) * 0.3;
		}
		SetTopLeft(int(x), int(y));

	}
	return false; //程式繼續執行

}

/*int GoldMine::GetObjStatus() {
	return obj_status;
}

void GoldMine::SetObjStatus(int value) {
	obj_status = value;
	//0=
}*/

// ---------------------Stone----------------------
Stone::Stone(int s, int x, int y) {
	size = s;
	this->LoadBitmapByString({ "resources/stone1.bmp", "resources/stone2.bmp", "resources/stone3.bmp" }, RGB(255, 255, 255));
	this->SetFrameIndexOfBitmap(size - 1);
	this->SetTopLeft(x, y);
}

Stone::~Stone() {

}

/*double Stone::Catch() {
	if (size == 1) {
		return 0.95;
	}
	else if (size == 2) {
		return 0.65;
	}
	else if (size == 3) {
		return 0.3;
	}
	else {
		return 1.0;
	}
}

void Stone::SetSize(int s) {
	Size(s);
	size = s;
	this->LoadBitmapByString({ "resources/stone1.bmp", "resources/stone2.bmp", "resources/stone3.bmp" }, RGB(255, 255, 255));
	this->SetFrameIndexOfBitmap(size - 1);
}*/

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

/*void Stone::SetPosition(int x, int y) {
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
}*/

/*bool Stone::GoldBackHome(double angle) {

	if (mine.GetTop() <= 75) {//回到一定高度後回收
		mine.SetTopLeft(0, 0);
		return true;
	}
	else if (obj_status == 2){
		//要再乘以速度設定(要跟鉤子的速度一樣
		double x = mine.GetLeft() + 10 * cos(angle);
		double y = mine.GetTop() + 10 * sin(angle);
		mine.SetTopLeft(int(x), int(y));
	}
	return false; //程式繼續執行
}*/

/*bool Stone::GoldBackHome(double angle) {

	if (mine.GetTop() <= 75) {//回到一定高度後回收
		this->SetTopLeft(0, 0);
		return true;
	}
	else if (obj_status == 2) {
		//要再乘以速度設定(要跟鉤子的速度一樣
		double x, y;
		if (size == 1) {
			x = this->GetLeft() + 10 * cos(angle) * 0.95;
			y = this->GetTop() + 10 * sin(angle) * 0.95;
		}
		else if (size == 2) {
			x = this->GetLeft() + 10 * cos(angle) * 0.65;
			y = this->GetTop() + 10 * sin(angle) * 0.65;
		}
		else {
			x = this->GetLeft() + 10 * cos(angle) * 0.3;
			y = this->GetTop() + 10 * sin(angle) * 0.3;
		}
		this->SetTopLeft(int(x), int(y));

	}
	return false; //程式繼續執行

}

int Stone::GetObjStatus() {
	return obj_status;
}

void Stone::SetObjStatus(int value) {
	obj_status = value;
}*/

// ---------------------Diamond----------------------
Diamond::Diamond(int x, int y) {
	this->LoadBitmapByString({ "resources/diamond.bmp" }, RGB(0, 0, 0));
	this->SetTopLeft(x, y);
}

Diamond::Diamond() {

}

Diamond::~Diamond() {

}

/*void Diamond::Set() {
	this->LoadBitmapByString({ "resources/diamond.bmp" }, RGB(0, 0, 0));
}

double Diamond::Catch() {
	return 0.9;
}*/

int Diamond::Time() {
	return 20;
}

/*void Diamond::Show() {
	mine.ShowBitmap();
}

void Diamond::UnShow() {
	mine.UnshowBitmap();
}

void Diamond::SetPosition(int x, int y) {
	mine.SetTopLeft(x, y);
}

int Diamond::GetPositionX() {
	return mine.GetLeft();
}

int Diamond::GetPositionY() {
	return mine.GetTop();
}

int Diamond::GetWidth() {
	return mine.GetWidth();
}

int Diamond::GetHeight() {
	return mine.GetHeight();
}

bool Diamond::GoldBackHome(double angle) {

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
}*/

/*int Diamond::GetObjStatus() {
	return obj_status;
}

void Diamond::SetObjStatus(int value) {
	obj_status = value;
}*/

// ---------------------Can----------------------
Can::Can(int x, int y) {
	this->LoadBitmapByString({ "resources/can.bmp" }, RGB(0, 255, 0));
	this->SetTopLeft(x, y);
}

Can::~Can() {

}

/*void Can::Set() {
	this->LoadBitmapByString({ "resources/can.bmp" }, RGB(0, 255, 0));
}

double Can::Catch() {
	return 1.0;
}*/

int Can::Time() {
	return -15;
}

/*void Can::Show() {
	mine.ShowBitmap();
}

void Can::UnShow() {
	mine.UnshowBitmap();
}

void Can::SetPosition(int x, int y) {
	mine.SetTopLeft(x, y);
}

int Can::GetPositionX() {
	return mine.GetLeft();
}

int Can::GetPositionY() {
	return mine.GetTop();
}

int Can::GetWidth() {
	return mine.GetWidth();
}

int Can::GetHeight() {
	return mine.GetHeight();
}

bool Can::GoldBackHome(double angle) {

	if (mine.GetTop() <= 75) {//回到一定高度後回收
		mine.SetTopLeft(0, 0);
		return true;
	}
	else if (obj_status == 2) {
		//要再乘以速度設定(要跟鉤子的速度一樣
		double x = mine.GetLeft() + 10 * cos(angle);
		double y = mine.GetTop() + 10 * sin(angle);
		mine.SetTopLeft(int(x), int(y));
	}
	return false; //程式繼續執行
}

int Can::GetObjStatus() {
	return obj_status;
}

void Can::SetObjStatus(int value) {
	obj_status = value;
}*/

// ------------------Mouse-------------------
Mouse::Mouse(int x, int y) {
	this->LoadBitmapByString({ "resources/mouse_left.bmp", "resources/mouse_right.bmp" }, RGB(255, 255, 255));
	this->SetTopLeft(x, y);
}

Mouse::~Mouse() {

}

/*void Mouse::Set() {
	this->LoadBitmapByString({ "resources/mouse_left.bmp", "resources/mouse_right.bmp" }, RGB(255, 255, 255));
}

double Mouse::Catch() {
	return 1.0;
}*/

int Mouse::Score() {
	return -7;
}

/*void Mouse::Show() {
	mine.ShowBitmap();
}

void Mouse::UnShow() {
	mine.UnshowBitmap();
}

void Mouse::SetPosition(int x, int y) {
	mine.SetTopLeft(x, y);
}

int Mouse::GetPositionX() {
	return mine.GetLeft();
}

int Mouse::GetPositionY() {
	return mine.GetTop();
}

int Mouse::GetWidth() {
	return mine.GetWidth();
}

int Mouse::GetHeight() {
	return mine.GetHeight();
}

bool Mouse::GoldBackHome(double angle) {

	if (mine.GetTop() <= 75) {//回到一定高度後回收
		mine.SetTopLeft(0, 0);
		return true;
	}
	else if (obj_status == 2) {
		//要再乘以速度設定(要跟鉤子的速度一樣
		double x = mine.GetLeft() + 10 * cos(angle);
		double y = mine.GetTop() + 10 * sin(angle);
		mine.SetTopLeft(int(x), int(y));
	}
	return false; //程式繼續執行
}

int Mouse::GetObjStatus() {
	return obj_status;
}

void Mouse::SetObjStatus(int value) {
	obj_status = value;
}*/

void Mouse::Move() {
	if (this->GetFrameIndexOfBitmap() == 0) {
		count += 1;
		if (count == 100) {
			this->SetFrameIndexOfBitmap(1);
			count = 0;
		}
		else {
			this->SetTopLeft(this->GetLeft() - 2, this->GetTop());
		}
	}
	else {
		count += 1;
		if (count == 100) {
			this->SetFrameIndexOfBitmap(0);
			count = 0;
		}
		else {
			this->SetTopLeft(this->GetLeft() + 2, this->GetTop());
		}
	}
}

Mummy::Mummy(int i, int x, int y) {
	this->LoadBitmapByString({ "resources/mummy_0.bmp", "resources/mummy_1.bmp"}, RGB(0,0,0));
	if (i == 0) {
		this->SetFrameIndexOfBitmap(0);
	}
	else {
		this->SetFrameIndexOfBitmap(1);
		obj_status = 3;
	}
	this->SetTopLeft(x, y);
}

Mummy::Mummy() {

}

Mummy::~Mummy() {

}

int Mummy::Score() {
	return 30;
}

void Mummy::SetObjStatus(int value) {
	obj_status = value;
	this->SetFrameIndexOfBitmap(0);
}