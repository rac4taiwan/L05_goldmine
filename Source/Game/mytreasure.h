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
		virtual bool GoldBackHome(double angle);
		virtual int GetObjStatus();
		virtual void SetObjStatus(int value);
		virtual void Move();
	protected:
		int obj_status = 1;
	};

	class GoldMine : public Treasure {
	public:
		GoldMine(int s, int x, int y);
		GoldMine();
		~GoldMine();
		virtual double Catch() override;
		virtual int Score() override;
		//virtual void SetSize(int s);
		//virtual void Size(int s);
		virtual bool GoldBackHome(double angle) override;
		//virtual int GetObjStatus();
		//virtual void SetObjStatus(int value);
	protected:
		int size = 0;
		//CMovingBitmap mine;
		//int state = 0;
		//int obj_status = 1;
	};

	class Stone : public GoldMine {
	public:
		Stone(int s, int x, int y);
		~Stone();
		//double Catch() override;
		//void SetSize(int s) override;
		int Score() override;
		//void SetPosition(int x, int y) override;
		//void Show() override;
		//void UnShow() override;
		//int GetPositionX() override;
		//int GetPositionY() override;
		//int GetWidth() override;
		//int GetHeight() override;
		//bool GoldBackHome(double angle) override;
		//int GetObjStatus() override;
		//void SetObjStatus(int value) override;
	private:
		//int size = 0;
		//CMovingBitmap mine;
		//int state = 0;
		//int obj_status = 1;
	};

	class Diamond : public Treasure {
	public:
		Diamond(int x, int y);
		Diamond();
		~Diamond();
		//virtual double Catch();
		virtual int Time() override;
		//virtual void Set();
		//void Show();
		//void UnShow();
		//void SetPosition(int x, int y);
		//int GetPositionX();
		//int GetPositionY();
		//int GetWidth();
		//int GetHeight();
		//bool GoldBackHome(double angle);
		//int GetObjStatus();
		//void SetObjStatus(int value);
	private:
		//int size = 0;
		//CMovingBitmap mine;
		//int state = 0;
		//int obj_status = 1;
	};

	class Can : public Diamond {
	public:
		Can(int x, int y);
		~Can();
		//virtual double Catch() override;
		int Time() override;
		//virtual void Set() override;
		//void Show();
		//void UnShow();
		//void SetPosition(int x, int y);
		//int GetPositionX();
		//int GetPositionY();
		//int GetWidth();
		//int GetHeight();
		//bool GoldBackHome(double angle);
		//int GetObjStatus();
		//void SetObjStatus(int value);
	private:
		//int size = 0;
		//CMovingBitmap mine;
		//int state = 0;
		//int obj_status = 1;
	};

	class Mouse : public Diamond {
	public:
		Mouse(int x, int y);
		~Mouse();
		//virtual double Catch() override;
		virtual int Score() override;
		//virtual void Set() override;
		//void Show();
		//void UnShow();
		//void SetPosition(int x, int y);
		//int GetPositionX();
		//int GetPositionY();
		//int GetWidth();
		//int GetHeight();
		//bool GoldBackHome(double angle);
		//int GetObjStatus();
		//void SetObjStatus(int value);
		void Move() override;
	private:
		//int size = 0;
		//CMovingBitmap mine;
		//int state = 0;
		//int obj_status = 1;
		int count = 0;
	};

	class Mummy : public Treasure {
	public:
		Mummy(int i, int x, int y);
		Mummy();
		~Mummy();
		//virtual double Catch() override;
		virtual int Score() override;
		//virtual void SetSize(int s);
		//virtual void Size(int s);
		//virtual bool GoldBackHome(double angle) override;
		//virtual int GetObjStatus();
		virtual void SetObjStatus(int value) override;
	protected:
		//int frame = 0;
		//CMovingBitmap mine;
		//int state = 0;
		//int obj_status = 1;
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
		void SetSpeed(double value);
	private:
		CMovingBitmap hook_stay;
		CMovingBitmap hook_attack;
		double x;
		double y;
		double angle;			//顯示目前角度
		double speed = 1.0;
		int hook_status = 0; //設定狀態：0=搖晃中，1=放線，2=收回線，3=非關卡途中
		int frameindex;
	};

}

#endif