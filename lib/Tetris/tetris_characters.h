#ifndef TETRIS_CHARACTERS_h
#define TETRIS_CHARACTERS_h

#include <Arduino.h>

enum struct blocktype_t
{
    Square = 0,
    L = 1,
    LReverse = 2,
    I = 3,
    S = 4,
    SReverse = 5,
    HalfCross = 6,
    Corner = 7,
};

struct fall_instruction_t
{
    blocktype_t blocktype;
    uint8_t color;
    int xPos;
    int yPos; // number from 1 to 16, 16 is the lowest row of the character
    int rotation; // number of 90 degree clockwise rotations
};

class TetrisCharacters
{
public:
    static void getShape(blocktype_t block, bool **shape, int *rows, int *cols);
    static fall_instruction_t getFallInstruction(char c, int blockindex);
    static int getBlocksPerCharacter(char c);
    
private:

    const static bool shapeSquare[2][2];
    const static bool shapeL[3][2];
    const static bool shapeLReverse[3][2];
    const static bool shapeI[1][4];
    const static bool shapeS[3][2];
    const static bool shapeSReverse[3][2];
    const static bool shapeHalfCross[2][3];
    const static bool shapeCorner[2][2];

    const static fall_instruction_t time_colon[2];

    const static fall_instruction_t num_0[12];
    const static fall_instruction_t num_1[5];
    const static fall_instruction_t num_2[11];
    const static fall_instruction_t num_3[11];
    const static fall_instruction_t num_4[9];
    const static fall_instruction_t num_5[11];
    const static fall_instruction_t num_6[12];
    const static fall_instruction_t num_7[7];
    const static fall_instruction_t num_8[13];
    const static fall_instruction_t num_9[12];

    const static int blocksPerNumber[10];
    
    const static fall_instruction_t a33[5];
    const static fall_instruction_t a34[4];
    const static fall_instruction_t a35[9];
    const static fall_instruction_t a36[8];
    const static fall_instruction_t a37[7];
    const static fall_instruction_t a38[8];
    const static fall_instruction_t a39[2];
    const static fall_instruction_t a40[4];
    const static fall_instruction_t a41[4];
    const static fall_instruction_t a42[6];
    const static fall_instruction_t a43[5];
    const static fall_instruction_t a44[2];
    const static fall_instruction_t a45[3];
    const static fall_instruction_t a46[1];
    const static fall_instruction_t a47[5];
    const static fall_instruction_t a48[10];
    const static fall_instruction_t a49[8];
    const static fall_instruction_t a50[9];
    const static fall_instruction_t a51[9];
    const static fall_instruction_t a52[8];
    const static fall_instruction_t a53[10];
    const static fall_instruction_t a54[10];
    const static fall_instruction_t a55[6];
    const static fall_instruction_t a56[8];
    const static fall_instruction_t a57[7];
    const static fall_instruction_t a58[2];
    const static fall_instruction_t a59[3];
    const static fall_instruction_t a60[5];
    const static fall_instruction_t a61[4];
    const static fall_instruction_t a62[5];
    const static fall_instruction_t a63[6];
    const static fall_instruction_t a64[8];
    const static fall_instruction_t a65[9];
    const static fall_instruction_t a66[9];
    const static fall_instruction_t a67[8];
    const static fall_instruction_t a68[9];
    const static fall_instruction_t a69[9];
    const static fall_instruction_t a70[7];
    const static fall_instruction_t a71[8];
    const static fall_instruction_t a72[9];
    const static fall_instruction_t a73[8];
    const static fall_instruction_t a74[7];
    const static fall_instruction_t a75[9];
    const static fall_instruction_t a76[6];
    const static fall_instruction_t a77[9];
    const static fall_instruction_t a78[9];
    const static fall_instruction_t a79[9];
    const static fall_instruction_t a80[8];
    const static fall_instruction_t a81[9];
    const static fall_instruction_t a82[9];
    const static fall_instruction_t a83[9];
    const static fall_instruction_t a84[6];
    const static fall_instruction_t a85[9];
    const static fall_instruction_t a86[10];
    const static fall_instruction_t a87[8];
    const static fall_instruction_t a88[7];
    const static fall_instruction_t a89[7];
    const static fall_instruction_t a90[9];

    const static int blocksPerChar[64];
};
#endif
