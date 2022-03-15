#include "Food.h"
#include <iostream>

Food::Food(int dType, int grow, int scr) :
	Consumables(scr),
	defineType(dType),
	growAmount(grow)
{
	//Loads textures from file
	if (!tMouse.loadFromFile("BigMouse.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tSquirrel.loadFromFile("Squirrel.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tRabbit.loadFromFile("Rabbit.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
}

void Food::FoodSpawn()
{
	//randomly sets a position within the gamewindow, set to a grid size equal to the size of the snake
	int x = rand() % 28 * 25 + 25;
	int y = rand() % 32 * 25 + 25;
	consumePos = sf::Vector2f((float)x, (float)y);

	//Randomly chooses a number between 1 and 6
	defineType = rand() % 6 + 1;

	//Sets the consumeType based on the random number above
	//this allows for a different probability for each type to spawn
	if (defineType == 1 || defineType == 2 || defineType == 3)
	{
		consumeType = eConsumeType::Mouse;
	}
	else if (defineType == 4 || defineType == 5)
	{
		consumeType = eConsumeType::Squirrel;
	}
	else if (defineType == 6)
	{
		consumeType = eConsumeType::Rabbit;
	}
	else
	{
		std::cout << "Define Type Error" << std::endl;
	}

	//Sets a different score value and grow amount value
	//depending on which type the consumable is spawning as
	switch (consumeType)
	{
	case eConsumeType::Mouse:
		growAmount = 1;
		score = 5;
		break;
	case eConsumeType::Squirrel:
		growAmount = 2;
		score = 10;
		break;
	case eConsumeType::Rabbit:
		growAmount = 3;
		score = 15;
		break;
	default:
		break;
	}
	isActive = true;
}

void Food::Render(sf::RenderWindow& window)
{
	sf::RectangleShape food(sf::Vector2f(25, 25));
	
	//Changes the texture of the consumable based on its type
	if (consumeType == eConsumeType::Mouse)
	{
		food.setTexture(&tMouse);
	}
	if (consumeType == eConsumeType::Squirrel)
	{
		food.setTexture(&tSquirrel);
	}
	if (consumeType == eConsumeType::Rabbit)
	{
		food.setTexture(&tRabbit);
	}
	food.setPosition(consumePos);
	window.draw(food);
}
