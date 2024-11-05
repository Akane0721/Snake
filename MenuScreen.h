#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Screen.h"

namespace sfSnake
{
class MenuScreen : public Screen
{
public:
	MenuScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Font titlefont_;
	sf::Font font_;
	sf::Text snakeText_;
	sf::Text text_;
	sf::Sprite background_;

	
	sf::SoundBuffer clickbuffer_;
	sf::Sound clicksound_;
};
}

#endif