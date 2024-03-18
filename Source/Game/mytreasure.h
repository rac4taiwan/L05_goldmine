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
		bool Overlap(CMovingBitmap hook, GoldMine bmp);
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

	class Tab : public CMovingBitmap {
	public:
		void UpdateObjectPosition(double angularAmplitude, double angularFrequency, double deltaTime);

	};
}

#endif