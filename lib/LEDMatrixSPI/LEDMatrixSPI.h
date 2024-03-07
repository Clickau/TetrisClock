#ifndef LEDMatrix_h
#define LEDMatrix_h

#include <Arduino.h>
#include <Adafruit_GFX.h>

// OE - active low
// LATCH / STB - active high
// CLK - active high

// OE must be inactivated and reactivated for the changes to be displayed
// R1 and R2 are two separate rows
// E pin is useless

class LEDMatrix : public Adafruit_GFX
{
public:
    LEDMatrix(uint8_t p_A, uint8_t p_B, uint8_t p_C, uint8_t p_D, uint8_t p_STB, uint8_t p_OE, SPIClass *spi);

    ~LEDMatrix();

    void begin();

    void drawPixel(int16_t x, int16_t y, uint16_t color) override;

    void drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue);

    void display(unsigned int show_time);

    void clearDisplay();

    void setGammaCorrection(bool b);

private:
    inline void latch();
    inline void output(unsigned int show_time);
    inline void setMultiplexer(uint8_t row);

private:
    int p_A;
    int p_B;
    int p_C;
    int p_D;
    int p_STB;
    int p_OE;
    uint8_t canvas[4][16][3][2][8]; // 4 color buffers, 16 groups of two rows, 3 colors, 2 rows, 8 bytes with 64 bits for each led
    SPIClass *spi;
    int current_buffer;
    bool gamma_correction;
    const uint8_t *gamma_correction_values;
};

#endif