#ifndef OPTIONSCREEN_H
#define OPTIONSCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "Draw.h"

namespace sfSnake
{
	class OptionScreen : public Screen
	{
	public:
		OptionScreen();
		void handleInput(sf::RenderWindow &window) override;
		void update(sf::Time delta) override;
		void render(sf::RenderWindow &window) override;

		static int current_grid;
		static int current_background;
		static float game_speed;

	private:
		sf::Font font_;
		sf::Font subtitlefont_;
		sf::Text subtitle_;
		sf::Text backgroundtext_;
		sf::Text gridtext_;
		sf::Text diffitext_;
		sf::Text continuetext_;
		sf::Sprite opbackground_;

		sf::SoundBuffer clickbuffer_;
		sf::Sound clicksound_;

		sf::SoundBuffer choosebuffer_;
		sf::Sound choosesound_;
		int pointer_ = 0;

		Draw interface;
	};
}
#endif
