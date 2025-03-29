#include "POCSAG.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/settings.h"
#include "core/utils.h"
#include <globals.h>
#include "modules/rf/rf.h" // This will probably change.
//#include "../lib/RadioLib/src/RadioLib.h" // Custom cc1101 library
//#include <RadioLib.h>

void POCSAGMenu::optionsMenu() {
    // Options
    options = {
        {"Set Frequency",         [=]() { pocsag_set_frequency(); }},
        {"Set baud rate",       [=]() { pocsag_set_baudrate(); }},
        {"Transmit",       [=]() { pocsag_transmit(); }},
        {"Exit",       [=]() { backToMenu(); }}
      };

    addOptionToMainMenu();

    delay(200);
    loopOptions(options,false,true,"POCSAG");
}

void POCSAGMenu::draw_icon() {
    // As per the example.
    tft.fillRect(iconX,iconY,80,80,BGCOLOR);

    tft.drawArc(19+iconX,45+iconY,12,10,130,230,FGCOLOR,BGCOLOR);
    tft.drawArc(19+iconX,45+iconY,22,20,130,230,FGCOLOR,BGCOLOR);
    tft.drawArc(19+iconX,45+iconY,32,30,130,230,FGCOLOR,BGCOLOR);
    tft.drawCentreString("POCSAG",40+iconX, 50+iconY, SMOOTH_FONT);
}
