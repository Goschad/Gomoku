#pragma once

#include "./Cell.hpp"
#include "./../utils/Define.hpp"

class Game
{
    private:
        int _turn;
        Cell _currentPlayer;

    public:
        Game();
        ~Game();

        void resetGame();
        void switchPlayer();

        void setTurn(int turn);
        void setCurrentPlayer(Cell player);

        int getTurn() const;
        Cell getCurrentPlayer() const;
};