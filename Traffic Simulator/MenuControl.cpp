#include "MenuControl.h"

MenuControl::MenuControl(UI* ui) : ui(ui) {
 
}

MenuControl::~MenuControl() {

}

void MenuControl::renderView(std::mt19937& mt) {
	ui->display();
}