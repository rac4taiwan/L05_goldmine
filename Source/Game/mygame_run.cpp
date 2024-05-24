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
	//bool check;
	// 礦物執行式
	for (int i = 0; i < mine_kind; i++) {
		for (int j = 0; j < int(treasure[i].size()); j++) {
			if (treasure[i][j]->GetObjStatus() == 1 && treasure[i][j]->GetID() == "mouse") {
				Mouse* tmp = dynamic_cast<Mouse*>(treasure[i][j]);
				tmp->Move();
			}
			else if (treasure[i][j]->GetObjStatus() == 3) {
				if (treasure[i][j - 1]->GetObjStatus() == 0) {
					treasure[i][j]->SetObjStatus(1);
				}
				//				treasure[i][j]->Order();
			}

			if (treasure[i][j]->GetObjStatus() == 1 || treasure[i][j]->GetObjStatus() == 2) {
				//check = hook.IsOverlap(treasure[i][j]->GetLeft(), treasure[i][j]->GetTop(), treasure[i][j]->GetWidth(), treasure[i][j]->GetHeight());
				//check = hook == treasure[i][j];
				if (hook == treasure[i][j]) {
					treasure[i][j]->SetObjStatus(2);
					hook.SetSpeed(treasure[i][j]->Catch());
				}
				if (treasure[i][j]->GoldBackHome(atan2(75 - treasure[i][j]->GetTop(), 385 - treasure[i][j]->GetLeft())) && treasure[i][j]->GetObjStatus() == 2) {
					treasure[i][j]->SetObjStatus(0);
					score += treasure[i][j]->Score();
					if (score >= 0) {
						//gm.GetPoint(treasure[i][j]->Score());
						gm += treasure[i][j]->Score();
					}
					// 分數小於零則進入結算
					else if (score < 0) {
						score = 0;
						gm.ChangeState(2);
					}
					//gm.SetTime(gm.GetTime() + treasure[i][j]->Time());
					gm = treasure[i][j]->Time();
				}
			}
		}
	}
	

	int gold_check = treasure[0].size();
	for (int i = 0; i < int(treasure[0].size()); i++) {
		if (treasure[0][i]->GetObjStatus() == 0) {
			gold_check -= 1;
		}
	}
	if (gold_check == 0 && gm.GetNowStage() == 1) {
		gm.ChangeState(2);
	}


	// 若進入結算畫面，需傳分數給mapframe  (即gm)，並刪除礦物陣列裡的物件
	if (gm.IsOver()) {
		gm.SendScore(score);
		for (int i = 0; i < mine_kind; i++) {
			for (int j = 0; j < int(treasure[i].size()); j++) {
				treasure[i].pop_back();
			}
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
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 2,2,3 };
		vector<int> mine_x = { 100, 200,450 };
		vector<int> mine_y = { 200,350,320 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(70, 50, 30);
	}
	else if (level == 2) {
		score = 0;
		gm.SetTime(40);
		int p = 0;
		vector<int> mine_size = { 1,2,3,1,2,3 };
		vector<int> mine_x = { 100,200,450,800,360,550 };
		vector<int> mine_y = { 200,350,320,380,470,150 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 3; i++) {
			treasure[1].push_back(new Stone(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 50, 30);
	}
	else if (level == 3) {
		score = 0;
		gm.SetTime(10);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,800,360 };
		vector<int> mine_y = { 200,350,320,380,470 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 2; i++) {
			treasure[2].push_back(new Diamond(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}
	else if (level == 4) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,800,360 };
		vector<int> mine_y = { 200,350,320,380,470 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 2; i++) {
			treasure[2].push_back(new Can(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}
	else if (level == 5) {
		score = 0;
		gm.SetTime(20);
		int p = 0;
		vector<int> mine_size = { 1,2,3,1,2,1,2 };
		vector<int> mine_x = { 100,200,450,650,80,350,700,800,360,760,250 };
		vector<int> mine_y = { 200,350,320,180,440,300,280,380,470,170,220 };
		for (int i = 0; i < 5; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 2; i++) {
			treasure[1].push_back(new Stone(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 2; i++) {
			treasure[2].push_back(new Diamond(mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 2; i++) {
			treasure[3].push_back(new Can(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);		
	}
	else if (level == 6) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,700 };
		vector<int> mine_y = { 200,350,320,300 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[4].push_back(new Mouse(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}
	else if (level == 7) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 2,2,2,1 };
		vector<int> mine_x = { 100,200,600,300,500,600 };
		vector<int> mine_y = { 200,400,400,320,300,220 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[1].push_back(new Stone(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[2].push_back(new Diamond(mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[4].push_back(new Mouse(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(40, 20, 10);
	}
	else if (level == 8) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,700 };
		vector<int> mine_y = { 200,350,320,300 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[4].push_back(new Mouse(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}
	else if (level == 9) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,700 };
		vector<int> mine_y = { 200,350,320,300 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[4].push_back(new Mouse(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}
	else if (level == 10) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1 };
		vector<int> mine_x = { 100,200,450,700 };
		vector<int> mine_y = { 200,350,320,250 };
		for (int i = 0; i < 1; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 3; i++) {
			treasure[4].push_back(new Mummy(i, mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}else if (level == 11) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,700 };
		vector<int> mine_y = { 200,350,320,300 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[4].push_back(new Mouse(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}
	else if (level == 12) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,700 };
		vector<int> mine_y = { 200,350,320,300 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[4].push_back(new Mouse(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}
	else if (level == 13) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,700 };
		vector<int> mine_y = { 200,350,320,300 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[4].push_back(new Mouse(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}
	else if (level == 14) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,700 };
		vector<int> mine_y = { 200,350,320,300 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[4].push_back(new Mouse(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
	}
	else if (level == 15) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1,2,3 };
		vector<int> mine_x = { 100,200,450,700 };
		vector<int> mine_y = { 200,350,320,300 };
		for (int i = 0; i < 3; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 1; i++) {
			treasure[4].push_back(new Mouse(mine_x[p], mine_y[p]));
			p += 1;
		}
		gm.SetThreshold(60, 40, 30);
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

		for (int i = 0; i < mine_kind; i++) {
			for (int j = 0; j < int(treasure[i].size()); j++) {
				if (treasure[i][j]->GetObjStatus() != 0) {
					treasure[i][j]->ShowBitmap();
				}
				else {
					treasure[i][j]->UnshowBitmap();
				}
			}
		}
	}
}
