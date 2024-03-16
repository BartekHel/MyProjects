#include "CarControl.h"

CarControl::CarControl(Program* prog) : prog(prog) {

}

CarControl::~CarControl() {

}

void CarControl::renderView(std::mt19937& mt) {
	prog->buttonsShow(mt);
	prog->renderProgram(mt);
}