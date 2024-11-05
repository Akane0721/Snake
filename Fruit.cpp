#include <SFML/Graphics.hpp>
#include<random>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 8.f;

Fruit::Fruit(sf::Vector2f position)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(SetColor());
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Color Fruit::SetColor()
{
	calorie_ = 0;
	static std::default_random_engine engine(std::random_device{}());	
	static std::uniform_int_distribution<int> color(1,8);
	switch (color(engine))
	{
	case 1:
		color_ = sf::Color(204,0,204); //purple
		calorie_ = -1;
		break;
	case 2:
		color_ = sf::Color::Blue; 
		break;
	case 3:
	case 4:
		color_ = sf::Color::Green;
		calorie_ = 1;
		break;
	case 5:
	case 6:
		color_ = sf::Color(255,128,0); //orange
		calorie_ = 2;
		break;
	default:
		color_ = sf::Color::Red;
		calorie_ = 3;
		break;
	}
	return color_;
}

int Fruit::digest()
{
	return calorie_;
}