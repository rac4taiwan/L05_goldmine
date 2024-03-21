#ifndef MYTREASURE_H
#define MYTREASURE_H


namespace game_framework {
	class Treasure : public CMovingBitmap {
	public:
		Treasure();
		~Treasure();
		virtual double Catch();
		virtual int Score();
		virtual int Time();
	};

	class GoldMine : public Treasure {
	public:
		GoldMine();
		~GoldMine();
		virtual double Catch() override;
		virtual int Score() override;
		virtual void SetSize(int s);
		void Show();
		void UnShow();
		void SetPosition(int x, int y);
		int GetPositionX();
		int GetPositionY();
	private:
		int size = 0;
		CMovingBitmap mine;
	};

	class Stone : GoldMine {
	public:
		Stone();
		~Stone();
		virtual void SetSize(int s) override;
	private:
		int size = 0;
		CMovingBitmap mine;
	};


	class hookcpp : public CMovingBitmap {
	public:
		hookcpp();
		~hookcpp();
		void LoadTheTab();
		void LoadHook();
		void SetHook(int frameindex);
		void Show();
		void UnShow();
		static void ReleaseTab(hookcpp hook, int frameindex);
		static void RollTab(hookcpp hook, int frameindex);
		static bool IsOverlap(hookcpp hook, int a, int b);
		static bool GoldBackHome(GoldMine bmp, int frameindex);
		void SetPosition(int x, int y);
		int GetPositionX();
		int GetPositionY();
		int GetFrameIndex();
		void SetAnimate(int delay, bool once);
	private:
		CMovingBitmap mine;
		static double x;
		static double y;
		double angle;			//顯示目前角度
	};

}

#endif