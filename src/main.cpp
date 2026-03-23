#include "./../include/core/Game.hpp"
#include "./../include/core/Board.hpp"
#include "./../include/render/Renderer.hpp"

int main(void)
{
    Game game = Game();
    Board board = Board(19, 19);
    Renderer render = Renderer();

    while (render.getWindow().isOpen())
    {
        while (const std::optional event = render.getWindow().pollEvent())
        {
            if (event->is<sf::Event::Closed>() || (event->getIf<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
            {
                render.getWindow().close();
            }
            else if ((event->getIf<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R))
            {
                game.resetGame();
                board.resetBoard();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)));
                render.getWindow().setView(sf::View(visibleArea));
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    render.calculateLayout(board.getRows());

                    board.setRow(-1);
                    board.setCol(-1);

                    if (board.getBoardPositionFromMouse(render.getLayout(), mousePressed->position.x, mousePressed->position.y))
                    {
                        if (board.getCell(board.getRow(), board.getCol()) == Cell::Empty && game.getWinner() == Winner::None)
                            game.playMove(board);
                    }
                }
            }
        }

        render.calculateLayout(board.getRows());

        render.getWindow().clear(sf::Color(210, 180, 140));
        render.drawGoban(render.getWindow(), render.getLayout(), board.getRows());
        render.drawStones(board, render.getLayout());
        if (game.getWinner() == Winner::None) 
            render.stonePreveiw(board, game, game.getCurrentPlayer());
        render.drawInfos(render.getWindow(), render.getLayout(), game);
        render.getWindow().display();
    }
}