#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>
#include<vector>

namespace sfSnake
{
class Draw
{
public:
    Draw();
    void setGridColor();//设置网格颜色
    void setBackgroundColor();//设置背景颜色
    void setButton(int n);
    void drawGrid(sf::RenderWindow& window);//绘制网格
    void drawBackground(sf::RenderWindow& window);//绘制背景
    void drawButtons(sf::RenderWindow& window);
    void changeOutline(sf::Text button);
    static std::vector<sf::Text> buttons_;
private:
    sf::Font font_;
    sf::Text text_;
    sf::Color grid_color_;//网格、背景颜色
    sf::Color background_color_;  
    sf::Texture gridtex_;
    sf::Texture backgroundtex_;
    sf::Sprite grid_;
    sf::Sprite background_;//网格、背景的精灵
};
}

#endif
