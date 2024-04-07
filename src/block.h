#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;

public:
    int id;
    std::map<int, std::vector<Position>> cells;
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int rowOffSet;
    int ColumnOffset;
};