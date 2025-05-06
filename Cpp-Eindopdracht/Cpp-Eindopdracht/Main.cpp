#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "PhysicsBody.h"
#include "Player.h"
#include "Parachutist.h"

#include <iostream>
#include <string>

int main()
{
    unsigned int borderSizeX = 800;
    unsigned int borderSizeY = 600;
    int playerRadius = 50.f;

    std::vector<Parachutist> parachutists;

    int enemyRadius = 50.f;
    Vector2 enemytransform = Vector2(200,0);
    Parachutist parachuteInstance = Parachutist(enemytransform, 0.1f, 1, 0.8f, 0.3f, borderSizeX, borderSizeY, playerRadius, true);

    //create player
    Vector2 playerTransform = Vector2(0,500);
    Player playerInstance = Player(playerTransform, 0, 1, 0.9f, 0.1f, borderSizeX, borderSizeY, playerRadius);


    sf::RenderWindow window(sf::VideoMode({ borderSizeX, borderSizeY }), "SFML window");

    //create player circle
    sf::CircleShape shape(playerRadius);
    shape.setFillColor(sf::Color::Green);

    sf::CircleShape shape2(enemyRadius);
    shape2.setFillColor(sf::Color::Blue);



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
        playerInstance.BorderDetection();

        parachuteInstance.HandlePhysics(deltaTime);
        parachuteInstance.BorderDetection();
        parachuteInstance.UpdateMovement();

        // Update the position of the player
        Vector2 playerPos = playerInstance.GetPosition();
        sf::Vector2f sfmlPosition(playerPos.GetX(), playerPos.GetY());
        shape.setPosition(sfmlPosition);

        Vector2 enemyPos = parachuteInstance.GetPosition();
        sf::Vector2f sfmlPosition2(enemyPos.GetX(), enemyPos.GetY());
        shape2.setPosition(sfmlPosition2);


        window.clear();

        //draw all shapes
        window.draw(shape);
        window.draw(shape2);

        window.display();
    }

    return 0;
}
