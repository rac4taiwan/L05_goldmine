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
		//virtual void Move();
		virtual string GetID();
	protected:
		int obj_status = 1;
	private:
		string ID = "treasure";
	};

	class GoldMine : public Treasure {
	public:
		GoldMine(int s, int x, int y);
		GoldMine();
		~GoldMine();
		virtual double Catch() override;
		virtual int Score() override;
		virtual bool GoldBackHome(double angle) override;
		virtual string GetID() override;
	protected:
		int size = 0;
	private:
		string ID = "goldmine";
	};

	class Stone : public GoldMine {
	public:
		Stone(int s, int x, int y);
		~Stone();
		int Score() override;
		string GetID() override;
	private:
		string ID = "stone";
	};

	class Diamond : public Treasure {
	public:
		Diamond(int x, int y);
		Diamond();
		~Diamond();
		virtual int Time() override;
		string GetID() override;
	private:
		string ID = "diamond";
	};

	class Can : public Diamond {
	public:
		Can(int x, int y);
		~Can();
		int Time() override;
		string GetID() override;
	private:
		string ID = "can";
	};

	class Mouse : public Diamond {
	public:
		Mouse(int x, int y);
		~Mouse();
		virtual int Score() override;
		void Move();
		string GetID() override;
	private:
		int count = 0;
		string ID = "mouse";
	};
	class Mummy : public Treasure {
	public:
		Mummy(int i, int x, int y);
		Mummy();
		~Mummy();
		virtual int Score() override;
		virtual void SetObjStatus(int value) override;
		string GetID() override;
	private:
		string ID = "mummy";
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
		bool operator==(Treasure* obj);
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