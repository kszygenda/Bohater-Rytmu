#ifndef NOTE_H
#define NOTE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

class Note : public sf::CircleShape
{

public:
    Note(sf::Vector2f pos) : CircleShape(72){
        setPosition(pos);
        setFillColor(sf::Color(255, 255, 255));
    }
       void animate(sf::Time elapsed)
       {
           move(0,vy*elapsed.asSeconds());
       }
        //do skonczenia
       bool check_range()
       {
          sf::FloatRect circlebounds = getGlobalBounds();
             if(circlebounds.top>800+vy*0.3 && circlebounds.top<800-vy*0.3)
            {
                 std::cout<<circlebounds.top<<std::endl;
           return true;
             }
            else
           return false;
       }
       friend void input(std::vector<Note> &vec);

private:
    float vy=700;
    //dla poziomu bedzie wczytywanie z pliku czy "czas generacji" jest odpowiedni. 
    //tworzenie samego chartu który będzie do rytmu to będzie dużo dodatkowego czasu, możliwe że będą tylko 2 poziomy
    float czas_generacji=0;
    sf::Time time= sf::milliseconds(czas_generacji);

};





#endif // NOTE_H
