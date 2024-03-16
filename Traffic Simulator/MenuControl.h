#pragma once

#include "Control.h"
#include "Program.h"

class MenuControl : public Control {
	UI* ui;

public:
	MenuControl(UI* ui);
	~MenuControl();

	void renderView(std::mt19937& mt);
};