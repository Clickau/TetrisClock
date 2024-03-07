#include "tetris_characters.h"

void TetrisCharacters::getShape(blocktype_t block, bool **shape, int *rows, int *cols)
{
    switch (block)
    {
    case blocktype_t::Square:
        *shape = (bool *)shapeSquare;
        *rows = 2;
        *cols = 2;
        break;
    case blocktype_t::L:
        *shape = (bool *)shapeL;
        *rows = 3;
        *cols = 2;
        break;
    case blocktype_t::LReverse:
        *shape = (bool *)shapeLReverse;
        *rows = 3;
        *cols = 2;
        break;
    case blocktype_t::I:
        *shape = (bool *)shapeI;
        *rows = 1;
        *cols = 4;
        break;
    case blocktype_t::S:
        *shape = (bool *)shapeS;
        *rows = 3;
        *cols = 2;
        break;
    case blocktype_t::SReverse:
        *shape = (bool *)shapeSReverse;
        *rows = 3;
        *cols = 2;
        break;
    case blocktype_t::HalfCross:
        *shape = (bool *)shapeHalfCross;
        *rows = 2;
        *cols = 3;
        break;
    case blocktype_t::Corner:
        *shape = (bool *)shapeCorner;
        *rows = 2;
        *cols = 2;
        break;
    }
}

fall_instruction_t TetrisCharacters::getFallInstruction(char c, int blockindex)
{
    switch (c) {
    case 0:
        return num_0[blockindex];
    case 1:
        return num_1[blockindex];
    case 2:
        return num_2[blockindex];
    case 3:
        return num_3[blockindex];
    case 4:
        return num_4[blockindex];
    case 5:
        return num_5[blockindex];
    case 6:
        return num_6[blockindex];
    case 7:
        return num_7[blockindex];
    case 8:
        return num_8[blockindex];
    case 9:
        return num_9[blockindex];
    case 10:
        return time_colon[blockindex];
    case 33:
        return a33[blockindex];
    case 34:
        return a34[blockindex];
    case 35:
        return a35[blockindex];
    case 36:
        return a36[blockindex];
    case 37:
        return a37[blockindex];
    case 38:
        return a38[blockindex];
    case 39:
        return a39[blockindex];
    case 40:
        return a40[blockindex];
    case 41:
        return a41[blockindex];
    case 42:
        return a42[blockindex];
    case 43:
        return a43[blockindex];
    case 44:
        return a44[blockindex];
    case 45:
        return a45[blockindex];
    case 46:
        return a46[blockindex];
    case 47:
        return a47[blockindex];
    case 48:
        return a48[blockindex];
    case 49:
        return a49[blockindex];
        break;
    case 50:
        return a50[blockindex];
    case 51:
        return a51[blockindex];
    case 52:
        return a52[blockindex];
    case 53:
        return a53[blockindex];
    case 54:
        return a54[blockindex];
    case 55:
        return a55[blockindex];
    case 56:
        return a56[blockindex];
    case 57:
        return a57[blockindex];
    case 58:
        return a58[blockindex];
    case 59:
        return a59[blockindex];
    case 60:
        return a60[blockindex];
    case 61:
        return a61[blockindex];
    case 62:
        return a62[blockindex];
    case 63:
        return a63[blockindex];
    case 64:
        return a64[blockindex];
    case 65:
        return a65[blockindex];
    case 66:
        return a66[blockindex];
    case 67:
        return a67[blockindex];
    case 68:
        return a68[blockindex];
    case 69:
        return a69[blockindex];
    case 70:
        return a70[blockindex];
    case 71:
        return a71[blockindex];
    case 72:
        return a72[blockindex];
    case 73:
        return a73[blockindex];
    case 74:
        return a74[blockindex];
    case 75:
        return a75[blockindex];
    case 76:
        return a76[blockindex];
    case 77:
        return a77[blockindex];
    case 78:
        return a78[blockindex];
    case 79:
        return a79[blockindex];
    case 80:
        return a80[blockindex];
        break;
    case 81:
        return a81[blockindex];
    case 82:
        return a82[blockindex];
    case 83:
        return a83[blockindex];
    case 84:
        return a84[blockindex];
    case 85:
        return a85[blockindex];
        break;
    case 86:
        return a86[blockindex];
    case 87:
        return a87[blockindex];
    case 88:
        return a88[blockindex];
    case 89:
        return a89[blockindex];
    case 90:
        return a90[blockindex];
    default:
        return {};
    }
}

int TetrisCharacters::getBlocksPerCharacter(char c)
{
    if (c <= 9)
        return blocksPerNumber[(int)c];
    if (c == 10)
        return 2;
    return blocksPerChar[c - 33];
}

const bool TetrisCharacters::shapeSquare[2][2] = {
    1, 1,
    1, 1,
};

const bool TetrisCharacters::shapeL[3][2] = {
    1, 0,
    1, 0,
    1, 1,
};

const bool TetrisCharacters::shapeLReverse[3][2] = {
    0, 1,
    0, 1,
    1, 1,
};

const bool TetrisCharacters::shapeI[1][4] = {
    1, 1, 1, 1,
};

const bool TetrisCharacters::shapeS[3][2] = {
    1, 0,
    1, 1,
    0, 1,
};

const bool TetrisCharacters::shapeSReverse[3][2] = {
    0, 1,
    1, 1,
    1, 0,
};

const bool TetrisCharacters::shapeHalfCross[2][3] = {
    0, 1, 0,
    1, 1, 1,
};

const bool TetrisCharacters::shapeCorner[2][2] = {
    1, 0,
    1, 1,
};

