#include "menu.h"
Menu::Menu(){
	*horz_menu_layer = 0;
	*vert_menu_layer = 0;
	}
Menu::~Menu(){
}

void Menu::change(){
        if(&horz_menu_layer == 0){
          *++vert_menu_layer;
      	  if (*vert_menu_layer % 3 == 0){
            *vert_menu_layer = 0;
      	  }
        }
}

void Menu::interact(){
	*++horz_menu_layer;
}

String Menu::print_horz(){
  if (*horz_menu_layer == 0){
    return "Menu";
  }else if (*horz_menu_layer == 1){
    return "Temperature:";
  }else if (*horz_menu_layer == 2){
    return "Parameters:";
  }
}

String Menu::print_vert(){
  if (&horz_menu_layer == 0){
    if(&vert_menu_layer == 0){
      return "Temperature";
    } else {
      return "Paramters";
    }
  }
  return "";
}



