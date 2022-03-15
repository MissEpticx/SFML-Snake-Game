#include "Snake.h"
#include "Food.h"
#include "Battery.h"
#include <iostream>
#include "Consumables.h"

//officially sets the size of each snake part, and electric part to a specific value
constexpr int snkSize{ 25 };
constexpr int electricSize{ 125 };

Snake::Snake(sf::Vector2f Pos)
{
	//pushes a new snake part into a vector & gives it a position that allows us to make checks against it later on
	snakePosition = Pos;
	snakePart.push_back(snakePosition);

	//loads all required snake textures
	if (!tHeadLeft.loadFromFile("HeadLeft.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tTailLeft.loadFromFile("TailLeft.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tBodyLeft.loadFromFile("BodyLeft.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tHeadRight.loadFromFile("HeadRight.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tBodyRight.loadFromFile("BodyRight.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tTailRight.loadFromFile("TailRight.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tHeadUp.loadFromFile("HeadUp.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tTailUp.loadFromFile("TailUp.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tBodyUp.loadFromFile("BodyUp.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tHeadDown.loadFromFile("HeadDown.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tBodyDown.loadFromFile("BodyDown.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
	if (!tTailDown.loadFromFile("TailDown.png"))
	{
		std::cout << "Failed to Load Texture\n" << std::endl;
		return;
	}
}

//Tells the snake that a new eDirection becomes its direction to move to
void Snake::ChangeDirection(eDirection dirChange)
{
	direction = dirChange;
}

//Renders the snake and its textures if snake is alive
void Snake::Render(sf::RenderWindow& window)
{
	snakeHead.setTexture(tHeadLeft);
	snakeBody.setTexture(tBodyLeft);
	snakeTail.setTexture(tTailLeft);

	for (sf::Vector2f& s : snakePart)
	{
		if (direction == eDirection::North)
		{
			snakeHead.setTexture(tHeadUp);
			snakeBody.setTexture(tBodyUp);
			snakeTail.setTexture(tTailUp);
		}
		if (direction == eDirection::East)
		{
			snakeHead.setTexture(tHeadRight);
			snakeBody.setTexture(tBodyRight);
			snakeTail.setTexture(tTailRight);
		}
		if (direction == eDirection::South)
		{
			snakeHead.setTexture(tHeadDown);
			snakeBody.setTexture(tBodyDown);
			snakeTail.setTexture(tTailDown);
		}
		if (direction == eDirection::West)
		{
			snakeHead.setTexture(tHeadLeft);
			snakeBody.setTexture(tBodyLeft);
			snakeTail.setTexture(tTailLeft);
		}
	}

	if (isAlive == true)
	{
		for (sf::Vector2f& s : snakePart)
		{
			if (s == snakePart.front())
			{
				snakeHead.setPosition(s);
				window.draw(snakeHead);
			}
			else if (s == snakePart.back())
			{
				snakeTail.setPosition(s);
				window.draw(snakeTail);
			}
			else
			{
				snakeBody.setPosition(s);
				window.draw(snakeBody);
			}
		}
	}
}

//checks to see if snakes collide with other snake battery effect. If it does, it dies
void Snake::CheckElectricCollision(Snake& other)
{
	if (this->GetIsAlive() && this->GetBatteryActive())
	{
		if (!other.GetIsAlive())
		{
			return;
		}
		for (sf::Vector2f otherPartsPos : other.snakePart)
		{
			for (sf::Vector2f buzzPos : eBuzz)
			{
				if (other.snakePart.front() == buzzPos)
				{
					other.Die();
				}
			}
		}
	}
	if (other.GetIsAlive() && other.GetBatteryActive())
	{
		if (!this->GetIsAlive())
		{
			return;
		}
		for (sf::Vector2f thisPartsPos : this->snakePart)
		{
			for (sf::Vector2f buzzPos : eBuzz)
			{
				if (this->snakePart.front() == buzzPos)
				{
					this->Die();
				}
			}
		}
	}
}

//Creates a collidable "aura" around the snake that consumed a battery
void Snake::AddElectric(sf::RenderWindow& window)
{
	sf::RectangleShape Buzz(sf::Vector2f (electricSize, electricSize));
	Buzz.setFillColor(sf::Color (50, 100, 200, 20));
	for (sf::Vector2f buzzPos : snakePart)
	{
		Buzz.setPosition(buzzPos.x - (snkSize * 2), buzzPos.y - (snkSize * 2));
		eBuzzPos = sf::Vector2f(buzzPos.x - (snkSize * 2), buzzPos.y - (snkSize * 2));
		eBuzz.push_back(eBuzzPos);
		eBuzzPos = sf::Vector2f(buzzPos.x + (snkSize * 2), buzzPos.y + (snkSize * 2));
		eBuzz.push_back(eBuzzPos);

		window.draw(Buzz);
	}
}

//Resets the timer for the next battery to work correctly
void Snake::RestartTimer()
{
	timer_Battery.restart();
}

//Allows the battery to only be active for a set amount of time
void Snake::CheckTimer()
{
	batteryTime = timer_Battery.getElapsedTime().asMilliseconds();
	if (batteryTime >=  5000)
	{
		batteryIsActive = false;
		eBuzz.empty();
	}
}

//Checks to see if a snake collides with battery, adds the effect and bonus points if it does
void Snake::CheckBatteryCollision(std::vector<Battery*>& battery)
{
	for (Battery* b : battery)
	{
		if (b->GetIsActive())
		{
			if (snakePart.front() == b->getPosition())
			{
				b->Die();
				batteryIsActive = true;
				RestartTimer();
				snakeScore = snakeScore + b->GetScore();
			}
		}
	}
}

//checks to see if a snake collides with a consumable, add points and grow amount if it does
void Snake::CheckConsumeCollision(std::vector<Food*>& consumables)
{
	for (Food* f : consumables)
	{
		if (f->GetIsActive())
		{
			if (snakePart.front() == f->getPosition())
			{
				f->Die();
				growAmount = f->GetGrowAmount();
				snakeScore = snakeScore + f->GetScore();
			}
		}
	}
}

//Check to see if snake hits the wall. If it does, it dies
void Snake::CheckWallCollision(sf::RenderWindow& window)
{
	if (snakePart.front().x > 750 || snakePart.front().x < 25 || snakePart.front().y > 850 || snakePart.front().y < 25)
	{
		Die();
	}
}

//Checks the head of the snake against every part of itself to see if they collide. If it does, it dies
void Snake::CheckSelfCollision()
{
	bool firstLoop{ true };
	for (sf::Vector2f thisPartsPos : snakePart)
	{
		if (firstLoop == true)
		{
			firstLoop = false;
			continue;
		}
		if (snakePart.front() == thisPartsPos)
		{
			Die();
		}
	}
}

//Checks the head of each snake against each part of any other living snakes for collision. If they do, they die.
void Snake::CheckCollision(Snake& other)
{
	if (!this->GetIsAlive())
	{
		return;
	}
	if (!other.GetIsAlive())
	{
		return;
	}
	for (sf::Vector2f otherPartsPos : other.snakePart)
	{
		for (sf::Vector2f thisPartsPos : snakePart)
		{

			if (this->snakePart.front() == otherPartsPos)
			{
				this->Die();
			}
			else if (other.snakePart.front() == thisPartsPos)
			{
				other.Die();
			}
			else if (otherPartsPos == this->snakePart.front() && thisPartsPos == other.snakePart.front())
			{
				other.Die();
				this->Die();
			}
		}
	}
}

//Allows the snakes to move, and grow correctly if they consume something with a grow value
void Snake::Move()
{
	sf::Vector2f snakePosition = snakePart.front();

	if (isAlive == true)
	{
		switch (direction)
		{
		case eDirection::North:
			snakePosition.y -= snkSize;
			break;
		case eDirection::South:
			snakePosition.y += snkSize;
			break;
		case eDirection::East:
			snakePosition.x += snkSize;
			break;
		case eDirection::West:
			snakePosition.x -= snkSize;
			break;
		default:
			break;
		}

		snakePart.push_front(snakePosition);

		if (growAmount > 0)
		{
			growAmount--;
		}
		else
		{
			snakePart.pop_back();
		}
	}
}