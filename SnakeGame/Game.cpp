#include <iostream>
#include <time.h>
#include "Game.h"
#include "Food.h"
#include "Menu.h"
#include "Battery.h"
#include "AiSnake.h"
#include "PlayerSnake.h"
#include <SFML/Graphics.hpp>

void Game::Run()
{
    //allows for true random to occur
    srand(time(NULL));

    //creates and sets my background texture
    sf::Texture background;
    if (!background.loadFromFile("SandBackground.png"))
    {
        std::cout << "Failed to Load Texture\n" << std::endl;
        return;
    }
    sf::Sprite Background;
    Background.setTexture(background);

    sf::RenderWindow window(sf::VideoMode(1100, 900), "C++ Snake ICA : A0208468");

    //pushes back 1 playable snake, and 1 ai snake into a vector
    snakeVector.push_back(new PlayerSnake(sf::Vector2f(400.0f, 450.0f)));
    snakeVector.push_back(new AiSnake(sf::Vector2f(300.0f, 500.0f)));
    snakeVector.push_back(new AiSnake(sf::Vector2f(200.0f, 200.0f)));

    //Create and Load the Title on the right hand panel
    sf::Font fTitle;
    fTitle.loadFromFile("Waffle Crisp.ttf");
    sf::Text Title;
    Title.setString("ZAPPY SNAKES");
    Title.setFont(fTitle);
    Title.setFillColor(sf::Color::Cyan);
    Title.setOutlineColor(sf::Color::Black);
    Title.setOutlineThickness(2);
    Title.setPosition(sf::Vector2f(840, 50));
    Title.setCharacterSize(50);
    Title.setOrigin(25, 25);

    //pushes back 4 consumables into a vector
    for (int i = 0; i < 4; i++)
    {
        consumeVector.push_back(new Food(1, 1, 5));
    }

    //pushes back 1 battery into a vector
    batteryVector.push_back(new Battery(25));

    //clock handles game time, allowing me to alter game speeds
    //gameClock allows me to initialise a timer displayable to the player
    sf::Clock clock;
    sf::Clock gameClock;

    // Main loop that continues until we call window.close()
    while (window.isOpen())
    {
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        //Checks the timer if the battery is consumed by any snake
        for (Snake* snake : snakeVector)
        {
            snake->Update();
            if (snake->GetBatteryActive())
            {
                snake->CheckTimer();
            }
        }
        
        //Randomly spawns Battery and food consumables, constantly checking if all possible consumables are already spawned
        if (rand() % 8 == 0)
        {
            for (Battery* battery : batteryVector)
            {
                if (!battery->GetIsActive())
                {
                    battery->BatterySpawn();
                    break;
                }
            }
            for (Food* consume : consumeVector)
            {
                if (!consume->GetIsActive())
                {
                    consume->FoodSpawn();
                    break;
                }
            }
        }

        //Checks collisions with other snakes, if snake 1 hits snake 2 or vice versa
		for (Snake* snake : snakeVector)
		{
            if (snake->GetIsAlive() == true)
            {
                for (int snakeIndex1 = 0; snakeIndex1 < snakeVector.size(); snakeIndex1++)
                {
                    for (int snakeIndex2 = snakeIndex1 + 1; snakeIndex2 < snakeVector.size(); snakeIndex2++)
                    {
                        snakeVector[snakeIndex1]->CheckCollision(*snakeVector[snakeIndex2]);
                    }
                    for (int snakeIndex3 = snakeIndex1 + 1; snakeIndex3 < snakeVector.size(); snakeIndex3++)
                    {
                        snakeVector[snakeIndex1]->CheckCollision(*snakeVector[snakeIndex3]);
                    }
                }
                for (int snakeIndex2 = 0; snakeIndex2 < snakeVector.size(); snakeIndex2++)
                {
                    for (int snakeIndex1 = snakeIndex2 + 1; snakeIndex1 < snakeVector.size(); snakeIndex1++)
                    {
                            snakeVector[snakeIndex2]->CheckCollision(*snakeVector[snakeIndex1]);
                    }
                    for (int snakeIndex3 = snakeIndex2 + 1; snakeIndex3 < snakeVector.size(); snakeIndex3++)
                    {
                        snakeVector[snakeIndex2]->CheckCollision(*snakeVector[snakeIndex3]);
                    }
                }
                for (int snakeIndex3 = 0; snakeIndex3 < snakeVector.size(); snakeIndex3++)
                {
                    for (int snakeIndex1 = snakeIndex3 + 1; snakeIndex1 < snakeVector.size(); snakeIndex1++)
                    {
                        snakeVector[snakeIndex3]->CheckCollision(*snakeVector[snakeIndex1]);
                    }
                    for (int snakeIndex2 = snakeIndex3 + 1; snakeIndex2 < snakeVector.size(); snakeIndex2++)
                    {
                        snakeVector[snakeIndex3]->CheckCollision(*snakeVector[snakeIndex2]);
                    }
                }
            }
		}

        //Checks battery effect collisions with other snakes, if snake 1 hits snake 2 or vice versa
        for (Snake* snake : snakeVector)
        {
            if (snake->GetIsAlive() == true && snake->GetBatteryActive() == true)
            {
                for (int snakeIndex1 = 0; snakeIndex1 < snakeVector.size(); snakeIndex1++)
                {
                    for (int snakeIndex2 = snakeIndex1 + 1; snakeIndex2 < snakeVector.size(); snakeIndex2++)
                    {
                        snakeVector[snakeIndex1]->CheckElectricCollision(*snakeVector[snakeIndex2]);
                    }
                    for (int snakeIndex3 = snakeIndex1 + 1; snakeIndex3 < snakeVector.size(); snakeIndex3++)
                    {
                        snakeVector[snakeIndex1]->CheckElectricCollision(*snakeVector[snakeIndex3]);
                    }
                }
                for (int snakeIndex2 = 0; snakeIndex2 < snakeVector.size(); snakeIndex2++)
                {
                    for (int snakeIndex1 = snakeIndex2 + 1; snakeIndex1 < snakeVector.size(); snakeIndex1++)
                    {
                        snakeVector[snakeIndex2]->CheckElectricCollision(*snakeVector[snakeIndex1]);
                    }
                    for (int snakeIndex3 = snakeIndex2 + 1; snakeIndex3 < snakeVector.size(); snakeIndex3++)
                    {
                        snakeVector[snakeIndex2]->CheckElectricCollision(*snakeVector[snakeIndex3]);
                    }
                }
                for (int snakeIndex3 = 0; snakeIndex3 < snakeVector.size(); snakeIndex3++)
                {
                    for (int snakeIndex1 = snakeIndex3 + 1; snakeIndex1 < snakeVector.size(); snakeIndex1++)
                    {
                        snakeVector[snakeIndex3]->CheckElectricCollision(*snakeVector[snakeIndex1]);
                    }
                    for (int snakeIndex2 = snakeIndex3 + 1; snakeIndex2 < snakeVector.size(); snakeIndex2++)
                    {
                        snakeVector[snakeIndex3]->CheckElectricCollision(*snakeVector[snakeIndex2]);
                    }
                }
            }
        }

        //Checks for snake collisions
        for (Snake* snake : snakeVector)
        {
            if (snake->GetIsAlive() == true)
            {
                snake->CheckSelfCollision();
                snake->CheckWallCollision(window);
                snake->CheckConsumeCollision(consumeVector);
                snake->CheckBatteryCollision(batteryVector);
            }
        }

        //Displays Player Score to the right hand side panel
        int playerScore = snakeVector[0]->GetSnakeScore();
        sf::Text Score;
        Score.setString("Player: " + std::to_string(playerScore) + '\n');
        Score.setFont(fTitle);
        Score.setFillColor(sf::Color(180, 20, 255));
        Score.setOutlineColor(sf::Color::Black);
        Score.setOutlineThickness(1);
        Score.setPosition(sf::Vector2f(900, 150));
        Score.setCharacterSize(30);
        Score.setOrigin(15, 15);

        //Displays Ai Snake Score to the right hand side panel
        int jeffScore = snakeVector[1]->GetSnakeScore();
        sf::Text JeffScore;
        JeffScore.setString("Jeffery: " + std::to_string(jeffScore) + '\n');
        JeffScore.setFont(fTitle);
        JeffScore.setFillColor(sf::Color::Cyan);
        JeffScore.setOutlineColor(sf::Color::Black);
        JeffScore.setOutlineThickness(1);
        JeffScore.setPosition(sf::Vector2f(900, 190));
        JeffScore.setCharacterSize(30);
        JeffScore.setOrigin(15, 15);

        //Displays Ai Snake Score to the right hand side panel
        int keithScore = snakeVector[2]->GetSnakeScore();
        sf::Text KeithScore;
        KeithScore.setString("Keith: " + std::to_string(keithScore) + '\n');
        KeithScore.setFont(fTitle);
        KeithScore.setFillColor(sf::Color::Green);
        KeithScore.setOutlineColor(sf::Color::Black);
        KeithScore.setOutlineThickness(1);
        KeithScore.setPosition(sf::Vector2f(900, 230));
        KeithScore.setCharacterSize(30);
        KeithScore.setOrigin(15, 15);

        //Displays Timer count down to the right hand side panel
        int gameTimer = gameClock.getElapsedTime().asSeconds();
        int countDown = 90;
        sf::Text Timer;
        Timer.setString("Timer: " + std::to_string(countDown - gameTimer) + '\n');
        Timer.setFont(fTitle);
        Timer.setFillColor(sf::Color::Red);
        Timer.setOutlineColor(sf::Color::Black);
        Timer.setOutlineThickness(1.5);
        Timer.setPosition(sf::Vector2f(900, 100));
        Timer.setCharacterSize(40);
        Timer.setOrigin(15, 15);

        //Checks if both snakes are dead
        for (Snake* snake : snakeVector)
        {
            for (int i = 0; i < snakeVector.size(); i++)
            {
                if (!snakeVector[0]->GetIsAlive() && !snakeVector[1]->GetIsAlive() && !snakeVector[2]->GetIsAlive())
                {
                    noSnakeLiving = true;
                }
            }
        }

        // Clears the window each time around the loop
        window.clear();

        //Draws all my additional text or textures
        window.draw(Background);
        window.draw(Title);
        window.draw(Score);
        window.draw(Timer);
        window.draw(JeffScore);
        window.draw(KeithScore);

        //Renders battery to be visible and collidable
        for (Battery* battery : batteryVector)
        {
            if (battery->GetIsActive())
            {
                battery->Render(window);
            }
        }
        //Renders consumables to be visible and collidable
        for (Food* consume : consumeVector)
        {
            if (consume->GetIsActive())
            {
                consume->Render(window);
            }
        }

        //Renders battery electricity to be visible and collidable
        for (Snake* snake : snakeVector)
        {
            if (snake->GetBatteryActive())
            {
                snake->AddElectric(window);
            }
        }

        //Renders snakes to be visible and collidable
        for (Snake* snake : snakeVector)
        {
            if (snake->GetIsAlive())
            {
                snake->Render(window);
            }
        }
        
        //If both snake are dead, game over and winner is declared
        if (noSnakeLiving == true)
        {
            sf::Text GameOver;
            GameOver.setString("Game Over!");
            GameOver.setFont(fTitle);
            GameOver.setFillColor(sf::Color(255, 40, 20));
            GameOver.setOutlineColor(sf::Color::Black);
            GameOver.setOutlineThickness(2.5);
            GameOver.setPosition(sf::Vector2f(250, 150));
            GameOver.setCharacterSize(100);
            GameOver.setOrigin(50, 50);
            window.draw(GameOver);

            sf::Text PressTab;
            PressTab.setString("---Press Tab to Return to Menu---");
            PressTab.setFont(fTitle);
            PressTab.setFillColor(sf::Color(180, 20, 255));
            PressTab.setOutlineColor(sf::Color::Black);
            PressTab.setOutlineThickness(2);
            PressTab.setPosition(sf::Vector2f(160, 700));
            PressTab.setCharacterSize(40);
            PressTab.setOrigin(20, 20);
            window.draw(PressTab);

            if (playerScore > jeffScore && playerScore > keithScore)
            {
                sf::Text PlayerWin;
                PlayerWin.setString("Player wins with a score of " + std::to_string(playerScore) + '\n');
                PlayerWin.setFont(fTitle);
                PlayerWin.setFillColor(sf::Color(180, 20, 255));
                PlayerWin.setOutlineColor(sf::Color::Black);
                PlayerWin.setOutlineThickness(2);
                PlayerWin.setPosition(sf::Vector2f(130, 250));
                PlayerWin.setCharacterSize(50);
                PlayerWin.setOrigin(25, 25);
                window.draw(PlayerWin);
            }
            else if (playerScore < jeffScore && jeffScore > keithScore)
            {
                sf::Text JeffWin;
                JeffWin.setString("Jeffery wins with a score of " + std::to_string(jeffScore) + '\n');
                JeffWin.setFont(fTitle);
                JeffWin.setFillColor(sf::Color::Cyan);
                JeffWin.setOutlineColor(sf::Color::Black);
                JeffWin.setOutlineThickness(2);
                JeffWin.setPosition(sf::Vector2f(130, 250));
                JeffWin.setCharacterSize(50);
                JeffWin.setOrigin(25, 25);
                window.draw(JeffWin);
            }
            else if (playerScore < keithScore && jeffScore < keithScore)
            {
                sf::Text KeithWin;
                KeithWin.setString("Keith wins with a score of " + std::to_string(keithScore) + '\n');
                KeithWin.setFont(fTitle);
                KeithWin.setFillColor(sf::Color::Green);
                KeithWin.setOutlineColor(sf::Color::Black);
                KeithWin.setOutlineThickness(2);
                KeithWin.setPosition(sf::Vector2f(155, 250));
                KeithWin.setCharacterSize(50);
                KeithWin.setOrigin(25, 25);
                window.draw(KeithWin);
            }
            else
            {
                sf::Text Draw;
                Draw.setString("It's a Draw!");
                Draw.setFont(fTitle);
                Draw.setFillColor(sf::Color(180, 20, 255));
                Draw.setOutlineColor(sf::Color::Black);
                Draw.setOutlineThickness(2);
                Draw.setPosition(sf::Vector2f(320, 250));
                Draw.setCharacterSize(50);
                Draw.setOrigin(25, 25);
                window.draw(Draw);
            }
            //Restarts the clock to stop the count down when Game End is called
            gameClock.restart();

            //Allows players to return to Menu and begin again
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
            {
                window.close();
                Menu gameMenu;
                gameMenu.Run();
            }
        }

        //Checks the timer and ends the game when it hits 90 seconds
        if (gameClock.getElapsedTime().asSeconds() >= 90)
        {
            for (Snake* snake : snakeVector)
            {
                if (snake->GetIsAlive())
                {
                    snake->Die();
                }
            }
            sf::Text GameOver;
            GameOver.setString("Game Over!");
            GameOver.setFont(fTitle);
            GameOver.setFillColor(sf::Color(255, 40, 20));
            GameOver.setOutlineColor(sf::Color::Black);
            GameOver.setOutlineThickness(2.5);
            GameOver.setPosition(sf::Vector2f(250, 150));
            GameOver.setCharacterSize(100);
            GameOver.setOrigin(50, 50);
            window.draw(GameOver);

            if (playerScore > jeffScore && playerScore > keithScore)
            {
                sf::Text PlayerWin;
                PlayerWin.setString("Player wins with a score of " + std::to_string(playerScore) + '\n');
                PlayerWin.setFont(fTitle);
                PlayerWin.setFillColor(sf::Color(180, 20, 255));
                PlayerWin.setOutlineColor(sf::Color::Black);
                PlayerWin.setOutlineThickness(2);
                PlayerWin.setPosition(sf::Vector2f(130, 250));
                PlayerWin.setCharacterSize(50);
                PlayerWin.setOrigin(25, 25);
                window.draw(PlayerWin);
            }
            else if (playerScore < jeffScore && jeffScore > keithScore)
            {
                sf::Text JeffWin;
                JeffWin.setString("Jeffery wins with a score of " + std::to_string(jeffScore) + '\n');
                JeffWin.setFont(fTitle);
                JeffWin.setFillColor(sf::Color::Cyan);
                JeffWin.setOutlineColor(sf::Color::Black);
                JeffWin.setOutlineThickness(2);
                JeffWin.setPosition(sf::Vector2f(130, 250));
                JeffWin.setCharacterSize(50);
                JeffWin.setOrigin(25, 25);
                window.draw(JeffWin);
            }
            else if (playerScore < keithScore && jeffScore < keithScore)
            {
                sf::Text KeithWin;
                KeithWin.setString("Keith wins with a score of " + std::to_string(keithScore) + '\n');
                KeithWin.setFont(fTitle);
                KeithWin.setFillColor(sf::Color::Green);
                KeithWin.setOutlineColor(sf::Color::Black);
                KeithWin.setOutlineThickness(2);
                KeithWin.setPosition(sf::Vector2f(155, 250));
                KeithWin.setCharacterSize(50);
                KeithWin.setOrigin(25, 25);
                window.draw(KeithWin);
            }
            else
            {
                sf::Text Draw;
                Draw.setString("It's a Draw!");
                Draw.setFont(fTitle);
                Draw.setFillColor(sf::Color(180, 20, 255));
                Draw.setOutlineColor(sf::Color::Black);
                Draw.setOutlineThickness(2);
                Draw.setPosition(sf::Vector2f(320, 250));
                Draw.setCharacterSize(50);
                Draw.setOrigin(25, 25);
                window.draw(Draw);
            }

            //Allows players to return to Menu and begin again
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
            {
                window.close();
                Menu gameMenu;
                gameMenu.Run();
            }
        }

        // Get the window to display its contents
        window.display();

        //Restarts clock after 150 milliseconds which increases speed of gameplay
        while (clock.getElapsedTime().asMilliseconds() < 150);
        {
            clock.restart();
        }
    }

    //Deletes all snakes, batteries and consumables at the end of the game
    for (Snake* snake : snakeVector)
    {
        delete snake;
    }
    for (Battery* battery : batteryVector)
    {
        delete battery;
    }
    for (Food* consume : consumeVector)
    {
        delete consume;
    }
}