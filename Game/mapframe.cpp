#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "mymapframe.h"

using namespace game_framework;

MapFrame::MapFrame(){

}

void MapFrame::Setting() {
	bb.LoadBitmapByString({ "resources/Cover.bmp" });
	bb.SetTopLeft(0, 0);
}

void MapFrame::Show()
{
	bb.ShowBitmap();
}
