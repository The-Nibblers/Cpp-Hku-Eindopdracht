#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "PhysicsBody.h"
#include "Player.h"
#include "Parachutist.h"

#include <random>
#include <iostream>
#include <string>


Parachutist SpawnParachutist(
    int borderSizeX, int borderSizeY,
    float minSize, float maxSize,
    float minX, float maxX,
    float minY, float maxY,
    float minGravity, float maxGravity,
    float minMass, float maxMass,
    float minFriction, float maxFriction,
    float minSpeed, float maxSpeed,
    int minDir, int maxDir
) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> sizeDist(minSize, maxSize);
    std::uniform_real_distribution<float> xDist(minX, maxX);
    std::uniform_real_distribution<float> yDist(minY, maxY);
    std::uniform_real_distribution<float> gravityDist(minGravity, maxGravity);
    std::uniform_real_distribution<float> massDist(minMass, maxMass);
    std::uniform_real_distribution<float> frictionDist(minFriction, maxFriction);
    std::uniform_real_distribution<float> speedDist(minSpeed, maxSpeed);
    std::uniform_int_distribution<int> dirDist(minDir, maxDir);

    float enemyRadius = sizeDist(gen);
    float posX = xDist(gen);
    float posY = yDist(gen);
    float gravityMod = gravityDist(gen);
    float mass = massDist(gen);
    float friction = frictionDist(gen);
    float speed = speedDist(gen);
    int moveDir = dirDist(gen);

    Vector2 enemyTransform = Vector2(posX, posY);

    return Parachutist(enemyTransform, gravityMod, mass, friction, speed, borderSizeX, borderSizeY, enemyRadius, moveDir);
}

void AddRandomParachutist(std::vector<Parachutist>& parachutists,
    int borderSizeX, int borderSizeY,
    float minSize, float maxSize,
    float minX, float maxX,
    float minY, float maxY,
    float minGravity, float maxGravity,
    float minMass, float maxMass,
    float minFriction, float maxFriction,
    float minSpeed, float maxSpeed,
    int minDir, int maxDir) {
    Parachutist newP = SpawnParachutist(
        borderSizeX, borderSizeY,
        minSize, maxSize,
        minX, maxX,
        minY, maxY,
        minGravity, maxGravity,
        minMass, maxMass,
        minFriction, maxFriction,
        minSpeed, maxSpeed,
        minDir, maxDir
    );
    parachutists.push_back(newP);
}




int main()
{
    unsigned int borderSizeX = 800;
    unsigned int borderSizeY = 600;
    int playerRadius = 50.f;

    //enemy ranges
    float minEnemySizeRange = 30.f;
    float maxEnemySizeRange = 70.f;
    float minEnemyTransformX = 0;
    float maxEnemyTransformX = borderSizeX;
    float minEnemyTransformY = 0;
    float maxEnemyTransfromy = 0;
    float minEnemyGracityModifier = 0.1f;
    float maxEnemyGravityModifier = 0.3f;
    float minEnemyMass = 0.1f;
    float maxEnemyMass = 1;
    float minEnemyFrictionModifier = 0;
    float maxEnemyFrictionModifier = 1;
    float minEnemyMoveSpeed = 0.3f;
    float maxEnemyMoveSpeed = 1;
    int minEnemyMoveDir = 0;
    int maxEnemyMoveDir = 1;
    float enemyTimeBetweenSpawns = 4.f;

    std::vector<Parachutist> parachutists;

    //create player
    Vector2 playerTransform = Vector2(0,500);
    Player playerInstance = Player(playerTransform, 0, 1, 0.9f, 0.1f, borderSizeX, borderSizeY, playerRadius);


    sf::RenderWindow window(sf::VideoMode({ borderSizeX, borderSizeY }), "SFML window");

    //create player circle
    sf::CircleShape shape(playerRadius);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    sf::Clock spawnClock;

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

        // spawn enemy every x seconds
        if (spawnClock.getElapsedTime().asSeconds() > enemyTimeBetweenSpawns) {
            AddRandomParachutist(parachutists,
                borderSizeX, borderSizeY,
                minEnemySizeRange, maxEnemySizeRange,
                minEnemyTransformX, maxEnemyTransformX,
                minEnemyTransformY, maxEnemyTransfromy,
                minEnemyGracityModifier, maxEnemyGravityModifier,
                minEnemyMass, maxEnemyMass,
                minEnemyFrictionModifier, maxEnemyFrictionModifier,
                minEnemyMoveSpeed, maxEnemyMoveSpeed,
                minEnemyMoveDir, maxEnemyMoveDir
            );
            spawnClock.restart();
        }

        //get deltatime
        float deltaTime = clock.restart().asSeconds();

        //handle physics of all objects
        playerInstance.HandlePhysics(deltaTime);
        playerInstance.BorderDetection();

        for (Parachutist& p : parachutists) {
            p.HandlePhysics(deltaTime);
            p.BorderDetection();
            p.UpdateMovement();
        }

        // Update the position of the player
        Vector2 playerPos = playerInstance.GetPosition();
        sf::Vector2f playerPosition(playerPos.GetX(), playerPos.GetY());
        shape.setPosition(playerPosition);

        window.clear();

        //draw player
        window.draw(shape);

        // Draw each parachutist
        for (Parachutist& p : parachutists) {
            float radius = p.radius;
            sf::CircleShape enemyShape(radius);
            enemyShape.setFillColor(sf::Color::Blue);

            Vector2 enemyPos = p.GetPosition();
            sf::Vector2f enemyPosition(enemyPos.GetX(), enemyPos.GetY());
            enemyShape.setPosition(enemyPosition);

            window.draw(enemyShape);
        }
        window.display();
    }

    return 0;
}
