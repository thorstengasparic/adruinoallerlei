/*
 * menu.h
 *
 * Created: 30.07.2012 19:06:57
 *  Author: OliverS
 */ 


#ifndef MENU_H_
#define MENU_H_

void Menu_MenuInit();
void Menu_MenuShow();
void Menu_LoadPage(const uint8_t pageIndex);
void editModeHandler();
void Menu_EnableAllItems ();

#endif /* MENU_H_ */