// *********************************************************************
// Colon for the time
// *********************************************************************
const fall_instruction_t TetrisCharacters::time_colon[2] = {
    {blocktype_t::Square, 3, 0, 14, 0},
    {blocktype_t::Square, 3, 0, 10, 0}
};

// *********************************************************************
// Number 0
// *********************************************************************
#define SIZE_NUM_0 12
const fall_instruction_t TetrisCharacters::num_0[SIZE_NUM_0] = {
    {(blocktype_t)2, 5, 4, 16, 0},
    {(blocktype_t)4, 7, 2, 16, 1},
    {(blocktype_t)3, 4, 0, 16, 1},
    {(blocktype_t)6, 6, 1, 16, 1},
    {(blocktype_t)5, 1, 4, 14, 0},
    {(blocktype_t)6, 6, 0, 13, 3},
    {(blocktype_t)5, 1, 4, 12, 0},
    {(blocktype_t)5, 1, 0, 11, 0},
    {(blocktype_t)6, 6, 4, 10, 1},
    {(blocktype_t)6, 6, 0, 9, 1},
    {(blocktype_t)5, 1, 1, 8, 1},
    {(blocktype_t)2, 5, 3, 8, 3}};

// *********************************************************************
// Number 1
// *********************************************************************
#define SIZE_NUM_1 5
const fall_instruction_t TetrisCharacters::num_1[SIZE_NUM_1] = {
    {(blocktype_t)2, 5, 4, 16, 0},
    {(blocktype_t)3, 4, 4, 15, 1},
    {(blocktype_t)3, 4, 5, 13, 3},
    {(blocktype_t)2, 5, 4, 11, 2},
    {(blocktype_t)0, 0, 4, 8, 0}};

// *********************************************************************
// Number 2
// *********************************************************************
#define SIZE_NUM_2 11
const fall_instruction_t TetrisCharacters::num_2[SIZE_NUM_2] = {
    {(blocktype_t)0, 0, 4, 16, 0},
    {(blocktype_t)3, 4, 0, 16, 1},
    {(blocktype_t)1, 2, 1, 16, 3},
    {(blocktype_t)1, 2, 1, 15, 0},
    {(blocktype_t)3, 4, 1, 12, 2},
    {(blocktype_t)1, 2, 0, 12, 1},
    {(blocktype_t)2, 5, 3, 12, 3},
    {(blocktype_t)0, 0, 4, 10, 0},
    {(blocktype_t)3, 4, 1, 8, 0},
    {(blocktype_t)2, 5, 3, 8, 3},
    {(blocktype_t)1, 2, 0, 8, 1}};

// *********************************************************************
// Number 3
// *********************************************************************
#define SIZE_NUM_3 11
const fall_instruction_t TetrisCharacters::num_3[SIZE_NUM_3] = {
    {(blocktype_t)1, 2, 3, 16, 3},
    {(blocktype_t)2, 5, 0, 16, 1},
    {(blocktype_t)3, 4, 1, 15, 2},
    {(blocktype_t)0, 0, 4, 14, 0},
    {(blocktype_t)3, 4, 1, 12, 2},
    {(blocktype_t)1, 2, 0, 12, 1},
    {(blocktype_t)3, 4, 5, 12, 3},
    {(blocktype_t)2, 5, 3, 11, 0},
    {(blocktype_t)3, 4, 1, 8, 0},
    {(blocktype_t)1, 2, 0, 8, 1},
    {(blocktype_t)2, 5, 3, 8, 3}};

// *********************************************************************
// Number 4
// *********************************************************************
#define SIZE_NUM_4 9
const fall_instruction_t TetrisCharacters::num_4[SIZE_NUM_4] = {
    {(blocktype_t)0, 0, 4, 16, 0},
    {(blocktype_t)0, 0, 4, 14, 0},
    {(blocktype_t)3, 4, 1, 12, 0},
    {(blocktype_t)1, 2, 0, 12, 1},
    {(blocktype_t)2, 5, 0, 10, 0},
    {(blocktype_t)2, 5, 3, 12, 3},
    {(blocktype_t)3, 4, 4, 10, 3},
    {(blocktype_t)2, 5, 0, 9, 2},
    {(blocktype_t)3, 4, 5, 10, 1}};

// *********************************************************************
// Number 5
// *********************************************************************
#define SIZE_NUM_5 11
const fall_instruction_t TetrisCharacters::num_5[SIZE_NUM_5] = {
    {(blocktype_t)0, 0, 0, 16, 0},
    {(blocktype_t)2, 5, 2, 16, 1},
    {(blocktype_t)2, 5, 3, 15, 0},
    {(blocktype_t)3, 4, 5, 16, 1},
    {(blocktype_t)3, 4, 1, 12, 0},
    {(blocktype_t)1, 2, 0, 12, 1},
    {(blocktype_t)2, 5, 3, 12, 3},
    {(blocktype_t)0, 0, 0, 10, 0},
    {(blocktype_t)3, 4, 1, 8, 2},
    {(blocktype_t)1, 2, 0, 8, 1},
    {(blocktype_t)2, 5, 3, 8, 3}};

// *********************************************************************
// Number 6
// *********************************************************************
#define SIZE_NUM_6 12
const fall_instruction_t TetrisCharacters::num_6[SIZE_NUM_6] = {
    {(blocktype_t)2, 5, 0, 16, 1},
    {(blocktype_t)5, 1, 2, 16, 1},
    {(blocktype_t)6, 6, 0, 15, 3},
    {(blocktype_t)6, 6, 4, 16, 3},
    {(blocktype_t)5, 1, 4, 14, 0},
    {(blocktype_t)3, 4, 1, 12, 2},
    {(blocktype_t)2, 5, 0, 13, 2},
    {(blocktype_t)3, 4, 2, 11, 0},
    {(blocktype_t)0, 0, 0, 10, 0},
    {(blocktype_t)3, 4, 1, 8, 0},
    {(blocktype_t)1, 2, 0, 8, 1},
    {(blocktype_t)2, 5, 3, 8, 3}};

