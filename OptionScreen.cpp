#include <SFML/Graphics.hpp>
#include <iostream>

#include "OptionScreen.h"
#include "Screen.h"
#include "GameScreen.h"
#include "Game.h"

using namespace sfSnake;

int OptionScreen::current_background = 0;
int OptionScreen::current_grid = 0;
float OptionScreen::game_speed = 1.0;
sf::Texture optex;
bool keylock = false;

OptionScreen::OptionScreen()
{
    clickbuffer_.loadFromFile("Sounds/click.wav");
    clicksound_.setBuffer(clickbuffer_);
    clicksound_.setVolume(150);

    choosebuffer_.loadFromFile("Sounds/choose.wav");
    choosesound_.setBuffer(choosebuffer_);
    choosesound_.setVolume(100);

    font_.loadFromFile("Fonts/content.otf");
    subtitlefont_.loadFromFile("Fonts/subtitle.ttf");
    optex.loadFromFile("Images/config.png");

    opbackground_.setTexture(optex);
    opbackground_.setPosition(0.f, 0.f);

    subtitle_.setFont(subtitlefont_);
    subtitle_.setString("CONFIG");
    subtitle_.setFillColor(sf::Color::Black);
    subtitle_.setCharacterSize(80);
    subtitle_.setOutlineColor(sf::Color::White);
    subtitle_.setOutlineThickness(1.f);
    subtitle_.setPosition(20.f, 0.f);

    backgroundtext_.setFont(font_);
    backgroundtext_.setString(L"选择地图：");
    backgroundtext_.setFillColor(sf::Color::Black);
    backgroundtext_.setCharacterSize(44);
    backgroundtext_.setStyle(sf::Text::Bold);
    backgroundtext_.setOutlineColor(sf::Color::White);
    backgroundtext_.setOutlineThickness(1.f);

    gridtext_.setFont(font_);
    gridtext_.setString(L"选择网格线：");
    gridtext_.setFillColor(sf::Color::Black);
    gridtext_.setCharacterSize(44);
    gridtext_.setStyle(sf::Text::Bold);
    gridtext_.setOutlineColor(sf::Color::White);
    gridtext_.setOutlineThickness(1.f);

    continuetext_.setFont(font_);
    continuetext_.setString(L"按[空格]以继续");
    continuetext_.setFillColor(sf::Color::White);
    continuetext_.setOutlineThickness(2.f);
    /*
        diffitext_.setFont(font_);
        diffitext_.setString("Choose Difficulty :\t\n[Z] Normal\t[X] Hard");
        diffitext_.setFillColor(sf::Color(95, 158, 160));
        diffitext_.setCharacterSize(34);
        diffitext_.setOutlineColor(sf::Color(75, 0, 130));
        diffitext_.setOutlineThickness(1.5f);
    */
    sf::FloatRect bgtextBounds = backgroundtext_.getLocalBounds();
    backgroundtext_.setOrigin(bgtextBounds.left + bgtextBounds.width / 2,
                              bgtextBounds.top + bgtextBounds.height / 2);
    backgroundtext_.setPosition(bgtextBounds.width / 2 + 20.f, Game::Height / 3);

    sf::FloatRect grtextBounds = gridtext_.getLocalBounds();
    gridtext_.setOrigin(grtextBounds.left + grtextBounds.width / 2,
                        grtextBounds.top + grtextBounds.height / 2);
    gridtext_.setPosition(grtextBounds.width / 2 + 20.f, Game::Height * 3 / 5);
    /*
        sf::FloatRect diftextBounds = diffitext_.getLocalBounds();
        diffitext_.setOrigin(diftextBounds.left + diftextBounds.width / 2,
                             diftextBounds.top + diftextBounds.height / 2);
        diffitext_.setPosition(diftextBounds.width / 2 + 20.f, Game::Height * 2 / 3);
    */
    sf::FloatRect ctntextBounds = continuetext_.getLocalBounds();
    continuetext_.setOrigin(ctntextBounds.left + ctntextBounds.width / 2,
                            ctntextBounds.top + ctntextBounds.height / 2);
    continuetext_.setPosition(Game::Width / 2, Game::Height * 9 / 10 + 30.f);
}

void OptionScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        clicksound_.play();
        sf::sleep(sf::seconds(clickbuffer_.getDuration().asSeconds() * 2 / 3));
        if (game_speed != 1.0)
            Game::SwitchMusic("Music/hard.ogg");
        else
            Game::SwitchMusic("Music/normal.ogg");
        Game::Screen = std::make_shared<GameScreen>();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !keylock)
    {
        keylock = true;
        if (pointer_ == 2)
            pointer_ = 0;
        else if (pointer_ == 6)
            pointer_ = 3;
        else
            pointer_++;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !keylock)
    {
        keylock = true;
        if (pointer_ == 0)
            pointer_ = 2;
        else if (pointer_ == 3)
            pointer_ = 6;
        else
            pointer_--;
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !keylock)
    {
        keylock = true;
        if (pointer_ <= 1)
            pointer_ += 3;
        else if (pointer_ == 2)
            pointer_ = 6;
        else if (pointer_ == 5)
            pointer_ = 1;
        else if (pointer_ == 6)
            pointer_ = 2;
        else
            pointer_ -= 3;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (keylock)
            keylock = false;
    }

   // std::cout << pointer_ << '\n';
    if (pointer_ < 3)
        current_background = pointer_;
    else
        current_grid = pointer_;
    
    for(int i=0;i<7;i++)
    {
        if(i==pointer_)
        Draw::buttons_[i].setOutlineColor(sf::Color::Green);
        else  Draw::buttons_[i].setOutlineColor(sf::Color(75, 0, 130));
    }

    /*
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        choosesound_.play();
        current_background = 0;
        backgroundtext_.setFillColor(sf::Color::White);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        choosesound_.play();
        current_background = 1;
        backgroundtext_.setFillColor(sf::Color::Black);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        choosesound_.play();
        current_background = 2;
        backgroundtext_.setFillColor(sf::Color(165, 42, 42));
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        choosesound_.play();
        current_grid = 0;
        gridtext_.setFillColor(sf::Color::White);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        choosesound_.play();
        current_grid = 1;
        gridtext_.setFillColor(sf::Color::Black);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        choosesound_.play();
        current_grid = 2;
        gridtext_.setFillColor(sf::Color(165, 42, 42));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        choosesound_.play();
        current_grid = 3;
        gridtext_.setFillColor(sf::Color::Transparent);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        choosesound_.play();
        game_speed = 1.0;
        diffitext_.setFillColor(sf::Color::Green);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        choosesound_.play();
        game_speed = 1.5;
        diffitext_.setFillColor(sf::Color::Red);
    }*/
}

void OptionScreen::update(sf::Time delta)
{
}

void OptionScreen::render(sf::RenderWindow &window)
{
    window.draw(opbackground_);
    window.draw(subtitle_);
    window.draw(backgroundtext_);
    window.draw(gridtext_);
    /*  window.draw(diffitext_);*/
    interface.drawButtons(window);
    window.draw(continuetext_);
}