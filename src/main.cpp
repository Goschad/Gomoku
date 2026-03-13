#include <SFML/Graphics.hpp>
#include <array>
#include <optional>
#include <string>
#include <algorithm>

constexpr int BOARD_SIZE = 19;
constexpr unsigned int WINDOW_WIDTH = 1200;
constexpr unsigned int WINDOW_HEIGHT = 800;

enum class Cell
{
    Empty,
    Black,
    White
};

using Board = std::array<std::array<Cell, BOARD_SIZE>, BOARD_SIZE>;

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

void initBoard(Board& board)
{
    for (auto& row : board)
    {
        for (auto& cell : row)
            cell = Cell::Empty;
    }
}

bool isInsideBoard(int row, int col)
{
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

Layout computeLayout(const sf::RenderWindow& window)
{
    Layout layout{};

    layout.margin = 30.f;
    layout.sidePanelWidth = 300.f;

    const sf::Vector2u winSize = window.getSize();

    const float availableWidth =
        static_cast<float>(winSize.x) - layout.sidePanelWidth - (layout.margin * 3.f);

    const float availableHeight =
        static_cast<float>(winSize.y) - (layout.margin * 2.f);

    layout.boardPixelSize = std::min(availableWidth, availableHeight);

    if (layout.boardPixelSize < 200.f)
        layout.boardPixelSize = 200.f;

    layout.cellSize = layout.boardPixelSize / static_cast<float>(BOARD_SIZE - 1);

    layout.boardOffsetX = layout.margin;
    layout.boardOffsetY = (static_cast<float>(winSize.y) - layout.boardPixelSize) / 2.f;

    layout.panelX = layout.boardOffsetX + layout.boardPixelSize + layout.margin;
    layout.panelY = layout.margin;
    layout.panelWidth = layout.sidePanelWidth;
    layout.panelHeight = static_cast<float>(winSize.y) - 2.f * layout.margin;

    return layout;
}

void drawBoardBackground(sf::RenderWindow& window, const Layout& layout)
{
    sf::RectangleShape background(sf::Vector2f(layout.boardPixelSize, layout.boardPixelSize));
    background.setPosition(sf::Vector2f(layout.boardOffsetX, layout.boardOffsetY));
    background.setFillColor(sf::Color(205, 170, 125));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2.f);

    window.draw(background);
}

void drawBoard(sf::RenderWindow& window, const Layout& layout)
{
    drawBoardBackground(window, layout);

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        sf::Vertex horizontal[2];
        horizontal[0].position = sf::Vector2f(layout.boardOffsetX, layout.boardOffsetY + i * layout.cellSize);
        horizontal[0].color = sf::Color::Black;
        horizontal[1].position = sf::Vector2f(layout.boardOffsetX + layout.boardPixelSize, layout.boardOffsetY + i * layout.cellSize);
        horizontal[1].color = sf::Color::Black;

        sf::Vertex vertical[2];
        vertical[0].position = sf::Vector2f(layout.boardOffsetX + i * layout.cellSize, layout.boardOffsetY);
        vertical[0].color = sf::Color::Black;
        vertical[1].position = sf::Vector2f(layout.boardOffsetX + i * layout.cellSize, layout.boardOffsetY + layout.boardPixelSize);
        vertical[1].color = sf::Color::Black;

        window.draw(horizontal, 2, sf::PrimitiveType::Lines);
        window.draw(vertical, 2, sf::PrimitiveType::Lines);
    }
}

void drawStones(sf::RenderWindow& window, const Board& board, const Layout& layout)
{
    const float stoneRadius = layout.cellSize * 0.38f;

    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (board[row][col] == Cell::Empty)
                continue;

            sf::CircleShape stone(stoneRadius);
            stone.setOrigin(sf::Vector2f(stoneRadius, stoneRadius));
            stone.setPosition(sf::Vector2f(
                layout.boardOffsetX + col * layout.cellSize,
                layout.boardOffsetY + row * layout.cellSize
            ));

            if (board[row][col] == Cell::Black)
                stone.setFillColor(sf::Color::Black);
            else
                stone.setFillColor(sf::Color::White);

            stone.setOutlineColor(sf::Color::Black);
            stone.setOutlineThickness(1.f);

            window.draw(stone);
        }
    }
}

