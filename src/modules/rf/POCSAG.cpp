#include "modules/rf/POCSAG.h"
#include "core/display.h"
#include "core/led_control.h"
#include "core/mykeyboard.h"
#include "core/sd_functions.h"
#include "core/settings.h"
#include <RadioLib.h>

// The cc1101 is on the main HSPI bus, and is already configured before we get here.
CC1101 rfmodule = new Module(CC1101_SS_PIN, CC1101_GDO0_PIN, RADIOLIB_NC, CC1101_GDO2_PIN, CC_NRF_SPI);
const int data_receive_pin = CC1101_GDO2_PIN;

PagerClient pager_client(&rfmodule);

/*
 * Receive function. All hard-coded for now, see if it works...
 */

void pocsag_receive(void) {
    Serial.println("POCSAG.cpp::pocsag_receive() started.");
    int fail = RADIOLIB_ERR_NONE; // Our failure detection variable

    // Set band on radio chip
    // SW1:1  SW0:0 --- 315MHz
    // SW1:0  SW0:1 --- 868/915MHz
    // SW1:1  SW0:1 --- 434MHz
    digitalWrite(CC1101_SW0_PIN, HIGH);
    digitalWrite(CC1101_SW1_PIN, HIGH);

    // Initialsigng SPI
    CC_NRF_SPI.begin(CC1101_SCK_PIN, CC1101_MISO_PIN, CC1101_MOSI_PIN, CC1101_SS_PIN);

    // Initialise the radio chip
    fail = rfmodule.begin();
    if (fail) { Serial.printf("POCSAG.cpp::Error %d when initialising cc1101.\n", fail); }

    // Attach pager client
    fail = pager_client.begin(433.920, 1200);
    if (fail) { Serial.printf("POCSAG.cpp::Error %d when initialising the pager client.\n", fail); }

    // In order to receive every page, we need to create an array of addresses.
    uint32_t addresses[] = {0, 216, 224, 208, 200, 2504, 4520};
    uint32_t masks[] = {0xFFFFF, 0xFFFFF, 0xFFFFF, 0xFFFFF, 0xFFFFF, 0xFFFFF, 0xFFFFF};

    // Start receiving
    fail = pager_client.startReceive(
        data_receive_pin, addresses, &masks[0], sizeof(addresses) >> 2
    ); // Second arg is ID, third is mask.

    // fail = pager_client.startReceive(data_receive_pin, 0, 0xFFFFF); // For single address
    if (fail) { Serial.printf("POCSAG.cpp::Error %d when starting receiving.\n", fail); }

    // Loop here until we press the button at the top
    while (digitalRead(BK_BTN)) {
        if (pager_client.available() > 2) {
            // Send it back over seial, for now.
            // Serial.println("POCSAG.cpp::Got something....");
            blinkLed(100);
            // Receive:
            uint32_t sender_address = 0;
            String received_string;
            fail = pager_client.readData(received_string, 0, &sender_address);
            if (fail) {
                Serial.printf("POCSAG.cpp::Error %d when reading data.\n", fail);
            } else {
                Serial.printf("[%d]: %s\n", sender_address, received_string.c_str());
            }
        }
    }

    Serial.println("Back button pressed, returning.");
    return;
}

void pocsag_set_frequency(void);
void pocsag_set_baudrate(void);
void pocsag_transmit(void);
