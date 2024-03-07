#include <Arduino.h>
#include <RTClib.h>
#include "LEDMatrixSPI.h"
#include "tetris.h"

const int p_A = 10;
const int p_B = 16;
const int p_C = 18;
const int p_D = 20;
const int p_E = 22;
const int p_STB = 12;
const int p_OE = 13;
const int p_CLK = 11;
const int p_R1 = 2;

// p_MOSI must be connected to p_R1
// p_SCLK must be connected to p_CLK
const int p_MOSI = 15;
const int p_SCLK = 14;

/*
connection on display connectors:
out     in
R1      R2
R2      G1
G1      G2
G2      B1
B1      B2
*/
// these will be set to input and cannot be used
const int p_R2 = 5;
const int p_G1 = 3;
const int p_G2 = 8;
const int p_B1 = 4;
const int p_B2 = 9;
const int p_MISO = 8;

const int clockPosX = 2;
const int clockPosY = 25;

LEDMatrix display(p_A, p_B, p_C, p_D, p_STB, p_OE, &SPI1);
Tetris tetris(&display);
RTC_DS3231 rtc;

volatile bool drawColon = true;
volatile bool finishedAnimating = false;
char lastDisplayedTime[6];

repeating_timer_t displayTimer;
repeating_timer_t animationTimer;
repeating_timer_t secondTimer;

bool animationHandler(repeating_timer_t *)
{
    if (finishedAnimating)
    {
        tetris.drawColon(drawColon);
    }
    else
    {
        display.clearDisplay();
        finishedAnimating = tetris.drawTime(drawColon);
    }
    return true;
}

bool displayHandler(repeating_timer_t *)
{
    display.display(10);
    return true;
}

bool secondHandler(repeating_timer_t *)
{
    drawColon = !drawColon;

    DateTime now = rtc.now();
    char buf[6] = "hh:mm";
    now.toString(buf);

    if (strcmp(buf, lastDisplayedTime) != 0)
    {
        strcpy(lastDisplayedTime, buf);
        tetris.setTimeString(buf, clockPosX, clockPosY, false);
        finishedAnimating = false;
    }
    return true;
}

void setup()
{
    Serial.begin(115200);

    
    Wire1.setSCL(7);
    Wire1.setSDA(6);
    rtc.begin(&Wire1);

    // while (!Serial)
    //     delay(100);
    
    // Serial.print("enter time:");
    // while (!Serial.available()) delay(100);
    // String s = Serial.readStringUntil('\n');
    // Serial.println(s);
    // int h = s.substring(0, 2).toInt(), m = s.substring(3, 5).toInt();
    // Serial.printf("h: %d, m: %d\n", h, m);
    // rtc.adjust(DateTime(2024, 3, 6, h, m, 0));

    // DateTime d = rtc.now();
    // char buf[100] = "DD.MM.YYYY hh:mm";
    // d.toString(buf);
    // Serial.println(buf);

    pinMode(p_R1, INPUT);
    pinMode(p_R2, INPUT);
    pinMode(p_G1, INPUT);
    pinMode(p_G2, INPUT);
    pinMode(p_B1, INPUT);
    pinMode(p_B2, INPUT);
    pinMode(p_CLK, INPUT);

    SPI1.setTX(p_MOSI);
    SPI1.setRX(p_MISO);
    SPI1.setSCK(p_SCLK);

    display.begin();
    display.setGammaCorrection(true);
    display.clearDisplay();

    srand(micros());
    tetris.setScale(2);

    add_repeating_timer_ms(-3, displayHandler, nullptr, &displayTimer);
    add_repeating_timer_ms(-200, animationHandler, nullptr, &animationTimer);
    add_repeating_timer_ms(-1000, secondHandler, nullptr, &secondTimer);
}

void loop()
{
    delay(1000);
}