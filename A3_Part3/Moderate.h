#pragma once
#include "Strategy.h"

/**
* A concrete Strategy that implements actions of a moderate player
*/

class Moderate : public Strategy {
public:
	void execute(Player);
};

