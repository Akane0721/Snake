#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"

namespace sfSnake
{
class GameOverScreen : public Screen
{
public:
	GameOverScreen(std::size_t score);

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	unsigned getHighestscore(unsigned score);

private:
	sf::Font font_;
	sf::Font scorefont_;
	sf::Text scoretext_;
	sf::Text ctntext_;
	sf::Sprite die_;
	sf::Sprite background_;
	unsigned score_;
};
}

#endif