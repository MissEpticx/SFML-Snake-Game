#pragma once
#include "Consumables.h"

enum class eConsumeType
{
	Mouse = 1,
	Squirrel = 2,
	Rabbit = 3
};

class Food : public Consumables
{
private:
	eConsumeType consumeType{ eConsumeType::Mouse };
	int defineType{ 1 };
	int growAmount{ 1 };
protected:
	sf::Texture tMouse;
	sf::Texture tSquirrel;
	sf::Texture tRabbit;
public:
	Food(int dType, int grow, int scr);
	int GetGrowAmount() { return growAmount; }
	void FoodSpawn();
	void Render(sf::RenderWindow& window);
};

