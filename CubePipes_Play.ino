#include <ArduboyFX.h>  
#include "fxdata/fxdata.h"

bool debug = false;



uint8_t puzzle_Orig[21] = { 0x11, 0x12, 0x20,    0x12, 0x31, 0x42,
0x40, 0x11, 0x30,   0x30, 0x32, 0x33,      0x42, 0x40, 0x13,
0x40, 0x11, 0x43,   0x32, 0x10, 0x10
 };

// uint8_t puzzle[21] = { 0x11, 0x12, 0x20,    0x12, 0x31, 0x42,
// 0x40, 0x11, 0x30,   0x30, 0x32, 0x33,      0x42, 0x40, 0x13,
// 0x40, 0x11, 0x43,   0x32, 0x10, 0x10
//  };



uint8_t puzzles[2][21] = {

//1
{ 0x11, 0x41, 0x30,    0x11, 0x21, 0x33,
0x40, 0x11, 0x33,   0x11, 0x12, 0x20,      0x13, 0x41, 0x13,
0x33, 0x40, 0x23,   0x33, 0x30, 0x13
 },

//2
{ 0x12, 0x31, 0x32,    0x12, 0x30, 0x13,
0x31, 0x10, 0x31,   0x13, 0x13, 0x12,      0x12, 0x31, 0x13,
0x32, 0x10, 0x40,   0x33, 0x30, 0x13
 },

// //3
// { 0x12, 0x31, 0x42,    0x12, 0x31, 0x42,
// 0x31, 0x10, 0x40,   0x30, 0x42, 0x40,      0x21, 0x13, 0x10,
// 0x31, 0x10, 0x40,   0x41, 0x43, 0x10
//  },

// //4
// { 0x12, 0x31, 0x32,    0x12, 0x30, 0x42,
// 0x10, 0x11, 0x32,   0x42, 0x30, 0x42,      0x42, 0x40, 0x13,
// 0x13, 0x11, 0x21,   0x32, 0x43, 0x10
//  },

// //5
// { 0x11, 0x41, 0x30,    0x41, 0x43, 0x10,
// 0x31, 0x10, 0x31,   0x11, 0x21, 0x30,      0x41, 0x43, 0x10,
// 0x32, 0x10, 0x40,   0x41, 0x43, 0x10
//  },

// // 6
// { 0x12, 0x40, 0x42,    0x12, 0x31, 0x13,
// 0x11, 0x11, 0x30,   0x30, 0x32, 0x33,      0x12, 0x31, 0x13,
// 0x40, 0x11, 0x43,   0x30, 0x11, 0x43
//  },

// // 7
// { 0x41, 0x20, 0x31,    0x12, 0x30, 0x42,
// 0x10, 0x11, 0x32,   0x42, 0x30, 0x21,      0x13, 0x21, 0x13,
// 0x42, 0x40, 0x21,   0x41, 0x43, 0x10
//  },

// //8
// { 0x41, 0x10, 0x31,    0x41, 0x43, 0x10,
// 0x11, 0x11, 0x30,   0x32, 0x43, 0x31,      0x41, 0x43, 0x10,
// 0x41, 0x10, 0x40,   0x42, 0x30, 0x13
//  },

// //9
// { 0x41, 0x20, 0x40,    0x11, 0x32, 0x43,
// 0x40, 0x11, 0x30,   0x40, 0x42, 0x10,      0x41, 0x20, 0x10,
// 0x40, 0x11, 0x30,   0x20, 0x30, 0x13
//  },

// // 10
// { 0x12, 0x31, 0x42,    0x12, 0x31, 0x13,
// 0x40, 0x11, 0x30,   0x30, 0x42, 0x31,      0x41, 0x43, 0x10,
// 0x20, 0x10, 0x11,   0x32, 0x43, 0x10
//  },

// // 11
// { 0x41, 0x10, 0x20,    0x12, 0x20, 0x12,
// 0x12, 0x40, 0x42,   0x33, 0x40, 0x42,      0x42, 0x31, 0x13,
// 0x42, 0x40, 0x21,   0x30, 0x21, 0x43
//  },

// //12
// { 0x11, 0x41, 0x33,    0x12, 0x31, 0x13,
// 0x40, 0x11, 0x33,   0x43, 0x41, 0x21,      0x12, 0x30, 0x13,
// 0x30, 0x11, 0x30,   0x12, 0x30, 0x13
//  },


// //13
// { 0x11, 0x11, 0x30,    0x12, 0x30, 0x42,
// 0x41, 0x10, 0x31,   0x12, 0x30, 0x42,      0x42, 0x31, 0x13,
// 0x21, 0x11, 0x30,   0x30, 0x13, 0x10
//  },

// //14
// { 0x11, 0x41, 0x30,    0x11, 0x32, 0x43,
// 0x20, 0x10, 0x11,   0x31, 0x33, 0x31,      0x12, 0x30, 0x13,
// 0x31, 0x10, 0x40,   0x21, 0x13, 0x10
//  },

// //15
// { 0x12, 0x31, 0x42,    0x11, 0x41, 0x33,
// 0x10, 0x11, 0x42,   0x33, 0x31, 0x42,      0x32, 0x10, 0x10,
// 0x33, 0x10, 0x11,   0x32, 0x43, 0x10
//  },

// //16
// { 0x11, 0x41, 0x43,    0x12, 0x20, 0x12,
// 0x40, 0x11, 0x30,   0x20, 0x33, 0x12,      0x42, 0x31, 0x13,
// 0x31, 0x10, 0x40,   0x33, 0x30, 0x13
//  },


// //17
// { 0x41, 0x20, 0x20,    0x11, 0x41, 0x33,
// 0x31, 0x10, 0x40,   0x30, 0x42, 0x40,      0x21, 0x42, 0x10,
// 0x40, 0x11, 0x43,   0x40, 0x11, 0x43
//  },


// //18
// { 0x12, 0x31, 0x21,    0x11, 0x32, 0x43,
// 0x31, 0x10, 0x40,   0x10, 0x32, 0x42,      0x11, 0x41, 0x43,
// 0x31, 0x10, 0x10,   0x33, 0x40, 0x13
//  },


// //19
// { 0x11, 0x41, 0x30,    0x11, 0x32, 0x43,
// 0x10, 0x11, 0x32,   0x31, 0x43, 0x31,      0x41, 0x43, 0x10,
// 0x32, 0x10, 0x10,   0x42, 0x40, 0x13
//  },


// //20
// { 0x11, 0x41, 0x30,    0x12, 0x43, 0x12,
// 0x40, 0x11, 0x33,   0x41, 0x20, 0x31,      0x21, 0x21, 0x43,
// 0x33, 0x40, 0x13,   0x32, 0x10, 0x10
//  },

};


