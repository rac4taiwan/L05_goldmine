#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "mytreasure.h"

using namespace game_framework;

Treasure::Treasure() {

}

Treasure::~Treasure() {

}

double Treasure::Catch() {
	return 0.9;
}

int Treasure::Score() {
	return 0;
}

int Treasure::Time() {
	return 0;
}