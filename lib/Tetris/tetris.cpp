#include <algorithm>
#include "tetris.h"

Tetris::Tetris(Adafruit_GFX *display)
{
    this->display = display;
    this->scale = 1;
    clear();
}

void Tetris::clear()
{
    for (int i = 0; i < TETRIS_MAX_CHARS; i++)
    {
        states[i] = {TETRIS_EMPTY_CHAR, 0, 0, 0};
    }
}

void Tetris::test()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            drawShape((blocktype_t) i, 0xffff, 10+5*i, 10+5*j, j);
        }
    }
}

bool Tetris::draw()
{
    bool finishedAnimating = true;
    for (int i = 0; i < TETRIS_MAX_CHARS && states[i].c != TETRIS_EMPTY_CHAR; i++)
    {
        if (states[i].fallingBlockIndex < TetrisCharacters::getBlocksPerCharacter(states[i].c))
        {
            finishedAnimating = false;
            fall_instruction_t instruction = TetrisCharacters::getFallInstruction(states[i].c, states[i].fallingBlockIndex);
            int rotation = computeRotation(instruction.rotation, states[i].fallingYOffset);

            drawShape(instruction.blocktype, states[i].colors[instruction.color], states[i].xPos + instruction.xPos * scale,
                states[i].finalYPos - states[i].fallingYOffset * scale + (instruction.yPos - 16) * scale, rotation);

            states[i].fallingYOffset--;
            if (states[i].fallingYOffset < 0)
            {
                states[i].fallingYOffset = TETRIS_FALLING_Y_POS;
                states[i].fallingBlockIndex++;
            }
        }

        // draw the static blocks
        for (int j = 0; j < states[i].fallingBlockIndex; j++)
        {
            fall_instruction_t instruction = TetrisCharacters::getFallInstruction(states[i].c, j);
            drawShape(instruction.blocktype, states[i].colors[instruction.color], states[i].xPos + instruction.xPos * scale, 
                states[i].finalYPos + (instruction.yPos - 16) * scale, instruction.rotation);
        }
    }
    return finishedAnimating;
}

bool Tetris::drawTime(bool displayColon)
{
    bool finishedAnimating = true;
    // HH:MM so 5 characters
    for (int i = 0; i < 5; i++)
    {
        // colon is on position 2
        if (i == 2)
        {
            if (!displayColon)
                continue;
            for (int j = 0; j < TetrisCharacters::getBlocksPerCharacter(states[i].c); j++)
            {
                fall_instruction_t instruction = TetrisCharacters::getFallInstruction(states[i].c, j);
                drawShape(instruction.blocktype, states[i].colors[instruction.color], states[i].xPos + instruction.xPos * scale, 
                    states[i].finalYPos + (instruction.yPos - 16) * scale, instruction.rotation);
            }
            continue;
        }

        if (states[i].fallingBlockIndex < TetrisCharacters::getBlocksPerCharacter(states[i].c))
        {
            finishedAnimating = false;
            fall_instruction_t instruction = TetrisCharacters::getFallInstruction(states[i].c, states[i].fallingBlockIndex);
            int rotation = computeRotation(instruction.rotation, states[i].fallingYOffset);

            drawShape(instruction.blocktype, states[i].colors[instruction.color], states[i].xPos + instruction.xPos * scale,
                states[i].finalYPos - states[i].fallingYOffset * scale + (instruction.yPos - 16) * scale, rotation);

            states[i].fallingYOffset--;
            if (states[i].fallingYOffset < 0)
            {
                states[i].fallingYOffset = TETRIS_FALLING_Y_POS;
                states[i].fallingBlockIndex++;
            }
        }

        // draw the static blocks
        for (int j = 0; j < states[i].fallingBlockIndex; j++)
        {
            fall_instruction_t instruction = TetrisCharacters::getFallInstruction(states[i].c, j);
            drawShape(instruction.blocktype, states[i].colors[instruction.color], states[i].xPos + instruction.xPos * scale, 
                states[i].finalYPos + (instruction.yPos - 16) * scale, instruction.rotation);
        }
    }
    return finishedAnimating;
}

// if displayColon is true, will draw the colon with white, otherwise it will draw it with black (so that it isn't visible)
void Tetris::drawColon(bool displayColon)
{
    uint16_t color = displayColon ? 0xffff : 0x0000;
    // colon is in position 2
    for (int j = 0; j < TetrisCharacters::getBlocksPerCharacter(states[2].c); j++)
    {
        fall_instruction_t instruction = TetrisCharacters::getFallInstruction(states[2].c, j);
        drawShape(instruction.blocktype, color, states[2].xPos + instruction.xPos * scale, 
            states[2].finalYPos + (instruction.yPos - 16) * scale, instruction.rotation);
    }
}

