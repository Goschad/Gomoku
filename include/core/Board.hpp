#pragma once

#include <vector>
#include "./../../include/render/Renderer.hpp"

enum class Cell
{
    Empty = 0,
    Black = 1,
    White = 2
};

class Board
{
    private:
        int _rows;
        int _cols;
        int _row;
        int _col;
        std::vector<std::vector<Cell>> _grid;

    public:
        Board(int r, int c);
        ~Board();
        
        int getRow() const;
        int getCol() const;
        int getRows() const;
        int getCols() const;
        Cell getCell(int r, int c) const;

        void setRow(int value);
        void setCol(int value);
        void setCell(int r, int c, Cell value);

        std::vector<std::vector<Cell>> getGrid() const;

        bool isInsideBoard(int row, int col);
        bool getBoardPositionFromMouse(const Layout& layout, int mouseX, int mouseY);

        void printGrid() const;
};