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
	gm.Setting();
	hook.Setting();
}


void CGameStateRun::OnMove()							// 移動遊戲元素
{
	gm.OnMove();

	hook.OnMove();
	bool check;
	for (int i = 0; i < int(gold.size()); i++) {
		if (gold[i]->GetObjStatus() == 1) {
			check = hook.IsOverlap(gold[i]->GetPositionX(), gold[i]->GetPositionY(), gold[i]->GetWidth(), gold[i]->GetHeight());
			if (check) {
				if (gold[i]->GoldBackHome(hook.GetFrameIndex()) && gold[i]->GetObjStatus() == 1) {
					gm.GetPoint(gold[i]->Score());
					gold[i]->SetObjStatus(0);
					score += gold[i]->Score();
				}
			}
		}
	}
	for (int i = 0; i < int(stone.size()); i++) {
		if (stone[i]->GetObjStatus() == 1) {
			check = hook.IsOverlap(stone[i]->GetPositionX(), stone[i]->GetPositionY(), stone[i]->GetWidth(), stone[i]->GetHeight());
			if (check) {
				if (stone[i]->GoldBackHome(hook.GetFrameIndex()) && stone[i]->GetObjStatus() == 1) {
					stone[i]->SetObjStatus(0);
					score += stone[i]->Score();
					if (score >= 0) {
						gm.GetPoint(stone[i]->Score());
					}
					else {
						score = 0;
						gm.ChangeState(2);
					}
				}
			}
		}
	}

	if (gm.IsOver()) {
		gm.SendScore(score);
		for (int i = 0; i < int(gold.size()); i++) {
			gold.pop_back();
		}
		for (int i = 0; i < int(stone.size()); i++) {
			stone.pop_back();
		}
		
	}

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	level = gm.OnKeyDown(nChar, nRepCnt, nFlags);
	if (level == 1) {
		score = 0;
		for (int i = 0; i < 5; i++) {
			gold.push_back(new GoldMine);
		}
		gold[0]->SetSize(2);
		gold[0]->SetPosition(100, 200);
		gold[1]->SetSize(2);
		gold[1]->SetPosition(200, 350);
		gold[2]->SetSize(3);
		gold[2]->SetPosition(450, 320);
		gold[3]->SetSize(1);
		gold[3]->SetPosition(700, 280);
		gold[4]->SetSize(2);
		gold[4]->SetPosition(550, 150);
	}
	else if (level == 2) {
		score = 0;
		for (int i = 0; i < 3; i++) {
			gold.push_back(new GoldMine);
		}
		gold[0]->SetSize(1);
		gold[0]->SetPosition(100, 200);
		gold[1]->SetSize(2);
		gold[1]->SetPosition(200, 350);
		gold[2]->SetSize(3);
		gold[2]->SetPosition(450, 320);
		for (int i = 0; i < 3; i++) {
			stone.push_back(new Stone);
		}
		stone[0]->SetSize(1);
		stone[0]->SetPosition(800, 380);
		stone[1]->SetSize(2);
		stone[1]->SetPosition(360, 470);
		stone[2]->SetSize(3);
		stone[2]->SetPosition(550, 150);
	}
	hook.OnKeyDown(nChar, nRepCnt, nFlags);
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

	gm.Show();
	if (gm.GetNowStage() == 1) {//遊戲中

		hook.OnShow();

		for (int i = 0; i < int(gold.size()); i++) {
			if (gold[i]->GetObjStatus() == 1) {//未碰到礦物/碰到後回家路上
				gold[i]->Show();
			}
			else {//碰到礦物已帶回家	
				gold[i]->UnShow();
			}
		}
		for (int i = 0; i < int(stone.size()); i++) {
			if (stone[i]->GetObjStatus() == 1) {//未碰到礦物/碰到後回家路上
				stone[i]->Show();
			}
			else {//碰到礦物已帶回家	
				stone[i]->UnShow();
			}
		}
	}
}