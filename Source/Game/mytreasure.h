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
		int GetWidth();
		int GetHeight();
		bool GoldBackHome(int frameindex);
		int GetObjStatus();
		void SetObjStatus(int value);
	private:
		int size = 0;
		CMovingBitmap mine;
		int state = 0;
		int obj_status = 1;
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
		void Setting();
		void OnMove();
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnShow();
		void ReleaseTab(int frameindex);
		void RollTab(int frameindex);
		bool IsOverlap(int ox, int oy, int ow, int oh);
		int GetFrameIndex();
		void SetAnimate(int delay, bool once);
	private:
		CMovingBitmap hook_stay;
		CMovingBitmap hook_attack;
		double x;
		double y;
		double angle;			//��ܥثe����
		int hook_status = 0; //�]�w���A�G0=�n�̤��A1=��u�A2=���^�u�A3=�D���d�~��
		int frameindex;
	};
}

#endif