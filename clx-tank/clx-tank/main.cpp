#include <SFML/Graphics.hpp>
#include "GameWrapper.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1900, 1050), "CLX TANK"/*, sf::Style::Fullscreen*/);
    
    window.setPosition(sf::Vector2i(0, 0));

    GameWrapper *gameWrapper = new GameWrapper();

    gameWrapper->setWindow(window);

    Player* playerOne = new Player();

    playerOne->setPosition(400.f, 400.f);

    Controls* playerOneControls = new Controls();
    
    playerOneControls->setMoveKeys(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);

    playerOne->setControls(*playerOneControls);

    gameWrapper->addPlayer(*playerOne);
    
    while (gameWrapper->isRuning())
    {
        gameWrapper->bindInputs();
        gameWrapper->update();
        gameWrapper->render();
    }

    return 0;
}