#include "LEDMatrixSPI.h"
#include <SPI.h>

#include "gamma_correction.h"

LEDMatrix::LEDMatrix(
    uint8_t p_A, uint8_t p_B, uint8_t p_C, uint8_t p_D, uint8_t p_STB, uint8_t p_OE, SPIClass *spi)
    : Adafruit_GFX(64, 32)
{
    this->p_A = p_A;
    this->p_B = p_B;
    this->p_C = p_C;
    this->p_D = p_D;
    this->p_STB = p_STB;
    this->p_OE = p_OE;
    this->spi = spi;
    this->current_buffer = 0;
    this->gamma_correction_values = gamma_correction_array;
}

LEDMatrix::~LEDMatrix()
{
    spi->endTransaction();
    spi->end();
}

void LEDMatrix::begin()
{
    pinMode(p_A, OUTPUT);
    pinMode(p_B, OUTPUT);
    pinMode(p_C, OUTPUT);
    pinMode(p_D, OUTPUT);
    pinMode(p_STB, OUTPUT);
    pinMode(p_OE, OUTPUT);

    digitalWrite(p_OE, HIGH);
    digitalWrite(p_STB, LOW);

    spi->begin();
    spi->beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
}

void LEDMatrix::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    // convert RGB565 to RGB888
    // taken from PxMatrix
    uint8_t r = ((((color >> 11) & 0x1F) * 527) + 23) >> 6;
    uint8_t g = ((((color >> 5) & 0x3F) * 259) + 33) >> 6;
    uint8_t b = (((color & 0x1F) * 527) + 23) >> 6;

    drawPixel(x, y, r, g, b);
}

void LEDMatrix::drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue)
{
    if (x < 0 || x >= 64 || y < 0 || y >= 32)
        return;
    
    if (gamma_correction)
    {
        red = gamma_correction_values[red];
        green = gamma_correction_values[green];
        blue = gamma_correction_values[blue];
    }
    
    // we have to flip the x axis around
    x = 63 - x;

    // one of the 16 groups of 2 rows
    int group = y;
    // which of the two rows of the group; reversed because the way we send bytes is FIFO
    int row = 1;
    // byte of the row to which the led belongs; also reversed
    int byte = 7 - x/8;
    // bit position in byte; no need to reverse because SPI is configured we send MSBFIRST
    int bit = x%8;
    if (y >= 16)
    {
        group -= 16;
        row = 0;
    }

    // we have 4 color buffers, so only 4 bit color precision
    red >>= 4;
    green >>= 4;
    blue >>= 4;

    // fill each color buffer
    for (int i = 0; i < 4; i++)
    {
        // order of colors in matrix is reversed (blue, green, red)
        if ((red >> i) & 0x1)
            canvas[i][group][2][row][byte] |= (1 << bit);
        else
            canvas[i][group][2][row][byte] &= ~(1 << bit);

        if ((green >> i) & 0x1)
            canvas[i][group][1][row][byte] |= (1 << bit);
        else
            canvas[i][group][1][row][byte] &= ~(1 << bit);

        if ((blue >> i) & 0x1)
            canvas[i][group][0][row][byte] |= (1 << bit);
        else
            canvas[i][group][0][row][byte] &= ~(1 << bit);
    }
}


void LEDMatrix::display(unsigned int show_time)
{
    // buffer 0 will be displayed for show_time milliseconds
    // buffer 1 will be displayed twice as long, buffer 2 twice as long as buffer 1 and so on
    show_time *= (1 << current_buffer);

    // we need to copy the canvas because the function spi->transfer overwrites the buffer with what it reads from SPI
    uint8_t copy[16][3][2][8];
    memcpy(copy, canvas[current_buffer], 16*3*2*8);
    for (uint8_t i = 0; i < 16; i++)
    {
        setMultiplexer(i);
        
        // order of data in matrix: row 2 blue, row 1 blue, row 2 green, row 1 green, row 2 red, row 1 red
        // because of the shift registers, the data will be stored by the display in reverse order:
        // row 1 red, row 2 red, row 1 green, row 2 green, row 1 blue, row 2 blue; which is what we want
        spi->transfer(copy[i], 3*2*8);

        latch();
        output(show_time);
    }

    current_buffer++;
    if (current_buffer >= 4)
        current_buffer = 0;
}

void LEDMatrix::clearDisplay()
{
    memset(canvas, 0, sizeof(canvas));
}

inline void LEDMatrix::latch()
{
    digitalWrite(p_STB, HIGH);
    digitalWrite(p_STB, LOW);
}

inline void LEDMatrix::output(unsigned int show_time)
{
    digitalWrite(p_OE, LOW);
    // delayMicroseconds(show_time);
    busy_wait_us(show_time);
    digitalWrite(p_OE, HIGH);
}

inline void LEDMatrix::setMultiplexer(uint8_t row)
{
    bool a = row % 2;
    row /= 2;
    bool b = row % 2;
    row /= 2;
    bool c = row % 2;
    row /= 2;
    bool d = row % 2;

    digitalWrite(p_A, a);
    digitalWrite(p_B, b);
    digitalWrite(p_C, c);
    digitalWrite(p_D, d);
}

void LEDMatrix::setGammaCorrection(bool b)
{
    gamma_correction = b;
}