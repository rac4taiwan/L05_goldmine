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

bool GoldMine::Overlap(CMovingBitmap hook, GoldMine bmp) {
	return mine.IsOverlap(hook, bmp);
}


// ---------------------Stone----------------------
Stone::Stone() {

}

Stone::~Stone() {

}

void Stone::SetSize(int s) {
	size = s;
	mine.LoadBitmapByString({ "resources/stone1.bmp", "resources/stone2.bmp", "resources/stone3.bmp" }, RGB(0, 0, 0));
	mine.SetFrameIndexOfBitmap(size - 1);
}