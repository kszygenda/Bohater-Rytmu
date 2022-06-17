#ifndef VIRTUALNOTE_H
#define VIRTUALNOTE_H
#include <SFML/Graphics.hpp>

class VirtualNote : public sf::CircleShape
{
private:

public:
    VirtualNote();
    virtual void move();

};

#endif // VIRTUALNOTE_H
