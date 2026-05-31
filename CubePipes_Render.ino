#include <ArduboyFX.h>  
#include "fxdata/fxdata.h"


void drawGame(uint8_t currentPlane) {

    // if (currentPlane == 0) {
    //     SpritesU::drawOverwriteFX(0, 0, Images::Background_07, currentPlane);
    // }

    for (uint8_t i = 0; i < 21; i = i + 3) {

        uint8_t x = Constants::Block_XPos[i / 3];
        uint8_t y = Constants::Block_YPos[i / 3];

		uint8_t val = game.puzzle_Grey[i] + (game.puzzle_Grey[i + 1] * 2) + (game.puzzle_Grey[i + 2] * 4);
 		drawGreyFace(x, y, val, currentPlane);

    }

    if (game.getFrameCount() % 90 < 45) {

        uint8_t x = Constants::Block_XPos[game.getCursor() / 3];
        uint8_t y = Constants::Block_YPos[game.getCursor() / 3];

        switch (game.getCursor() % 3) {

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

    }

    for (uint8_t i = 0; i < 21; i++) {

        uint8_t block = game.puzzle[i] & 0xF0;
        uint8_t rotation = game.puzzle[i] & 0x0F;

        uint8_t x = Constants::Block_XPos[i / 3];
        uint8_t y = Constants::Block_YPos[i / 3];

        drawBlock(x, y, i % 3, block, rotation, currentPlane);

    }

}

void drawGreyFace(uint8_t x, uint8_t y, uint8_t val, uint8_t currentPlane) {
    
	SpritesU::drawPlusMaskFX(x, y, Images::Block_Grey, (val * 3) + currentPlane);

}

void drawBlock(uint8_t x, uint8_t y, uint8_t face, uint8_t block, uint8_t rotation, uint8_t currentPlane) {
    

	switch (face) {

		case Constants::Cube_Top:

			switch (block) {
				
				case Constants::Block_Knob:
					SpritesU::drawPlusMaskFX(x, y, Images::Block_Top_01, (3 * rotation) + currentPlane);
					break;

				case Constants::Block_Line:
					SpritesU::drawPlusMaskFX(x, y, Images::Block_Top_02, (3 * rotation) + currentPlane);
					break;

				case Constants::Block_Tee:
					SpritesU::drawPlusMaskFX(x, y, Images::Block_Top_03, (3 * rotation) + currentPlane);
					break;

				case Constants::Block_Curve:
					SpritesU::drawPlusMaskFX(x, y, Images::Block_Top_04, (3 * rotation) + currentPlane);
					break;

			}

			break;

		case Constants::Cube_Left:
			
			switch (block) {
			
				case Constants::Block_Knob:
				SpritesU::drawPlusMaskFX(x, y + 7, Images::Block_Left_01, (3 * rotation) + currentPlane);
				break;

				case Constants::Block_Line:
				SpritesU::drawPlusMaskFX(x, y + 7, Images::Block_Left_02, (3 * rotation) + currentPlane);
				break;

				case Constants::Block_Tee:
				SpritesU::drawPlusMaskFX(x, y + 7, Images::Block_Left_03, (3 * rotation) + currentPlane);
				break;

				case Constants::Block_Curve:
				SpritesU::drawPlusMaskFX(x, y + 7, Images::Block_Left_04, (3 * rotation) + currentPlane);
				break;

			}

			break;

		case Constants::Cube_Right:
			
			switch (block) {
			
				case Constants::Block_Knob:
				SpritesU::drawPlusMaskFX(x + 11, y + 7, Images::Block_Right_01, (3 * rotation) + currentPlane);
				break;

				case Constants::Block_Line:
				SpritesU::drawPlusMaskFX(x + 11, y + 7, Images::Block_Right_02, (3 * rotation) + currentPlane);
				break;

				case Constants::Block_Tee:
				SpritesU::drawPlusMaskFX(x + 11, y + 7, Images::Block_Right_03, (3 * rotation) + currentPlane);
				break;

				case Constants::Block_Curve:
				SpritesU::drawPlusMaskFX(x + 11, y + 7, Images::Block_Right_04, (3 * rotation) + currentPlane);
				break;

			}

			break;

	}

}