#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "Obstacles.h"
#include "Draw.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	bool check_OO_collision(const sf::Vector2f& op);
	bool check_FO_collision(const sf::Vector2f& fp);

	void generateFruit();
	void generateObstacles();
	void score(sf::RenderWindow& window);

private:
	Snake snake_;
	int score_;
	std::vector<Fruit> fruit_;
	std::vector<Obstacles> obs_;
	
	Draw interface;
	sf::Text scoretext_;
	sf::Font font_;
};
}

#endif