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
	Stage[0].LoadBitmapByString({ "resources/Stage1_0.bmp", "resources/Stage1_1.bmp", "resources/Stage1_2.bmp", "resources/Stage1_3.bmp" }, RGB(0, 0, 0));
	Stage[0].SetFrameIndexOfBitmap(0);
	Stage[0].SetTopLeft(0, 0);
	Stage[1].LoadBitmapByString({ "resources/Stage2_0.bmp", "resources/Stage2_1.bmp", "resources/Stage2_2.bmp", "resources/Stage2_3.bmp" }, RGB(0, 0, 0));
	Stage[1].SetFrameIndexOfBitmap(0);
	Stage[1].SetTopLeft(200, 0);
	Background.LoadBitmapByString({ "resources/background.bmp" });
	Background.SetTopLeft(0, 0);
	Time_label.LoadBitmapByString({ "resources/Time.bmp" }, RGB(255, 255, 255));
	Time_label.SetTopLeft(670, 30);
	for (int i = 0; i < 3; i++) {
		Time_number[i].LoadBitmapByString({ "resources/T0.bmp", "resources/T1.bmp", "resources/T2.bmp", "resources/T3.bmp", "resources/T4.bmp", "resources/T5.bmp", "resources/T6.bmp", "resources/T7.bmp", "resources/T8.bmp", "resources/T9.bmp" }, RGB(255, 255, 255));
		Time_number[i].SetTopLeft(775 + i * (25), 30);
	}
	Time_number[0].SetFrameIndexOfBitmap(1);
	Time_number[1].SetFrameIndexOfBitmap(0);
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
	Score_number[0].SetFrameIndexOfBitmap(v3);
	Score_number[1].SetFrameIndexOfBitmap(v2);
	Score_number[2].SetFrameIndexOfBitmap(v1);
}

int MapFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_RETURN) {
		if (state == 0) {
			state = 1;
			return level_choose;
		}
		if (state == 2) {
			state = 0;
			Time_number[0].SetFrameIndexOfBitmap(1);
			Time_number[1].SetFrameIndexOfBitmap(2);
			Time_number[2].SetFrameIndexOfBitmap(9);
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
		Stage[0].ShowBitmap();
		Stage[1].ShowBitmap();
	}
	else if (state == 1) {//遊戲中
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
		Finish.ShowBitmap();
	}
}