uint8_t puzzleIDX = 0;

// constexpr uint8_t BLOCK_KNOB = 0x10;
// constexpr uint8_t BLOCK_LINE = 0x20;
// constexpr uint8_t BLOCK_TEE = 0x30;
// constexpr uint8_t BLOCK_CURVE = 0x40;



// uint8_t puzzle[21] = { 0x11, 0x12, 0x20,    0x12, 0x31, 0x42,
// 0x40, 0x11, 0x30,   0x30, 0x32, 0x33,      0x42, 0x40, 0x13,
// 0x40, 0x11, 0x43,   0x32, 0x10, 0x10
//  };
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

uint8_t valid_moves[7][3] = { 

{ 4 + 8 + 16, 1 + 2 + 4, 1 + 2 + 4 + 8 },
{ 4 + 8 + 32, 1 + 2 + 4 + 8, 1 + 4 + 8 },

{ 2 + 4 + 8 + 16, 1 + 2, 1 + 2 + 4 + 8 },
{ 1 + 2 + 4 + 8 + 16 + 32, 1 + 2 + 4 + 8, 1 + 2 + 4 + 8 },
{ 1 + 2 + 4 + 8 + 32, 1 + 2 + 4 + 8, 1 + 8 },

{ 1 + 2 + 4 + 8 + 16, 1 + 2, 1 + 2 + 8 },
{ 1 + 2 + 4 + 8 + 32, 1 + 2 + 8, 1 + 8}

};

uint8_t cursor_P = 0;

constexpr uint8_t CUBE_RIGHT = 2;
constexpr uint8_t CUBE_TOP = 0;
constexpr uint8_t CUBE_LEFT = 1;

constexpr uint8_t BLOCK_KNOB = 0x10;
constexpr uint8_t BLOCK_LINE = 0x20;
constexpr uint8_t BLOCK_TEE = 0x30;
constexpr uint8_t BLOCK_CURVE = 0x40;

const uint8_t xPos[] = { 41, 63, 30, 52, 74, 41, 63 };
const uint8_t yPos[] = { 1, 1, 19, 19, 19, 37, 37 };

bool endOfGame = false;



