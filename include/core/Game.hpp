#pragma once

#include <set>

#include "./Cell.hpp"
#include "./../utils/Define.hpp"

class Board;

class Game
{
    private:
        int _turn;
        Cell _currentPlayer;
        int _captureBlack;
        int _captureWhite;
        Cell _winner;
        Cell _pendingWinner;
        std::vector<std::pair<int,int>> _pendingLine;

        Cell getOpponent() const;
        void addCapturePoints();
        void clearPendingWinner();
        int countDirection(Board &board, int x, int y, int dx, int dy);
        std::vector<std::pair<int,int>> collectWinningLine(Board &board, int x, int y);
        std::vector<std::pair<int,int>> checkCaptureIfPlayed(Board &board, int x, int y, Cell player);
        bool lineStillExists(Board &board) const;

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
        void setPendingWinner(Cell player, const std::vector<std::pair<int,int>> &line);

        int getTurn() const;
        int getCaptureBlack() const;
        int getCaptureWhite() const;
        int getCurrentPlayerCapture() const;
        Cell getWinner() const;
        Cell getPendingWinner() const;
        Cell getCurrentPlayer() const;

        bool checkCapture(Board &board, int r, int c);
        bool hasFiveOrMore(Board &board, int x, int y);

        bool isWinningLineBreakable(Board &board, const std::vector<std::pair<int,int>> &line);

        void playMove(Board &board);
};