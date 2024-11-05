#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	static void SwitchMusic(const std::string& musicFile);
	void handleInput();
	void update(sf::Time delta);
	void render();

	static const int Width = 960;
	static const int Height = 720;

	static std::shared_ptr<Screen> Screen;

private:
	sf::RenderWindow window_;
	static sf::Music bgMusic_;
	
	static const sf::Time TimePerFrame;
};
}


#endif