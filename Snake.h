#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"
#include "Obstacles.h"

namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down, MOUSE
	};

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);
	void checkObstaclesCollisions(std::vector<Obstacles>& obstacles);

	bool hitSelf() const;

	unsigned getSize() const;

private:
	void move();
	void grow(int growth);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;
	int growth;

	sf::Vector2f position_;
	Direction direction_;
	sf::Vector2f directionVector_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;
	
	std::vector<SnakeNode> nodes_;

	static const int InitialSize;
};
}

#endif