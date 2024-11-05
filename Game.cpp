#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);
sf::Music Game::bgMusic_;

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), L"贪吃蛇")
{
	std::ofstream file("Save/highestscore.txt");
	if(file.is_open())
	{
		file << 0;
		file.close();
	}
	bgMusic_.openFromFile("Music/title.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::SwitchMusic(const std::string& musicFile)
{
    bgMusic_.stop();
	if(musicFile != "")
	{
		bgMusic_.openFromFile(musicFile);  
   	 	bgMusic_.setLoop(true);
    	bgMusic_.play();  
	}     
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window_.clear();
	Game::Screen->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}