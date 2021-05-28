#include <SFML/Graphics.hpp>
#include "GameWrapper.h"
#include <string>
#include <windows.h>

int main()
{
    sf::Texture texture;

    if (!texture.loadFromFile("images/spaceship.png", sf::IntRect(0, 0, 64, 64))) {
        return 1;
    }

    const int windowWidth = 1000, windowHeight = 1000;

    const float windowRatio = static_cast<float>(windowWidth) / windowHeight;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "CLX TANK"/*, sf::Style::Fullscreen*/);
    
    window.setPosition(sf::Vector2i(0, 0));

    GameWrapper *gameWrapper = new GameWrapper();

    gameWrapper->setWindow(window);

    Player* playerOne = new Player();

    playerOne->setPosition(400.f, 400.f);

    playerOne->setTexture(texture);

    Controls* playerOneControls = new Controls();

    playerOneControls->setMovementLimits(0.f, static_cast<float>(windowWidth), static_cast<float>(windowHeight), 0.f);
    
    playerOneControls->setMoveKeys(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);

    playerOneControls->setMovementFactor(0.5 * windowRatio, 0.5 * windowRatio);
        
    playerOne->setControls(*playerOneControls);

    gameWrapper->addPlayer(*playerOne);
    
    while (gameWrapper->isRuning())
    {
        gameWrapper->bindInputs();
        gameWrapper->update();
        gameWrapper->render();
        gameWrapper->clearAndReallocateResources();
    }

    return 0;
}