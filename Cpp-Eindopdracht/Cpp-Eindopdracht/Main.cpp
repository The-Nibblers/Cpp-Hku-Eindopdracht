#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "PhysicsBody.h"

#include <iostream>
#include <string>

int main()
{
    Vector2 transform;
    PhysicsBody newcircle = PhysicsBody(transform, 2, 1, 0.1f);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Create a clock to manage time step
    sf::Clock clock;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Get elapsed time since last frame
        float deltaTime = clock.restart().asSeconds();

        // Handle physics with deltaTime (adjusting physics for frame time)
        newcircle.HandlePhysics(deltaTime);

        // Update the position of the shape to match the updated position of newcircle
        Vector2 pos = newcircle.GetPosition();
        sf::Vector2f sfmlPosition(pos.GetX(), pos.GetY());
        shape.setPosition(sfmlPosition);

        // Debugging: Print the position of the shape to the console
        std::cout << "Shape position: (" << pos.GetX() << ", " << pos.GetY() << ")" << std::endl;

        // Clear screen
        window.clear();

        // Draw the shape
        window.draw(shape);

        // Update the window
        window.display();
    }

    return 0;
}
