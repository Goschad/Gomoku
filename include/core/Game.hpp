#pragma once

#include "./Cell.hpp"
#include "./../utils/Define.hpp"

class Board;

class Game
{
    private:
        int _turn;
        Cell _currentPlayer;
        int _capture_black;
        int _capture_white;
        Cell _winner;
        bool _pending_winner;

        Cell getOpponent() const;
        void addCapturePoints();

    public:
        Game();
        ~Game();

        void resetGame();
        void switchPlayer();

        void setTurn(int turn);
        void setCaptureBlack(int value);
        void setCaptureWhite(int value);
        void setCurrentPlayer(Cell player);

        int getTurn() const;
        int getCaptureBlack() const;
        int getCaptureWhite() const;
        Cell getCurrentPlayer() const;

        bool checkCapture(Board &board, int r, int c);

        void playMove(Board &board);
};