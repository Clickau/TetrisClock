#include <Arduino.h>
#include <RTClib.h>
#include <FreeRTOS.h>
#include <task.h>
#include "LEDMatrixSPI.h"
#include "tetris.h"

enum class Button {
    Up = 1,
    Enter = 2
};

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

const int p_ENTER = 19;
const int p_UP = 21;

const int clockPosX = 2;
const int clockPosY = 25;

LEDMatrix display(p_A, p_B, p_C, p_D, p_STB, p_OE, &SPI1);
Tetris tetris(&display);
RTC_DS3231 rtc;

volatile bool state = 0; // 0 is clock operation, 1 is setup
volatile bool forceSetTime = false;
volatile unsigned long lastButtonPress = 0;
volatile bool drawColon = true;
volatile bool finishedAnimating = false;
char lastDisplayedTime[6];

repeating_timer_t displayTimer;
repeating_timer_t animationTimer;
repeating_timer_t secondTimer;

TaskHandle_t setupHandle;

void setupTask(void *);
void enterHandler();
void upHandler();
bool secondHandler(repeating_timer_t *);
bool animationHandler(repeating_timer_t *);
bool displayHandler(repeating_timer_t *);
void startClock();
void stopClock();

void startClock()
{
    display.clearDisplay();
    tetris.clear();
    tetris.setScale(2);
    forceSetTime = true;
    add_repeating_timer_ms(-200, animationHandler, nullptr, &animationTimer);
    add_repeating_timer_ms(-1000, secondHandler, nullptr, &secondTimer);
}

void stopClock()
{
    cancel_repeating_timer(&animationTimer);
    cancel_repeating_timer(&secondTimer);
}

void displayPrompt()
{
    display.clearDisplay();
    tetris.setScale(1);
    tetris.setText("SET TIME", 8, 4, 20, true);
    tetris.draw(false);
}

void displayTime(const char *timeString)
{
    display.clearDisplay();
    tetris.setScale(2);
    tetris.setTimeString(timeString, clockPosX, clockPosY, false);
    tetris.drawTime(true, false);
}

void setupTask(void *)
{
    while (true)
    {
        vTaskSuspend(nullptr);

        stopClock();
        displayPrompt();
        delay(2000);

        bool visible = true;
        int currentlyEditing = 0;
        DateTime time = rtc.now();
        int values[2] = {time.hour(), time.minute()};
        const int max_values[2] = {23, 59};

        while (true)
        {
            char buffer[6] = "hh:mm";
            time = DateTime(time.year(), time.month(), time.day(), values[0], values[1], 0);
            time.toString(buffer);

            if (!visible)
            {
                if (currentlyEditing == 0)
                {
                    buffer[0] = ' ' + 33;
                    buffer[1] = ' ' + 33;
                }
                else if (currentlyEditing == 1)
                {
                    buffer[3] = ' ' + 33;
                    buffer[4] = ' ' + 33;
                }
            }
            visible = !visible;
            displayTime(buffer);

            uint32_t notification = 0;
            BaseType_t pressed = xTaskNotifyWait(
                0,
                ULONG_MAX,
                &notification,
                pdMS_TO_TICKS(200)
            );

            Button button = (Button) notification;

            if (pressed == pdTRUE)
            {
                if (button == Button::Up)
                {
                    values[currentlyEditing]++;
                    if (values[currentlyEditing] > max_values[currentlyEditing])
                        values[currentlyEditing] = 0;
                }
                else if (button == Button::Enter)
                {
                    currentlyEditing++;
                }
                visible = true;
            }

            if (currentlyEditing >= 2)
            {
                rtc.adjust(time);
                state = 0;
                startClock();
                break;
            }
        }
    }
}

void enterHandler()
{
    if (millis() - lastButtonPress < 100) return;
    lastButtonPress = millis();
    if (!state)
    {
        state = 1;
        BaseType_t yieldRequired = xTaskResumeFromISR(setupHandle);
        portYIELD_FROM_ISR(yieldRequired);
    }
    else
    {
        BaseType_t yieldRequired = pdFALSE;
        xTaskNotifyFromISR(
            setupHandle,
            (uint32_t) Button::Enter,
            eSetValueWithoutOverwrite,
            &yieldRequired
        );
        portYIELD_FROM_ISR(yieldRequired);
    }
}

void upHandler()
{
    if (millis() - lastButtonPress < 100) return;
    lastButtonPress = millis();
    if (state == 0) return;
    BaseType_t yieldRequired = pdFALSE;
    xTaskNotifyFromISR(
        setupHandle,
        (uint32_t) Button::Up,
        eSetValueWithoutOverwrite,
        &yieldRequired
    );
    portYIELD_FROM_ISR(yieldRequired);
}

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

    if (strcmp(buf, lastDisplayedTime) != 0 || forceSetTime)
    {
        strcpy(lastDisplayedTime, buf);
        tetris.setTimeString(buf, clockPosX, clockPosY, false);
        finishedAnimating = false;
        forceSetTime = false;
    }
    return true;
}

void setup()
{
    Serial.begin(115200);

    Wire1.setSCL(7);
    Wire1.setSDA(6);
    rtc.begin(&Wire1);

    pinMode(p_R1, INPUT);
    pinMode(p_R2, INPUT);
    pinMode(p_G1, INPUT);
    pinMode(p_G2, INPUT);
    pinMode(p_B1, INPUT);
    pinMode(p_B2, INPUT);
    pinMode(p_CLK, INPUT);
    pinMode(p_ENTER, INPUT_PULLUP);
    pinMode(p_UP, INPUT_PULLUP);

    SPI1.setTX(p_MOSI);
    SPI1.setRX(p_MISO);
    SPI1.setSCK(p_SCLK);

    display.begin();
    display.setGammaCorrection(true);

    srand(micros());

    add_repeating_timer_ms(-3, displayHandler, nullptr, &displayTimer);
    startClock();

    attachInterrupt(p_ENTER, enterHandler, FALLING);
    attachInterrupt(p_UP, upHandler, FALLING);

    xTaskCreate(
        setupTask,
        "Setup Task",
        1024,
        nullptr,
        0,
        &setupHandle
    );

    vTaskDelete(nullptr);
}

void loop() {}