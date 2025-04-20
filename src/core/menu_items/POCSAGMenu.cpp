#include "POCSAGMenu.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/settings.h"
#include "core/utils.h"
#include "modules/rf/POCSAG.h"
#include <RadioLib.h>

void POCSAGMenu::optionsMenu() {
    // Options
    options = {
        // The linker complains that these are not there yet, which is fair. Commented out for now.
        {"Start receiving", [=]() { pocsag_receive(); }          },
        {"Monitor channel", [=]() { /*pocsag_receive();*/ }      },
        {"Set Frequency",   [=]() { /*pocsag_set_frequency();*/ }},
        {"Set baud rate",   [=]() { /*pocsag_set_baudrate();*/ } },
        {"Set ID",          [=]() { /*pocsag_set_id();*/ }       },
        {"Send message",    [=]() { /*pocsag_transmit();*/ }     },
        {"Exit",            [=]() { backToMenu(); }              }
    };

    addOptionToMainMenu();

    loopOptions(options, MENU_TYPE_SUBMENU, "POCSAG");
}

void POCSAGMenu::drawIconImg() {
    drawImg(
        *bruceConfig.themeFS(),
        bruceConfig.getThemeItemImg(bruceConfig.theme.paths.pocsag),
        0,
        imgCenterY,
        true
    ); // See theme.h, right now a bunch of empty strings.
}

void POCSAGMenu::drawIcon(float scale) {
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
