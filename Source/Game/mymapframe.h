#ifndef MYMAPFRAME_H
#define MYMAPFRAME_H

namespace game_framework {
	class MapFrame : public CMovingBitmap {
	public:
		MapFrame();
		void Setting();
		void Show();
	private:
		CMovingBitmap bb;
	};
}

#endif
