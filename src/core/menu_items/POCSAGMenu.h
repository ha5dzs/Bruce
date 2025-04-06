#ifndef __POCSAG_MENU_H__
#define __POCSAG_MENU_H__

#include <MenuItemInterface.h>

class POCSAGMenu : public MenuItemInterface {
public:
    POCSAGMenu() : MenuItemInterface("POCSAG") {}

    void optionsMenu(void);
    void draw_icon(float scale);
};

#endif
