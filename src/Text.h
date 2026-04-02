#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#ifndef TEXT_H
#  define TEXT_H

class Text
{
public:
	void init(int x, int y, std::string text, sf::Color color);

	sf::Text string;
	sf::Font font;
};
#endif // TEXT_H