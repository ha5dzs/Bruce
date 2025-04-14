#ifndef __POCSAG_MENU_H__
#define __POCSAG_MENU_H__

#include <MenuItemInterface.h>

class POCSAGMenu : public MenuItemInterface {
public:
    POCSAGMenu() : MenuItemInterface("POCSAG") {}

    // These must be here.
    void optionsMenu(void);
    void drawIcon(float scale);
    void drawIconImg();
    bool getTheme() { return bruceConfig.theme.pocsag; } // Set to false in theme.h
};

#endif
