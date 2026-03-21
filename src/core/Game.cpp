#include "./../../include/core/Game.hpp"
#include "./../../include/core/Board.hpp"

Game::Game()
{
    this->_turn = 0;
    this->_captureBlack = 0;
    this->_captureWhite = 0;
    this->_currentPlayer = Cell::Black;
    this->_pendingWinner = Cell::Empty;
    this->_winner = Cell::Empty;
    this->_pendingLine = {};
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
    this->_captureBlack = value;
}

void Game::setCaptureWhite(int value)
{
    this->_captureWhite = value;
}

void Game::setCurrentPlayer(Cell player)
{
    this->_currentPlayer = player;
}

void Game::setWinner(Cell player)
{
    this->_winner = player;
}

void Game::setPendingWinner(Cell player, const std::vector<std::pair<int,int>> &line)
{
    _pendingWinner = player;
    _pendingLine = line;
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
    return (this->_captureBlack);
}

int Game::getCaptureWhite() const
{
    return (this->_captureWhite);
}

int Game::getCurrentPlayerCapture() const
{
    if (getCurrentPlayer() == Cell::White)
        return (this->_captureWhite);
    else
        return (this->_captureBlack);
}


Cell Game::getCurrentPlayer() const
{
    return (this->_currentPlayer);
}

Cell Game::getWinner() const
{
    return (this->_winner);
}

Cell Game::getPendingWinner() const
{
    return (this->_winner);
}

Cell Game::getOpponent() const
{
    if (getCurrentPlayer() == Cell::Black)
        return (Cell::White);
    else
        return (Cell::Black);
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
    setWinner(Cell::Empty);
    setPendingWinner(Cell::Empty, {});
}

void Game::switchPlayer()
{
    if (getCurrentPlayer() == Cell::Black)
        setCurrentPlayer(Cell::White);
    else
        setCurrentPlayer(Cell::Black);
}

// ----------------------------- //
// Capture
// ----------------------------- //

void Game::addCapturePoints()
{
    if (getCurrentPlayer() == Cell::Black)
        setCaptureBlack(getCaptureBlack() + 2);
    else
        setCaptureWhite(getCaptureWhite() + 2);
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
                return (true);
            }
        }
    }
    return (false);
}

// ----------------------------- //
// Five
// ----------------------------- //

void Game::clearPendingWinner()
{
    _pendingWinner = Cell::Empty;
    _pendingLine.clear();
}

bool Game::lineStillExists(Board &board) const
{
    if (_pendingLine.empty()) return false;
    for (auto &p : _pendingLine)
    {
        if (!board.isInsideBoard(p.first, p.second))
            return false;
        if (board.getCell(p.first, p.second) != _pendingWinner)
            return false;
    }
    return true;
}

int Game::countDirection(Board &board, int x, int y, int dx, int dy)
{
    int count = 0;
    int nx = x + dx;
    int ny = y + dy;

    while (board.isInsideBoard(nx, ny) && board.getCell(nx, ny) == getCurrentPlayer())
    {
        count++;
        nx += dx;
        ny += dy;
    }

    return count;
}

bool Game::hasFiveOrMore(Board &board, int x, int y)
{
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int i = 0; i < 4; i++)
    {
        int dx = directions[i][0];
        int dy = directions[i][1];

        int count = 1;

        count += countDirection(board, x, y, dx, dy);
        count += countDirection(board, x, y, -dx, -dy);

        if (count >= 5)
        {
            return true;
        }
    }

    return false;
}

std::vector<std::pair<int,int>> Game::collectWinningLine(Board &board, int x, int y)
{
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    Cell player = getCurrentPlayer();

    for (int i = 0; i < 4; i++)
    {
        int dx = directions[i][0];
        int dy = directions[i][1];

        std::vector<std::pair<int,int>> coords;
        coords.push_back({x, y});

        for (int step = 1; ; step++)
        {
            int nx = x + dx * step, ny = y + dy * step;
            if (!board.isInsideBoard(nx, ny) || board.getCell(nx, ny) != player) break;
            coords.push_back({nx, ny});
        }
        for (int step = 1; ; step++)
        {
            int nx = x - dx * step, ny = y - dy * step;
            if (!board.isInsideBoard(nx, ny) || board.getCell(nx, ny) != player) break;
            coords.push_back({nx, ny});
        }

        if ((int)coords.size() >= 5)
            return coords;
    }
    return {};
}