// ─── Full scene render (called each plane) ────────────────────────────────────
void drawScene(uint8_t currentPlane) {


  if (currentPlane == 0) {
  SpritesU::drawOverwriteFX(0, 0, Images::Background_07, currentPlane);
  }

  if (game.getFrameCount() % 120 < 60) {

    uint8_t x = xPos[cursor_P / 3];
    uint8_t y = yPos[cursor_P / 3];

// Serial.print(x);
// Serial.print(" ");
// Serial.print(y);
// Serial.print(" ");
// Serial.println(cursor_P % 3);

    switch (cursor_P % 3) {

      case 0:
        SpritesU::drawPlusMaskFX(x, y, Images::Cursor_Top, currentPlane);
        break;

      case 1:
        SpritesU::drawPlusMaskFX(x, y + 6, Images::Cursor_Left, currentPlane);
        break;

      case 2:
        SpritesU::drawPlusMaskFX(x + 11, y + 6, Images::Cursor_Right, currentPlane);
        break;
    
    }

  // Serial.println(frameCount);
  //  SpritesU::drawPlusMaskFX(30, 7, Images::Cursor_Left, currentPlane);
 
  }

  for (uint8_t i = 0; i < 21; i++) {

    uint8_t block = puzzles[puzzleIDX][i] & 0xF0;
    uint8_t rotation = puzzles[puzzleIDX][i] & 0x0F;

	uint8_t x = xPos[i / 3];
	uint8_t y = yPos[i / 3];

	drawBlock(x, y, i % 3, block, rotation, currentPlane);
   


  }

	if (endOfGame) {
		SpritesU::drawPlusMaskFX(5, 22, Images::Complete, currentPlane);
	}

}

void drawBlock(uint8_t x, uint8_t y, uint8_t face, uint8_t block, uint8_t rotation, uint8_t currentPlane) {
    

	switch (face) {

		case 0:

			switch (block) {
			
			case BLOCK_KNOB:
				SpritesU::drawPlusMaskFX(x, y, Images::Block_Top_01, (3 * rotation) + currentPlane);
				break;

			case BLOCK_LINE:
				SpritesU::drawPlusMaskFX(x, y, Images::Block_Top_02, (3 * rotation) + currentPlane);
				break;

			case BLOCK_TEE:
				SpritesU::drawPlusMaskFX(x, y, Images::Block_Top_03, (3 * rotation) + currentPlane);
				break;

			case BLOCK_CURVE:
				SpritesU::drawPlusMaskFX(x, y, Images::Block_Top_04, (3 * rotation) + currentPlane);
				break;

			}

			break;

		case 1:
			
			switch (block) {
			
				case BLOCK_KNOB:
				SpritesU::drawPlusMaskFX(x, y + 7, Images::Block_Left_01, (3 * rotation) + currentPlane);
				break;

				case BLOCK_LINE:
				SpritesU::drawPlusMaskFX(x, y + 7, Images::Block_Left_02, (3 * rotation) + currentPlane);
				break;

				case BLOCK_TEE:
				SpritesU::drawPlusMaskFX(x, y + 7, Images::Block_Left_03, (3 * rotation) + currentPlane);
				break;

				case BLOCK_CURVE:
				SpritesU::drawPlusMaskFX(x, y + 7, Images::Block_Left_04, (3 * rotation) + currentPlane);
				break;

			}

			break;

		case 2:
			
			switch (block) {
			
				case BLOCK_KNOB:
				SpritesU::drawPlusMaskFX(x + 11, y + 7, Images::Block_Right_01, (3 * rotation) + currentPlane);
				break;

				case BLOCK_LINE:
				SpritesU::drawPlusMaskFX(x + 11, y + 7, Images::Block_Right_02, (3 * rotation) + currentPlane);
				break;

				case BLOCK_TEE:
				SpritesU::drawPlusMaskFX(x + 11, y + 7, Images::Block_Right_03, (3 * rotation) + currentPlane);
				break;

				case BLOCK_CURVE:
				SpritesU::drawPlusMaskFX(x + 11, y + 7, Images::Block_Right_04, (3 * rotation) + currentPlane);
				break;

			}

			break;

	}

}

void checkResult() {

	for (uint8_t i = 0; i < 21; i++) {
	
		if (puzzles[puzzleIDX][i] != puzzle_Orig[i]) {
		
			endOfGame = false;
			return;

		}

	}

	endOfGame = true;

}

