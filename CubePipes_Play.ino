#include <ArduboyFX.h>  
#include "fxdata/fxdata.h"

bool debug = false;

void play_Init() { 

    gameState = nextGameState; //GameState::Play;

}

void handleMenu(uint8_t justPressed) {

    if (justPressed & UP_BUTTON) {

        if (popoutMenu.getSelect() >= (game.getUndoCount() == 0 ? 2 : 1)) {
            popoutMenu.setSelect(popoutMenu.getSelect() - 1);
        }

    }

    else if (justPressed & DOWN_BUTTON) {

        if (popoutMenu.getSelect() < 2) {
            popoutMenu.setSelect(popoutMenu.getSelect() + 1);
        }

    }

    else if (justPressed & A_BUTTON) {

        puff.setCounter(0);

        switch (popoutMenu.getSelect()) {
        
            case 0:
                game.revertMove();
                popoutMenu.setAllowClose(true);
                if (game.getUndoCount() == 0) {
                    popoutMenu.setDirection(Direction::Right);
                }
                break;
        
            case 1:
                popoutMenu.setAllowClose(true);
                gameState = GameState::Play_Init;
                nextGameState = GameState::Play;
                break;
        
            case 2:
                popoutMenu.setAllowClose(true);
                gameState = GameState::Title_Init;
                break;
                
        }

    }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//

void play_Update() { 

    uint8_t justPressed = getJustPressedButtons();
    uint8_t pressed = getPressedButtons();

    game.incFrameCount();

    if (gameState == GameState::Play) {

        if (popoutMenu.getX() == 128) {
            
            // if (doIncLava) {
            //     incLava();
            //     doIncLava = false;
            // }
            // else {

                // if (justPressed & LEFT_BUTTON && isWalkable(ObjectType::Player, -1, 0)) {
                //     game.captureMove();
                //     game.getPlayer().decX();
                //     updateBlocks();
                //     updateGreenDoors();
                //     incWater();
                //     doIncLava = true;
                // }

                // else if (justPressed & RIGHT_BUTTON && isWalkable(ObjectType::Player, 1, 0)) {
                //     game.captureMove();
                //     game.getPlayer().incX();
                //     updateBlocks();
                //     updateGreenDoors();
                //     incWater();
                //     doIncLava = true;
                // }

                // else if (justPressed & UP_BUTTON && isWalkable(ObjectType::Player, 0, -1)) {
                //     game.captureMove();
                //     game.getPlayer().decY();
                //     updateBlocks();
                //     updateGreenDoors();
                //     incWater();
                //     fix_World_Y_Offset();
                //     doIncLava = true;
                // }

                // else if (justPressed & DOWN_BUTTON && isWalkable(ObjectType::Player, 0, 1)) {
                //     game.captureMove();
                //     game.getPlayer().incY();
                //     updateBlocks();
                //     updateGreenDoors();
                //     incWater();
                //     fix_World_Y_Offset();
                //     doIncLava = true;
                // }

            // }


            // Have we won?

            if (false) {

                titleCounter = 0;
            
                game.getPuzzle(game.getLevel()).setStatus(PuzzleStatus::Complete);
                game.getPuzzle(game.getLevel()).setNumberOfMoves(game.getMoveCount());
                
                uint8_t completed = 0;

                for (uint8_t i = 0; i < Constants::Level_Count; i++) {

                    if (game.getPuzzle(i).getStatus() == PuzzleStatus::Complete) {
                        completed++;
                    }

                }

                if (completed == 24) {

                    gameState = GameState::Play_FadeOut;
                    nextGameState = GameState::GameOver_Init;

                }
                else {

                    if (game.getLevel() < Constants::Level_Count - 1 && game.getPuzzle(game.getLevel() + 1).getStatus() != PuzzleStatus::Complete) {

                        gameState = GameState::Play_FadeOut;
                        nextGameState = GameState::Play_FadeIn;

                    }
                    else {

                        gameState = GameState::Play_FadeOut;
                        nextGameState = GameState::Title_Select;

                    }

                }

                saveCookie();

            }

        }
        else {

            handleMenu(justPressed);

        }



            
        // Open menu ..

        if (justPressed & B_BUTTON) {
                    
            if (popoutMenu.getX() == 128) {
                popoutMenu.setDirection(Direction::Left);
                popoutMenu.setSelect(game.getUndoCount() == 0 ? 1 : 0); 
            }
            else if (popoutMenu.getX() == 128 - 32 && popoutMenu.getAllowClose()) {
                popoutMenu.setDirection(Direction::Right);
            }
            
        }

        switch (popoutMenu.getDirection()) {
        
            case Direction::Left:

                popoutMenu.setX(popoutMenu.getX() - 2);

                if (popoutMenu.getX() == 128 - 32) {
                    popoutMenu.setDirection(Direction::None);
                }

                break;
        
            case Direction::Right:

                popoutMenu.setX(popoutMenu.getX() + 2);

                if (popoutMenu.getX() == 128) {
                    popoutMenu.setDirection(Direction::None);
                }

                break;
            
        }


        if (puff.getCounter() > 0 && game.getFrameCount() % 4 == 0) {

            if (puff.getCounter() <10) {

                puff.setCounter(puff.getCounter() + 1);
            
            }

            switch (puff.getCounter()) {
            
                case 4:
                    
                    break;

                case 9:

                    popoutMenu.setDirection(Direction::Left);
                    popoutMenu.setAllowClose(false);
                    break;

            }

        }

    }
    else {
    
        gameState = GameState::Play_Init;
    
    }

}


void play(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    uint8_t currentPlane = a.currentPlane();
    if (a.needsUpdate()) { play_Update(); }


    // Draw Mini Hud ..

    SpritesU::drawOverwriteFX(120, 0, Images::Mini_HUD, currentPlane);
    SpritesU::drawOverwriteFX(121, 17, Images::Numbers_HUD, ((game.getLevel() + 1) * 3) + currentPlane);
    SpritesU::drawOverwriteFX(121, 50, Images::Numbers_HUD, ((game.getMoveCount() / 10) * 3) + currentPlane);
    SpritesU::drawOverwriteFX(121, 54, Images::Numbers_HUD, ((game.getMoveCount() % 100) * 3) + currentPlane);



    // Fade Out

    if (gameState == GameState::Play_FadeOut) {

        // if (titleCounter < 42) {
        //     SpritesU::drawPlusMaskFX(0, -64 + (titleCounter - 10) * 2, Images::Title_Top, currentPlane);
        //     SpritesU::drawPlusMaskFX(0, 71 - (titleCounter - 10) * 2, Images::Title_Bottom, currentPlane);
        // }
        // else {
        //     SpritesU::drawPlusMaskFX(0, -64 + 64, Images::Title_Top, currentPlane);
        //     SpritesU::drawPlusMaskFX(0, 71 - 64, Images::Title_Bottom, currentPlane);

        // }

    }

    // Fade In

    else if (gameState == GameState::Play_FadeIn) {

        // if (titleCounter < 42) {

        //     SpritesU::drawPlusMaskFX(0, - 20 - (titleCounter - 10) * 2, Images::Title_Top, currentPlane);
        //     SpritesU::drawPlusMaskFX(0, 32 + (titleCounter - 10) * 2, Images::Title_Bottom, currentPlane);

        // }

    }

}
