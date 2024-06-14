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

void hookcpp::Setting() {
	// 載入鉤子擺動的圖片
	hook_stay.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", 
		"resources/hook_3.bmp", "resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", 
		"resources/hook_7.bmp", "resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", 
		"resources/hook_11.bmp", "resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp", 
		"resources/hook_15.bmp", "resources/hook_16.bmp", 
		"resources/hook_16.bmp", "resources/hook_15.bmp", "resources/hook_14.bmp", "resources/hook_13.bmp",
		"resources/hook_12.bmp", "resources/hook_11.bmp", "resources/hook_10.bmp", "resources/hook_9.bmp",
		"resources/hook_8.bmp", "resources/hook_7.bmp",	"resources/hook_6.bmp", "resources/hook_5.bmp",
		"resources/hook_4.bmp", "resources/hook_3.bmp", "resources/hook_2.bmp", "resources/hook_1.bmp", 
		}, RGB(255, 255, 255));
	hook_stay.SetTopLeft(375, 75);

	// 載入發射鉤子的圖片
	hook_attack.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", 
		"resources/hook_3.bmp", "resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", 
		"resources/hook_7.bmp","resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", 
		"resources/hook_11.bmp","resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp", 
		"resources/hook_15.bmp", "resources/hook_16.bmp" }, RGB(255, 255, 255));
	hook_attack.SetTopLeft(400, 75);

	hook_status = 0; //設定狀態：0=搖晃中，1=放線，2=收回線，3=非關卡途中
}

void hookcpp::OnMove() {
	if (hook_status == 0) {//鉤子擺動中
		hook_stay.SetAnimation(100, false);
	}
	else if (hook_status == 1) {//鉤子出發狩獵
		//決定角度
		frameindex = hook_stay.GetFrameIndexOfBitmap();
		if (frameindex > 15)frameindex = 32 - frameindex;
		//hook.SetHook(frameindex);
		hook_attack.SetFrameIndexOfBitmap(frameindex);
		//鉤子出發
		this->ReleaseTab(frameindex);
	}

	if (hook_status == 2) {
		//鉤子回家
		this->RollTab(frameindex);
	}
}

void hookcpp::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_DOWN && hook_status == 0) {
		hook_status = 1; //狀態：放線
	}
}

void hookcpp::OnShow() {
	if (hook_status == 0) {//鉤子擺動中
		hook_attack.UnshowBitmap();
		hook_stay.ShowBitmap();
	}
	else if (hook_status == 1 || hook_status == 2) {//鉤子出發
		hook_stay.UnshowBitmap();
		hook_attack.ShowBitmap();
	}
}

int hookcpp::GetFrameIndex() {
	frameindex = hook_attack.GetFrameIndexOfBitmap();
	return frameindex;
}

void hookcpp::SetAnimate(int delay, bool once) {
	hook_stay.SetAnimation(delay, once);
}

//-----------------------------

void hookcpp::ReleaseTab(int frameindex)
{
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;
	if (hook_attack.GetLeft() + 150 > 900 || hook_attack.GetLeft() < 0 || hook_attack.GetTop() + 100 > 600) {
		hook_status = 2;//鉤子到底了 回家吧
	}
	else {//鉤子繼續走
		x = hook_attack.GetLeft() + 10 * cos(angle);
		y = hook_attack.GetTop() - 10 * sin(angle);
		hook_attack.SetTopLeft(int(x), int(y));
	}	
}

void hookcpp::RollTab(int frameindex)
{
	//double angle = 340 - (10 * frameindex);
	//angle = angle * 3.1416 / 180;
	double angle = atan2(75 - hook_attack.GetTop(), hook_attack.GetLeft() - 385);//xy對調：會畫圓


	if (hook_attack.GetTop() <= 75) {//回到一定高度後回收
		hook_status = 0;
		hook_attack.SetTopLeft(385, 75);
		speed = 1.0;
	}
	else {
		//要再乘以速度設定
		x = hook_attack.GetLeft() - 10 * cos(angle) * speed;
		y = hook_attack.GetTop() + 10 * sin(angle) * speed;
		hook_attack.SetTopLeft(int(x), int(y));
	}	
}

bool hookcpp::IsOverlap(int ox, int oy, int ow, int oh){
	double angle = 340 - (10 * hook_attack.GetFrameIndexOfBitmap());
	angle = angle * 3.1416 / 180;
	double hx = hook_attack.GetLeft() + 30 + (hook_attack.GetWidth() / 2) + 10 * cos(angle);
	double hy = hook_attack.GetTop() - 10 * sin(angle);
	double ocx = ox + (double(ow) / 2);
	double ocy = oy + (double(oh) / 2);

	if (hy > ocy - 100 && hy < ocy) {
		if (hx > ocx && hx < ocx + 81) {
			hook_status = 2;//鉤子回家
			return true;
		}
	}
	return false;
}

bool hookcpp::operator==(Treasure* obj) {
	double angle = 340 - (10 * hook_attack.GetFrameIndexOfBitmap());
	angle = angle * 3.1416 / 180;
	double hx = hook_attack.GetLeft() + 30 + (hook_attack.GetWidth() / 2) + 10 * cos(angle);
	double hy = hook_attack.GetTop() - 10 * sin(angle);
	double ocx = obj->GetLeft() + (double(obj->GetWidth()) / 2);
	double ocy = obj->GetTop() + (double(obj->GetHeight()) / 2);

	if (hy > ocy - 100 && hy < ocy) {
		if (hx > ocx && hx < ocx + 81) {
			hook_status = 2;//鉤子回家
			return true;
		}
	}
	return false;
}

void hookcpp::SetSpeed(double value) {
	speed = value;
}

void hookcpp::BeginState() {
	hook_status = 0;
	hook_attack.SetTopLeft(385, 75);
	speed = 1.0;
}