// *********************************************************************
// Number 7
// *********************************************************************
#define SIZE_NUM_7 7
const fall_instruction_t TetrisCharacters::num_7[SIZE_NUM_7] = {
    {(blocktype_t)0, 0, 4, 16, 0},
    {(blocktype_t)1, 2, 4, 14, 0},
    {(blocktype_t)3, 4, 5, 13, 1},
    {(blocktype_t)2, 5, 4, 11, 2},
    {(blocktype_t)3, 4, 1, 8, 2},
    {(blocktype_t)2, 5, 3, 8, 3},
    {(blocktype_t)1, 2, 0, 8, 1}};

// *********************************************************************
// Number 8
// *********************************************************************
#define SIZE_NUM_8 13
const fall_instruction_t TetrisCharacters::num_8[SIZE_NUM_8] = {
    {(blocktype_t)3, 4, 1, 16, 0},
    {(blocktype_t)6, 6, 0, 16, 1},
    {(blocktype_t)3, 4, 5, 16, 1},
    {(blocktype_t)1, 2, 2, 15, 3},
    {(blocktype_t)4, 7, 0, 14, 0},
    {(blocktype_t)1, 2, 1, 12, 3},
    {(blocktype_t)6, 6, 4, 13, 1},
    {(blocktype_t)2, 5, 0, 11, 1},
    {(blocktype_t)4, 7, 0, 10, 0},
    {(blocktype_t)4, 7, 4, 11, 0},
    {(blocktype_t)5, 1, 0, 8, 1},
    {(blocktype_t)5, 1, 2, 8, 1},
    {(blocktype_t)1, 2, 4, 9, 2}};

// *********************************************************************
// Number 9
// *********************************************************************
#define SIZE_NUM_9 12
const fall_instruction_t TetrisCharacters::num_9[SIZE_NUM_9] = {
    {(blocktype_t)0, 0, 0, 16, 0},
    {(blocktype_t)3, 4, 2, 16, 0},
    {(blocktype_t)1, 2, 2, 15, 3},
    {(blocktype_t)1, 2, 4, 15, 2},
    {(blocktype_t)3, 4, 1, 12, 2},
    {(blocktype_t)3, 4, 5, 12, 3},
    {(blocktype_t)5, 1, 0, 12, 0},
    {(blocktype_t)1, 2, 2, 11, 3},
    {(blocktype_t)5, 1, 4, 9, 0},
    {(blocktype_t)6, 6, 0, 10, 1},
    {(blocktype_t)5, 1, 0, 8, 1},
    {(blocktype_t)6, 6, 2, 8, 2}};

const int TetrisCharacters::blocksPerNumber[10] = {SIZE_NUM_0, SIZE_NUM_1, SIZE_NUM_2, SIZE_NUM_3, SIZE_NUM_4, SIZE_NUM_5, SIZE_NUM_6, SIZE_NUM_7, SIZE_NUM_8, SIZE_NUM_9};

//
// ASCII characters
//

// *********************************************************************
// ascii 33 - !
// *********************************************************************

const fall_instruction_t TetrisCharacters::a33[5] = {
    {(blocktype_t)0,0,2,16,0},
    {(blocktype_t)2,5,3,13,2},
    {(blocktype_t)1,3,1,13,2},
    {(blocktype_t)7,1,1,10,3},
    {(blocktype_t)7,6,3,10,0}
};

// *********************************************************************
// ascii 34 - "
// *********************************************************************

const fall_instruction_t TetrisCharacters::a34[4] = {
    {(blocktype_t)7,0,1,11,3},
    {(blocktype_t)7,1,4,11,3},
    {(blocktype_t)7,2,1,10,1},
    {(blocktype_t)7,5,4,10,1}
};

// *********************************************************************
// ascii 35 - #
// *********************************************************************

const fall_instruction_t TetrisCharacters::a35[9] = {
    {(blocktype_t)7,0,0,16,2},
    {(blocktype_t)7,5,4,16,1},
    {(blocktype_t)0,6,2,15,0},
    {(blocktype_t)7,3,0,14,2},
    {(blocktype_t)7,1,4,14,1},
    {(blocktype_t)6,3,0,12,2},
    {(blocktype_t)6,4,3,12,2},
    {(blocktype_t)6,6,0,10,0},
    {(blocktype_t)6,7,3,10,0}
};

// *********************************************************************
// ascii 36 - $
// *********************************************************************

const fall_instruction_t TetrisCharacters::a36[8] = {
    {(blocktype_t)2,2,0,16,3},
    {(blocktype_t)7,0,3,16,1},
    {(blocktype_t)7,3,4,14,3},
    {(blocktype_t)1,6,2,13,3},
    {(blocktype_t)1,7,1,13,1},
    {(blocktype_t)7,3,0,12,1},
    {(blocktype_t)7,1,1,10,3},
    {(blocktype_t)2,2,3,10,1}
};

// *********************************************************************
// ascii 37 - %
// *********************************************************************

