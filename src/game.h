#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
private:
    std::vector<Block> blocks;
    Sound rotateSound;
    Sound clearSound;
    Block currentBlock;
    Block nextBlock;
    Grid grid;
    std::vector<Block> GetAllBlocks();
    Block GetRandomBlock();
    void MoveBlockRight();
    void MoveBlockLeft();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);

public:
    Music music;
    bool gameOver;
    int score;
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
};