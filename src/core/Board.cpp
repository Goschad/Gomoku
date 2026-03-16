#include <iostream>
#include "./../../include/core/Board.hpp"

Board::Board(int r, int c)
{
    this->_row = -1;
    this->_col = -1;
    this->_rows = r;
    this->_cols = c;
    this->_grid = std::vector<std::vector<Cell>>(r, std::vector<Cell>(c, Cell::Empty));

    std::cout << "Board constructor called..." << std::endl;
}

Board::~Board()
{
    std::cout << "Board destructor called..." << std::endl;
}

void Board::setRow(int value)
{
    this->_row = value;
}

void Board::setCol(int value)
{
    this->_col = value;
}

void Board::setCell(int r, int c, Cell value)
{
    this->_grid[r][c] = value;
}

std::vector<std::vector<Cell>> Board::getGrid() const
{
    return (this->_grid);
}

Cell Board::getCell(int r, int c) const
{
    return this->_grid[r][c];
}

int Board::getRow() const
{
    return (this->_row);
}

int Board::getCol() const
{
    return (this->_col);
}

int Board::getRows() const
{
    return (this->_rows);
}

int Board::getCols() const
{
    return (this->_cols);
}

void Board::resetBoard()
{
    for (int i = 0; i < getRows(); i++)
    {
        for (int j = 0; j < getRows(); j++)
        {
            setCell(i, j, Cell::Empty);
        }
    }
    std::cout << "Reset Board" << std::endl;
}

bool Board::isInsideBoard(int row, int col)
{
    return row >= 0 && row < this->_rows && col >= 0 && col < this->_cols;
}

bool Board::getBoardPositionFromMouse(const Layout& layout, int mouseX, int mouseY)
{
    const float localX = static_cast<float>(mouseX) - layout.boardOffsetX;
    const float localY = static_cast<float>(mouseY) - layout.boardOffsetY;

    setRow(static_cast<int>((localY + layout.cellSize / 2.f) / layout.cellSize));
    setCol(static_cast<int>((localX + layout.cellSize / 2.f) / layout.cellSize));;

    return isInsideBoard(this->_row, this->_col);
}

// ===================
//  DEBUG
// ===================

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void Board::printGrid() const
{
    std::cout << "=====================================" << std::endl;
    for (int r = 0; r < _rows; r++)
    {
        for (int c = 0; c < _cols; c++)
        {
            switch (_grid[r][c])
            {
                case Cell::Empty:
                    std::cout << ". ";
                    break;

                case Cell::Black:
                    std::cout << RED << "B " << RESET;
                    break;

                case Cell::White:
                    std::cout << GREEN << "W " << RESET;
                    break;
            }
        }
        std::cout << std::endl;
    }
}