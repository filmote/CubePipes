#include <ArduboyFX.h>  
#include "fxdata/fxdata.h"
#include "src/entities/Puzzles.h"

GameOver endOfGame = GameOver::No;
uint16_t bPressed = 0;

void checkResult() {

    uint8_t completed = 0;

	for (uint8_t i = 0; i < 21; i++) {
	
        uint8_t v = pgm_read_byte(&puzzles[game.getLevel()][i]);

		if (game.puzzle[i] != v) {
		
			endOfGame = GameOver::No;
			return;

		}

	}


    // Complete ?

    game.getPuzzle(game.getLevel()).setStatus(PuzzleStatus::Complete);
    game.getPuzzle(game.getLevel()).setTime(game.getTime());

    for (uint8_t i = 0; i < Constants::Level_Count; i++) {

        if (game.getPuzzle(i).getStatus() == PuzzleStatus::Complete) {
            completed++;
        }

    }

    if (completed == 24) {

    	endOfGame = GameOver::GameOver;
        return;

    }

    endOfGame = GameOver::LevelOver;

}

void play_Init() { 

    popoutMenu.setSelect(0);
    popoutMenu.setX(128);
    popoutMenu.setDirection(Direction::None);

    gameState = GameState::Play;
    game.setTime(0);
    endOfGame = GameOver::No;

    memcpy_P(game.puzzle, puzzles[game.getLevel()], 21);
    memcpy_P(game.puzzle_Orig, puzzles[game.getLevel()], 21);
    game.setCursor(0);

	for (uint8_t i = 0; i < 21; i++) {
	
		game.puzzle[i] = (game.puzzle[i] & 0xf0) | (0x0f & static_cast<uint8_t>(random(0,4)));
        
	}

	for (uint8_t i = 0; i < 21; i++) {
	
		game.puzzle_Orig[i] = game.puzzle[i];
        
	}

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
                game.setCursor(0);
                memcpy(game.puzzle, game.puzzle_Orig, 21);
                popoutMenu.setDirection(Direction::Right);
                
                break;
        
            case 2:
                popoutMenu.setAllowClose(true);
                gameState = GameState::Title_Init;
                break;
                
        }

    }

    else if (justPressed & B_BUTTON) {

        popoutMenu.setAllowClose(true);
        popoutMenu.setDirection(Direction::Right);

    }

}


