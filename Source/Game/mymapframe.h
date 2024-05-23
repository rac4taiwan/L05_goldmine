#ifndef MYMAPFRAME_H
#define MYMAPFRAME_H

namespace game_framework {
	class Episode : public CMovingBitmap {
	public:
		Episode();
		void SetTopLeft(int x, int y);
		void Big();
		void Setting(int value);
		void Show();
		void SetStar(int value);
	private:
		CMovingBitmap frame;
		CMovingBitmap number;
	};

	class End : public CMovingBitmap {
	public:
		End();
		void Setting(int score, int level);
		int GetStar();
		void SetStar(int value);
		void SetThreshold(int a, int b, int c);
	private:
		CMovingBitmap frame;
		CMovingBitmap number[3];
		int threshold[3] = { 0,0,0 };
		int star;
	};

	class MapFrame : public CMovingBitmap {
	public:
		MapFrame();
		void Setting();
		void OnMove();
		void GetPoint(int value);
		int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		int GetNowStage();
		void Show();
		void ChangeState(int value);
		bool IsOver();
		void SendScore(int score);
		void SetTime(int value);
		int GetTime();
		void SetThreshold(int a, int b, int c);
	private:
		CMovingBitmap Start;
		CMovingBitmap Background;
		Episode Stage[9];
		CMovingBitmap Time_label;
		CMovingBitmap Time_number[3];
		CMovingBitmap Finish;
		CMovingBitmap Score_label;
		CMovingBitmap Score_number[3];
		End EndGame;
		int state = 0;
		int count = 0;
		int now_level = 1;
		int total_level = 9;
		int end_score = 0;
		int time = 0;
		int score = 0;
	};
}

#endif