const fall_instruction_t TetrisCharacters::a37[7] = {
    {(blocktype_t)0,6,4,16,0},
    {(blocktype_t)7,1,0,16,3},
    {(blocktype_t)7,3,1,15,1},
    {(blocktype_t)0,0,2,13,0},
    {(blocktype_t)7,5,3,12,0},
    {(blocktype_t)7,7,4,10,1},
    {(blocktype_t)0,2,0,10,0}
};

// *********************************************************************
// ascii 38 - &
// *********************************************************************

const fall_instruction_t TetrisCharacters::a38[8] = {
    {(blocktype_t)2,1,1,16,1},
    {(blocktype_t)4,0,4,16,0},
    {(blocktype_t)5,4,0,15,0},
    {(blocktype_t)6,7,2,14,3},
    {(blocktype_t)7,6,1,12,0},
    {(blocktype_t)5,3,4,12,0},
    {(blocktype_t)5,1,0,11,0},
    {(blocktype_t)2,2,2,10,3}
};

// *********************************************************************
// ascii 39 - '
// *********************************************************************

const fall_instruction_t TetrisCharacters::a39[2] = {
    {(blocktype_t)7,3,2,10,1},
    {(blocktype_t)7,0,2,11,3}
};

// *********************************************************************
// ascii 40 - (
// *********************************************************************

const fall_instruction_t TetrisCharacters::a40[4] = {
    {(blocktype_t)5,0,1,16,1},
    {(blocktype_t)2,6,0,14,0},
    {(blocktype_t)2,3,0,13,2},
    {(blocktype_t)4,5,1,10,1}
};

// *********************************************************************
// ascii 41 - )
// *********************************************************************

const fall_instruction_t TetrisCharacters::a41[4] = {
    {(blocktype_t)4,6,2,16,1},
    {(blocktype_t)2,0,4,14,0},
    {(blocktype_t)2,3,4,13,2},
    {(blocktype_t)5,6,2,10,1}
};

// *********************************************************************
// ascii 42 - *
// *********************************************************************

const fall_instruction_t TetrisCharacters::a42[6] = {
    {(blocktype_t)4,6,0,14,1},
    {(blocktype_t)5,5,3,14,1},
    {(blocktype_t)0,2,1,12,0},
    {(blocktype_t)0,0,3,12,0},
    {(blocktype_t)2,1,3,10,1},
    {(blocktype_t)1,2,0,10,3}
};

// *********************************************************************
// ascii 43 - +
// *********************************************************************

const fall_instruction_t TetrisCharacters::a43[5] = {
    {(blocktype_t)2,1,2,15,0},
    {(blocktype_t)2,6,0,14,3},
    {(blocktype_t)0,3,4,13,0},
    {(blocktype_t)3,4,0,12,0},
    {(blocktype_t)0,2,2,11,0}
};

// *********************************************************************
// ascii 44 -,
// *********************************************************************

const fall_instruction_t TetrisCharacters::a44[2] = {
    {(blocktype_t)7,4,1,16,3},
    {(blocktype_t)7,0,2,15,2}
};

// *********************************************************************
// ascii 45 - - 
// *********************************************************************

const fall_instruction_t TetrisCharacters::a45[3] = {
    {(blocktype_t)3,1,1,13,0},
    {(blocktype_t)2,6,3,13,3},
    {(blocktype_t)1,0,0,13,1}
};


// *********************************************************************
// ascii 46 - .
// *********************************************************************

const fall_instruction_t TetrisCharacters::a46[1] = {
    {(blocktype_t)0,1,3,16,0}
};

// *********************************************************************
// ascii 47 - /
// *********************************************************************

const fall_instruction_t TetrisCharacters::a47[5] = {
    {(blocktype_t)4,6,0,16,1},
    {(blocktype_t)7,0,1,14,3},
    {(blocktype_t)7,3,2,13,2},
    {(blocktype_t)7,5,3,11,0},
    {(blocktype_t)7,7,4,10,1}
};

// *********************************************************************
// ascii 48 - 0
// *********************************************************************

const fall_instruction_t TetrisCharacters::a48[10] = {
    {(blocktype_t)7,0,2,16,3},
    {(blocktype_t)6,3,0,16,2},
    {(blocktype_t)7,4,4,16,1},
    {(blocktype_t)3,2,0,14,1},
    {(blocktype_t)6,5,1,14,1},
    {(blocktype_t)0,1,4,14,0},
    {(blocktype_t)1,3,3,12,3},
    {(blocktype_t)6,7,0,11,3},
    {(blocktype_t)0,2,2,10,0},
    {(blocktype_t)6,3,4,11,1}
};

// *********************************************************************
// ascii 49 - 1
// *********************************************************************

const fall_instruction_t TetrisCharacters::a49[8] = {
    {(blocktype_t)0,4,0,16,0},
    {(blocktype_t)1,2,2,16,1},
    {(blocktype_t)1,4,3,16,3},
    {(blocktype_t)7,3,2,14,3},
    {(blocktype_t)5,1,2,13,0},
    {(blocktype_t)6,6,0,11,0},
    {(blocktype_t)7,6,0,10,1},
    {(blocktype_t)0,0,2,10,0}
};

// *********************************************************************
// ascii 50 - 2
// *********************************************************************

const fall_instruction_t TetrisCharacters::a50[9] = {
    {(blocktype_t)7,4,0,16,2},
    {(blocktype_t)1,2,2,16,1},
    {(blocktype_t)1,6,3,16,3},
    {(blocktype_t)0,2,0,14,0},
    {(blocktype_t)1,3,2,13,3},
    {(blocktype_t)1,2,4,13,2},
    {(blocktype_t)6,6,3,10,0},
    {(blocktype_t)7,0,2,10,1},
    {(blocktype_t)0,6,0,10,0}
};

