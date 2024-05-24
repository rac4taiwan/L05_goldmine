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

string GoldMine::GetID() {
	return ID;
}

// ---------------------Stone----------------------
Stone::Stone(int s, int x, int y) {
	size = s;
	this->LoadBitmapByString({ "resources/stone1.bmp", "resources/stone2.bmp", "resources/stone3.bmp" }, RGB(255, 255, 255));
	this->SetFrameIndexOfBitmap(size - 1);
	this->SetTopLeft(x, y);
}

Stone::~Stone() {

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

string Stone::GetID() {
	return ID;
}

// ---------------------Diamond----------------------
Diamond::Diamond(int x, int y) {
	this->LoadBitmapByString({ "resources/diamond.bmp" }, RGB(0, 0, 0));
	this->SetTopLeft(x, y);
}

Diamond::Diamond() {

}

Diamond::~Diamond() {

}

int Diamond::Time() {
	return 20;
}

string Diamond::GetID() {
	return ID;
}

// ---------------------Can----------------------
Can::Can(int x, int y) {
	this->LoadBitmapByString({ "resources/can.bmp" }, RGB(0, 255, 0));
	this->SetTopLeft(x, y);
}

Can::~Can() {

}

int Can::Time() {
	return -15;
}

string Can::GetID() {
	return ID;
}

// ------------------Mouse-------------------
// ---------------------Can----------------------
Mouse::Mouse(int x, int y) {
	this->LoadBitmapByString({ "resources/mouse_left.bmp", "resources/mouse_right.bmp" }, RGB(255, 255, 255));
	this->SetTopLeft(x, y);
}

Mouse::~Mouse() {

}

int Mouse::Score() {
	return -7;
}

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

string Mouse::GetID() {
	return ID;
}

// ------------- Mummy ---------------
Mummy::Mummy(int i, int x, int y) {
	this->LoadBitmapByString({ "resources/mummy_0.bmp", "resources/mummy_1.bmp" }, RGB(0, 0, 0));
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

string Mummy::GetID() {
	return ID;
}