#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), bool head = false);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window);
	void changeface(int score);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	static const float Width;
	static const float Height;

private:
	sf::Sprite sprite_;
	sf::Vector2f position_;
	bool head_;
};
}

#endif