// *********************************************************************
// ascii 51 - 3
// *********************************************************************

const fall_instruction_t TetrisCharacters::a51[9] = {
    {(blocktype_t)1,2,1,16,3},
    {(blocktype_t)1,5,0,16,1},
    {(blocktype_t)5,4,4,16,0},
    {(blocktype_t)6,6,3,14,2},
    {(blocktype_t)0,2,1,13,0},
    {(blocktype_t)1,1,3,12,3},
    {(blocktype_t)6,5,4,11,1},
    {(blocktype_t)1,3,1,10,3},
    {(blocktype_t)1,3,0,10,1}
};

// *********************************************************************
// ascii 52 - 4
// *********************************************************************

const fall_instruction_t TetrisCharacters::a52[8] = {
    {(blocktype_t)2,1,4,16,0},
    {(blocktype_t)3,2,4,15,1},
    {(blocktype_t)3,3,5,13,3},
    {(blocktype_t)1,0,1,13,3},
    {(blocktype_t)1,5,0,13,1},
    {(blocktype_t)7,1,0,11,3},
    {(blocktype_t)7,3,0,10,1},
    {(blocktype_t)2,6,4,11,2}
};

// *********************************************************************
// ascii 53 - 5
// *********************************************************************

const fall_instruction_t TetrisCharacters::a53[10] = {
    {(blocktype_t)2,3,0,16,1},
    {(blocktype_t)2,4,1,16,3},
    {(blocktype_t)0,6,4,16,0},
    {(blocktype_t)0,7,4,14,0},
    {(blocktype_t)2,1,1,13,1},
    {(blocktype_t)2,5,0,13,2},
    {(blocktype_t)3,2,2,12,0},
    {(blocktype_t)1,4,0,10,1},
    {(blocktype_t)1,1,1,10,3},
    {(blocktype_t)0,0,4,10,0}
};

// *********************************************************************
// ascii 54 - 6
// *********************************************************************

const fall_instruction_t TetrisCharacters::a54[10] = {
    {(blocktype_t)4,4,1,16,1},
    {(blocktype_t)4,3,3,16,1},
    {(blocktype_t)2,3,0,15,0},
    {(blocktype_t)0,0,4,14,0},
    {(blocktype_t)3,3,0,14,1},
    {(blocktype_t)7,4,1,13,2},
    {(blocktype_t)7,2,3,13,1},
    {(blocktype_t)6,6,0,11,3},
    {(blocktype_t)6,6,3,10,0},
    {(blocktype_t)7,4,2,10,1}
};

// *********************************************************************
// ascii 55 - 7
// *********************************************************************

const fall_instruction_t TetrisCharacters::a55[6] = {
    {(blocktype_t)0,0,2,16,0},
    {(blocktype_t)0,5,3,14,0},
    {(blocktype_t)2,5,4,12,0},
    {(blocktype_t)2,6,2,11,3},
    {(blocktype_t)0,0,0,10,0},
    {(blocktype_t)3,1,2,9,0},
};

// *********************************************************************
// ascii 56 - 8
// *********************************************************************

const fall_instruction_t TetrisCharacters::a56[8] = {
    {(blocktype_t)5,1,0,16,1},
    {(blocktype_t)4,4,3,16,1},
    {(blocktype_t)2,2,0,14,0},
    {(blocktype_t)1,2,4,14,0},
    {(blocktype_t)0,5,2,13,0},
    {(blocktype_t)0,6,0,11,0},
    {(blocktype_t)0,0,4,11,0},
    {(blocktype_t)3,1,1,9,0}
};

// *********************************************************************
// ascii 57 - 9
// *********************************************************************

const fall_instruction_t TetrisCharacters::a57[7] = {
    {(blocktype_t)2,3,4,16,0},
    {(blocktype_t)2,2,4,15,2},
    {(blocktype_t)3,7,1,12,0},
    {(blocktype_t)6,6,4,12,3},
    {(blocktype_t)7,5,0,11,0},
    {(blocktype_t)7,4,4,10,1},
    {(blocktype_t)1,1,1,10,1}
};

// *********************************************************************
// ascii 58 - :
// *********************************************************************

const fall_instruction_t TetrisCharacters::a58[2] = {
    {(blocktype_t)0,1,2,15,0},
    {(blocktype_t)0,6,2,11,0}
};

// *********************************************************************
// ascii 59 - ;
// *********************************************************************

const fall_instruction_t TetrisCharacters::a59[3] = {
    {(blocktype_t)7,3,1,16,3},
    {(blocktype_t)7,4,2,15,2},
    {(blocktype_t)0,2,2,11,0}
};

// *********************************************************************
// ascii 60 - <
// *********************************************************************

const fall_instruction_t TetrisCharacters::a60[5] = {
    {(blocktype_t)7,6,3,16,0},
    {(blocktype_t)7,1,1,15,2},
    {(blocktype_t)0,3,0,13,0},
    {(blocktype_t)7,2,1,11,3},
    {(blocktype_t)7,4,3,10,1}
};


// *********************************************************************
// ascii 61 - =
// *********************************************************************

const fall_instruction_t TetrisCharacters::a61[4] = {
    {(blocktype_t)1,1,2,15,3},
    {(blocktype_t)1,2,1,15,1},
    {(blocktype_t)1,3,2,11,3},
    {(blocktype_t)1,5,1,11,1}
};


// *********************************************************************
// ascii 62 - >
// *********************************************************************

const fall_instruction_t TetrisCharacters::a62[5] = {
    {(blocktype_t)7,4,1,16,3},
    {(blocktype_t)7,2,3,15,1},
    {(blocktype_t)0,5,4,13,0},
    {(blocktype_t)7,3,3,11,0},
    {(blocktype_t)7,1,1,10,2}
};

