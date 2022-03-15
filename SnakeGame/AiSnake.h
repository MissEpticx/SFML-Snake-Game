#pragma once
#include "Snake.h"
class AiSnake : public Snake
{
protected:
	bool freeSpace = true;
public:
	AiSnake(sf::Vector2f Pos);
	bool CheckFreeSpace();
	void Update() override;
};