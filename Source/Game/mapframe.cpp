#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "mymapframe.h"

using namespace game_framework;

MapFrame::MapFrame(){

}

void MapFrame::Setting() {
	//Start.LoadBitmapByString({ "resources/Cover.bmp" });
	//Start.SetTopLeft(0, 0);
	/*Stage[0].LoadBitmapByString({ "resources/Stage1_0.bmp", "resources/Stage1_1.bmp", "resources/Stage1_2.bmp", "resources/Stage1_3.bmp" }, RGB(0, 0, 0));
	Stage[0].SetFrameIndexOfBitmap(0);
	Stage[0].SetTopLeft(0, 0);
	Stage[1].LoadBitmapByString({ "resources/Stage2_0.bmp", "resources/Stage2_1.bmp", "resources/Stage2_2.bmp", "resources/Stage2_3.bmp" }, RGB(0, 0, 0));
	Stage[1].SetFrameIndexOfBitmap(0);
	Stage[1].SetTopLeft(200, 0);*/
	for (int i = 0; i < total_level; i++) {
		Stage[i].Setting(i+1);
		Stage[i].SetTopLeft(180 * i, 0);
	}
	Background.LoadBitmapByString({ "resources/background_0.bmp","resources/background.bmp" }, RGB(255,255,255));
	Background.SetTopLeft(0, 0);
	Time_label.LoadBitmapByString({ "resources/Time.bmp" }, RGB(255, 255, 255));
	Time_label.SetTopLeft(670, 30);
	for (int i = 0; i < 3; i++) {
		Time_number[i].LoadBitmapByString({ "resources/T0.bmp", "resources/T1.bmp", "resources/T2.bmp", "resources/T3.bmp", "resources/T4.bmp", "resources/T5.bmp", "resources/T6.bmp", "resources/T7.bmp", "resources/T8.bmp", "resources/T9.bmp" }, RGB(255, 255, 255));
		Time_number[i].SetTopLeft(775 + i * (25), 30);
	}
	Time_number[0].SetFrameIndexOfBitmap(0);
	Time_number[1].SetFrameIndexOfBitmap(2);
	Time_number[2].SetFrameIndexOfBitmap(3);
	Finish.LoadBitmapByString({ "resources/times_up.bmp" }, RGB(255, 255, 255));
	Finish.SetTopLeft(60, 50);
	Score_label.LoadBitmapByString({ "resources/Score.bmp" }, RGB(255, 255, 255));
	Score_label.SetTopLeft(-10, 30);
	for (int i = 0; i < 3; i++) {
		Score_number[i].LoadBitmapByString({ "resources/T0.bmp", "resources/T1.bmp", "resources/T2.bmp", "resources/T3.bmp", "resources/T4.bmp", "resources/T5.bmp", "resources/T6.bmp", "resources/T7.bmp", "resources/T8.bmp", "resources/T9.bmp" }, RGB(255, 255, 255));
		Score_number[i].SetTopLeft(105 + i * (25), 30);
	}
	Score_number[0].SetFrameIndexOfBitmap(0);
	Score_number[1].SetFrameIndexOfBitmap(0);
	Score_number[2].SetFrameIndexOfBitmap(0);
}

