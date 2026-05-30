#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "Player.h"
#include "Puzzle.h"

struct Game {

    private:

        uint8_t mapData[9][14];
        uint8_t prevMapData[Constants::Undo_Count][9][14];
        uint8_t level = 0;
        int8_t world_Y_Offset = 0;
        uint16_t frameCount = 0;
        uint16_t moveCount = 0;
        uint8_t undoCount = 0;

        Puzzle puzzles[Constants::Level_Count];

    public:

        uint16_t getFrameCount()                        { return this->frameCount; }
        uint16_t getFrameCount(uint8_t val)             { return this->frameCount % val < val / 2; }
        int8_t getWorld_Y_Offset()                      { return this->world_Y_Offset; }
        uint8_t getLevel()                              { return this->level; }
        uint8_t getUndoCount()                          { return this->undoCount; }
        uint16_t getMoveCount()                         { return this->moveCount; }
        Puzzle &getPuzzle(uint8_t level)                { return this->puzzles[level]; }

        void setMoveCount(uint16_t val)                 { this->moveCount = val; }
        void setFrameCount(uint16_t val)                { this->frameCount = val; }
        void setWorld_Y_Offset(uint8_t val)             { this->world_Y_Offset = val; }
        void setLevel(uint8_t val)                      { this->level = val; }


        void resetLevel() {

            this->undoCount= 0;
            // this->player.reset();

        }

        void incFrameCount() {

            this->frameCount++;

        }

        void resetFrameCount() {

            this->frameCount = 0;
            
        }

        void captureMove() {

            this->moveCount++;
            if (this->undoCount < Constants::Undo_Count) this->undoCount++;
  
        }

        void revertMove() {


            this->undoCount--;

        }

        void loadMap(uint8_t level) {

            this->resetLevel();

        }

};