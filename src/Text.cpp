#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Text.h"

void Text::init(int x, int y, std::string text, sf::Color color)
{
    // init menu text
    if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
    {
        std::cout << "font did not load \n";
    }
    string.setString(text);
    string.setFont(font);
    string.setCharacterSize(25);
    string.setFillColor(color);
    string.setPosition(x, y);
}