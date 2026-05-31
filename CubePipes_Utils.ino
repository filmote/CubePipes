#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/utils/SpritesU.hpp"


uint8_t getJustPressedButtons() {

    a.pollButtons();

    return a.justPressedButtons();

}

uint8_t getPressedButtons() {

    return a.pressedButtons();

}

uint8_t getJustReleasedButtons(uint8_t button) {

    return a.justReleasedButtons(button);

}


void fix_World_Y_Offset() {

    // switch (game.getPlayer().getY()) {
    
    //     case 1 ... 3:
    //         game.setWorld_Y_Offset(0);
    //         break;

    //     case 4:
    //         game.setWorld_Y_Offset(4);
    //         break;

    //     case 5:
    //         game.setWorld_Y_Offset(8);
    //         break;

    //     case 6 ... 9:
    //         game.setWorld_Y_Offset(12);
    //         break;


    // }
    
}

void saveCookie() {

    FX::saveGameState(cookie);

}

void cookieReset() {

    for (uint8_t i = 0; i < 24; i++) {

        #ifdef _DEBUG
        if (i < 23) { //SJH
            game.getPuzzle(i).setStatus(PuzzleStatus::InProgress);
            game.getPuzzle(i).setTime(0);
        }
        else {
            game.getPuzzle(i).setStatus(PuzzleStatus::Locked);
            game.getPuzzle(i).setTime(0);
        }
        #endif

        #ifdef DEBUG
        if (i < 23) { 
            game.getPuzzle(i).setStatus(PuzzleStatus::Complete);
            game.getPuzzle(i).setTime(i);
        }
        else {
            game.getPuzzle(i).setStatus(PuzzleStatus::InProgress);
            game.getPuzzle(i).setTime(0);
        }
        #endif

        #ifndef DEBUG
        if (i == 0) { 
            game.getPuzzle(i).setStatus(PuzzleStatus::InProgress);
            game.getPuzzle(i).setTime(0);
        }
        else {
            game.getPuzzle(i).setStatus(PuzzleStatus::Locked);
            game.getPuzzle(i).setTime(0);
        }
        #endif

    }
   

}