#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

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
	thetab.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", "resources/hook_3.bmp",
		"resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", "resources/hook_7.bmp",
		"resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", "resources/hook_11.bmp",
		"resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp" , "resources/hook_13.bmp",
		"resources/hook_12.bmp","resources/hook_11.bmp", "resources/hook_10.bmp", "resources/hook_9.bmp",
		"resources/hook_8.bmp", "resources/hook_7.bmp",	"resources/hook_6.bmp", "resources/hook_5.bmp", 
		"resources/hook_4.bmp", "resources/hook_3.bmp", "resources/hook_2.bmp", "resources/hook_1.bmp" }, RGB(255, 255, 255));
	thetab.SetTopLeft(375,75);
	hook.LoadBitmapByString({ "resources/hook_1.bmp", "resources/hook_2.bmp", "resources/hook_3.bmp",
		"resources/hook_4.bmp", "resources/hook_5.bmp", "resources/hook_6.bmp", "resources/hook_7.bmp",
		"resources/hook_8.bmp", "resources/hook_9.bmp", "resources/hook_10.bmp", "resources/hook_11.bmp",
		"resources/hook_12.bmp", "resources/hook_13.bmp", "resources/hook_14.bmp" }, RGB(255, 255, 255));
	hook.SetTopLeft(400 , 75);

	status = 0; //�]�w���A�G0=�n�̤��A1=��u�A2=���^�u�A3=�D���d�~��
}

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
	if (status == 0) {//�_�l�\�ʤ�
		thetab.SetAnimation(100, false);
	}
	if (status == 1) {
		frameindex = thetab.GetFrameIndexOfBitmap();
		if (frameindex > 13)frameindex = 27 - frameindex;
		hook.SetFrameIndexOfBitmap(frameindex - 1);
		ReleaseTab(frameindex);
	}
	if (status == 2) {
		RollTab(frameindex);
	}
	//if (tmp_treasure == 2) {//���I���q���B�a�^�a
		//���q�����^�a
		//GoldBackHome(gold, angle);
	//}

	//�p�G���U�����s ���A�אּ3
	//�p�G���A��3 ���U�}�l ���A�אּ0
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
	if (nChar == VK_DOWN && status == 0) {
		status = 1; //���A�G��u
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
		if (status == 0) {//�_�l�\�ʤ�
			thetab.ShowBitmap();
			hook.UnshowBitmap();
		}
		else if (status == 1 || status == 2) {//�_�l�X�o
			thetab.UnshowBitmap();
			hook.ShowBitmap();
		}
		if (tmp_treasure == 0) {//�I���q���w�a�^�a	
			gold.UnShow();
		}
		else if (tmp_treasure == 1 || tmp_treasure == 2) {//���I���q��/�I���^�a���W
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