// *********************************************************************
// ascii 63 - ?
// *********************************************************************

const fall_instruction_t TetrisCharacters::a63[6] = {
    {(blocktype_t)7,1,2,16,3},
    {(blocktype_t)4,3,2,14,1},
    {(blocktype_t)2,2,4,12,0},
    {(blocktype_t)2,6,2,11,3},
    {(blocktype_t)0,4,0,11,0},
    {(blocktype_t)3,5,1,9,0}
};


// *********************************************************************
// ascii 64 - @
// *********************************************************************

const fall_instruction_t TetrisCharacters::a64[8] = {
    {(blocktype_t)6,2,1,16,0},
    {(blocktype_t)6,1,3,16,2},
    {(blocktype_t)1,3,0,15,0},
    {(blocktype_t)1,4,2,13,1},
    {(blocktype_t)3,5,0,12,1},
    {(blocktype_t)7,6,1,10,1},
    {(blocktype_t)6,3,2,10,0},
    {(blocktype_t)1,2,4,12,2}
};


// *********************************************************************
// ascii 65 - A
// *********************************************************************

const fall_instruction_t TetrisCharacters::a65[9] = {
    {(blocktype_t)0,2,0,16,0},
    {(blocktype_t)0,1,4,16,0},
    {(blocktype_t)5,5,3,14,1},
    {(blocktype_t)4,2,0,14,1},
    {(blocktype_t)4,1,4,13,0},
    {(blocktype_t)5,0,0,13,0},
    {(blocktype_t)4,3,4,11,0},
    {(blocktype_t)5,2,0,11,0},
    {(blocktype_t)0,1,2,10,0}
};


// *********************************************************************
// ascii 66 - B
// *********************************************************************

const fall_instruction_t TetrisCharacters::a66[9] = {
    {(blocktype_t)2,7,0,16,0},
    {(blocktype_t)1,6,2,16,3},
    {(blocktype_t)4,3,4,15,0},
    {(blocktype_t)2,1,0,15,2},
    {(blocktype_t)2,4,0,13,3},
    {(blocktype_t)5,1,3,13,0},
    {(blocktype_t)0,7,0,11,0},
    {(blocktype_t)4,0,4,11,0},
    {(blocktype_t)3,3,0,9,0}
};


// *********************************************************************
// ascii 67 - C
// *********************************************************************

const fall_instruction_t TetrisCharacters::a67[8] = {
    {(blocktype_t)6,5,1,16,0},
    {(blocktype_t)6,3,3,16,2},
    {(blocktype_t)7,1,0,15,3},
    {(blocktype_t)5,7,0,14,0},
    {(blocktype_t)7,6,0,12,1},
    {(blocktype_t)6,3,0,10,0},
    {(blocktype_t)7,6,2,10,2},
    {(blocktype_t)7,7,4,10,0}
};

// *********************************************************************
// ascii 68 - D
// *********************************************************************

const fall_instruction_t TetrisCharacters::a68[9] = {
    {(blocktype_t)3,7,0,16,1},
    {(blocktype_t)0,2,1,16,0},
    {(blocktype_t)5,3,3,16,0},
    {(blocktype_t)6,5,4,14,3},
    {(blocktype_t)1,1,0,14,2},
    {(blocktype_t)6,2,4,12,1},
    {(blocktype_t)7,5,0,11,0},
    {(blocktype_t)7,3,2,10,3},
    {(blocktype_t)6,4,0,10,2}
};

// *********************************************************************
// ascii 69 - E
// *********************************************************************

const fall_instruction_t TetrisCharacters::a69[9] = {
    {(blocktype_t)0,6,4,16,0},
    {(blocktype_t)3,2,0,16,0},
    {(blocktype_t)3,3,0,15,0},
    {(blocktype_t)4,4,0,14,1},
    {(blocktype_t)2,1,1,13,3},
    {(blocktype_t)2,6,0,13,2},
    {(blocktype_t)3,0,0,10,0},
    {(blocktype_t)3,4,0,9,0},
    {(blocktype_t)0,2,4,10,0}
};


// *********************************************************************
// ascii 70 - F
// *********************************************************************

const fall_instruction_t TetrisCharacters::a70[7] = {
    {(blocktype_t)2,1,0,16,0},
    {(blocktype_t)3,2,0,15,1},
    {(blocktype_t)1,3,1,13,0},
    {(blocktype_t)5,4,2,13,1},
    {(blocktype_t)5,5,0,11,0},
    {(blocktype_t)0,6,2,10,2},
    {(blocktype_t)0,4,4,10,0}
};

// *********************************************************************
// ascii 71 - G
// *********************************************************************

const fall_instruction_t TetrisCharacters::a71[8] = {
    {(blocktype_t)6,7,1,16,0},
    {(blocktype_t)7,4,3,16,2},
    {(blocktype_t)4,2,4,15,0},
    {(blocktype_t)3,1,0,15,1},
    {(blocktype_t)3,0,1,15,1},
    {(blocktype_t)0,2,0,11,2},
    {(blocktype_t)6,6,3,10,0},
    {(blocktype_t)6,7,1,10,2}
};

// *********************************************************************
// ascii 72 - H
// *********************************************************************

