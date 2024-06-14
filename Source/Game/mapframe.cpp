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

	// 設定關卡圖案
	for (int i = 0; i < total_level; i++) { 
		if (i < 5) {
			Stage[i].Setting(i + 1);
			Stage[i].SetTopLeft(180 * i, 0);
		}
		else if (i < 10) {
			Stage[i].Setting(i + 1);
			Stage[i].SetTopLeft(180 * (i % 5), 150);
		}
		else if (i < 15) {
			Stage[i].Setting(i + 1);
			Stage[i].SetTopLeft(180 * (i % 5), 300);

		}
		
	}
	// 載入背景圖
	Background.LoadBitmapByString({ "resources/background_0.bmp","resources/background.bmp" }, RGB(255,255,255));
	Background.SetTopLeft(0, 0);
	// 載入遊戲進行時的時間
	Time_label.LoadBitmapByString({ "resources/Time.bmp" }, RGB(255, 255, 255));
	Time_label.SetTopLeft(670, 30);
	for (int i = 0; i < 3; i++) {
		Time_number[i].LoadBitmapByString({ "resources/T0.bmp", "resources/T1.bmp", "resources/T2.bmp", "resources/T3.bmp", "resources/T4.bmp", "resources/T5.bmp", "resources/T6.bmp", "resources/T7.bmp", "resources/T8.bmp", "resources/T9.bmp" }, RGB(255, 255, 255));
		Time_number[i].SetTopLeft(775 + i * (25), 30);
	}

	// 載入遊戲進行時的分數
	Score_label.LoadBitmapByString({ "resources/Score.bmp" }, RGB(255, 255, 255));
	Score_label.SetTopLeft(-10, 30);
	for (int i = 0; i < 3; i++) {
		Score_number[i].LoadBitmapByString({ "resources/T0.bmp", "resources/T1.bmp", "resources/T2.bmp", "resources/T3.bmp", "resources/T4.bmp", "resources/T5.bmp", "resources/T6.bmp", "resources/T7.bmp", "resources/T8.bmp", "resources/T9.bmp" }, RGB(255, 255, 255));
		Score_number[i].SetTopLeft(105 + i * (25), 30);
	}
}

void MapFrame::OnMove() {
	// state ==  0 為選關畫面; 1 為遊戲進行狀態; 2 為結算畫面
	if (state == 1) {
		count += 1;
		// count 為計時器，每30個count為一秒
		// number[0]、[1]、[2]分別為百、十、個位數，若百位數為0則隱藏，十位數同理
		if (count == 30) {
			count = 0;
			time -= 1;
		}
		if (time <= 0) {
			state = 2;
		}
	}
}

void MapFrame::GetPoint(int value) {
	score += value;
}

void MapFrame::operator+=(int value) {
	score += value;
}

int MapFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_RETURN) {
		if (state == 0) {
			state = 1;
			score = 0;
			return now_level;
		}
		if (state == 2) {
			state = 0;
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
	else if (nChar == VK_DOWN && state == 0) {
		if ((now_level+5) <= total_level) {
			now_level += 5;
		}
	}
	else if (nChar == VK_UP && state == 0) {
		if ((now_level-5) >= 1) {
			now_level -= 5;
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
		if (time >= 0) {
			if ((time / 100) != 0) {
				Time_number[0].SetFrameIndexOfBitmap(time / 100);
				Time_number[1].SetFrameIndexOfBitmap((time % 100) / 10);
				Time_number[0].ShowBitmap();
				Time_number[1].ShowBitmap();
			}
			else if (((time % 100) / 10) != 0) {
				Time_number[1].SetFrameIndexOfBitmap((time % 100) / 10);
				Time_number[1].ShowBitmap();
			}
			Time_number[2].SetFrameIndexOfBitmap(time % 10);
			Time_number[2].ShowBitmap();
		}
		if ((score / 100) != 0) {
			Score_number[0].SetFrameIndexOfBitmap(score / 100);
			Score_number[1].SetFrameIndexOfBitmap((score % 100) / 10);
			Score_number[0].ShowBitmap();
			Score_number[1].ShowBitmap();
		}
		else if (((score % 100) / 10) != 0) {
			Score_number[1].SetFrameIndexOfBitmap((score % 100) / 10);
			Score_number[1].ShowBitmap();
		}
		Score_number[2].SetFrameIndexOfBitmap(score % 10);
		Score_number[2].ShowBitmap();
	}
	else if (state == 2) {
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
void MapFrame::SetTime(int value) {
	time = value;
}

void MapFrame::operator=(int value) {
	time += value;
}

int MapFrame::GetTime() {
	return time;
}

void MapFrame::SetThreshold(int a, int b, int c) {
	EndGame.SetThreshold(a, b, c);
}


//     class Episode
Episode::Episode() {

}

void Episode::Setting(int value) {
	frame.LoadBitmapByString({ "resources/Episode_0.bmp", "resources/Episode_1.bmp", "resources/Episode_2.bmp", "resources/Episode_3.bmp" }, RGB(255, 255, 255));
	for (int i = 0; i < 2; i++) {
		number[i].LoadBitmapByString({ "resources/L0.bmp", "resources/L1.bmp", "resources/L2.bmp", "resources/L3.bmp", "resources/L4.bmp", "resources/L5.bmp", "resources/L6.bmp", "resources/L7.bmp", "resources/L8.bmp", "resources/L9.bmp" }, RGB(0, 0, 0));
	}
	if (value < 10) {
		number[0].SetFrameIndexOfBitmap(value);
	}
	else {
		number[0].SetFrameIndexOfBitmap(value % 10);
		number[1].SetFrameIndexOfBitmap(value / 10);
	}
	level = value;
}

void Episode::SetTopLeft(int x, int y) {
	frame.SetTopLeft(x, y);
	if (level < 10) {
		number[0].SetTopLeft(x-5, y-13);
	}
	else {
		number[0].SetTopLeft(x + 8, y - 13);
		number[1].SetTopLeft(x - 24, y - 13);
	}
}

void Episode::Big() {
	frame.ShowBitmap(1.1);
	if (level < 10) {
		number[0].ShowBitmap(1.1);
	}
	else {
		for (int i = 0; i < 2; i++) {
			number[i].ShowBitmap(1.1);
		}
	}
}

void Episode::Show() {
	frame.ShowBitmap();
	if (level < 10) {
		number[0].ShowBitmap();
	}
	else {
		for (int i = 0; i < 2; i++) {
			number[i].ShowBitmap();
		}
	}
}

void Episode::SetStar(int value) {
	frame.SetFrameIndexOfBitmap(value);
}

//      class End
End::End() {

}

void End::SetThreshold(int a, int b, int c) {
	threshold[0] = a;
	threshold[1] = b;
	threshold[2] = c;
}

void End::Setting(int score, int level) {
	frame.LoadBitmapByString({ "resources/End_0.bmp", "resources/End_1.bmp", "resources/End_2.bmp", "resources/End_3.bmp" });
	frame.SetTopLeft(0, 0);
	if (score >= threshold[0]) {
		frame.SetFrameIndexOfBitmap(3);
		star = 3;
	}
	else if (score >= threshold[1]) {
		frame.SetFrameIndexOfBitmap(2);
		star = 2;
	}
	else if (score >= threshold[2]) {
		frame.SetFrameIndexOfBitmap(1);
		star = 1;
	}
	else {
		frame.SetFrameIndexOfBitmap(0);
		star = 0;
	}


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
