#pragma once
#include "../../fxdata/fxdata.h"
#include "../../fxdata/images/Images.h"

#define _DEBUG
#define _DEBUG_PRINT    Serial.print
#define _DEBUG_PRINTLN  Serial.println
#define DEBUG_BREAK    asm volatile("break\n");

namespace Constants {

    constexpr uint8_t levelSelect_Offset[] = { 0, 0, 14, 31, 43, 43 };
    constexpr uint8_t Undo_Count = 8;
    constexpr uint8_t Level_Count = 24;
        
    //     1   2
    //      \ /
    // 32 -  X - 16
    //      / \
    //     8   4

    //       1
    //       |
    //  8 -  x  - 2
    //       |
    //       4

    constexpr uint8_t Direction_Top_UL = 1;
    constexpr uint8_t Direction_Top_UR = 2;
    constexpr uint8_t Direction_Top_R = 16;
    constexpr uint8_t Direction_Top_L = 32;
    constexpr uint8_t Direction_Top_DL = 8;
    constexpr uint8_t Direction_Top_DR = 4;


    constexpr uint8_t Direction_Side_U = 1;
    constexpr uint8_t Direction_Side_R = 2;
    constexpr uint8_t Direction_Side_D = 4;
    constexpr uint8_t Direction_Side_L = 8;


    constexpr uint8_t Valid_Moves[7][3] = { 

        { 4 + 8 + 16, 1 + 2 + 4, 1 + 2 + 4 + 8 },
        { 4 + 8 + 32, 1 + 2 + 4 + 8, 1 + 4 + 8 },

        { 2 + 4 + 8 + 16, 1 + 2, 1 + 2 + 4 + 8 },
        { 1 + 2 + 4 + 8 + 16 + 32, 1 + 2 + 4 + 8, 1 + 2 + 4 + 8 },
        { 1 + 2 + 4 + 8 + 32, 1 + 2 + 4 + 8, 1 + 8 },

        { 1 + 2 + 4 + 8 + 16, 1 + 2, 1 + 2 + 8 },
        { 1 + 2 + 4 + 8 + 32, 1 + 2 + 8, 1 + 8}

    };


    constexpr uint8_t Block_XPos[] = { 41, 63, 30, 52, 74, 41, 63 };
    constexpr uint8_t Block_YPos[] = { 1, 1, 19, 19, 19, 37, 37 };

    constexpr uint8_t Cube_Right = 2;
    constexpr uint8_t Cube_Top = 0;
    constexpr uint8_t Cube_Left = 1;

    constexpr uint8_t Block_Knob = 0x10;
    constexpr uint8_t Block_Line = 0x20;
    constexpr uint8_t Block_Tee = 0x30;
    constexpr uint8_t Block_Curve = 0x40;

};