void play_Update() { 

    uint8_t justPressed = getJustPressedButtons();
    uint8_t pressed = getPressedButtons();

    game.incFrameCount();


    if (gameState == GameState::Play) {

        if (popoutMenu.getX() == 128) {

            if (endOfGame == GameOver::No) {

                if (game.getFrameCount() % 52 == 0) {
                    game.incTime();
                }

                if (justPressed & A_BUTTON) {

                    game.captureMove();

                    switch (game.puzzle[game.getCursor()] & 0xF0) {
                    
                        case Constants::Block_Line:
                            game.puzzle[game.getCursor()] = (game.puzzle[game.getCursor()] & 0xF0) + (((game.puzzle[game.getCursor()] & 0x0F) + 1 ) % 2);
                            break;

                        default:
                            game.puzzle[game.getCursor()] = (game.puzzle[game.getCursor()] & 0xF0) + (((game.puzzle[game.getCursor()] & 0x0F) + 1 ) % 4);
                            break;
                    
                    }

                    checkResult();

                    if (endOfGame != GameOver::No) {
                        justPressed = 0;
                    }

                }

                if (pressed & B_BUTTON) {
                
                    bPressed++;

                }

                if (a.notPressed(B_BUTTON)) {

                    if (bPressed > 0 && bPressed < 10) {

                        game.captureMove();

                        switch (game.puzzle[game.getCursor()] & 0xF0) {
                        
                            case Constants::Block_Line:
                                game.puzzle[game.getCursor()] = (game.puzzle[game.getCursor()] & 0xF0) + (((game.puzzle[game.getCursor()] & 0x0F) + 3 ) % 2);
                                break;

                            default:
                                game.puzzle[game.getCursor()] = (game.puzzle[game.getCursor()] & 0xF0) + (((game.puzzle[game.getCursor()] & 0x0F) + 3 ) % 4);
                                break;
                        
                        }
                        
                        checkResult();

                        if (endOfGame != GameOver::No) {
                            justPressed = 0;
                        }

                    }

                }
                        

                uint8_t cursorMod3 = game.getCursor() % 3;

                uint8_t moves_Top = Constants::Valid_Moves[game.getCursor() / 3][Constants::Cube_Top];
                uint8_t moves_Left = Constants::Valid_Moves[game.getCursor() / 3][Constants::Cube_Left];
                uint8_t moves_Right = Constants::Valid_Moves[game.getCursor() / 3][Constants::Cube_Right];


                if (a.justPressed(UP_BUTTON)) {
                
                    if (cursorMod3 == Constants::Cube_Top && (moves_Top & Constants::Direction_Top_UL || moves_Top & Constants::Direction_Top_UR)) {
                    
                        if (a.pressed(LEFT_BUTTON) && moves_Top & Constants::Direction_Top_UL) {

                            game.incCursor(-7);
                            // Serial.println("Up T1");

                        }
                        else if (a.pressed(RIGHT_BUTTON) && moves_Top & Constants::Direction_Top_UR) {

                            switch (game.getCursor()) {
                            
                                case 6:
                                case 9:
                                case 12:
                                    game.incCursor(-5);
                                    break;

                                case 15:
                                case 18:
                                    game.incCursor(-8);
                                    break;

                            }

                            // Serial.println("Up T2");

                        }
                        else {

                            switch (game.getCursor()) {
                            
                                case 6:
                                    // Serial.println("Up T3_1");
                                    game.incCursor(-5);
                                    break;

                                case 9:
                                case 12:
                                    // Serial.println("Up T3_1");
                                    game.incCursor(-7);
                                    break;

                                case 15:
                                case 18:
                                    // Serial.println("Up T3_2");
                                    game.incCursor(-7);
                                    break;

                            }


                        }

                    }

                    else if (cursorMod3 == Constants::Cube_Left && moves_Left & Constants::Direction_Side_U) {

                        game.incCursor(-1);
                        // Serial.println("Up L");

                    }
                    
                    else if (cursorMod3 == Constants::Cube_Right && moves_Right & Constants::Direction_Side_U) {

                        game.incCursor(-2);
                        // Serial.println("Up R");

                    }

                }

                else if (a.justPressed(DOWN_BUTTON)) {

            // Serial.print("Down ");
            // Serial.print(moves_Top);
            // Serial.print(" ");
            // Serial.print(moves_Left);
            // Serial.print(" ");
            // Serial.println(moves_Right);
                
                    if (cursorMod3 == Constants::Cube_Top && (moves_Top & Constants::Direction_Top_DL || moves_Top & Constants::Direction_Top_DR)) {
                    
                        if (a.pressed(LEFT_BUTTON) && moves_Top & Constants::Direction_Top_DL) {

                            game.incCursor(1);
                            // Serial.println("Down T1");

                        }
                        else if (a.pressed(RIGHT_BUTTON) && moves_Top & Constants::Direction_Top_DR) {

                            game.incCursor(2);
                            // Serial.println("Down T2");

                        }
                        else {

                            game.incCursor(1);
                            // Serial.println("Down T3");

                        }

                    }

                    else if (cursorMod3 == Constants::Cube_Left && moves_Left & Constants::Direction_Side_D) {

                        game.incCursor(5);
                        // Serial.println("Down L");

                    }
                    
                    else if (cursorMod3 == Constants::Cube_Right && moves_Right & Constants::Direction_Side_D) {

                        game.incCursor(7);
                        // Serial.println("Down R");

                    }

                }


                else if (a.justPressed(RIGHT_BUTTON)) {

            // Serial.print("Right ");
            // Serial.print(moves_Top);
            // Serial.print(" ");
            // Serial.print(moves_Left);
            // Serial.print(" ");
            // Serial.println(moves_Right);

                    if (cursorMod3 == Constants::Cube_Top && moves_Top & Constants::Direction_Top_R) {

                        game.incCursor(3);

                    }
                    else if (cursorMod3 == Constants::Cube_Left) {

                        game.incCursor(1);

                    }
                    else if (cursorMod3 == Constants::Cube_Right && moves_Right & Constants::Direction_Side_R) {

                        game.incCursor(2);

                    }

                }


                else if (a.justPressed(LEFT_BUTTON)) {

            // Serial.print("Left ");
            // Serial.print(moves_Top);
            // Serial.print(" ");
            // Serial.print(moves_Left);
            // Serial.print(" ");
            // Serial.println(moves_Right);

                    if (cursorMod3 == Constants::Cube_Top && moves_Top & Constants::Direction_Top_L) {

                        game.incCursor(-3);

                    }
                    else if (cursorMod3 == Constants::Cube_Right) {

                        game.incCursor(-1);

                    }
                    else if (cursorMod3 == Constants::Cube_Left && moves_Right & Constants::Direction_Side_L) {

                        game.incCursor(-2);

                    }

                }
            }

            // Have we won?

            else {

                if (justPressed & A_BUTTON) {

                    titleCounter = 0;
                    endOfGame = GameOver::No;
                
                    game.getPuzzle(game.getLevel()).setStatus(PuzzleStatus::Complete);
                    game.getPuzzle(game.getLevel()).setTime(game.getTime());
                    
                    uint8_t completed = 0;

                    for (uint8_t i = 0; i < Constants::Level_Count; i++) {

                        if (game.getPuzzle(i).getStatus() == PuzzleStatus::Complete) {
                            completed++;
                        }

                    }

                    if (completed == 24) {

                        gameState = GameState::Title_Init;

                    }
                    else {

                        if (game.getLevel() < Constants::Level_Count - 1 && game.getPuzzle(game.getLevel() + 1).getStatus() != PuzzleStatus::Complete) {

                            gameState = GameState::Play_Init;
                            game.getPuzzle(game.getLevel() + 1).setStatus(PuzzleStatus::InProgress);
                            game.setLevel(game.getLevel() + 1);
                            levelSelect.increaseGame();

                        }
                        else {

                            gameState = GameState::Title_Select;

                        }

                    }

                    saveCookie();

                }

            }

        }
        else {

            handleMenu(justPressed);

        }



            
        // Open menu ..

        if (a.notPressed(B_BUTTON) & bPressed > 10) {
                    
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

    }
    else {

        titleCounter++;

        gameState = GameState::Play_Init;
        game.getPuzzle(game.getLevel() + 1).setStatus(PuzzleStatus::InProgress);
        game.setLevel(game.getLevel() + 1);
        levelSelect.increaseGame();
    
    }


    if (a.notPressed(B_BUTTON)) {

        bPressed = 0;

    }

}


void play(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    uint8_t currentPlane = a.currentPlane();
    if (a.needsUpdate()) { play_Update(); }


    // Draw Mini Hud ..

    drawGame(a.currentPlane());

    SpritesU::drawOverwriteFX(120, 0, Images::Mini_HUD, currentPlane);
    SpritesU::drawOverwriteFX(121, 17, Images::Numbers_HUD, ((game.getLevel() + 1) * 3) + currentPlane);
    SpritesU::drawOverwriteFX(121, 46, Images::Numbers_HUD, ((game.getTime() / 100) * 3) + currentPlane);
    SpritesU::drawOverwriteFX(121, 54, Images::Numbers_HUD, ((game.getTime() % 100) * 3) + currentPlane);


    if (popoutMenu.getX() < 128) {
        SpritesU::drawOverwriteFX(popoutMenu.getX(), 0, Images::Menu, ((popoutMenu.getSelect() + (game.getUndoCount() == 0 ? 2 : 0)) * 3) + ((popoutMenu.getAllowClose() ? 0 : 5) * 3) + currentPlane);
    }


	if (endOfGame == GameOver::LevelOver) {
		SpritesU::drawPlusMaskFX(5, 22, Images::Complete, currentPlane);
	}

	if (endOfGame == GameOver::GameOver) {
		SpritesU::drawPlusMaskFX(0, 22, Images::GameOver, currentPlane);
	}

}
