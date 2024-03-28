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
	hook_stay.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", "resources/hook_3.bmp",
		"resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", "resources/hook_7.bmp",
		"resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", "resources/hook_11.bmp",
		"resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp" , "resources/hook_13.bmp",
		"resources/hook_12.bmp","resources/hook_11.bmp", "resources/hook_10.bmp", "resources/hook_9.bmp",
		"resources/hook_8.bmp", "resources/hook_7.bmp",	"resources/hook_6.bmp", "resources/hook_5.bmp",
		"resources/hook_4.bmp", "resources/hook_3.bmp", "resources/hook_2.bmp", "resources/hook_1.bmp" }, RGB(255, 255, 255));
	hook_stay.SetTopLeft(375, 75);

	hook_attack.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", "resources/hook_3.bmp",
		"resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", "resources/hook_7.bmp",
		"resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", "resources/hook_11.bmp",
		"resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp" }, RGB(255, 255, 255));
	hook_attack.SetTopLeft(400, 75);

	hook_status = 0; //�]�w���A�G0=�n�̤��A1=��u�A2=���^�u�A3=�D���d�~��
}

void hookcpp::OnMove() {
	if (hook_status == 0) {//�_�l�\�ʤ�
		hook_stay.SetAnimation(100, false);
	}
	else if (hook_status == 1) {//�_�l�X�o���y
		//�M�w����
		//frameindex = hook_stay.GetFrameIndex();
		frameindex = hook_stay.GetFrameIndexOfBitmap();
		if (frameindex > 13)frameindex = 27 - frameindex;
		//hook.SetHook(frameindex);
		hook_attack.SetFrameIndexOfBitmap(frameindex);
		//�_�l�X�o
		this->ReleaseTab(frameindex);

	}

	if (hook_status == 2) {
		//�_�l�^�a
		this->RollTab(frameindex);
	}
}

void hookcpp::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_DOWN && hook_status == 0) {
		hook_status = 1; //���A�G��u
	}
}

void hookcpp::OnShow() {
	if (hook_status == 0) {//�_�l�\�ʤ�
		hook_attack.UnshowBitmap();
		hook_stay.ShowBitmap();
	}
	else if (hook_status == 1 || hook_status == 2) {//�_�l�X�o
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
		hook_status = 2;//�_�l�쩳�F �^�a�a
	}
	else {//�_�l�~��
		x = hook_attack.GetLeft() + 10 * cos(angle);
		y = hook_attack.GetTop() - 10 * sin(angle);
		hook_attack.SetTopLeft(int(x), int(y));
	}
	
	/*if (obj_status == 1) {//�q���y�����A�ˬd�_�l�q���O�_���|
		//���C���q���gfor�j��Ggold[i]�Bobj_status[i]
		if (IsOverlap(390, 300)) {
			obj_status = 2;//���A�G�I���^�a���W
			hook_status = 2;
		}
		//�j�鵲��
	}*/
	
}

void hookcpp::RollTab(int frameindex)
{
	double angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (hook_attack.GetTop() <= 75) {//�^��@�w���׫�^��
		hook_status = 0;
		hook_attack.SetTopLeft(400, 75);
	}
	else {
		//�n�A���H�t�׳]�w
		x = hook_attack.GetLeft() - 10 * cos(angle);
		y = hook_attack.GetTop() + 10 * sin(angle);
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
			hook_status = 2;
			return true;
		}
	}
	return false;
}