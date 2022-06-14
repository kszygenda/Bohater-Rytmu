#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape{
private:

public:
    Button(sf::Vector2f size, sf::Vector2f pos)
        : RectangleShape(size)
    {
        setPosition(pos);
        setFillColor(sf::Color(123,123,123));
    }
    bool is_within(sf::RenderWindow &window);
};

#endif // BUTTON_H
