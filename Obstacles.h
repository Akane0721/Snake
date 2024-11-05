#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Obstacles
{
public:
	Obstacles(sf::Vector2f position = sf::Vector2f(0, 0));

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

   // bool checkposition(sf::Vector2f position)


private:
	sf::Sprite sprite_;
};
}

#endif