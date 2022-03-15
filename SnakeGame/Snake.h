#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class Food;
class Battery;

enum class eDirection
{
	North,
	South,
	East,
	West
};

struct snakeParts
{
	eDirection visibleDirection;
	sf::Vector2f partPosition;
};

class Snake
{
private:
	sf::Vector2f snakePosition;
protected:
	sf::Sprite snakeHead;
	sf::Sprite snakeBody;
	sf::Sprite snakeTail;

	sf::Clock timer_Battery;
	float batteryTime = 0;
	bool batteryIsActive {false};

	std::vector<sf::Vector2f>eBuzz;
	sf::Vector2f eBuzzPos;

	sf::Texture tHeadLeft;
	sf::Texture tBodyLeft;
	sf::Texture tTailLeft;
	sf::Texture tHeadRight;
	sf::Texture tBodyRight;
	sf::Texture tTailRight;
	sf::Texture tHeadUp;
	sf::Texture tBodyUp;
	sf::Texture tTailUp;
	sf::Texture tHeadDown;
	sf::Texture tBodyDown;
	sf::Texture tTailDown;

	std::list<sf::Vector2f>snakePart;
	eDirection direction {eDirection::East};

	int growAmount = 4;
	int snakeScore = 0;

	void ChangeDirection(eDirection dirChange);
	void Move();

	bool isAlive {true};
	bool noneAlive {false};

public:
	int GetSnakeScore() {return snakeScore;}
	bool GetIsAlive() {return isAlive;}

	Snake(sf::Vector2f Pos);

	virtual void Render(sf::RenderWindow& window);
	virtual void Update() = 0;

	void Die() {isAlive = false;}
	void AddElectric(sf::RenderWindow& window);
	bool GetBatteryActive() {return batteryIsActive;}
	void RestartTimer();
	void CheckTimer();
	void CheckConsumeCollision(std::vector<Food*>& consumables);
	void CheckBatteryCollision(std::vector<Battery*>& battery);
	void CheckElectricCollision(Snake& other);
	void CheckWallCollision(sf::RenderWindow& window);
	void CheckSelfCollision();
	void CheckCollision(Snake& other);
};