void MapFrame::OnMove() {
	if (state == 1) {
		count += 1;
		if (count == 30) {
			count = 0;
			int number[3];
			number[0] = Time_number[0].GetFrameIndexOfBitmap();
			number[1] = Time_number[1].GetFrameIndexOfBitmap();
			number[2] = Time_number[2].GetFrameIndexOfBitmap();
			if (number[2] > 0) {
				Time_number[2].SetFrameIndexOfBitmap(number[2] - 1);
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
}

void MapFrame::GetPoint(int score) {
	int v1 = Score_number[2].GetFrameIndexOfBitmap() + score % 10;
	int v2 = Score_number[1].GetFrameIndexOfBitmap() + score / 10 + v1 / 10;
	int v3 = Score_number[0].GetFrameIndexOfBitmap() + v2 / 10;
	Score_number[0].SetFrameIndexOfBitmap(v3%10);
	Score_number[1].SetFrameIndexOfBitmap(v2%10);
	Score_number[2].SetFrameIndexOfBitmap(v1%10);
}

int MapFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_RETURN) {
		if (state == 0) {
			state = 1;
			return now_level;
		}
		if (state == 2) {
			state = 0;
			Time_number[0].SetFrameIndexOfBitmap(0);
			Time_number[1].SetFrameIndexOfBitmap(2);
			Time_number[2].SetFrameIndexOfBitmap(9);
			Score_number[0].SetFrameIndexOfBitmap(0);
			Score_number[1].SetFrameIndexOfBitmap(0);
			Score_number[2].SetFrameIndexOfBitmap(0);
			EndGame.SetStar(0);
		}
	}
	else if (nChar == VK_LEFT && state == 0) {
		if (now_level > 1) {
			now_level -= 1;
		}
	}
	else if (nChar == VK_RIGHT && state == 0) {
		if (now_level < total_level) {
			now_level += 1;
		}
	}
	return 0;
}

int MapFrame::GetNowStage() {
	return state;
}

void MapFrame::Show()
{
	//Start.ShowBitmap();
	if (state == 0) {//選單畫面
		Background.SetFrameIndexOfBitmap(0);
		Background.ShowBitmap();
		//Stage[0].ShowBitmap();
		//Stage[1].ShowBitmap();
		for (int i = 0; i < total_level; i++) {
			if ((i+1) == now_level) {
				Stage[i].Big();
			}
			else {
				Stage[i].Show();
			}
		}
	}
	else if (state == 1) {//遊戲中
		Background.SetFrameIndexOfBitmap(1);
		Background.ShowBitmap();
		Time_label.ShowBitmap();
		Score_label.ShowBitmap();
		/*if (hook_status == 0) {//鉤子擺動中
			hook.UnShow();
			thetab.Show();
		}
		else if (hook_status == 1 || hook_status == 2) {//鉤子出發
			thetab.UnShow();
			hook.Show();
		}
		if (obj_status == 1 || obj_status == 2) {//未碰到礦物/碰到後回家路上
			gold.Show();
		}
		else if (obj_status == 0) {//碰到礦物已帶回家	
			gold.UnShow();
		}*/
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
		//Finish.ShowBitmap();
		EndGame.Setting(end_score,now_level);
		Stage[now_level - 1].SetStar(EndGame.GetStar());
	}
}

void MapFrame::ChangeState(int value) {
	state = value;
}

bool MapFrame::IsOver() {
	if (state == 2) {
		return true;
	}
	else {
		return false;
	}
}

void MapFrame::SendScore(int score) {
	end_score = score;
}


//     class Episode
Episode::Episode() {

}

void Episode::Setting(int value) {
	frame.LoadBitmapByString({ "resources/Episode_0.bmp", "resources/Episode_1.bmp", "resources/Episode_2.bmp", "resources/Episode_3.bmp" }, RGB(255, 255, 255));
	number.LoadBitmapByString({ "resources/L0.bmp", "resources/L1.bmp", "resources/L2.bmp", "resources/L3.bmp", "resources/L4.bmp", "resources/L5.bmp", "resources/L6.bmp", "resources/L7.bmp", "resources/L8.bmp", "resources/L9.bmp" }, RGB(0, 0, 0));
	number.SetFrameIndexOfBitmap(value);
}

void Episode::SetTopLeft(int x, int y) {
	frame.SetTopLeft(x, y);
	number.SetTopLeft(x-5, y-13);
}

void Episode::Big() {
	frame.ShowBitmap(1.1);
	number.ShowBitmap(1.1);
}

void Episode::Show() {
	frame.ShowBitmap();
	number.ShowBitmap();
}

void Episode::SetStar(int value) {
	frame.SetFrameIndexOfBitmap(value);
}

//      class End
End::End() {

}

void End::Setting(int score, int level) {
	frame.LoadBitmapByString({ "resources/End_0.bmp", "resources/End_1.bmp", "resources/End_2.bmp", "resources/End_3.bmp" });
	frame.SetTopLeft(0, 0);
	if (level == 1) {
		if (score > 90) {
			frame.SetFrameIndexOfBitmap(3);
			star =  3;
		}
		else if (score > 50) {
			frame.SetFrameIndexOfBitmap(2);
			star =  2;
		}
		else if (score > 30) {
			frame.SetFrameIndexOfBitmap(1);
			star = 1;
		}
		else {
			frame.SetFrameIndexOfBitmap(0);
			star = 0;
		}
	}
	else if (level == 2) {
		if (score > 90) {
			frame.SetFrameIndexOfBitmap(3);
			star = 3;
		}
		else if (score > 50) {
			frame.SetFrameIndexOfBitmap(2);
			star = 2;
		}
		else if (score > 30) {
			frame.SetFrameIndexOfBitmap(1);
			star = 1;
		}
		else {
			frame.SetFrameIndexOfBitmap(0);
			star = 0;
		}
	}
	/*else if (level == 2) {
		if (score > 90) {
			frame.SetFrameIndexOfBitmap(3);
			star = 3;
		}
		else if (score > 50) {
			frame.SetFrameIndexOfBitmap(2);
			star = 2;
		}
		else if (score > 30) {
			frame.SetFrameIndexOfBitmap(1);
			star = 1;
		}
		else {
			frame.SetFrameIndexOfBitmap(0);
			star = 0;
		}
	}*/
	frame.ShowBitmap();
	for (int i = 0; i < 3; i++) {
		number[i].LoadBitmapByString({ "resources/E0.bmp", "resources/E1.bmp", "resources/E2.bmp", "resources/E3.bmp", "resources/E4.bmp", "resources/E5.bmp", "resources/E6.bmp", "resources/E7.bmp", "resources/E8.bmp", "resources/E9.bmp" }, RGB(0, 0, 0));
		number[i].SetTopLeft(380 + 50 * i, 200);
	}
	if (score / 100 != 0) {
		number[0].SetFrameIndexOfBitmap(score / 100);
		number[1].SetFrameIndexOfBitmap((score / 10) % 10);
		number[2].SetFrameIndexOfBitmap(score % 10);
		number[0].ShowBitmap();
		number[1].ShowBitmap();
		number[2].ShowBitmap();
	}
	else if (score / 10 != 0) {
		number[0].UnshowBitmap();
		number[1].SetFrameIndexOfBitmap(score / 10);
		number[2].SetFrameIndexOfBitmap(score % 10);
		number[1].ShowBitmap();
		number[2].ShowBitmap();
	}
	else {
		number[0].UnshowBitmap();
		number[1].UnshowBitmap();
		number[2].SetFrameIndexOfBitmap(score);
		number[2].ShowBitmap();
	}

}

int End::GetStar() {
	return star;
}

void End::SetStar(int value) {
	star = value;
}
