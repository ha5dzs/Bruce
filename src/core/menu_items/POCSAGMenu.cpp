#include "POCSAGMenu.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/settings.h"
#include "core/utils.h"
#include "modules/rf/POCSAG.h"

void POCSAGMenu::optionsMenu() {
    // Options
    options = {
        {"Set Frequency", [=]() { pocsag_set_frequency(); }},
        {"Set baud rate", [=]() { pocsag_set_baudrate(); } },
        {"Transmit",      [=]() { pocsag_transmit(); }     },
        {"Exit",          [=]() { backToMenu(); }          }
    };

    addOptionToMainMenu();

    loopOptions(options, MENU_TYPE_SUBMENU, "POCSAG");
}

void POCSAGMenu::draw_icon(float scale) {
    // As per the example, and neighbouring files here.
    clearIconArea();
    int iconSize = scale * 60;
    int radius = scale * 7;
    int deltaRadius = scale * 10;

    int iconX = iconCenterX - iconSize / 2;
    int iconY = iconCenterY - iconSize / 2;

    tft.fillRect(iconX, iconY, iconSize, iconSize, bruceConfig.bgColor);

    tft.drawArc(19 + iconX, 45 + iconY, 12, 10, 130, 230, bruceConfig.priColor, bruceConfig.bgColor);
    tft.drawArc(19 + iconX, 45 + iconY, 22, 20, 130, 230, bruceConfig.priColor, bruceConfig.bgColor);
    tft.drawArc(19 + iconX, 45 + iconY, 32, 30, 130, 230, bruceConfig.priColor, bruceConfig.bgColor);
    tft.drawCentreString("POCSAG", 40 + iconX, 50 + iconY, SMOOTH_FONT);
}
