#include <Arduino.h>
#include "pincfg.h"
#include "dispcfg.h"
#include "AXS15231B_touch.h"
#include <Arduino_GFX_Library.h>



Arduino_DataBus *bus = new Arduino_ESP32QSPI(TFT_CS, TFT_SCK, TFT_SDA0, TFT_SDA1, TFT_SDA2, TFT_SDA3);
Arduino_GFX *g = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, TFT_res_W, TFT_res_H);
Arduino_Canvas *gfx = new Arduino_Canvas(TFT_res_W, TFT_res_H, g, 0, 0, 0);
AXS15231B_Touch touch(Touch_SCL, Touch_SDA, Touch_INT, Touch_ADDR, 0);


void setup(void) {
    Serial.begin(115200);
    Serial.println("Arduino_GFX JC3248W535 Test");

    // Switch backlight on
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    // Touch setup
    if(!touch.begin()) {
        Serial.println("Failed to initialize touch module!");
    }
    touch.setRotation(TFT_rot);
    touch.enOffsetCorrection(true);
    touch.setOffsets(Touch_X_min, Touch_X_max, TFT_res_W-1, Touch_Y_min, Touch_Y_max, TFT_res_H-1);

    // Display setup
    if(!gfx->begin()) {
        Serial.println("Failed to initialize display!");
    }
    gfx->setRotation(TFT_rot);
    gfx->fillScreen(WHITE);

    // Print something on the screen
    gfx->setCursor(105, 125);
    gfx->setTextSize(4);
    gfx->setTextColor(BLACK);
    gfx->printf("Hello World!");
    gfx->flush();
    delay(2000);
}

void loop() {
    // Read touch point
    uint16_t x, y;
    if (touch.touched()) {
        touch.readData(&x, &y);
        Serial.printf("X = %d, Y = %d\n", x, y);
        gfx->fillScreen(WHITE);
        gfx->setCursor(140, 140);
        gfx->setTextSize(2);
        gfx->setTextColor(BLUE);
        gfx->printf("X = %d, Y = %d\n", x, y);
        gfx->flush();
    } 
}
