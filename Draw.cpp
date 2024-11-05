#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <utility>

#include "Draw.h"
#include "Game.h"
#include "OptionScreen.h"

using namespace sfSnake;

std::vector<sf::Text> Draw::buttons_;
std::vector<std::wstring> text = {L"古代树森林", L"地带火山", L"壁外雪原", L"黑色", L"白色", L"棕色", L"无"};
std::vector<std::pair<float, float>> position = {
    {Game::Width / 3, Game::Height / 3}, {Game::Width / 3 + 250.f, Game::Height / 3}, {Game::Width / 3 + 500.f, Game::Height / 3}, {Game::Width / 3, Game::Height * 3 / 5}, {Game::Width / 3 + 175.f, Game::Height * 3 / 5}, {Game::Width / 3 + 350.f, Game::Height * 3 / 5}, {Game::Width / 3 + 525.f, Game::Height * 3 / 5}};

Draw::Draw()
{
    setBackgroundColor();
    setGridColor();
    for (int i = 0; i < 7; i++)
    {
        setButton(i);
    }
}

void Draw::setBackgroundColor()
{
    int bg = OptionScreen::current_background;
    auto background_path = "Images/background" + std::to_string(bg) + ".png";
    backgroundtex_.loadFromFile(background_path);
    background_.setTexture(backgroundtex_);
    background_.setPosition(0.f, 0.f);
}

void ::Draw::setGridColor()
{
    int gr = OptionScreen::current_grid;
    if (gr == 3)
        return;
    auto grid_path = "Images/grid" + std::to_string(gr) + ".png";
    gridtex_.loadFromFile(grid_path);
    grid_.setTexture(gridtex_);
    grid_.setPosition(0.f, 0.f);
}

void Draw::setButton(int n)
{
    font_.loadFromFile("Fonts/content.otf");
    text_.setFont(font_);
    text_.setString(text[n]);
    text_.setFillColor(sf::Color(95, 158, 160));
    text_.setCharacterSize(34);
    text_.setStyle(sf::Text::Bold);
    text_.setOutlineColor(sf::Color(75, 0, 130));
    text_.setOutlineThickness(1.5f);

    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
    text_.setPosition(position[n].first, position[n].second);

    buttons_.emplace_back(text_);
}

void Draw::changeOutline(sf::Text button)
{
    button.setOutlineColor(sf::Color::Green);
    button.setOutlineThickness(3.5f);
}

void Draw::drawBackground(sf::RenderWindow &window)
{
    window.draw(background_);
}

void Draw::drawGrid(sf::RenderWindow &window)
{
    window.draw(grid_);
}

void Draw::drawButtons(sf::RenderWindow &window)
{
    for (const auto button : buttons_)
    {
        window.draw(button);
    }
}