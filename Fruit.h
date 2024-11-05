#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0));

	sf::Color SetColor();

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	int digest();

private:
	sf::CircleShape shape_;
	sf::Color color_;
	int calorie_;
	static const float Radius;
};
}

#endif