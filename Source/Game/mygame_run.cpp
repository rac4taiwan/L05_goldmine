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
	gm.Setting();  //跳至mapframe::Setting
	hook.Setting(); //跳至hookcpp::Setting
}


void CGameStateRun::OnMove()							// 移動遊戲元素
{
	gm.OnMove();  // 跳至mapframe::OnMove

	hook.OnMove(); // 跳至hookcpp::OnMove
	bool check;
	// 每個礦物的執行式
	for (int i = 0; i < int(gold.size()); i++) {
		// 如果礦物還在場上
		if (gold[i]->GetObjStatus() == 1 || gold[i]->GetObjStatus() == 2) {
			//確認礦物與鉤子有接觸
			check = hook.IsOverlap(gold[i]->GetPositionX(), gold[i]->GetPositionY(), gold[i]->GetWidth(), gold[i]->GetHeight());
			if (check) {//確認有重疊到
				gold[i]->SetObjStatus(2);
				hook.SetSpeed(gold[i]->Catch());
			}
			// 確認礦物已回原點，需計算分數或時間等
			if (gold[i]->GoldBackHome(atan2(75 - gold[i]->GetPositionY(), 385 - gold[i]->GetPositionX())) && gold[i]->GetObjStatus() == 2) {//礦回原點的時候計分
				gm.GetPoint(gold[i]->Score());
				gold[i]->SetObjStatus(0);
				score += gold[i]->Score();

			}
		}
	}
	for (int i = 0; i < int(stone.size()); i++) {
		if (stone[i]->GetObjStatus() == 1 || stone[i]->GetObjStatus() == 2) {
			check = hook.IsOverlap(stone[i]->GetPositionX(), stone[i]->GetPositionY(), stone[i]->GetWidth(), stone[i]->GetHeight());
			if (check) {
				stone[i]->SetObjStatus(2);
			}
			if (stone[i]->GoldBackHome(atan2(75 - stone[i]->GetPositionY(), 385 - stone[i]->GetPositionX())) && stone[i]->GetObjStatus() == 2) {
				stone[i]->SetObjStatus(0);
				score += stone[i]->Score();
				if (score >= 0) {
					gm.GetPoint(stone[i]->Score());
				}
				// 分數小於零則進入結算
				else {
					score = 0;
					gm.ChangeState(2);
				}
			}
		}
	}
	for (int i = 0; i < int(diamond.size()); i++) {
		if (diamond[i]->GetObjStatus() == 1 || diamond[i]->GetObjStatus() == 2) {
			check = hook.IsOverlap(diamond[i]->GetPositionX(), diamond[i]->GetPositionY(), diamond[i]->GetWidth(), diamond[i]->GetHeight());
			if (check) {//確認有重疊到
				diamond[i]->SetObjStatus(2);
			}
			if (diamond[i]->GoldBackHome(atan2(75 - diamond[i]->GetPositionY(), 385 - diamond[i]->GetPositionX())) && diamond[i]->GetObjStatus() == 2) {//礦回原點的時候計分
				/*這邊要改成時間*/
				gm.GetPoint(diamond[i]->Time());
				diamond[i]->SetObjStatus(0);
				score += diamond[i]->Time();

			}
		}
	}
	for (int i = 0; i < int(can.size()); i++) {
		if (can[i]->GetObjStatus() == 1 || can[i]->GetObjStatus() == 2) {
			check = hook.IsOverlap(can[i]->GetPositionX(), can[i]->GetPositionY(), can[i]->GetWidth(), can[i]->GetHeight());
			if (check) {//確認有重疊到
				can[i]->SetObjStatus(2);
			}
			if (can[i]->GoldBackHome(atan2(75 - can[i]->GetPositionY(), 385 - can[i]->GetPositionX())) && can[i]->GetObjStatus() == 2) {//礦回原點的時候計分
				/*這邊要改成時間*/
				gm.GetPoint(can[i]->Time());
				can[i]->SetObjStatus(0);
				score += can[i]->Time();

			}
		}
	}

	// 若進入結算畫面，需傳分數給mapframe  (即gm)，並刪除礦物陣列裡的物件
	if (gm.IsOver()) {
		gm.SendScore(score);
		for (int i = 0; i < int(gold.size()); i++) {
			gold.pop_back();
		}
		for (int i = 0; i < int(stone.size()); i++) {
			stone.pop_back();
		}
		for (int i = 0; i < int(diamond.size()); i++) {
			diamond.pop_back();
		}
		for (int i = 0; i < int(can.size()); i++) {
			can.pop_back();
		}
		
	}

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// 關卡設計在這裡
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
	}else if (level == 3) {
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
		for (int i = 0; i < 2; i++) {
			diamond.push_back(new Diamond);
		}
		diamond[0]->Set();
		diamond[0]->SetPosition(800, 380);
		diamond[1]->Set();
		diamond[1]->SetPosition(360, 470);
	}else if (level == 4) {
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
		for (int i = 0; i < 2; i++) {
			can.push_back(new Can);
		}
		can[0]->Set();
		can[0]->SetPosition(800, 380);
		can[1]->Set();
		can[1]->SetPosition(360, 470);
	}else if (level == 5) {
		score = 0;
		
		
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
			if (gold[i]->GetObjStatus() != 0) {//未碰到礦物/碰到後回家路上
				gold[i]->Show();
			}
			else {//碰到礦物已帶回家	
				gold[i]->UnShow();
			}
		}
		for (int i = 0; i < int(stone.size()); i++) {
			if (stone[i]->GetObjStatus() != 0) {//未碰到礦物/碰到後回家路上
				stone[i]->Show();
			}
			else {//碰到礦物已帶回家	
				stone[i]->UnShow();
			}
		}
		for (int i = 0; i < int(diamond.size()); i++) {
			if (diamond[i]->GetObjStatus() != 0) {//未碰到礦物/碰到後回家路上
				diamond[i]->Show();
			}
			else {//碰到礦物已帶回家	
				diamond[i]->UnShow();
			}
		}
		for (int i = 0; i < int(can.size()); i++) {
			if (can[i]->GetObjStatus() != 0) {//未碰到礦物/碰到後回家路上
				can[i]->Show();
			}
			else {//碰到礦物已帶回家	
				can[i]->UnShow();
			}
		}
	}
}