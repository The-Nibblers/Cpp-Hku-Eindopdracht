#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "PhysicsBody.h"

#include <iostream>
#include <string>

int main()
{
    Vector2 transform;
    PhysicsBody newcircle = PhysicsBody(transform, 3, 2);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

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

        // Handle physics (this changes the position of newcircle)
        newcircle.HandlePhysics();

        // Update the position of the shape to match the updated position of the newcircle
        Vector2 pos = newcircle.GetPosition();
        sf::Vector2f sfmlPosition(pos.GetX(), pos.GetY());
        shape.setPosition(sfmlPosition);

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
