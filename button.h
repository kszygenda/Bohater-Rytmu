#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape{
private:
    sf::Text text_guzika;
    sf::Font font;
    std::string napis;
    sf::Color kolor_napisu;

public:
    Button();
    Button(sf::Vector2f size, sf::Vector2f pos, std::string napis_guzik, sf::Color kolor_guzika, sf::Color kolor_tekstu,int char_size);
    bool is_within(sf::RenderWindow &window);
    void intro();
    void draw_text(sf::RenderWindow &window,sf::Font &font);
    void is_hovering(sf::RenderWindow &window);
};

#endif // BUTTON_H