void drawSidePanel(sf::RenderWindow& window, const Layout& layout)
{
    sf::RectangleShape panel(sf::Vector2f(layout.panelWidth, layout.panelHeight));
    panel.setPosition(sf::Vector2f(layout.panelX, layout.panelY));
    panel.setFillColor(sf::Color(235, 220, 190));
    panel.setOutlineColor(sf::Color::Black);
    panel.setOutlineThickness(2.f);

    window.draw(panel);
}

sf::Text makeText(const sf::Font& font, const std::string& str, unsigned int size, float x, float y)
{
    sf::Text text(font, str, size);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(x, y));
    return text;
}

void drawInfos(
    sf::RenderWindow& window,
    const Layout& layout,
    const sf::Font& font,
    int turnCount,
    Cell currentPlayer,
    const std::string& modeText)
{
    const float x = layout.panelX + 20.f;
    float y = layout.panelY + 20.f;

    sf::Text title = makeText(font, "Gomoku", 30, x, y);
    window.draw(title);

    y += 70.f;
    sf::Text mode = makeText(font, "Mode : " + modeText, 22, x, y);
    window.draw(mode);

    y += 50.f;
    sf::Text turns = makeText(font, "Nombre de tours : " + std::to_string(turnCount), 22, x, y);
    window.draw(turns);

    y += 50.f;
    const std::string player = (currentPlayer == Cell::Black) ? "Noir" : "Blanc";
    sf::Text current = makeText(font, "A qui de jouer : " + player, 22, x, y);
    window.draw(current);

    y += 70.f;
    sf::Text help1 = makeText(font, "Clic gauche : poser un pion", 18, x, y);
    window.draw(help1);

    y += 35.f;
    sf::Text help2 = makeText(font, "Le plateau reste carre", 18, x, y);
    window.draw(help2);

    y += 35.f;
    sf::Text help3 = makeText(font, "meme en plein ecran", 18, x, y);
    window.draw(help3);
}

bool getBoardPositionFromMouse(const Layout& layout, int mouseX, int mouseY, int& row, int& col)
{
    const float localX = static_cast<float>(mouseX) - layout.boardOffsetX;
    const float localY = static_cast<float>(mouseY) - layout.boardOffsetY;

    col = static_cast<int>((localX + layout.cellSize / 2.f) / layout.cellSize);
    row = static_cast<int>((localY + layout.cellSize / 2.f) / layout.cellSize);

    return isInsideBoard(row, col);
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)),
        "Gomoku",
        sf::Style::Default
    );

    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("assets/fonts/arial.ttf"))
        return 1;

    Board board;
    initBoard(board);

    Cell currentPlayer = Cell::Black;
    int turnCount = 0;
    const std::string modeText = "Joueur vs Joueur";

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea(
                    sf::Vector2f(0.f, 0.f),
                    sf::Vector2f(static_cast<float>(resized->size.x), static_cast<float>(resized->size.y))
                );
                window.setView(sf::View(visibleArea));
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    Layout layout = computeLayout(window);

                    int row = -1;
                    int col = -1;

                    if (getBoardPositionFromMouse(layout, mousePressed->position.x, mousePressed->position.y, row, col))
                    {
                        if (board[row][col] == Cell::Empty)
                        {
                            board[row][col] = currentPlayer;
                            ++turnCount;
                            currentPlayer = (currentPlayer == Cell::Black) ? Cell::White : Cell::Black;
                        }
                    }
                }
            }
        }

        const Layout layout = computeLayout(window);

        window.clear(sf::Color(210, 180, 140));
        drawBoard(window, layout);
        drawStones(window, board, layout);
        drawSidePanel(window, layout);
        drawInfos(window, layout, font, turnCount, currentPlayer, modeText);
        window.display();
    }

    return 0;
}