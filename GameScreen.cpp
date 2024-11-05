#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "OptionScreen.h"
#include "Game.h"
#include "Draw.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{
	score_ = 0;
	if(OptionScreen::game_speed!=1.0)	generateObstacles();	
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();
	if(snake_.getSize()-4 > score_)
		score_ = snake_.getSize()-4;
	snake_.update(delta);
	snake_.checkObstaclesCollisions(obs_);
	snake_.checkFruitCollisions(fruit_);
	

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(score_);
}

void GameScreen::score(sf::RenderWindow& window)
{
	font_.loadFromFile("Fonts/content.otf");
	scoretext_.setFont(font_);
	scoretext_.setCharacterSize(24);
	scoretext_.setFillColor(sf::Color::Magenta);
	scoretext_.setOutlineColor(sf::Color::Cyan);
	scoretext_.setOutlineThickness(2.f);
	scoretext_.setString("Your Score: " + std::to_string(score_));
	scoretext_.setPosition(Game::Width - scoretext_.getGlobalBounds().width-10.f, scoretext_.getLocalBounds().height);
	window.draw(scoretext_);
}

void GameScreen::render(sf::RenderWindow& window)
{
	interface.drawBackground(window);
	interface.drawGrid(window);
	snake_.render(window);

	for(auto obstacles : obs_)
		obstacles.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);

	score(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine(std::random_device{}());
	static std::uniform_int_distribution<int> xDistribution(SnakeNode::Width, Game::Width - 2 * SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(SnakeNode::Height, Game::Height - 2 * SnakeNode::Height);
	while(true)
	{
		auto x = xDistribution(engine);
		auto y = yDistribution(engine);
		if(check_FO_collision(sf::Vector2f(x,y)))
		{
			fruit_.push_back(Fruit(sf::Vector2f(x,y)));
			break;
		}			
	}	
}

void GameScreen::generateObstacles()
{
	obs_.clear();
	static std::default_random_engine engine(std::random_device{}());
	static std::uniform_int_distribution<int> xDistribution(SnakeNode::Width, Game::Width - 2 * SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(SnakeNode::Height, Game::Height - 2 * SnakeNode::Height);
	int obsize=0;
	while(obsize<4)
	{
		auto x = xDistribution(engine);
		auto y=  yDistribution(engine);
		if(!check_OO_collision(sf::Vector2f(x,y)))	continue;
		obs_.push_back(Obstacles(sf::Vector2f(x,y)));
		obsize++;
	}
}


bool GameScreen::check_OO_collision(const sf::Vector2f& op)
{
	if(op.x > Game::Width/2 - 40.f && op.x < Game::Width/2 + 40.f)
	return false;
	
	for (auto it = obs_.begin(); it != obs_.end(); ++it)
	{
		sf::FloatRect obsbound = it->getBounds();
		if(op.x <= obsbound.left + 80.f && op.x >= obsbound.left - 80.f)
			return false;
		if(op.y <= obsbound.top + 80.f && op.x >= obsbound.top - 80.f)
			return false;	
	}
	return true;
}

bool GameScreen::check_FO_collision(const sf::Vector2f& fp)
{
	for (auto it = obs_.begin(); it != obs_.end(); ++it)
	{
		sf::FloatRect obsbound = it->getBounds();
		if(obsbound.left <= fp.x + 25.f && obsbound.left >= fp.x - 25.f)
			return false;
		if(obsbound.top <= fp.y + 25.f && obsbound.top >= fp.y - 25.f)
			return false;	
	}
	return true;
}



