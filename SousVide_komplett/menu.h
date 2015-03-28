#include <WString.h>
#pragma once
#define _MENU_

class Menu{
public:
	Menu();
	~Menu();
	void change();
	void interact();
	String print_horz();
	String print_vert();

private:
	unsigned int* horz_menu_layer;
	unsigned int* vert_menu_layer;
};
