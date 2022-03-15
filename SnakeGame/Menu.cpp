#include "Menu.h"
#include "Game.h"
#include "ControlMenu.h"
#include <time.h>
#include <iostream>
#include <SFML/Graphics.hpp>

void Menu::Run()
{
    sf::RenderWindow mainMenu(sf::VideoMode(800, 900), "C++ Snake ICA : A0208468");

    sf::Texture menuBackground;
    if (!menuBackground.loadFromFile("MenuBackground.png"))
    {
        std::cout << "Failed to Load Texture\n" << std::endl;
        return;
    }
    sf::Sprite MenuBackground;
    MenuBackground.setTexture(menuBackground);

    sf::Font fTitle;
    fTitle.loadFromFile("Waffle Crisp.ttf");
    sf::Text Title;
    Title.setString("ZAPPY SNAKES");
    Title.setFont(fTitle);
    Title.setFillColor(sf::Color::Cyan);
    Title.setOutlineColor(sf::Color::Black);
    Title.setOutlineThickness(2);
    Title.setPosition(sf::Vector2f(220, 200));
    Title.setCharacterSize(80);
    Title.setOrigin(40, 40);

    sf::Text Begin;
    Begin.setString("Press Enter to Begin");
    Begin.setFont(fTitle);
    Begin.setFillColor(sf::Color(180, 20, 255));
    Begin.setOutlineColor(sf::Color::Black);
    Begin.setOutlineThickness(2);
    Begin.setPosition(sf::Vector2f(220, 350));
    Begin.setCharacterSize(50);
    Begin.setOrigin(25, 25);

    sf::Text Controls;
    Controls.setString("Press Space for Controls");
    Controls.setFont(fTitle);
    Controls.setFillColor(sf::Color(180, 20, 255));
    Controls.setOutlineColor(sf::Color::Black);
    Controls.setOutlineThickness(2);
    Controls.setPosition(sf::Vector2f(170, 450));
    Controls.setCharacterSize(50);
    Controls.setOrigin(25, 25);

    while (mainMenu.isOpen())
    {
        sf::Event event;
        while (mainMenu.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                mainMenu.close();
                break;
            default:
                break;
            }
        }

        //Closes the menu and Opens the Game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            mainMenu.close();
            Game myGame;
            myGame.Run();
        }

        //Closes the menu and Opens the Controls screen
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            mainMenu.close();
            ControlMenu controlMenu;
            controlMenu.Run();
        }

        //Closes the Menu - Game cannot be loaded
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            mainMenu.close();
        }

        mainMenu.clear();

        mainMenu.draw(MenuBackground);
        mainMenu.draw(Title);
        mainMenu.draw(Begin);
        mainMenu.draw(Controls);

        mainMenu.display();
    }
}