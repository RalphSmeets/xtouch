#ifndef GT911_TOUCH_DRIVER_H
#define GT911_TOUCH_DRIVER_H

#include <Wire.h>
#include <TAMC_GT911.h>

SPIClass x_touch_spi = SPIClass(HSPI);
TAMC_GT911 x_touch_touchScreen(TOUCH_SDA, TOUCH_SCL, TOUCH_IRQ, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);
XTouchPanelConfig x_touch_touchConfig;

class ScreenPoint
{
public:
    int16_t x;
    int16_t y;

    // default constructor
    ScreenPoint()
    {
    }

    ScreenPoint(int16_t xIn, int16_t yIn)
    {
        x = xIn;
        y = yIn;
    }
};

ScreenPoint getScreenCoords(int16_t x, int16_t y)
{
    int16_t xCoord = round((x * x_touch_touchConfig.xCalM) + x_touch_touchConfig.xCalC);
    int16_t yCoord = round((y * x_touch_touchConfig.yCalM) + x_touch_touchConfig.yCalC);
    if (xCoord < 0)
        xCoord = 0;
    if (xCoord >= TFT_WIDTH)
        xCoord = TFT_WIDTH - 1;
    if (yCoord < 0)
        yCoord = 0;
    if (yCoord >= TFT_HEIGHT)
        yCoord = TFT_HEIGHT - 1;
    return (ScreenPoint(xCoord, yCoord));
}

void xtouch_loadTouchConfig(XTouchPanelConfig &config)
{
    // Open file for reading
    File file = xtouch_filesystem_open(SD, xtouch_paths_touch);

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<512> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error)
        ConsoleError.println(F("[XTouch][Touch] Failed to read touch config"));

    config.xCalM = doc["xCalM"].as<float>();
    config.yCalM = doc["yCalM"].as<float>();
    config.xCalC = doc["xCalC"].as<float>();
    config.yCalC = doc["yCalC"].as<float>();

    file.close();
}

void xtouch_saveTouchConfig(XTouchPanelConfig &config)
{
    StaticJsonDocument<512> doc;
    doc["xCalM"] = config.xCalM;
    doc["yCalM"] = config.yCalM;
    doc["xCalC"] = config.xCalC;
    doc["yCalC"] = config.yCalC;
    xtouch_filesystem_writeJson(SD, xtouch_paths_touch, doc);
}

void xtouch_resetTouchConfig()
{
    ConsoleInfo.println(F("[XTouch][FS] Resetting touch config"));
    xtouch_filesystem_deleteFile(SD, xtouch_paths_touch);
    delay(500);
    ESP.restart();
}

bool hasTouchConfig()
{
    ConsoleInfo.println(F("[XTouch][FS] Checking for touch config"));
    return xtouch_filesystem_exist(SD, xtouch_paths_touch);
}

void xtouch_touch_setup()
{
    if (hasTouchConfig())
    {
        ConsoleInfo.println(F("[XTouch][TOUCH] Load from disk"));
        xtouch_loadTouchConfig(x_touch_touchConfig);
    }
    else
    {
        ConsoleInfo.println(F("[XTouch][TOUCH] Touch Setup"));
        TP_Point p;
        int16_t x1, y1, x2, y2;

        lv_label_set_text(introScreenCaption, "Touch the  " LV_SYMBOL_PLUS "  with the stylus");
        lv_timer_handler();

        // wait for no touch
        while (x_touch_touchScreen.isTouched)
            ;
        tft.drawFastHLine(0, 10, 20, ILI9341_WHITE);
        tft.drawFastVLine(10, 0, 20, ILI9341_WHITE);
        while (!x_touch_touchScreen.isTouched)
            ;
        delay(50);
        p = x_touch_touchScreen.points[0];
        x1 = p.x;
        y1 = p.y;
        tft.drawFastHLine(0, 10, 20, ILI9341_BLACK);
        tft.drawFastVLine(10, 0, 20, ILI9341_BLACK);
        delay(500);

        while (x_touch_touchScreen.isTouched)
            ;
        tft.drawFastHLine(TFT_WIDTH - 20, TFT_HEIGHT - 10, 20, ILI9341_WHITE);
        tft.drawFastVLine(TFT_WIDTH - 10, TFT_HEIGHT - 20, 20, ILI9341_WHITE);

        while (!x_touch_touchScreen.isTouched)
            ;
        delay(50);
        p = x_touch_touchScreen.points[0];
        x2 = p.x;
        y2 = p.y;
        tft.drawFastHLine(TFT_WIDTH - 20, TFT_HEIGHT - 10, 20, ILI9341_BLACK);
        tft.drawFastVLine(TFT_WIDTH - 10, TFT_HEIGHT - 20, 20, ILI9341_BLACK);

        int16_t xDist = TFT_WIDTH - 40;
        int16_t yDist = TFT_HEIGHT - 40;

        x_touch_touchConfig.xCalM = (float)xDist / (float)(x2 - x1);
        x_touch_touchConfig.xCalC = 20.0 - ((float)x1 * x_touch_touchConfig.xCalM);
        // y
        x_touch_touchConfig.yCalM = (float)yDist / (float)(y2 - y1);
        x_touch_touchConfig.yCalC = 20.0 - ((float)y1 * x_touch_touchConfig.yCalM);

        xtouch_saveTouchConfig(x_touch_touchConfig);

        loadScreen(-1);
    }
}

#endif