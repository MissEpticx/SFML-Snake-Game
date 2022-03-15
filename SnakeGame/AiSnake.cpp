#include "AiSnake.h"

AiSnake::AiSnake(sf::Vector2f Pos) : Snake(Pos)
{
}

//Checks to see if the next space over is clear of potential collisions
bool AiSnake::CheckFreeSpace()
{
	freeSpace = true;

	if (snakePart.front().y < 100 && direction == eDirection::North)
	{
		freeSpace = false;
	}
	if (snakePart.front().x > 600 && direction == eDirection::East)
	{
		freeSpace = false;
	}
	if (snakePart.front().y > 700 && direction == eDirection::South)
	{
		freeSpace = false;
	}
	if (snakePart.front().x < 100 && direction == eDirection::West)
	{
		freeSpace = false;
	}
	else
	{
		freeSpace = true;
	}

	for (sf::Vector2f aiPartsPos : snakePart)
	{
		if (aiPartsPos.y == (snakePart.front().y + 25))
		{
			freeSpace = false;
		}
		else if (aiPartsPos.y == (snakePart.front().y - 25))
		{
			freeSpace = false;
		}
		else if (aiPartsPos.x == (snakePart.front().x + 25))
		{
			freeSpace = false;
		}
		else if (aiPartsPos.x == (snakePart.front().x - 25))
		{
			freeSpace = false;
		}
		else
		{
			freeSpace = true;
		}
	}
	return freeSpace;
}

void AiSnake::Update()
{
	eDirection newDirection = eDirection::East;

	//Allows the snake to move in a random direction if it is
	//not going to collide with itself
	switch (rand() % 4)
	{
	case 0:
		if (direction != eDirection::South)
		{
			newDirection = eDirection::North;
		}
		break;
	case 1:
		if (direction != eDirection::West)
		{
			newDirection = eDirection::East;
		}
		break;
	case 2:
		if (direction != eDirection::North)
		{
			newDirection = eDirection::South;
		}
		break;
	case 3:
		if (direction != eDirection::East)
		{
			newDirection = eDirection::West;
		}
		break;
	default:
		break;
	}

	//check if North is possible
	if (newDirection == eDirection::North && direction != eDirection::South && CheckFreeSpace())
	{
		direction = eDirection::North;
	}
	
	//check if East is possible
	else if (newDirection == eDirection::East && direction != eDirection::West && CheckFreeSpace())
	{
		direction = eDirection::East;
	}

	//check if South is possible
	else if (newDirection == eDirection::South && direction != eDirection::North && CheckFreeSpace())
	{
		direction = eDirection::South;
	}

	//check if West is possible
	else if (newDirection == eDirection::West && direction != eDirection::East && CheckFreeSpace())
	{
		direction = eDirection::West;
	}

	Move();
}