int Tetris::computeRotation(int finalRotation, int fallingYOffset)
{
    switch (finalRotation)
    {
    case 1:
        if (fallingYOffset >= TETRIS_FALLING_Y_POS / 2)
            return 0;
        return 1;
    case 2:
        if (fallingYOffset >= TETRIS_FALLING_Y_POS * 2 / 3)
            return 0;
        if (fallingYOffset >= TETRIS_FALLING_Y_POS / 3)
            return 1;
        return 2;
    case 3:
        if (fallingYOffset >= TETRIS_FALLING_Y_POS * 3 / 4)
            return 0;
        if (fallingYOffset >= TETRIS_FALLING_Y_POS * 2 / 4)
            return 1;
        if (fallingYOffset >= TETRIS_FALLING_Y_POS / 4)
            return 2;
        return 3;
    default:
        return 0;
    }
}

void Tetris::setText(const char *text, int len, int x, int y, bool forceRefresh)
{
    char buf[TETRIS_MAX_CHARS];
    if (len < TETRIS_MAX_CHARS)
    {
        memcpy(buf, text, len);
        memset(buf + len, TETRIS_EMPTY_CHAR, TETRIS_MAX_CHARS - len);
    }
    else
        memcpy(buf, text, TETRIS_MAX_CHARS);
    
    for (int i = 0; i < TETRIS_MAX_CHARS; i++)
    {
        if (!forceRefresh && states[i].c == text[i])
            continue;

        states[i] = {
            text[i], /* character */
            0, /* falling block index */
            x + i * TETRIS_SPACE_BETWEEN_CHARACTERS * scale, /* xPos */
            y, /* finalYPos */
            TETRIS_FALLING_Y_POS /* fallingYOffset */
        };
        randomizeColors(states[i].colors);
    }
}

// time must be of the format "HH:MM"
void Tetris::setTimeString(const char *time, int x, int y, bool forceRefresh)
{
    char buf[TETRIS_MAX_CHARS];
    buf[0] = time[0] - '0';
    buf[1] = time[1] - '0';
    buf[2] = 10; // colon
    buf[3] = time[3] - '0';
    buf[4] = time[4] - '0';
    memset(buf + 5, TETRIS_EMPTY_CHAR, TETRIS_MAX_CHARS - 5);
    
    for (int i = 0; i < TETRIS_MAX_CHARS; i++)
    {
        if (!forceRefresh && states[i].c == buf[i])
            continue;

        int xPos;
        if (i < 3)
            xPos = x + i * TETRIS_SPACE_BETWEEN_CHARACTERS * scale;
        else
            xPos = x + (i-1) * TETRIS_SPACE_BETWEEN_CHARACTERS * scale + 3 * scale;
        
        states[i] = {
            buf[i],
            0,
            xPos,
            y,
            TETRIS_FALLING_Y_POS
        };
        if (i == 2)
            memcpy(states[i].colors, tetrisColors, sizeof(tetrisColors));
        else
            randomizeColors(states[i].colors);
    }
}

// draws rectangle with bottom-left corner at (x, y) with sides of length scale
void Tetris::drawScaledPixel(int16_t x, int16_t y, uint16_t color)
{
    display->fillRect(x, y - scale + 1, scale, scale, color);
}

void Tetris::drawShape(blocktype_t block, uint16_t color, int xPos, int yPos, int rotation)
{
    // pointer to bool[rows][cols]
    bool *shape = nullptr;
    int rows = 0, cols = 0;
    TetrisCharacters::getShape(block, &shape, &rows, &cols);

    rotation %= 4;
    if (rotation == 0)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (shape[cols * i + j])
                    drawScaledPixel(xPos + j * scale, yPos + (-rows + i + 1) * scale, color);
            }
        }
    }
    else if (rotation == 1)
    {
        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                if (shape[cols * (rows - j - 1) + i])
                    drawScaledPixel(xPos + j * scale, yPos + (-cols + i + 1) * scale, color);
            }
        }
    }
    else if (rotation == 2)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (shape[cols * (rows - i - 1) + (cols - j - 1)])
                    drawScaledPixel(xPos + j * scale, yPos + (-rows + i + 1) * scale, color);
            }
        }
    }
    else if (rotation == 3)
    {
        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                if (shape[cols * j + (cols - i - 1)])
                    drawScaledPixel(xPos + j * scale, yPos + (-cols + i + 1) * scale, color);
            }
        }
    }
}

void Tetris::setScale(uint8_t s)
{
    scale = s;
}

void Tetris::randomizeColors(uint16_t *colors)
{
    memcpy(colors, tetrisColors, sizeof(tetrisColors));
    std::random_shuffle(&colors[0], &colors[8], [](int i) { return rand() % i; });
}

const uint16_t Tetris::tetrisColors[8] = {tetrisRED, tetrisGREEN, tetrisBLUE, tetrisWHITE, tetrisYELLOW, tetrisCYAN, tetrisMAGENTA, tetrisORANGE};
