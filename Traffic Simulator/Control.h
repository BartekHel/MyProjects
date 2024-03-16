#pragma once

#include <random>

class Control {
public:
	virtual ~Control() { };

	void virtual renderView(std::mt19937& mt) = 0;
};