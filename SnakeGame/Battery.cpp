#include "Battery.h"
#include <iostream>

Battery::Battery(int scr) :
	Consumables(scr)
{
	//Loads texture from file
	if (!tBattery.loadFromFile("Battery.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
}

void Battery::BatterySpawn()
{
	//randomly sets a position within the gamewindow, set to a grid size equal to the size of the snake
	int x = rand() % 28 * 25 + 25;
	int y = rand() % 32 * 25 + 25;
	consumePos = sf::Vector2f((float)x, (float)y);
	isActive = true;
}

void Battery::Render(sf::RenderWindow& window)
{
	sf::RectangleShape battery(sf::Vector2f(25, 25));
	battery.setTexture(&tBattery);
	battery.setPosition(consumePos);
	window.draw(battery);
}