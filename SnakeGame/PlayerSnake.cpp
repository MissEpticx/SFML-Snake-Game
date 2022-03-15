#include "PlayerSnake.h"
#include <iostream>

//Creates a player constructor
PlayerSnake::PlayerSnake(sf::Vector2f Pos) : Snake(Pos)
{
}

void PlayerSnake::Update()
{
    //Clock allows me to update movement in a shorter time, allowing for faster and smoother movement
    sf::Clock clock;

    //When player presses a directional key on a keyboard, the snake will move to the associated direction
    do
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != eDirection::South)
        {
            ChangeDirection(eDirection::North);
            break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != eDirection::North)
        {
            ChangeDirection(eDirection::South);
            break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != eDirection::East)
        {
            ChangeDirection(eDirection::West);
            break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != eDirection::West)
        {
            ChangeDirection(eDirection::East);
            break;
        }
    } while (clock.getElapsedTime().asMilliseconds() < 200);

    //allows the snake to move (called from the snake.cpp)
    Move();
}