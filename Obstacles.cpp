#include <SFML/Graphics.hpp>
#include<random>

#include "Obstacles.h"

using namespace sfSnake;

sf::Texture obtex;


Obstacles::Obstacles(sf::Vector2f position)
{   
    obtex.loadFromFile("Images/fire.png");
	sprite_.setTexture(obtex);
    sprite_.setPosition(position);
}

void Obstacles::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}

sf::FloatRect Obstacles::getBounds() const
{
	auto bound = sprite_.getGlobalBounds();
	bound.top += 5.f;
	bound.left += 2.f;
	bound.height -= 6.f;
	bound.width -= 4.f;
	return bound;
}



