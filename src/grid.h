#pragma once
#include <vector>
#include <raylib.h>

class Grid 
{
private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
    bool isRowFull( int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);

public:
    int grid[20][10];
    Grid();
    void Initialize();
    void Draw();
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    void Print();
    int ClearFullRows();
};