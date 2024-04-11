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
	private:
		CMovingBitmap frame;
		CMovingBitmap number[3];
		int star;
	};

	class MapFrame : public CMovingBitmap {
	public:
		MapFrame();
		void Setting();
		void OnMove();
		void GetPoint(int score);
		int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		int GetNowStage();
		void Show();
		void ChangeState(int value);
		bool IsOver();
		void SendScore(int score);
	private:
		CMovingBitmap Start;
		CMovingBitmap Background;
		Episode Stage[5];
		CMovingBitmap Time_label;
		CMovingBitmap Time_number[3];
		CMovingBitmap Finish;
		CMovingBitmap Score_label;
		CMovingBitmap Score_number[3];
		End EndGame;
		int state = 0;
		int count = 0;
		int now_level = 1;
		int total_level = 5;
		int end_score = 0;
	};
}

#endif
