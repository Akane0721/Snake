#include <SFML/Graphics.hpp>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 20.f;
const float SnakeNode::Height = 20.f;

sf::Texture headtex;
sf::Texture bodytex;

SnakeNode::SnakeNode(sf::Vector2f position, bool head)
: position_(position),head_(head)
{
	if(head_)
	{
		headtex.loadFromFile("Images\\head.png");
		sprite_.setTexture(headtex);
	}
	else
	{
		bodytex.loadFromFile("Images\\body.png");
		sprite_.setTexture(bodytex);
	}
	sprite_.setPosition(position_);
}

void SnakeNode::changeface(int score)
{
	switch (score)
	{
	case -1:
		headtex.loadFromFile("Images\\-1.png");
		break;
	case 0:
		headtex.loadFromFile("Images\\0.png");
		break;
	case 1:
		headtex.loadFromFile("Images\\1.png");		
		break;
	case 2:
		headtex.loadFromFile("Images\\2.png");
		break;		
	default:
		headtex.loadFromFile("Images\\3.png");
		break;
	}
	sprite_.setTexture(headtex);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	sprite_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	sprite_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	sprite_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}