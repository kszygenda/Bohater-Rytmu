#include "note.h"
#include "Poziom.h"

Note::Note(sf::Vector2f pos) : CircleShape(72){
    setPosition(pos);
    setFillColor(sf::Color(255, 255, 255));
}
Note::Note(){}


int Note::return_speed(){
    return vy;
}
void Note::animate(sf::Time elapsed){
    move(0,vy*elapsed.asSeconds());
}
bool Note::check_range(){
    sf::FloatRect circlebounds = getGlobalBounds();
    if(circlebounds.top<800+vy*0.3 && circlebounds.top>800-vy*0.3) {return true;}
    else {return false;}
}