const fall_instruction_t TetrisCharacters::a72[9] = {
    {(blocktype_t)0,6,0,16,0},
    {(blocktype_t)1,5,4,16,0},
    {(blocktype_t)1,2,0,14,0},
    {(blocktype_t)1,1,4,15,2},
    {(blocktype_t)3,7,1,13,1},
    {(blocktype_t)0,3,2,13,2},
    {(blocktype_t)3,4,4,12,1},
    {(blocktype_t)3,5,5,12,1},
    {(blocktype_t)2,1,0,11,2}
};

// *********************************************************************
// ascii 73 - I
// *********************************************************************

const fall_instruction_t TetrisCharacters::a73[8] = {
    {(blocktype_t)6,5,0,16,0},
    {(blocktype_t)4,1,2,16,0},
    {(blocktype_t)0,2,4,16,0},
    {(blocktype_t)4,7,2,14,0},
    {(blocktype_t)6,6,2,12,3},
    {(blocktype_t)0,2,4,10,0},
    {(blocktype_t)7,1,0,10,0},
    {(blocktype_t)6,3,1,10,2}
};

// *********************************************************************
// ascii 74 - J
// *********************************************************************

const fall_instruction_t TetrisCharacters::a74[7] = {
    {(blocktype_t)1,7,1,16,3},
    {(blocktype_t)6,2,0,16,1},
    {(blocktype_t)6,3,3,15,3},
    {(blocktype_t)6,4,3,13,1},
    {(blocktype_t)6,2,4,11,1},
    {(blocktype_t)0,6,2,10,0},
    {(blocktype_t)0,1,0,10,0}
};

// *********************************************************************
// ascii 75 - K
// *********************************************************************

const fall_instruction_t TetrisCharacters::a75[9] = {
    {(blocktype_t)0,2,4,16,0},
    {(blocktype_t)3,6,0,16,1},
    {(blocktype_t)2,2,1,16,2},
    {(blocktype_t)6,7,3,15,1},
    {(blocktype_t)0,5,1,13,0},
    {(blocktype_t)3,4,0,12,1},
    {(blocktype_t)1,2,1,11,0},
    {(blocktype_t)7,0,3,11,1},
    {(blocktype_t)7,1,4,10,2}
};

// *********************************************************************
// ascii 76 - L
// *********************************************************************

const fall_instruction_t TetrisCharacters::a76[6] = {
    {(blocktype_t)1,3,3,16,3},
    {(blocktype_t)1,1,2,16,1},
    {(blocktype_t)0,0,0,16,0},
    {(blocktype_t)2,4,0,14,0},
    {(blocktype_t)2,2,0,13,2},
    {(blocktype_t)0,6,0,10,0}
};

// *********************************************************************
// ascii 77 - M
// *********************************************************************

const fall_instruction_t TetrisCharacters::a77[9] = {
    {(blocktype_t)1,0,0,16,0},
    {(blocktype_t)2,1,4,16,0},
    {(blocktype_t)1,3,0,15,2},
    {(blocktype_t)2,3,4,15,2},
    {(blocktype_t)0,5,2,13,0},
    {(blocktype_t)4,6,0,12,1},
    {(blocktype_t)5,2,3,12,3},
    {(blocktype_t)6,2,4,11,3},
    {(blocktype_t)6,1,0,11,1}
};

// *********************************************************************
// ascii 78 - N
// *********************************************************************

const fall_instruction_t TetrisCharacters::a78[9] = {
    {(blocktype_t)1,6,0,16,0},
    {(blocktype_t)2,1,4,16,0},
    {(blocktype_t)1,3,0,15,2},
    {(blocktype_t)2,0,4,15,2},
    {(blocktype_t)4,4,2,13,0},
    {(blocktype_t)2,6,0,12,0},
    {(blocktype_t)1,1,4,12,0},
    {(blocktype_t)1,2,4,11,2},
    {(blocktype_t)2,4,0,11,2}
};


// *********************************************************************
// ascii 79 - O
// *********************************************************************

const fall_instruction_t TetrisCharacters::a79[9] = {
    {(blocktype_t)4,1,0,16,0},
    {(blocktype_t)5,0,4,16,0},
    {(blocktype_t)0,4,2,16,0},
    {(blocktype_t)6,4,0,14,3},
    {(blocktype_t)6,5,4,14,1},
    {(blocktype_t)6,6,0,12,1},
    {(blocktype_t)6,2,4,12,3},
    {(blocktype_t)0,1,3,10,0},
    {(blocktype_t)0,4,1,10,0}
};


// *********************************************************************
// ascii 80 - P
// *********************************************************************

const fall_instruction_t TetrisCharacters::a80[8] = {
    {(blocktype_t)0,6,0,16,0},
    {(blocktype_t)4,2,0,14,1},
    {(blocktype_t)5,4,2,13,3},
    {(blocktype_t)7,5,4,12,0},
    {(blocktype_t)6,0,0,13,1},
    {(blocktype_t)4,1,0,11,0},
    {(blocktype_t)7,2,4,11,2},
    {(blocktype_t)3,4,1,9,0}
};

// *********************************************************************
// ascii 81 - Q
// *********************************************************************

const fall_instruction_t TetrisCharacters::a81[9] = {
    {(blocktype_t)5,2,3,16,1},
    {(blocktype_t)4,0,1,15,1},
    {(blocktype_t)7,3,4,14,0},
    {(blocktype_t)0,5,0,14,0},
    {(blocktype_t)6,6,4,13,3},
    {(blocktype_t)0,3,0,12,0},
    {(blocktype_t)7,1,4,11,1},
    {(blocktype_t)6,2,0,10,0},
    {(blocktype_t)6,5,2,10,2}
};

// *********************************************************************
// ascii 82 - R
// *********************************************************************

