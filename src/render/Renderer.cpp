#include "./../../include/render/Renderer.hpp"

// ----------------------------- //
// Constructor / Destructor
// ----------------------------- //

Renderer::Renderer()
{
    this->_fps = FPS_LIMIT;
    this->_width = WIDTH;
    this->_height = HEIGHT;
    this->_title = WINDOW_TITLE;
    this->_window.create(sf::VideoMode({this->_width, this->_height}), this->_title, sf::Style::Default);

    setFont();
    setIcon();
    setFpsLimit();

    std::cout << "Renderer constructor called..." << std::endl;
}

Renderer::~Renderer()
{
    std::cout << "Renderer destructor called..." << std::endl;
}

// ----------------------------- //
// Window init
// ----------------------------- //

void Renderer::setFont()
{
    sf::Font font;

    if (!font.openFromFile(FONT_PATH))
    {
        exit(1);
    }
}

void Renderer::setIcon()
{
    sf::Image icon;

    if (icon.loadFromFile(ICON_PATH))
        getWindow().setIcon(icon);
}

void Renderer::setFpsLimit()
{
    getWindow().setFramerateLimit(getFps());
}

void Renderer::calculateLayout(int board_size)
{
    _layout.margin = 30.f;
    _layout.sidePanelWidth = 300.f;

    const sf::Vector2u winSize = _window.getSize();

    const float availableWidth =
        static_cast<float>(winSize.x) - _layout.sidePanelWidth - (_layout.margin * 3.f);

    const float availableHeight =
        static_cast<float>(winSize.y) - (_layout.margin * 2.f);

    _layout.boardPixelSize = std::min(availableWidth, availableHeight);

    if (_layout.boardPixelSize < 200.f)
        _layout.boardPixelSize = 200.f;

    _layout.cellSize = _layout.boardPixelSize / static_cast<float>(board_size - 1);

    _layout.boardOffsetX = _layout.margin;
    _layout.boardOffsetY = (static_cast<float>(winSize.y) - _layout.boardPixelSize) / 2.f;

    _layout.panelX = _layout.boardOffsetX + _layout.boardPixelSize + _layout.margin;
    _layout.panelY = _layout.margin;
    _layout.panelWidth = _layout.sidePanelWidth;
    _layout.panelHeight = static_cast<float>(winSize.y) - 2.f * _layout.margin;
}

// ----------------------------- //
// Get
// ----------------------------- //

sf::RenderWindow& Renderer::getWindow()
{
    return (this->_window);
}

const Layout& Renderer::getLayout() const
{
    return _layout;
}

const std::string& Renderer::getTitle() const
{
    return (this->_title);
}

unsigned int Renderer::getFps() const
{
    return (this->_fps);
}

unsigned int Renderer::getWidth() const
{
    return (this->_width);
}

unsigned int Renderer::getHeight() const
{
    return (this->_height);
}

// ----------------------------- //
// Create Goban
// ----------------------------- //

void Renderer::drawGobanBackground(sf::RenderWindow& window, const Layout& layout)
{
    sf::RectangleShape background(sf::Vector2f(layout.boardPixelSize, layout.boardPixelSize));

    background.setPosition(sf::Vector2f(layout.boardOffsetX, layout.boardOffsetY));
    background.setFillColor(sf::Color(205, 170, 125));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2.f);

    window.draw(background);
}

void Renderer::drawHorizontalLine(sf::RenderWindow& window, const Layout& layout, int row)
{
    sf::Vertex horizontal[2];

    horizontal[0].position = sf::Vector2f(layout.boardOffsetX, layout.boardOffsetY + row * layout.cellSize);
    horizontal[0].color = sf::Color::Black;
    horizontal[1].position = sf::Vector2f(layout.boardOffsetX + layout.boardPixelSize, layout.boardOffsetY + row * layout.cellSize);
    horizontal[1].color = sf::Color::Black;

    window.draw(horizontal, 2, sf::PrimitiveType::Lines);
}

void Renderer::drawVerticalLine(sf::RenderWindow& window, const Layout& layout, int col)
{
    sf::Vertex vertical[2];

    vertical[0].position = sf::Vector2f(layout.boardOffsetX + col * layout.cellSize, layout.boardOffsetY);
    vertical[0].color = sf::Color::Black;
    vertical[1].position = sf::Vector2f(layout.boardOffsetX + col * layout.cellSize, layout.boardOffsetY + layout.boardPixelSize);
    vertical[1].color = sf::Color::Black;

    window.draw(vertical, 2, sf::PrimitiveType::Lines);
}

void Renderer::drawHoshi(sf::RenderWindow& window, const Layout& layout)
{
    const int hoshiPositions[3] = {3, 9, 15};
    const float radius = layout.cellSize * 0.08f;

    for (int rowIndex = 0; rowIndex < 3; ++rowIndex)
    {
        for (int colIndex = 0; colIndex < 3; ++colIndex)
        {
            const int row = hoshiPositions[rowIndex];
            const int col = hoshiPositions[colIndex];

            sf::CircleShape hoshi(radius);
            hoshi.setOrigin(sf::Vector2f(radius, radius));
            hoshi.setPosition(sf::Vector2f(
                layout.boardOffsetX + col * layout.cellSize,
                layout.boardOffsetY + row * layout.cellSize
            ));
            hoshi.setFillColor(sf::Color::Black);

            window.draw(hoshi);
        }
    }
}

void Renderer::drawGoban(sf::RenderWindow& window, const Layout& layout, const int board_size)
{
    drawGobanBackground(window, layout);

    for (int i = 0; i < board_size; ++i)
    {
        drawHorizontalLine(window, layout, i);
        drawVerticalLine(window, layout, i);
    }
    drawHoshi(window, layout);
}