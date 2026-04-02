#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "GameObject.h"
#include "Vector.h"

GameObject::GameObject()
{
    sprite = sf::Sprite();
    position = Vector(0, 0);
    velocity = Vector(0, 0);
    is_visible = true;
}
GameObject::~GameObject()
{

}

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
    // Load the texture from the file
    if (!texture.loadFromFile(filename))
    {
        std::cout << "Failed to load " << filename << std::endl;
        return false;
    }

    sprite.setTexture(texture);

    return true;
}

sf::Sprite& GameObject::getSprite()
{
    return sprite;
}
void GameObject::setIsVisible(bool visibility)
{
    is_visible = visibility;
}
bool GameObject::getIsVisible()
{
    return is_visible;
}
sf::Vector2f GameObject::getCentre()
{
    sf::Vector2f position = sprite.getPosition();
    float half_width = sprite.getGlobalBounds().width / 2;
	float half_height = sprite.getGlobalBounds().height / 2;
	return sf::Vector2f(position + sf::Vector2f(half_width, half_height));
}
bool GameObject::collisionCheck(sf::Sprite& sprite1, sf::Sprite& sprite2)
{
    // Get the position and size of the sprites' bounding boxes
    sf::FloatRect sprite1Bounds = sprite1.getGlobalBounds();
    sf::FloatRect sprite2Bounds = sprite2.getGlobalBounds();

    float sprite1x = sprite1Bounds.left;
    float sprite1y = sprite1Bounds.top;
    float sprite1_width = sprite1Bounds.width;
    float sprite1_height = sprite1Bounds.height;

    float sprite2x = sprite2Bounds.left;
    float sprite2y = sprite2Bounds.top;
    float sprite2_width = sprite2Bounds.width;
    float sprite2_height = sprite2Bounds.height;

    // Check if the sprites' bounding boxes intersect
    if (
        sprite1x <= sprite2x + sprite2_width &&
        sprite1x + sprite1_width >= sprite2x &&
        sprite1y <= sprite2y + sprite2_height &&
        sprite1y + sprite1_height >= sprite2y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void GameObject::moveTowards(sf::Vector2f& target)
{
    direction.x = target.x - (getSprite().getPosition().x + getSprite().getGlobalBounds().width / 2);
    direction.y = target.y - (getSprite().getPosition().y + getSprite().getGlobalBounds().height / 2);

    direction.normalise();

    velocity.x = direction.x * getSpeed();
    velocity.y = direction.y * getSpeed();

    target_position = target;
}
bool GameObject::hasReachedTarget()
{
    if (
		std::abs((position.x + getSprite().getGlobalBounds().width / 2) - target_position.x) <= 2 &&
        std::abs((position.y + getSprite().getGlobalBounds().height / 2) - target_position.y) <= 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void GameObject::update()
{
    // store sprite position in vector
    position.y = getSprite().getPosition().y;
    position.x = getSprite().getPosition().x;

    // Update position using Vector class
    position.x += velocity.x;
    position.y += velocity.y;
    getSprite().setPosition(position.x, position.y);
}