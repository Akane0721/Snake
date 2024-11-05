#include <SFML/Graphics.hpp>

#include <fstream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "OptionScreen.h"

using namespace sfSnake;

sf::Texture dietex;
sf::Texture bgrtex;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	unsigned highscore = getHighestscore(score);
	Game::SwitchMusic("Music/gameover.wav");
	font_.loadFromFile("Fonts/content.otf");
	scorefont_.loadFromFile("Fonts/score.ttf");
	scoretext_.setFont(scorefont_);
	ctntext_.setFont(font_);

	scoretext_.setString("Your score:	   " + std::to_string(score)+ 
		"\nHighest score:	"+std::to_string(highscore) 
		);
	scoretext_.setFillColor(sf::Color(255,215,0));
	scoretext_.setCharacterSize(50);
	scoretext_.setOutlineColor(sf::Color(128,0,128));
	scoretext_.setOutlineThickness(1.2f);

	ctntext_.setString("Press [SPACE] to retry"
		"\nPress [ESC] to quit");
	ctntext_.setFillColor(sf::Color::White);
	ctntext_.setOutlineColor(sf::Color::Black);
	ctntext_.setOutlineThickness(1.f);

	dietex.loadFromFile("Images/perish.png");
	die_.setTexture(dietex);

	sf::FloatRect scoretextBounds = scoretext_.getLocalBounds();
	scoretext_.setOrigin(scoretextBounds.left + scoretextBounds.width / 2,
		scoretextBounds.top + scoretextBounds.height / 2);
	scoretext_.setPosition(Game::Width / 2, Game::Height *2 / 3);

	sf::FloatRect diebounds = die_.getLocalBounds();
	die_.setOrigin(diebounds.left + diebounds.width / 2,
	diebounds.top + diebounds.height / 2);
	die_.setPosition(Game::Width / 2, Game::Height *2 / 5);

	sf::FloatRect ctnbounds = ctntext_.getLocalBounds();
	ctntext_.setOrigin(ctnbounds.left + ctnbounds.width / 2,
	ctnbounds.top + ctnbounds.height / 2);
	ctntext_.setPosition(Game::Width / 2, Game::Height * 8 / 9);

	bgrtex.loadFromFile("Images/gameover.png");
	background_.setTexture(bgrtex);
	background_.setPosition(0.f,0.f);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if(OptionScreen::game_speed != 1.0) Game::SwitchMusic("Music/hard.ogg");
		else Game::SwitchMusic("Music/normal.ogg");
		Game::Screen = std::make_shared<GameScreen>();
	}
		
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(background_);
	window.draw(die_);
	window.draw(scoretext_);
	window.draw(ctntext_);
}

unsigned GameOverScreen::getHighestscore(unsigned score)
{
    unsigned highscore;
	std::ifstream fin("Save/highestscore.txt");
	if (fin.is_open()) {
    	fin >> highscore;
    	fin.close();
	}
	if(score > highscore)
	{
		highscore = score;
		std::ofstream fout("Save/highestscore.txt");
		fout << highscore;
		fout.close();
	}
	return highscore;
}