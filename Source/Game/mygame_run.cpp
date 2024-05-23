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
	gm.Setting();  //����mapframe::Setting
	hook.Setting(); //����hookcpp::Setting
}


void CGameStateRun::OnMove()							// ���ʹC������
{
	gm.OnMove();  // ����mapframe::OnMove

	hook.OnMove(); // ����hookcpp::OnMove
	bool check;
	// �ˬd�C���q��
	for (int i = 0; i < mine_kind; i++) {
		for (int j = 0; j < int(treasure[i].size()); j++) {
			if (treasure[i][j]->GetObjStatus() == 1) {
				treasure[i][j]->Move();
			}
			else if (treasure[i][j]->GetObjStatus() == 3) {
				if (treasure[i][j - 1]->GetObjStatus() == 0) {
					treasure[i][j]->SetObjStatus(1);
				}
//				treasure[i][j]->Order();
			}
			// �p�G�q������ܦb���W
			if (treasure[i][j]->GetObjStatus() == 1 || treasure[i][j]->GetObjStatus() == 2) {
				// �T�{�q���O�_�P�_�l����Ĳ
				check = hook.IsOverlap(treasure[i][j]->GetLeft(), treasure[i][j]->GetTop(), treasure[i][j]->GetWidth(), treasure[i][j]->GetHeight());
				// �T�{���|
				if (check) {
					treasure[i][j]->SetObjStatus(2);
					hook.SetSpeed(treasure[i][j]->Catch());
				}
				// �T�{�q���w�^���I�A�ݭp����Ʃήɶ���
				if (treasure[i][j]->GoldBackHome(atan2(75 - treasure[i][j]->GetTop(), 385 - treasure[i][j]->GetLeft())) && treasure[i][j]->GetObjStatus() == 2) {
					treasure[i][j]->SetObjStatus(0);
					score += treasure[i][j]->Score();
					if (score >= 0) {
						gm.GetPoint(treasure[i][j]->Score());
					}
					// ���Ƥp��s�h�i�J����
					else if (score < 0) {
						score = 0;
						gm.ChangeState(2);
					}
					gm.SetTime(gm.GetTime() + treasure[i][j]->Time());
				}
			}
		}
	}
	// �C���q�������榡
	/*for (int i = 0; i < int(gold.size()); i++) {
		// �p�G�q���٦b���W
		if (gold[i]->GetObjStatus() == 1 || gold[i]->GetObjStatus() == 2) {
			//�T�{�q���P�_�l����Ĳ
			check = hook.IsOverlap(gold[i]->GetLeft(), gold[i]->GetTop(), gold[i]->GetWidth(), gold[i]->GetHeight());
			if (check) {//�T�{�����|��
				gold[i]->SetObjStatus(2);
				hook.SetSpeed(gold[i]->Catch());
			}
			// �T�{�q���w�^���I�A�ݭp����Ʃήɶ���
			if (gold[i]->GoldBackHome(atan2(75 - gold[i]->GetTop(), 385 - gold[i]->GetLeft())) && gold[i]->GetObjStatus() == 2) {//�q�^���I���ɭԭp��
				gm.GetPoint(gold[i]->Score());
				gold[i]->SetObjStatus(0);
				score += gold[i]->Score();

			}
		}
	}
	for (int i = 0; i < int(stone.size()); i++) {
		if (stone[i]->GetObjStatus() == 1 || stone[i]->GetObjStatus() == 2) {
			check = hook.IsOverlap(stone[i]->GetLeft(), stone[i]->GetTop(), stone[i]->GetWidth(), stone[i]->GetHeight());
			if (check) {
				stone[i]->SetObjStatus(2);
				hook.SetSpeed(stone[i]->Catch());
			}
			if (stone[i]->GoldBackHome(atan2(75 - stone[i]->GetTop(), 385 - stone[i]->GetLeft())) && stone[i]->GetObjStatus() == 2) {
				stone[i]->SetObjStatus(0);
				score += stone[i]->Score();
				if (score >= 0) {
					gm.GetPoint(stone[i]->Score());
				}
				// ���Ƥp��s�h�i�J����
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
			if (check) {//�T�{�����|��
				diamond[i]->SetObjStatus(2);
				hook.SetSpeed(diamond[i]->Catch());
			}
			if (diamond[i]->GoldBackHome(atan2(75 - diamond[i]->GetPositionY(), 385 - diamond[i]->GetPositionX())) && diamond[i]->GetObjStatus() == 2) {//�q�^���I���ɭԭp��*/
				/*�o��n�令�ɶ�*/
				/*gm.SetTime(gm.GetTime() + diamond[i]->Time());
				diamond[i]->SetObjStatus(0);

			}
		}
	}
	for (int i = 0; i < int(can.size()); i++) {
		if (can[i]->GetObjStatus() == 1 || can[i]->GetObjStatus() == 2) {
			check = hook.IsOverlap(can[i]->GetPositionX(), can[i]->GetPositionY(), can[i]->GetWidth(), can[i]->GetHeight());
			if (check) {//�T�{�����|��
				can[i]->SetObjStatus(2);
				hook.SetSpeed(can[i]->Catch());
			}
			if (can[i]->GoldBackHome(atan2(75 - can[i]->GetPositionY(), 385 - can[i]->GetPositionX())) && can[i]->GetObjStatus() == 2) {//�q�^���I���ɭԭp��
				/*�o��n�令�ɶ�*/
				/*gm.SetTime(gm.GetTime() + can[i]->Time());
				can[i]->SetObjStatus(0);

			}
		}
	}
	for (int i = 0; i < int(mouse.size()); i++) {
		if (mouse[i]->GetObjStatus() == 1) {
			mouse[i]->Move();
		}
		if (mouse[i]->GetObjStatus() == 1 || mouse[i]->GetObjStatus() == 2) {
			check = hook.IsOverlap(mouse[i]->GetPositionX(), mouse[i]->GetPositionY(), mouse[i]->GetWidth(), mouse[i]->GetHeight());
			if (check) {//�T�{�����|��
				mouse[i]->SetObjStatus(2);
				hook.SetSpeed(mouse[i]->Catch());
			}
			if (mouse[i]->GoldBackHome(atan2(75 - mouse[i]->GetPositionY(), 385 - mouse[i]->GetPositionX())) && mouse[i]->GetObjStatus() == 2) {
				mouse[i]->SetObjStatus(0);
				score += mouse[i]->Score();
				if (score >= 0) {
					gm.GetPoint(mouse[i]->Score());
				}
				// ���Ƥp��s�h�i�J����
				else {
					score = 0;
					gm.ChangeState(2);
				}
			}
		}
	}*/

	/*int gold_check = gold.size();
	for (int i = 0; i < int(gold.size()); i++) {
		if (gold[i]->GetObjStatus() == 0) {
			gold_check -= 1;
		}
	}
	int total = gold_check;
	if (total == 0 && gm.GetNowStage() == 1) {
		gm.ChangeState(2);
	}*/
	// �Ҧ������M�� �C���N�|����
	int gold_check = treasure[0].size();
	for (int i = 0; i < int(treasure[0].size()); i++) {
		if (treasure[0][i]->GetObjStatus() == 0) {
			gold_check -= 1;
		}
	}
	if (gold_check == 0 && gm.GetNowStage() == 1) {
		gm.ChangeState(2);
	}


	// �Y�i�J����e���A�ݶǤ��Ƶ�mapframe  (�Ygm)�A�çR���q���}�C�̪�����
	if (gm.IsOver()) {
		gm.SendScore(score);
		for (int i = 0; i < mine_kind; i++) {
			for (int j = 0; j < int(treasure[i].size()); j++) {
				treasure[i].pop_back();
			}
		}
		/*for (int i = 0; i < int(gold.size()); i++) {
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
		for (int i = 0; i < int(mouse.size()); i++) {
			mouse.pop_back();
		}*/
		
	}

}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// ���d�]�p�b�o��
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
		// �C�ӬP�P���Ū�����
		gm.SetThreshold(70, 50, 30);
		/*int number = 3;
		vector<int> size = { 2, 2, 3 };
		vector<int> x = { 100,200,450 };
		vector<int> y = { 200,350,320 };
		PushTreasure("gold", number, size, x, y);
		gm.SetThreshold(60, 50, 30);*/
		/*for (int i = 0; i < 1; i++) {
			gold.push_back(new GoldMine);
		}
		gold[0]->SetSize(2);
		gold[0]->SetPosition(100, 200);*/
		/*gold[1]->SetSize(2);
		gold[1]->SetPosition(200, 350);
		gold[2]->SetSize(3);
		gold[2]->SetPosition(450, 320);
		gold[3]->SetSize(1);
		gold[3]->SetPosition(700, 280);
		gold[4]->SetSize(2);
		gold[4]->SetPosition(550, 150);*/
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
		//PushTreasure("gold", 3, { 1, 100, 200, 2, 200, 350, 3, 450, 320 });
		//PushTreasure("stone", 3, { 1, 800, 380, 2, 360, 470, 3, 550, 150 });
		gm.SetThreshold(60, 50, 30);
		/*for (int i = 0; i < 3; i++) {
			gold.push_back(new GoldMine);
		}
		gold[0]->SetSize(1);
		gold[0]->SetPosition(100, 200);
		gold[1]->SetSize(2);
		gold[1]->SetPosition(200, 350);
		gold[2]->SetSize(3);
		gold[2]->SetPosition(450, 320);*/
		/*for (int i = 0; i < 3; i++) {
			stone.push_back(new Stone);
		}
		stone[0]->SetSize(1);
		stone[0]->SetPosition(800, 380);
		stone[1]->SetSize(2);
		stone[1]->SetPosition(360, 470);
		stone[2]->SetSize(3);
		stone[2]->SetPosition(550, 150);*/
	}else if (level == 3) {
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
		//PushTreasure("gold", 3, { 1, 100, 200, 2, 200, 350, 3, 450, 320 });
		//PushTreasure("diamond", 2, { 800, 380, 360, 470 });
		gm.SetThreshold(60, 40, 30);
		/*for (int i = 0; i < 3; i++) {
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
		diamond[1]->SetPosition(360, 470);*/
	}else if (level == 4) {
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
		//PushTreasure("gold", 3, { 1, 100, 200, 2, 200, 350, 3, 450, 320 });
		//PushTreasure("can", 2, { 800, 380, 360, 470 });
		gm.SetThreshold(60, 40, 30);
		/*for (int i = 0; i < 3; i++) {
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
		can[1]->SetPosition(360, 470);*/
	}else if (level == 5) {
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
		//PushTreasure("gold", 5, { 1, 100, 200, 2, 200, 350, 3, 450, 320, 1, 650, 180, 2, 80, 440 });
		//PushTreasure("stone", 2, { 1, 350, 300, 2, 700, 280 });
		//PushTreasure("diamond", 2, { 800, 380, 360, 470 });
		//PushTreasure("can", 2, { 760, 170, 250, 220 });
		gm.SetThreshold(60, 40, 30);
		/*for (int i = 0; i < 5; i++) {
			gold.push_back(new GoldMine);
		}
		gold[0]->SetSize(1);
		gold[0]->SetPosition(100, 200);
		gold[1]->SetSize(2);
		gold[1]->SetPosition(200, 350);
		gold[2]->SetSize(3);
		gold[2]->SetPosition(450, 320);
		gold[3]->SetSize(1);
		gold[3]->SetPosition(650, 180);
		gold[4]->SetSize(2);
		gold[4]->SetPosition(80, 440);
		for (int i = 0; i < 2; i++) {
			stone.push_back(new Stone);
		}
		stone[0]->SetSize(1);
		stone[0]->SetPosition(350, 300);
		stone[1]->SetSize(2);
		stone[1]->SetPosition(700, 280);
		for (int i = 0; i < 2; i++) {
			diamond.push_back(new Diamond);
		}
		diamond[0]->Set();
		diamond[0]->SetPosition(800, 380);
		diamond[1]->Set();
		diamond[1]->SetPosition(360, 470);
		for (int i = 0; i < 2; i++) {
			can.push_back(new Can);
		}
		can[0]->Set();
		can[0]->SetPosition(760, 170);
		can[1]->Set();
		can[1]->SetPosition(250, 220);*/
		
	}else if (level == 6) {
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
		//PushTreasure("gold", 3, { 1, 100, 200, 2, 200, 350 });
		//PushTreasure("mouse", 1, { 700, 300 });
		gm.SetThreshold(60, 40, 30);
		/*for (int i = 0; i < 3; i++) {
			gold.push_back(new GoldMine);
		}
		gold[0]->SetSize(1);
		gold[0]->SetPosition(100, 200);
		gold[1]->SetSize(2);
		gold[1]->SetPosition(200, 350);
		gold[2]->SetSize(3);
		gold[2]->SetPosition(450, 320);
		for (int i = 0; i < 1; i++) {
			mouse.push_back(new Mouse);
		}
		mouse[0]->Set();
		mouse[0]->SetPosition(700, 300);*/
	}else if (level == 7) {
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
	//PushTreasure("gold", 3, { 1, 100, 200, 2, 200, 350 });
	//PushTreasure("mouse", 1, { 700, 300 });
		gm.SetThreshold(60, 40, 30);
	/*for (int i = 0; i < 3; i++) {
		gold.push_back(new GoldMine);
	}
	gold[0]->SetSize(1);
	gold[0]->SetPosition(100, 200);
	gold[1]->SetSize(2);
	gold[1]->SetPosition(200, 350);
	gold[2]->SetSize(3);
	gold[2]->SetPosition(450, 320);
	for (int i = 0; i < 1; i++) {
		mouse.push_back(new Mouse);
	}
	mouse[0]->Set();
	mouse[0]->SetPosition(700, 300);*/
	}else if (level == 8) {
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
		//PushTreasure("gold", 3, { 1, 100, 200, 2, 200, 350 });
		//PushTreasure("mouse", 1, { 700, 300 });
		gm.SetThreshold(60, 40, 30);
		/*for (int i = 0; i < 3; i++) {
			gold.push_back(new GoldMine);
		}
		gold[0]->SetSize(1);
		gold[0]->SetPosition(100, 200);
		gold[1]->SetSize(2);
		gold[1]->SetPosition(200, 350);
		gold[2]->SetSize(3);
		gold[2]->SetPosition(450, 320);
		for (int i = 0; i < 1; i++) {
			mouse.push_back(new Mouse);
		}
		mouse[0]->Set();
		mouse[0]->SetPosition(700, 300);*/
	}else if (level == 9) {
		score = 0;
		gm.SetTime(30);
		int p = 0;
		vector<int> mine_size = { 1 };
		vector<int> mine_x = { 100,200,450,700};
		vector<int> mine_y = { 200,350,320,250};
		for (int i = 0; i < 1; i++) {
			treasure[0].push_back(new GoldMine(mine_size[p], mine_x[p], mine_y[p]));
			p += 1;
		}
		for (int i = 0; i < 3; i++) {
			treasure[4].push_back(new Mummy(i, mine_x[p], mine_y[p]));
			p += 1;
		}
		//PushTreasure("gold", 3, { 1, 100, 200, 2, 200, 350 });
		//PushTreasure("mouse", 1, { 700, 300 });
		gm.SetThreshold(60, 40, 30);
		/*for (int i = 0; i < 3; i++) {
			gold.push_back(new GoldMine);
		}
		gold[0]->SetSize(1);
		gold[0]->SetPosition(100, 200);
		gold[1]->SetSize(2);
		gold[1]->SetPosition(200, 350);
		gold[2]->SetSize(3);
		gold[2]->SetPosition(450, 320);
		for (int i = 0; i < 1; i++) {
			mouse.push_back(new Mouse);
		}
		mouse[0]->Set();
		mouse[0]->SetPosition(700, 300);*/
	}
	hook.OnKeyDown(nChar, nRepCnt, nFlags);
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

	gm.Show();
	if (gm.GetNowStage() == 1) {//�C����

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

		/*for (int i = 0; i < int(gold.size()); i++) {
			if (gold[i]->GetObjStatus() != 0) {//���I���q��/�I���^�a���W
				gold[i]->ShowBitmap();
			}
			else {//�I���q���w�a�^�a	
				gold[i]->UnshowBitmap();
			}
		}
		for (int i = 0; i < int(stone.size()); i++) {
			if (stone[i]->GetObjStatus() != 0) {//���I���q��/�I���^�a���W
				stone[i]->ShowBitmap();
			}
			else {//�I���q���w�a�^�a	
				stone[i]->UnshowBitmap();
			}
		}
		for (int i = 0; i < int(diamond.size()); i++) {
			if (diamond[i]->GetObjStatus() != 0) {//���I���q��/�I���^�a���W
				diamond[i]->Show();
			}
			else {//�I���q���w�a�^�a	
				diamond[i]->UnShow();
			}
		}
		for (int i = 0; i < int(can.size()); i++) {
			if (can[i]->GetObjStatus() != 0) {//���I���q��/�I���^�a���W
				can[i]->Show();
			}
			else {//�I���q���w�a�^�a	
				can[i]->UnShow();
			}
		}
		for (int i = 0; i < int(mouse.size()); i++) {
			if (mouse[i]->GetObjStatus() != 0) {//���I���q��/�I���^�a���W
				mouse[i]->Show();
			}
			else {//�I���q���w�a�^�a	
				mouse[i]->UnShow();
			}
		}*/
	}
}

