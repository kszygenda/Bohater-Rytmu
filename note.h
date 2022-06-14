#ifndef NOTE_H
#define NOTE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Poziom.h"

class Note : public sf::CircleShape
{

public:
    Note(sf::Vector2f pos);
    Note();
    int return_speed();
    friend class Poziom;
    void animate(sf::Time elapsed);
    //do skonczenia
    bool check_range();
    friend void generate_level(std::vector<Note> &LineD,std::vector<Note> &LineF,std::vector<Note> &LineJ,std::vector<Note> &LineK);
private:
    float vy=1800;
};


#endif // NOTE_H
