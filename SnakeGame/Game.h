#pragma once
#include <vector>

class Snake;
class Food;
class Battery;
class PlayerSnake;

class Game
{
protected:
	std::vector<Snake*>snakeVector;
	std::vector<Food*>consumeVector;
	std::vector<Battery*>batteryVector;
	bool noSnakeLiving = false;
public:
	void Run();
};