#include "MapControl.h"

MapControl::MapControl(Program* prog) : prog(prog) {

}

MapControl::~MapControl() {

}

void MapControl::renderView(std::mt19937& mt) {
	prog->buttonsShow(mt);
}