#include <SFML/Graphics.hpp>
#include<iostream>

#include <memory>
#include <iostream>
#include <math.h>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "Obstacles.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "OptionScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 4;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds\\pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds\\demise.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(60);
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		if(i==0)	nodes_.push_back(SnakeNode(sf::Vector2f(Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i)),true));
		else 		nodes_.push_back(SnakeNode(sf::Vector2f(Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
	}
}

void Snake::handleInput(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if(direction_ == Direction::Down)	return;
		direction_ = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if(direction_ == Direction::Up)	return;
		direction_ = Direction::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if(direction_ == Direction::Right)	return;
		direction_ = Direction::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if(direction_ == Direction::Left)	return;
		direction_ = Direction::Right;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		direction_ = Direction::MOUSE;
		sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
		directionVector_ = sf::Vector2f(static_cast<sf::Vector2f>(mouseposition)-nodes_[0].getPosition());
		float length = std::sqrt(directionVector_.x*directionVector_.x+directionVector_.y*directionVector_.y);
		directionVector_.x/=length;
		directionVector_.y/=length;
		}
}


void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
			growth = it->digest();
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		grow(growth);
		nodes_[0].changeface(growth);
		fruits.erase(toRemove);
	}
}

void Snake::checkObstaclesCollisions(std::vector<Obstacles>& obstacles)
{
	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
		{			
			Game::SwitchMusic("");
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()/3));
			hitSelf_ = true;
		}
	}	
}

void Snake::grow(int growth)
{
	while(growth>0)
	{
		switch (direction_)
		{
		case Direction::Up:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
				nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));
			break;
		case Direction::Down:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
				nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height)));
			break;
		case Direction::Left:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width,
				nodes_[nodes_.size() - 1].getPosition().y)));
			break;
		case Direction::Right:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width,
				nodes_[nodes_.size() - 1].getPosition().y)));
			break;
		case Direction::MOUSE:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width*directionVector_.x,
				nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height*directionVector_.y)));
			break;
		}
		growth--;
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}


void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 2; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			Game::SwitchMusic("");
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()/3));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}
	float speed = OptionScreen::game_speed;
	switch (direction_)
	{
		case Direction::Up:
			nodes_[0].move(0, -SnakeNode::Height * speed);
			break;
		case Direction::Down:
			nodes_[0].move(0, SnakeNode::Height * speed);
			break;
		case Direction::Left:
			nodes_[0].move(-SnakeNode::Width * speed, 0);
			break;
		case Direction::Right:
			nodes_[0].move(SnakeNode::Width * speed, 0);
			break;
		case Direction::MOUSE:
			nodes_[0].move(directionVector_.x * SnakeNode::Width * speed,directionVector_.y * SnakeNode::Height * speed);
			break;
		
	}
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto node : nodes_)
		node.render(window);
}