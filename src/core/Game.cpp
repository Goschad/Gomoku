#include "./../../include/core/Game.hpp"

Game::Game()
{
    this->_turn = 0;
    this->_currentPlayer = Cell::Black;
    std::cout << "Game constructor called..." << std::endl;
}

Game::~Game()
{
    std::cout << "Game destructor called..." << std::endl;
}

void Game::resetGame()
{
    setTurn(0);
    setCurrentPlayer(Cell::Black);
}

void Game::switchPlayer()
{
    if (getCurrentPlayer() == Cell::Black)
        setCurrentPlayer(Cell::White);
    else
        setCurrentPlayer(Cell::Black);
}

void Game::setTurn(int turn)
{
    this->_turn = turn;
}

void Game::setCurrentPlayer(Cell player)
{
    this->_currentPlayer = player;
}

int Game::getTurn() const
{
    return (this->_turn);
}

Cell Game::getCurrentPlayer() const
{
    return (this->_currentPlayer);
}
