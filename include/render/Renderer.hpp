#pragma once

#include "./../core/Cell.hpp"
#include <SFML/Graphics.hpp>
#include "./../utils/Define.hpp"

class Game;
class Board;

struct Layout
{
    float margin;
    float sidePanelWidth;
    float boardPixelSize;
    float cellSize;
    float boardOffsetX;
    float boardOffsetY;
    float panelX;
    float panelY;
    float panelWidth;
    float panelHeight;
};

class Renderer
{
    private:
        Layout _layout;
        sf::Font _font;
        std::string _title;
        unsigned int _fps;
        unsigned int _width;
        unsigned int _height;
        std::string _modeText;
        sf::RenderWindow _window;

        void setIcon();
        void setFpsLimit();
        sf::Font setFont();

        void drawGobanBackground(sf::RenderWindow& window, const Layout& layout);
        void drawHorizontalLine(sf::RenderWindow& window, const Layout& layout, int row);
        void drawVerticalLine(sf::RenderWindow& window, const Layout& layout, int col);
        void drawHoshi(sf::RenderWindow& window, const Layout& layout);

        void drawStone(const Layout& layout, int row, int col, Cell cell);
        void drawGhostStone(const Layout& layout, int row, int col, Cell player);

        sf::Text makeText(const sf::Font& font, const std::string& str, unsigned int size, float x, float y);

    public:
        Renderer();
        ~Renderer();

        sf::RenderWindow& getWindow();
        sf::Font& getFont();
        const Layout& getLayout() const;
        const std::string& getModeText() const;
        const std::string& getTitle() const;
        unsigned int getFps() const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;

        void setModeText(std::string modeText);

        void calculateLayout(int board_size);
        void stonePreveiw(Board &board, Cell player);
        void drawStones(const Board& board, const Layout& layout);
        void drawInfos(sf::RenderWindow& window, const Layout& layout, const Game& game);
        void drawGoban(sf::RenderWindow& window, const Layout& layout, const int board_size);
        bool mouseToBoard(const Layout& layout, const sf::Vector2i& mousePos, int& row, int& col, int boardSize);
};


// Initialization functions
/*
void init_font(void);
void init_fps_limit(sf::RenderWindow& window, unsigned int fps);
sf::RenderWindow init_window(unsigned int width, unsigned int height);
void init_icon(sf::RenderWindow& window, const std::filesystem::path& iconPath);
*/

// init the layout of the board and side panel based on the current window size


// Layout computeLayout(const sf::RenderWindow& window);

// Draw the goban and the stones

// void drawBoard(sf::RenderWindow& window, const Layout& layout);