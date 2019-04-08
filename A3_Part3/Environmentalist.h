#pragma once
#include "Strategy.h"

/**
* A concrete Strategy that implements actions of an environmentalist player
*/

class Environmentalist : public Strategy {
public:
	void execute(Player);
};
