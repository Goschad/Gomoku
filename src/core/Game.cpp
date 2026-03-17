#include "./../../include/core/Game.hpp"
#include "./../../include/core/Board.hpp"

Game::Game()
{
    this->_turn = 0;
    this->_capture_black = 0;
    this->_capture_white = 0;
    this->_currentPlayer = Cell::Black;
    this->_pending_winner = false;
    this->_winner = Cell::Empty;
    std::cout << "Game constructor called..." << std::endl;
}

Game::~Game()
{
    std::cout << "Game destructor called..." << std::endl;
}

// ----------------------------- //
// Set
// ----------------------------- //

void Game::setTurn(int turn)
{
    this->_turn = turn;
}

void Game::setCaptureBlack(int value)
{
    this->_capture_black = value;
}

void Game::setCaptureWhite(int value)
{
    this->_capture_white = value;
}

void Game::setCurrentPlayer(Cell player)
{
    this->_currentPlayer = player;
}

// ----------------------------- //
// Get
// ----------------------------- //

int Game::getTurn() const
{
    return (this->_turn);
}

int Game::getCaptureBlack() const
{
    return (this->_capture_black);
}

int Game::getCaptureWhite() const
{
    return (this->_capture_white);
}

Cell Game::getCurrentPlayer() const
{
    return (this->_currentPlayer);
}

// ----------------------------- //
// Event
// ----------------------------- //

void Game::resetGame()
{
    setTurn(0);
    setCaptureBlack(0);
    setCaptureWhite(0);
    setCurrentPlayer(Cell::Black);
}

void Game::switchPlayer()
{
    if (getCurrentPlayer() == Cell::Black)
        setCurrentPlayer(Cell::White);
    else
        setCurrentPlayer(Cell::Black);
}

// ----------------------------- //
// Game logic
// ----------------------------- //

void Game::addCapturePoints()
{
    if (getCurrentPlayer() == Cell::Black)
        setCaptureBlack(getCaptureBlack() + 2);
    else
        setCaptureWhite(getCaptureWhite() + 2);
}

Cell Game::getOpponent() const
{
    if (getCurrentPlayer() == Cell::Black)
        return (Cell::White);
    else
        return (Cell::Black);
}

bool Game::checkCapture(Board &board, int r, int c)
{
    int dx[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    int dy[8] = {0, 0, 1, -1, 1, -1, -1, 1};

    Cell opponent = getOpponent();

    for (int d = 0; d < 8; d++)
    {
        int x1 = r + dx[d];
        int y1 = c + dy[d];

        int x2 = r + 2 * dx[d];
        int y2 = c + 2 * dy[d];

        int x3 = r + 3 * dx[d];
        int y3 = c + 3 * dy[d];

        if (board.isInsideBoard(x1, y1) && board.isInsideBoard(x2, y2) && board.isInsideBoard(x3, y3))
        {
            if (board.getCell(x1, y1) == opponent && board.getCell(x2, y2) == opponent && board.getCell(x3, y3) == getCurrentPlayer())
            {
                board.setCell(x1, y1, Cell::Empty);
                board.setCell(x2, y2, Cell::Empty);
                addCapturePoints();
            }
        }
    }
    return (true);
}

// ----------------------------- //
// Play Move
// ----------------------------- //

void Game::playMove(Board &board)
{
    int r = board.getRow();
    int c = board.getCol();

    board.setCell(r, c, getCurrentPlayer());

    // check double three

    // capture 
    checkCapture(board, r, c);
    
    // victory by capture (10)

    // check 5

    // + pending if capture is possible
    setTurn(getTurn() + 1);
    switchPlayer();
}