const fall_instruction_t TetrisCharacters::a82[9] = {
    {(blocktype_t)0,2,4,16,0},
    {(blocktype_t)0,3,0,16,0},
    {(blocktype_t)2,1,4,14,2},
    {(blocktype_t)1,0,1,14,1},
    {(blocktype_t)2,6,0,14,2},
    {(blocktype_t)7,1,4,11,3},
    {(blocktype_t)7,0,0,11,3},
    {(blocktype_t)7,4,0,10,1},
    {(blocktype_t)2,5,2,10,3}
};

// *********************************************************************
// ascii 83 - S
// *********************************************************************

const fall_instruction_t TetrisCharacters::a83[9] = {
    {(blocktype_t)6,2,0,16,2},
    {(blocktype_t)6,7,2,16,0},
    {(blocktype_t)7,3,4,15,3},
    {(blocktype_t)0,5,3,14,0},
    {(blocktype_t)1,6,2,13,1},
    {(blocktype_t)6,0,0,13,3},
    {(blocktype_t)5,1,0,11,0},
    {(blocktype_t)0,1,2,10,0},
    {(blocktype_t)7,2,4,10,0}
};

// *********************************************************************
// ascii 84 - T
// *********************************************************************

const fall_instruction_t TetrisCharacters::a84[6] = {
    {(blocktype_t)0,3,2,16,0},
    {(blocktype_t)3,2,2,14,1},
    {(blocktype_t)3,1,3,14,1},
    {(blocktype_t)2,5,2,10,1},
    {(blocktype_t)2,6,3,10,3},
    {(blocktype_t)0,1,0,10,0}
};

// *********************************************************************
// ascii 85 - U
// *********************************************************************

const fall_instruction_t TetrisCharacters::a85[9] = {
    {(blocktype_t)6,1,4,16,1},
    {(blocktype_t)0,4,2,16,0},
    {(blocktype_t)6,3,0,16,3},
    {(blocktype_t)4,5,4,14,0},
    {(blocktype_t)5,6,0,14,0},
    {(blocktype_t)6,1,4,12,3},
    {(blocktype_t)6,0,0,12,1},
    {(blocktype_t)7,4,4,10,1},
    {(blocktype_t)7,5,0,10,2}
};

// *********************************************************************
// ascii 86 - V
// *********************************************************************

const fall_instruction_t TetrisCharacters::a86[10] = {
    {(blocktype_t)6,0,1,16,3},
    {(blocktype_t)7,1,3,16,1},
    {(blocktype_t)6,4,3,14,0},
    {(blocktype_t)1,0,1,14,1},
    {(blocktype_t)2,6,0,14,2},
    {(blocktype_t)7,1,4,13,2},
    {(blocktype_t)7,3,0,11,3},
    {(blocktype_t)7,4,4,11,0},
    {(blocktype_t)7,3,4,10,2},
    {(blocktype_t)7,5,0,10,1}
};


// *********************************************************************
// ascii 87 - W
// *********************************************************************

const fall_instruction_t TetrisCharacters::a87[8] = {
    {(blocktype_t)2,0,1,16,2},
    {(blocktype_t)1,1,3,16,2},
    {(blocktype_t)3,4,5,15,1},
    {(blocktype_t)3,3,0,15,1},
    {(blocktype_t)2,1,4,13,2},
    {(blocktype_t)1,2,0,13,2},
    {(blocktype_t)0,6,0,10,0},
    {(blocktype_t)0,4,4,10,0}
};


// *********************************************************************
// ascii 88 - X
// *********************************************************************

const fall_instruction_t TetrisCharacters::a88[7] = {
    {(blocktype_t)7,6,0,16,1},
    {(blocktype_t)7,7,4,16,2},
    {(blocktype_t)3,2,1,14,0},
    {(blocktype_t)0,5,2,13,0},
    {(blocktype_t)3,6,1,11,0},
    {(blocktype_t)7,3,4,10,3},
    {(blocktype_t)7,1,0,10,0}
};

// *********************************************************************
// ascii 89 - Y
// *********************************************************************

const fall_instruction_t TetrisCharacters::a89[7] = {
    {(blocktype_t)0,2,2,16,0},
    {(blocktype_t)1,7,2,14,0},
    {(blocktype_t)7,6,3,13,1},
    {(blocktype_t)6,5,3,11,0},
    {(blocktype_t)7,6,4,10,2},
    {(blocktype_t)6,2,1,12,1},
    {(blocktype_t)2,1,0,11,2}
};

// *********************************************************************
// ascii 90 - Z
// *********************************************************************

const fall_instruction_t TetrisCharacters::a90[9] = {
    {(blocktype_t)2,5,0,16,1},
    {(blocktype_t)1,3,3,16,3},
    {(blocktype_t)3,1,1,15,0},
    {(blocktype_t)0,0,2,14,0},
    {(blocktype_t)7,6,3,13,2},
    {(blocktype_t)1,1,4,11,2},
    {(blocktype_t)4,7,3,11,0},
    {(blocktype_t)7,6,1,10,3},
    {(blocktype_t)7,2,0,10,1}
};

// holds the number of blocks in each character
                      // ! " # $ % & ' ( ) * + , - . / 0  1 2 3 4 5  6  7 8 9 : ; < = > ? @ A B C D E F G H I J K L M N O P Q R S T U  V W X Y Z
const int TetrisCharacters::blocksPerChar[64] = {5,4,9,8,7,8,2,4,4,6,5,2,3,1,5,10,8,9,9,8,10,10,6,8,7,2,3,5,4,5,6,8,9,9,8,9,9,7,8,9,8,7,9,6,9,9,9,8,9,9,9,6,9,10,8,7,7,9};