/*void CGameStateRun::PushTreasure(string name, int number, vector<int> size, vector<int> x, vector<int> y) {
	if (name == "gold") {
		for (int i = 0; i < number; i++) {
			gold.push_back(new GoldMine);
			gold[i]->SetSize(size[i]);
			gold[i]->SetTopLeft(x[i], y[i]);
		}
	}*/
	/*else if (name == "stone") {
		for (int i = 0; i < number; i++) {
			stone.push_back(new Stone);
			stone[i]->SetSize(value[3*i]);
			stone[i]->SetTopLeft(value[3*i+1], value[3*i+2]);
		}
	}
	else if (name == "diamond") {
		for (int i = 0; i < number; i++) {
			diamond.push_back(new Diamond);
			diamond[i]->Set();
			diamond[i]->SetPosition(value[2*i], value[2*i+1]);
		}
	}
	else if (name == "can") {
		for (int i = 0; i < number; i++) {
			can.push_back(new Can);
			can[i]->Set();
			can[i]->SetPosition(value[2 * i], value[2 * i + 1]);
		}
	}
	else if (name == "mouse") {
		for (int i = 0; i < number; i++) {
			mouse.push_back(new Mouse);
			mouse[i]->Set();
			mouse[i]->SetPosition(value[2 * i], value[2 * i + 1]);
		}
	}*/
//}