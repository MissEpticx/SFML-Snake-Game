#include "ControlMenu.h"
#include "Menu.h"
#include <time.h>
#include <iostream>
#include <SFML/Graphics.hpp>

void ControlMenu::Run()
{
    //allows for true random to occur
    srand(time(NULL));

    sf::RenderWindow controlMenu(sf::VideoMode(800, 900), "C++ Snake ICA : A0208468");

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
    Title.setPosition(sf::Vector2f(220, 100));
    Title.setCharacterSize(80);
    Title.setOrigin(40, 40);

    sf::Text Controls;
    Controls.setString("Controls");
    Controls.setFont(fTitle);
    Controls.setFillColor(sf::Color(50, 100, 150));
    Controls.setOutlineColor(sf::Color::Black);
    Controls.setOutlineThickness(2);
    Controls.setPosition(sf::Vector2f(320, 200));
    Controls.setCharacterSize(60);
    Controls.setOrigin(30, 30);

    sf::Text Up;
    Up.setString("Up Arrow Key to Move Up");
    Up.setFont(fTitle);
    Up.setFillColor(sf::Color(50, 100, 150));
    Up.setOutlineColor(sf::Color::Black);
    Up.setOutlineThickness(2);
    Up.setPosition(sf::Vector2f(260, 300));
    Up.setOrigin(15, 15);

    sf::Text Down;
    Down.setString("Down Arrow Key to Move Down");
    Down.setFont(fTitle);
    Down.setFillColor(sf::Color(50, 100, 150));
    Down.setOutlineColor(sf::Color::Black);
    Down.setOutlineThickness(2);
    Down.setPosition(sf::Vector2f(235, 350));
    Down.setOrigin(15, 15);

    sf::Text Left;
    Left.setString("Left Arrow Key to Move Left");
    Left.setFont(fTitle);
    Left.setFillColor(sf::Color(50, 100, 150));
    Left.setOutlineColor(sf::Color::Black);
    Left.setOutlineThickness(2);
    Left.setPosition(sf::Vector2f(245, 400));
    Left.setOrigin(15, 15);

    sf::Text Right;
    Right.setString("Right Arrow Key to Move Right");
    Right.setFont(fTitle);
    Right.setFillColor(sf::Color(50, 100, 150));
    Right.setOutlineColor(sf::Color::Black);
    Right.setOutlineThickness(2);
    Right.setPosition(sf::Vector2f(235, 450));
    Right.setOrigin(15, 15);

    sf::Text Return;
    Return.setString("---Press BackSpace to Return to Menu---");
    Return.setFont(fTitle);
    Return.setFillColor(sf::Color(180, 20, 255));
    Return.setOutlineColor(sf::Color::Black);
    Return.setOutlineThickness(2);
    Return.setPosition(sf::Vector2f(100, 700));
    Return.setCharacterSize(40);
    Return.setOrigin(20, 20);

    while (controlMenu.isOpen())
    {
        sf::Event event;
        while (controlMenu.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                controlMenu.close();
                break;
            default:
                break;
            }
        }

        //Closes the control menu and opens the main menu
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        {
            Menu gameMenu;
            gameMenu.Run();
            controlMenu.close();
        }

        controlMenu.clear();

        controlMenu.draw(MenuBackground);
        controlMenu.draw(Title);
        controlMenu.draw(Controls);
        controlMenu.draw(Up);
        controlMenu.draw(Down);
        controlMenu.draw(Left);
        controlMenu.draw(Right);
        controlMenu.draw(Return);

        controlMenu.display();
    }
}
