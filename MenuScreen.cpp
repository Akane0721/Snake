#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "OptionScreen.h"

using namespace sfSnake;

sf::Texture bgtex;

MenuScreen::MenuScreen()
{
	titlefont_.loadFromFile("Fonts/title.ttf");
	font_.loadFromFile("Fonts/content.otf");
	bgtex.loadFromFile("Images/title_.png");
	text_.setFont(font_);
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit");

	snakeText_.setFont(titlefont_);
	snakeText_.setString("Snake!");
	snakeText_.setFillColor(sf::Color(218,112,214));
	snakeText_.setCharacterSize(120);
	snakeText_.setOutlineColor(sf::Color::Black);
	snakeText_.setOutlineThickness(3.f);

	background_.setTexture(bgtex);
	background_.setPosition(0.f,0.f);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setFillColor(sf::Color::White);
	text_.setOutlineColor(sf::Color::Black);
	text_.setOutlineThickness(2.f);
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height *2 / 3);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);

	clickbuffer_.loadFromFile("Sounds/click.wav");
    clicksound_.setBuffer(clickbuffer_);
    clicksound_.setVolume(150);
}


void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{		
		clicksound_.play();
		sf::sleep(sf::seconds(clickbuffer_.getDuration().asSeconds()*2/3));
		Game::Screen = std::make_shared<OptionScreen>();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(background_);
	window.draw(text_);
	window.draw(snakeText_);
	
}