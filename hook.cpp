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

void hookcpp::LoadTheTab() {
	mine.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", "resources/hook_3.bmp",
		"resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", "resources/hook_7.bmp",
		"resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", "resources/hook_11.bmp",
		"resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp" , "resources/hook_13.bmp",
		"resources/hook_12.bmp","resources/hook_11.bmp", "resources/hook_10.bmp", "resources/hook_9.bmp",
		"resources/hook_8.bmp", "resources/hook_7.bmp",	"resources/hook_6.bmp", "resources/hook_5.bmp",
		"resources/hook_4.bmp", "resources/hook_3.bmp", "resources/hook_2.bmp", "resources/hook_1.bmp" }, RGB(255, 255, 255));
}

void hookcpp::LoadHook() {
	mine.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", "resources/hook_3.bmp",
		"resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", "resources/hook_7.bmp",
		"resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", "resources/hook_11.bmp",
		"resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp" }, RGB(255, 255, 255));
}

void hookcpp::SetHook(int frameindex) {
	mine.SetFrameIndexOfBitmap(frameindex);
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

int hookcpp::GetFrameIndex() {
	return mine.GetFrameIndexOfBitmap();
}

void hookcpp::SetAnimate(int delay, bool once) {
	mine.SetAnimation(delay, once);
}

//-----------------------------

void hookcpp::ReleaseTab(hookcpp hook, int frameindex)
{
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (hook.GetPositionX() + 150 > 900 || hook.GetPositionX() < 0 || hook.GetPositionY() + 100 > 600) {
		hook_status = 2;//鉤子到底了 回家吧
	}
	else {//鉤子繼續走
		x = hook.GetPositionX() + 10 * cos(angle);
		y = hook.GetPositionY() - 10 * sin(angle);
		hook.SetPosition(int(x), int(y));
	}
	
	if (obj_status == 1) {//礦物流浪中，檢查鉤子礦物是否重疊
		//為每個礦物寫for迴圈：gold[i]、obj_status[i]
		if (hookcpp::IsOverlap(hook, 390, 300)) {
			obj_status = 2;//狀態：碰到後回家路上
			hook_status = 2;
		}
		//迴圈結束
	}
	
}

void hookcpp::RollTab(hookcpp hook, int frameindex)
{
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (hook.GetPositionY() <= 75) {//回到一定高度後回收
		hook_status = 0;
		hook.SetPosition(400, 75);
	}
	else {
		//要再乘以速度設定
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
	
	if (bmp.GetPositionY() <= 75) {//回到一定高度後回收
		/*int v1 = Score_number[2].GetFrameIndexOfBitmap() + gold.Score() % 10;
		int v2 = Score_number[1].GetFrameIndexOfBitmap() + gold.Score() / 10 + v1 / 10;
		int v3 = Score_number[0].GetFrameIndexOfBitmap() + v2 / 10;
		Score_number[0].SetFrameIndexOfBitmap(v3);
		Score_number[1].SetFrameIndexOfBitmap(v2);
		Score_number[2].SetFrameIndexOfBitmap(v1);*/
		obj_status = 0; 
		return true;
	}
	else {
		//要再乘以速度設定(要跟鉤子的速度一樣
		x = bmp.GetPositionX() - 10 * cos(angle);
		y = bmp.GetPositionY() + 10 * sin(angle);
		bmp.SetPosition(int(x), int(y));

		return false; //程式繼續執行
	}
}