std::vector<std::pair<int,int>> Game::checkCaptureIfPlayed(Board &board, int x, int y, Cell player)
{
    if (!board.isInsideBoard(x, y) || board.getCell(x, y) != Cell::Empty)
        return {};

    int dx[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    int dy[8] = {0, 0, 1, -1, 1, -1, -1, 1};

    Cell opponent = (player == Cell::Black) ? Cell::White : Cell::Black;
    std::vector<std::pair<int,int>> captured;

    for (int d = 0; d < 8; d++)
    {
        int x1 = x + dx[d],  y1 = y + dy[d];
        int x2 = x + 2*dx[d], y2 = y + 2*dy[d];
        int x3 = x + 3*dx[d], y3 = y + 3*dy[d];

        if (board.isInsideBoard(x1, y1) && board.isInsideBoard(x2, y2) && board.isInsideBoard(x3, y3))
        {
            if (board.getCell(x1, y1) == opponent &&
                board.getCell(x2, y2) == opponent &&
                board.getCell(x3, y3) == player)
            {
                captured.push_back({x1, y1});
                captured.push_back({x2, y2});
            }
        }
    }
    return captured;
}

bool Game::isWinningLineBreakable(Board &board, const std::vector<std::pair<int,int>> &line)
{
    if (line.empty()) return false;

    Cell opponent = getOpponent();

    // Calcul de la bounding box de la ligne + marge de 3
    int minX = line[0].first, maxX = line[0].first;
    int minY = line[0].second, maxY = line[0].second;
    for (auto &p : line)
    {
        minX = std::min(minX, p.first);
        maxX = std::max(maxX, p.first);
        minY = std::min(minY, p.second);
        maxY = std::max(maxY, p.second);
    }

    int searchMinX = std::max(0, minX - 3);
    int searchMaxX = std::min(board.getRows() - 1, maxX + 3);
    int searchMinY = std::max(0, minY - 3);
    int searchMaxY = std::min(board.getCols() - 1, maxY + 3);

    std::set<std::pair<int,int>> lineSet(line.begin(), line.end());

    for (int mx = searchMinX; mx <= searchMaxX; mx++)
    {
        for (int my = searchMinY; my <= searchMaxY; my++)
        {
            if (board.getCell(mx, my) != Cell::Empty)
                continue;

            // Simule le coup adverse et récupère les captures
            std::vector<std::pair<int,int>> caps = checkCaptureIfPlayed(board, mx, my, opponent);
            if (caps.empty())
                continue;

            // Si une cellule capturée appartient à la ligne → la ligne est cassable
            for (auto &cap : caps)
            {
                if (lineSet.count(cap))
                    return true;
            }
        }
    }
    return false;
}

// ----------------------------- //
// Play Move
// ----------------------------- //

void Game::playMove(Board &board)
{
    int r = board.getRow();
    int c = board.getCol();
    Cell played = getCurrentPlayer();

    board.setCell(r, c, played);

    // check double three

    if (checkCapture(board, r, c))
    {
        if (getCurrentPlayerCapture() == 10)
        {
            setWinner(getCurrentPlayer());
        }
    }

    if (_pendingWinner != Cell::Empty && _pendingWinner != getCurrentPlayer())
    {
        if (lineStillExists(board))
        {
            setWinner(_pendingWinner);
            clearPendingWinner();
            // win
            return;
        }
        else
            clearPendingWinner();
    }

    if (hasFiveOrMore(board, r, c))
    {
        std::vector<std::pair<int,int>> line = collectWinningLine(board, r, c);
        if (!line.empty())
        {
            std::vector<std::pair<int,int>> line = collectWinningLine(board, r, c);
            if (!line.empty())
            {
                if (isWinningLineBreakable(board, line))
                    setPendingWinner(getCurrentPlayer(), line);
                else
                {
                    setWinner(getCurrentPlayer());
                    // win
                }
            }
        }
    }

    setTurn(getTurn() + 1);
    switchPlayer();
}