void play_Init() { 

    popoutMenu.setSelect(0);
    popoutMenu.setX(128);
    popoutMenu.setDirection(Direction::None);

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
Serial.println("GameState::Play");
        if (popoutMenu.getX() == 128) {
Serial.println("popoutMenu.getX() == 128");


            if (a.justPressed(A_BUTTON)) {

            puzzles[puzzleIDX][cursor_P] = (puzzles[puzzleIDX][cursor_P] & 0xF0) + (((puzzles[puzzleIDX][cursor_P] & 0x0F) + 1 ) % 4);

                checkResult();

            }


            if (a.justPressed(B_BUTTON)) {

                puzzles[puzzleIDX][cursor_P] = (puzzles[puzzleIDX][cursor_P] & 0xF0) + (((puzzles[puzzleIDX][cursor_P] & 0x0F) + 3 ) % 4);
                checkResult();

            }
                    

            uint8_t moves[3];
            uint8_t cursor_P3 = cursor_P % 3;

            moves[0] = valid_moves[cursor_P / 3][0];
            moves[1] = valid_moves[cursor_P / 3][1];
            moves[2] = valid_moves[cursor_P / 3][2];


            if (a.justPressed(UP_BUTTON)) {

        Serial.print("Up ");
        Serial.print(moves[0]);
        Serial.print(" ");
        Serial.print(moves[1]);
        Serial.print(" ");
        Serial.println(moves[2]);
            
                if (cursor_P3 == 0 && (moves[0] & 1 || moves[0] & 2)) {
                
                    if (a.pressed(LEFT_BUTTON) && moves[0] & 1) {

                        cursor_P = cursor_P - 7;
                        Serial.println("Up T1");

                    }
                    else if (a.pressed(RIGHT_BUTTON) && moves[0] & 2) {

                        cursor_P = cursor_P - 4;
                        Serial.println("Up T2");

                    }
                    else {

                        cursor_P = cursor_P - 7;
                        Serial.println("Up T3");

                    }

                }

                else if (cursor_P3 == 1 && moves[1] & 1) {

                    cursor_P = cursor_P - 1;			
                    Serial.println("Up L");

                }
                
                else if (cursor_P3 == 2 && moves[2] & 1) {

                    cursor_P = cursor_P - 2;			
                    Serial.println("Up R");

                }

            }

            else if (a.justPressed(DOWN_BUTTON)) {

        Serial.print("Down ");
        Serial.print(moves[0]);
        Serial.print(" ");
        Serial.print(moves[1]);
        Serial.print(" ");
        Serial.println(moves[2]);
            
                if (cursor_P3 == 0 && (moves[0] & 8 || moves[0] & 4)) {
                
                    if (a.pressed(LEFT_BUTTON) && moves[0] & 8) {

                        cursor_P = cursor_P + 1;
                        Serial.println("Down T1");

                    }
                    else if (a.pressed(RIGHT_BUTTON) && moves[0] & 4) {

                        cursor_P = cursor_P + 2;
                        Serial.println("Down T2");

                    }
                    else {

                        cursor_P = cursor_P + 1;
                        Serial.println("Down T3");

                    }

                }

                else if (cursor_P3 == 1 && moves[1] & 4) {

                    cursor_P = cursor_P + 5;			
                    Serial.println("Down L");

                }
                
                else if (cursor_P3 == 2 && moves[2] & 4) {

                    cursor_P = cursor_P + 4 + 3;			
                    Serial.println("Down R");

                }

            }





            else if (a.justPressed(RIGHT_BUTTON)) {

        Serial.print("Right ");
        Serial.print(moves[0]);
        Serial.print(" ");
        Serial.print(moves[1]);
        Serial.print(" ");
        Serial.println(moves[2]);

                if (cursor_P3 == 0 && moves[0] & 16) {

                    cursor_P = cursor_P + 3;

                }
                else if (cursor_P3 == 1) {

                    cursor_P++;

                }
                else if (cursor_P3 == 2 && moves[2] & 2) {

                    cursor_P = cursor_P + 2;

                }

            }


            else if (a.justPressed(LEFT_BUTTON)) {

        Serial.print("Left ");
        Serial.print(moves[0]);
        Serial.print(" ");
        Serial.print(moves[1]);
        Serial.print(" ");
        Serial.println(moves[2]);

                if (cursor_P3 == 0 && moves[0] & 32) {

                    cursor_P = cursor_P - 3;

                }
                else if (cursor_P3 == 2) {

                    cursor_P--;

                }
                else if (cursor_P3 == 1 && moves[2] & 8) {

                    cursor_P = cursor_P - 2;

                }

            }

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
Serial.println(justPressed);
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

drawScene(a.currentPlane());


    if (popoutMenu.getX() < 128) {
        SpritesU::drawOverwriteFX(popoutMenu.getX(), 0, Images::Menu, ((popoutMenu.getSelect() + (game.getUndoCount() == 0 ? 2 : 0)) * 3) + ((popoutMenu.getAllowClose() ? 0 : 5) * 3) + currentPlane);
    }


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
