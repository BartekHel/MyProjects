#pragma once

#include "Control.h"
#include "Program.h"

class MapControl : public Control {
	Program* prog;

public:
	MapControl(Program* prog);
	~MapControl();

	void renderView(std::mt19937& mt);
};