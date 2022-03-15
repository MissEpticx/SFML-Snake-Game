#pragma once
#include "Consumables.h"

//Battery is inherited from my Consumables class
class Battery : public Consumables
{
private:
	sf::Texture tBattery;
public:
	Battery(int scr);
	void BatterySpawn();
	void Render(sf::RenderWindow& window);
};