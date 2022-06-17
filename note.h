#ifndef NOTE_H
#define NOTE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

class Note : public sf::CircleShape
{
private:
    float vy=2200;
public:
    friend class Poziom;
    Note(sf::Vector2f pos);
    Note();
    int return_speed();
    void animate(sf::Time elapsed);
    bool check_range();
};


#endif // NOTE_H
