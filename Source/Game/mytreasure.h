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
		double Catch() override;
		virtual int Score() override;
		virtual void SetSize(int s);
		virtual void Show();
		virtual void UnShow();
		virtual void SetPosition(int x, int y);
		virtual int GetPositionX();
		virtual int GetPositionY();
		virtual int GetWidth();
		virtual int GetHeight();
		virtual bool GoldBackHome(double angle);
		virtual int GetObjStatus();
		virtual void SetObjStatus(int value);
	private:
		int size = 0;
		CMovingBitmap mine;
		int state = 0;
		int obj_status = 1;
	};

	class Stone : public GoldMine {
	public:
		Stone();
		~Stone();
		void SetSize(int s) override;
		int Score() override;
		void SetPosition(int x, int y) override;
		void Show() override;
		void UnShow() override;
		int GetPositionX() override;
		int GetPositionY() override;
		int GetWidth() override;
		int GetHeight() override;
		bool GoldBackHome(double angle) override;
		int GetObjStatus() override;
		void SetObjStatus(int value) override;
	private:
		int size = 0;
		CMovingBitmap mine;
		int state = 0;
		int obj_status = 1;
	};

	class Diamond : public Treasure {
	public:
		Diamond();
		~Diamond();
		virtual double Catch() override;
		virtual int Time() override;
		virtual void Set();
		void Show();
		void UnShow();
		void SetPosition(int x, int y);
		int GetPositionX();
		int GetPositionY();
		int GetWidth();
		int GetHeight();
		bool GoldBackHome(double angle);
		int GetObjStatus();
		void SetObjStatus(int value);
	private:
		//int size = 0;
		CMovingBitmap mine;
		int state = 0;
		int obj_status = 1;
	};

	class Can : public Diamond {
	public:
		Can();
		~Can();
		virtual double Catch() override;
		virtual int Time() override;
		virtual void Set() override;
		void Show();
		void UnShow();
		void SetPosition(int x, int y);
		int GetPositionX();
		int GetPositionY();
		int GetWidth();
		int GetHeight();
		bool GoldBackHome(double angle);
		int GetObjStatus();
		void SetObjStatus(int value);
	private:
		//int size = 0;
		CMovingBitmap mine;
		int state = 0;
		int obj_status = 1;
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
		double angle;			//顯示目前角度
		int hook_status = 0; //設定狀態：0=搖晃中，1=放線，2=收回線，3=非關卡途中
		int frameindex;
	};

}

#endif