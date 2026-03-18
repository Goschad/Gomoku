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
        Cell _pending_winner;

        Cell getOpponent() const;
        void addCapturePoints();
        int countDirection(Board &board, int x, int y, int dx, int dy);

    public:
        Game();
        ~Game();

        void resetGame();
        void switchPlayer();

        void setTurn(int turn);
        void setCaptureBlack(int value);
        void setCaptureWhite(int value);
        void setCurrentPlayer(Cell player);
        void setWinner(Cell player);

        int getTurn() const;
        int getCaptureBlack() const;
        int getCaptureWhite() const;
        int getCurrentPlayerCapture() const;
        Cell getWinner() const;
        Cell getPendingWinner() const;
        Cell getCurrentPlayer() const;

        bool checkCapture(Board &board, int r, int c, bool pending_test);
        bool hasFiveOrMore(Board &board, int x, int y);

        void playMove(Board &board);
};