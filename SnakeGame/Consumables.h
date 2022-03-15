#pragma once
#include <SFML/Graphics.hpp>

class Consumables
{
protected:
	sf::Vector2f consumePos;
	int score{ 5 };
	bool isActive{ false };
public:
	sf::Vector2f getPosition() const {return consumePos;}
	int GetScore() {return score;}
	Consumables(int scr);
	bool GetIsActive() const { return isActive; }
	void Die() { isActive = false; }
};