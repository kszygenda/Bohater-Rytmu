#include "note.h"
#include "Poziom.h"


Note::Note(sf::Vector2f pos) : CircleShape(72){
    setPosition(pos);
    setFillColor(sf::Color(255, 255, 255));
}
Note::Note(){}

//zwracanie skladowej prywatnej, potrzebne do funkcji judgement
int Note::return_speed(){
    return vy;
}
//poruszanie się obiektu
void Note::animate(sf::Time elapsed){
    move(0,vy*elapsed.asSeconds());
}
//funkcja sprawdzająca czy obiekt znajduje się w zakresie "Judgementu"
bool Note::check_range(){
    sf::FloatRect circlebounds = getGlobalBounds();
    if(circlebounds.top<800+vy*0.14 && circlebounds.top>800-vy*0.14) {return true;}
    else {return false;}
}

