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
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
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

	status = 0; //設定狀態：0=搖晃中，1=放線，2=收回線，3=非關卡途中
}

void CGameStateRun::OnMove()							// 移動遊戲元素
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
	if (status == 0) {//鉤子擺動中
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
	//if (tmp_treasure == 2) {//有碰到礦物且帶回家
		//讓礦物飛回家
		//GoldBackHome(gold, angle);
	//}

	//如果按下選單按鈕 狀態改為3
	//如果狀態為3 按下開始 狀態改為0
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
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
		status = 1; //狀態：放線
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	if (state == 0) {//選單畫面
		Stage.ShowBitmap();
	}
	else if (state == 1) {//遊戲中
		background.ShowBitmap();
		Time.ShowBitmap();
		Score.ShowBitmap();
		if (status == 0) {//鉤子擺動中
			thetab.ShowBitmap();
			hook.UnshowBitmap();
		}
		else if (status == 1 || status == 2) {//鉤子出發
			thetab.UnshowBitmap();
			hook.ShowBitmap();
		}
		if (tmp_treasure == 0) {//碰到礦物已帶回家	
			gold.UnShow();
		}
		else if (tmp_treasure == 1 || tmp_treasure == 2) {//未碰到礦物/碰到後回家路上
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