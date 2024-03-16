#pragma once

#include "Control.h"
#include "Program.h"

class CarControl : public Control {
	Program* prog;

public:
	CarControl(Program* prog);
	~CarControl();

	void renderView(std::mt19937& mt);
};