#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "PhysicsBody.h"
#include "Player.h"

#include <iostream>
#include <string>

int main()
{
    //create gravity test circle
    Vector2 transform;
    Player playerInstance = Player(transform, 0, 1, 0.1f, 0.1f);


    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");

    //create circle
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);



    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //handle player input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan(sf::Keyboard::Key::A))) {
            
            playerInstance.MoveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan(sf::Keyboard::Key::D))) {

            playerInstance.MoveRight();
        }

        //get deltatime
        float deltaTime = clock.restart().asSeconds();

        //handle physics of all objects
        playerInstance.HandlePhysics(deltaTime);

        // Update the position of the shape to match the updated position of newcircle
        Vector2 pos = playerInstance.GetPosition();
        sf::Vector2f sfmlPosition(pos.GetX(), pos.GetY());
        shape.setPosition(sfmlPosition);


        window.clear();

        //draw all shapes
        window.draw(shape);

        window.display();
    }

    return 0;
}
