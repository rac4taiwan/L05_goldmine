#ifndef MYMAPFRAME_H
#define MYMAPFRAME_H

namespace game_framework {
	class MapFrame : public CMovingBitmap {
	public:
		MapFrame();
		void Setting();
		void OnMove();
		void GetPoint(int score);
		int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		int GetNowStage();
		void Show();
	private:
		CMovingBitmap Start;
		CMovingBitmap Background;
		CMovingBitmap Stage[2];
		CMovingBitmap Time_label;
		CMovingBitmap Time_number[3];
		CMovingBitmap Finish;
		CMovingBitmap Score_label;
		CMovingBitmap Score_number[3];
		int state = 0;
		int count = 0;
		int level_choose = 1;
	};
}

#endif
