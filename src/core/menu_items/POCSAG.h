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

// GUI callback function declarations

void pocsag_set_frequency(void);
void pocsag_set_baudrate(void);
void pocsag_transmit(void);

