#ifndef TETRIS_h
#define TETRIS_h

#define TETRIS_MAX_CHARS 9
#define TETRIS_SPACE_BETWEEN_CHARACTERS 7
#define TETRIS_FALLING_Y_POS 8
#define TETRIS_EMPTY_CHAR (char) 255

#include <Adafruit_GFX.h>
#include "tetris_characters.h"

struct char_state_t
{
    char c; // 0 - 9 for numbers, ascii value for characters, -1 for empty
    int fallingBlockIndex;
    int xPos;
    int finalYPos;
    int fallingYOffset;
    uint16_t colors[8];
};

class Tetris
{
public:
    Tetris(Adafruit_GFX *display);
    void clear();

    void test();
    bool draw(bool animate = true);
    bool drawTime(bool displayColon, bool animate = true);
    void drawColon(bool displayColon);
    void setText(const char *text, int len, int x, int y, bool forceRefresh = false);
    void setTimeString(const char *time, int x, int y, bool forceRefresh = false);
    void setScale(uint8_t s);


    const static uint16_t tetrisRED = 0xF800;
    const static uint16_t tetrisGREEN = 0x07E0;
    const static uint16_t tetrisBLUE = 0x325F;
    const static uint16_t tetrisWHITE = 0xFFFF;
    const static uint16_t tetrisYELLOW = 0xFFE0;
    const static uint16_t tetrisCYAN = 0x07FF;
    const static uint16_t tetrisMAGENTA = 0xF81F;
    const static uint16_t tetrisORANGE = 0xFB00;
    const static uint16_t tetrisBLACK = 0x0000;
    const static uint16_t tetrisColors[8];

private:
    void drawShape(blocktype_t block, uint16_t color, int xPos, int yPos, int rotation);
    int computeRotation(int finalRotation, int fallingYOffset);
    void randomizeColors();
    void drawScaledPixel(int16_t x, int16_t y, uint16_t color);
    void randomizeColors(uint16_t *colors);

    Adafruit_GFX *display;
    char_state_t states[TETRIS_MAX_CHARS];
    uint8_t scale;
};

#endif