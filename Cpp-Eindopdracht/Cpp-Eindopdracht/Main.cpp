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

void RemoveParachutistFromVector(std::vector<Parachutist>& vector, const Parachutist& parachutistInstance) {
    vector.erase(std::remove(vector.begin(), vector.end(), parachutistInstance), vector.end());
}





int main()
{
    unsigned int borderSizeX = 800;
    unsigned int borderSizeY = 600;
    float playerRadius = 50.f;
    int score{};


    //enemy ranges
    float minEnemySizeRange = 20.f;
    float maxEnemySizeRange = 50.f;
    float minEnemyTransformX = 0;
    float maxEnemyTransformX = borderSizeX - 100;
    float minEnemyTransformY = 0;
    float maxEnemyTransfromy = 0;
    float minEnemyGracityModifier = 0.1f;
    float maxEnemyGravityModifier = 0.3f;
    float minEnemyMass = 1;
    float maxEnemyMass = 2.5f;
    float minEnemyFrictionModifier = 0;
    float maxEnemyFrictionModifier = 1;
    float minEnemyMoveSpeed = 0.3f;
    float maxEnemyMoveSpeed = 1;
    int minEnemyMoveDir = 0;
    int maxEnemyMoveDir = 1;
    float enemyTimeBetweenSpawns = 4.f;

    std::vector<Parachutist> parachutists;

    int gameOverCounter = 0;
    int maxMisses = 5;
    bool gameOver = false;

    //create player
    Vector2 playerTransform = Vector2(borderSizeX / 2,borderSizeY * 0.9f);
    Player playerInstance = Player(playerTransform, 0, 1, 0.9f, 0.1f, borderSizeX, borderSizeY, playerRadius);


    sf::RenderWindow window(sf::VideoMode({ borderSizeX, borderSizeY }), "SFML window");

    //create player circle
    sf::CircleShape shape(playerRadius);
    shape.setFillColor(sf::Color::Green);
    sf::Vector2 playerOrgin(playerRadius, playerRadius);
    shape.setOrigin(playerOrgin);

    //create clocks
    sf::Clock clock;
    sf::Clock spawnClock;

    //create text
    sf::Font font;
    if (!font.openFromFile("D:/github/Cpp-Hku-Eindopdracht/Cpp-Eindopdracht/Fonts/arial.ttf"))
    {
        std::cout << "font does NOT work";
    }
    sf::Text scoreText(font);
    scoreText.setCharacterSize(45);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setString("0");

    sf::Text gameOverText(font);
    gameOverText.setCharacterSize(45);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //handle player input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            
            playerInstance.MoveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {

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

        for (auto it = parachutists.begin(); it != parachutists.end(); ) {
            it->HandlePhysics(deltaTime);
            it->BorderDetection();
            it->UpdateMovement();

            if (it->markedForDeletion) {
                it = parachutists.erase(it);
                gameOverCounter++;
                if (gameOverCounter >= maxMisses) {
                    gameOver = true;
                }
            }
            else if (playerInstance.CollisionDetection(playerInstance.transform, it->transform, playerRadius, it->radius)) {
                it = parachutists.erase(it);
                score++;
                scoreText.setString(std::to_string(score));
            }
            else {
                ++it;
            }
        }



        // Update the position of the player
        Vector2 playerPos = playerInstance.GetPosition();
        sf::Vector2f playerPosition(playerPos.GetX(), playerPos.GetY());
        shape.setPosition(playerPosition);

        window.clear();
        if (!gameOver)
        {
            //draw player
            window.draw(shape);

            // Draw each parachutist
            for (Parachutist& p : parachutists) {
                float radius = p.radius;
                sf::CircleShape enemyShape(radius);
                enemyShape.setFillColor(sf::Color::Blue);

                sf::Vector2 enemyOrgin(radius, radius);
                enemyShape.setOrigin(enemyOrgin);

                Vector2 enemyPos = p.GetPosition();
                sf::Vector2f enemyPosition(enemyPos.GetX(), enemyPos.GetY());
                enemyShape.setPosition(enemyPosition);

                window.draw(enemyShape);
            }

            //draw score text
            window.draw(scoreText);
        }
        else {
            sf::Vector2f gameOverTextPos(borderSizeX * 0.5f, borderSizeY * 0.5f);
            gameOverText.setPosition(gameOverTextPos);
            window.draw(gameOverText);
            window.draw(scoreText);
        }

        window.display();
    }

    return 0;
}
