#pragma once
#include "Snake.h"

//PlayerSnake is inherited from my Snake class
class PlayerSnake : public Snake
{
public:
	PlayerSnake(sf::Vector2f Pos);
	void Update() override;
};