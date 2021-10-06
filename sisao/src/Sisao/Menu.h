#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <string>
#include "Text.h"

class Menu
{
public:
	void init();
	void update(int deltatime);
	void render();
		
private:
	Text *title, *instructions;

};


#endif // _MENU_INCLUDE
