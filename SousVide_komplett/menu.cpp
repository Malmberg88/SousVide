Menu::Menu(){
	horz_menu_layer = 0;
	vert_menu_layer = 0;
}
Menu::~Menu();

void Menu::change(){
	++vert_menu_layer;
}

void Menu::interact(){
	++horz_menu_layer
}

string Menu::print_hortz(){

}

string Menu::print_vert(){

}



