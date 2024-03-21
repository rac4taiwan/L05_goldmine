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

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	Stage.LoadBitmapByString({ "resources/Stage1_0.bmp", "resources/Stage1_1.bmp", "resources/Stage1_2.bmp", "resources/Stage1_3.bmp" }, RGB(0,0,0));
	Stage.SetFrameIndexOfBitmap(0);
	Stage.SetTopLeft(0, 0);
	background.LoadBitmapByString({ "resources/background.bmp" });
	background.SetTopLeft(0, 0);
	Time.LoadBitmapByString({ "resources/Time.bmp" }, RGB(255,255,255));
	Time.SetTopLeft(670, 30);
	for (int i = 0; i < 3; i++) {
		Time_number[i].LoadBitmapByString({ "resources/T0.bmp", "resources/T1.bmp", "resources/T2.bmp", "resources/T3.bmp", "resources/T4.bmp", "resources/T5.bmp", "resources/T6.bmp", "resources/T7.bmp", "resources/T8.bmp", "resources/T9.bmp" }, RGB(255, 255, 255));
		Time_number[i].SetTopLeft(775+i*(25), 30);
	}
	Time_number[0].SetFrameIndexOfBitmap(1);
	Time_number[1].SetFrameIndexOfBitmap(0);
	Time_number[2].SetFrameIndexOfBitmap(3);
	Times_up.LoadBitmapByString({ "resources/times_up.bmp" }, RGB(255, 255, 255));
	Times_up.SetTopLeft(60, 50);
	gold.SetSize(2);
	gold.SetPosition(390, 300);
	Score.LoadBitmapByString({ "resources/Score.bmp" }, RGB(255, 255, 255));
	Score.SetTopLeft(-10, 30);
	for (int i = 0; i < 3; i++) {
		Score_number[i].LoadBitmapByString({ "resources/T0.bmp", "resources/T1.bmp", "resources/T2.bmp", "resources/T3.bmp", "resources/T4.bmp", "resources/T5.bmp", "resources/T6.bmp", "resources/T7.bmp", "resources/T8.bmp", "resources/T9.bmp" }, RGB(255, 255, 255));
		Score_number[i].SetTopLeft(105 + i * (25), 30);
	}
	Score_number[0].SetFrameIndexOfBitmap(0);
	Score_number[1].SetFrameIndexOfBitmap(0);
	Score_number[2].SetFrameIndexOfBitmap(0);

	// -------------
	thetab.LoadTheTab();
	thetab.SetPosition(375, 75);
	hook.LoadHook();
	hook.SetPosition(400, 75);

	hook_status = 0; //�]�w���A�G0=�n�̤��A1=��u�A2=���^�u�A3=�D���d�~��

}
int game_framework::hook_status;
int game_framework::obj_status;

double hookcpp::x = 0;
double hookcpp::y = 0;

void CGameStateRun::OnMove()							// ���ʹC������
{
	if (state == 1) {
		count += 1;
		if (count == 30) {
			count = 0;
			int number[3];
			number[0] = Time_number[0].GetFrameIndexOfBitmap();
			number[1] = Time_number[1].GetFrameIndexOfBitmap();
			number[2] = Time_number[2].GetFrameIndexOfBitmap();
			if (number[2] > 0) {
				Time_number[2].SetFrameIndexOfBitmap(number[2]-1);
			}
			else {
				if (number[1] > 0) {
					Time_number[1].SetFrameIndexOfBitmap(number[1] - 1);
					Time_number[2].SetFrameIndexOfBitmap(9);
				}
				else {
					if (number[0] > 0) {
						Time_number[0].SetFrameIndexOfBitmap(number[0] - 1);
						Time_number[1].SetFrameIndexOfBitmap(9);
						Time_number[2].SetFrameIndexOfBitmap(9);
					}
					else {
						Time_number[2].SetFrameIndexOfBitmap(0);
						state = 2;
					}
				}
			}
		}
	}
	if (hook_status == 0) {//�_�l�\�ʤ�
		thetab.SetAnimate(100, false);
		obj_status = 1;//���I���q��
	}

	if (hook_status == 1) {//�_�l�X�o���y
		//�M�w����
		frameindex = thetab.GetFrameIndex();
		if (frameindex > 13)frameindex = 27 - frameindex;
		//hook.SetHook(frameindex);
		//�_�l�X�o
		hookcpp::ReleaseTab(hook, frameindex);
		double angle = 340 - (10 * frameindex);
		angle = angle * 3.1416 / 180;
	}

	if (hook_status == 2) {
		//�_�l�^�a
		hookcpp::RollTab(hook, frameindex);
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN) {
		if (state == 0) {
			state = 1;
		}
		if (state == 2) {
			state = 0;
			Time_number[0].SetFrameIndexOfBitmap(1);
			Time_number[1].SetFrameIndexOfBitmap(2);
			Time_number[2].SetFrameIndexOfBitmap(9);
		}
	}
	if (nChar == VK_DOWN && hook_status == 0) {

		hook_status = 1; //���A�G��u
		//hook.SetPosition(0, 0);
		//hookcpp::ReleaseTab(hook, frameindex);

	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	if (state == 0) {//���e��
		Stage.ShowBitmap();
	}
	else if (state == 1) {//�C����
		background.ShowBitmap();
		Time.ShowBitmap();
		Score.ShowBitmap();
		if (hook_status == 0) {//�_�l�\�ʤ�
			hook.UnShow();
			thetab.Show();
			//hook.Show();
		}
		else if (hook_status == 1 || hook_status == 2) {//�_�l�X�o
			thetab.UnShow();
			hook.Show();
			//thetab.Show();

		}
		if (obj_status == 0) {//�I���q���w�a�^�a	
			gold.UnShow();
		}
		else if (obj_status == 1 || obj_status == 2) {//���I���q��/�I���^�a���W
			gold.Show();
		}
		if (Time_number[0].GetFrameIndexOfBitmap() == 0) {
			Time_number[0].UnshowBitmap();
			if (Time_number[1].GetFrameIndexOfBitmap() == 0) {
				Time_number[1].UnshowBitmap();
			}
			else {
				Time_number[1].ShowBitmap();
			}
		}
		else {
			for (int i = 0; i < 2; i++) {
				Time_number[i].ShowBitmap();
			}
		}
		Time_number[2].ShowBitmap();

		if (Score_number[0].GetFrameIndexOfBitmap() == 0) {
			Score_number[0].UnshowBitmap();
			if (Score_number[1].GetFrameIndexOfBitmap() == 0) {
				Score_number[1].UnshowBitmap();
			}
			else {
				Score_number[1].ShowBitmap();
			}
		}
		else {
			for (int i = 0; i < 2; i++) {
				Score_number[i].ShowBitmap();
			}
		}
		Score_number[2].ShowBitmap();
	}
	else if (state == 2) {
		Times_up.ShowBitmap();
	}
}