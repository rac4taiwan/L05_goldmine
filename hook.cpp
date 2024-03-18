#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Source/Game/mygame.h"
#include "Source/Game/mytreasure.h"
#include <cmath>

using namespace game_framework;

void CGameStateRun::ReleaseTab(int frameindex)
{
	angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (0) {
		tmp_treasure = 2;
		status = 2;
	}
	else if (hook.GetLeft() + 150 > 900 || hook.GetLeft()  < 0 || hook.GetTop() +100 > 600) {
		status = 2;
	}
	else {
		x = hook.GetLeft() + 10 * cos(angle);
		y = hook.GetTop() - 10 * sin(angle);
		hook.SetTopLeft(int(x), int(y));
	}
}

void CGameStateRun::RollTab(int frameindex)
{
	angle = 340 - (10 * frameindex);
	angle = angle * 3.1416 / 180;

	if (hook.GetTop() <= 75) {//回到一定高度後回收
		status = 0;
		hook.SetTopLeft(400, 75);
	}
	else {
		//要再乘以速度設定
		x = hook.GetLeft() - 10 * cos(angle);
		y = hook.GetTop() + 10 * sin(angle);
		hook.SetTopLeft(int(x), int(y));

	}	
}

/*bool CGameStateRun::IsOverlap(CMovingBitmap hook, GoldMine bmp) {
	if (hook.GetTop() > bmp.GetPositionY() && hook.GetTop() < bmp.GetPositionY() + 85) {
		if (hook.GetLeft() > bmp.GetPositionX() && hook.GetLeft() < bmp.GetPositionX() + 150) {
			return true;
		}
	}
	return false;
}*/

void CGameStateRun::GoldBackHome(GoldMine bmp, double angle) {
	if (bmp.GetPositionY() <= 75) {//回到一定高度後回收
		int v1 = Score_number[2].GetFrameIndexOfBitmap() + gold.Score() % 10;
		int v2 = Score_number[1].GetFrameIndexOfBitmap() + gold.Score() / 10 + v1 / 10;
		int v3 = Score_number[0].GetFrameIndexOfBitmap() + v2 / 10;
		Score_number[0].SetFrameIndexOfBitmap(v3);
		Score_number[1].SetFrameIndexOfBitmap(v2);
		Score_number[2].SetFrameIndexOfBitmap(v1);
		tmp_treasure = 1;
	}
	else {
		//要再乘以速度設定
		x = bmp.GetPositionX() - 10 * cos(angle);
		y = bmp.GetPositionY() + 10 * sin(angle);
		bmp.SetPosition(int(x), int(y));
	}
}