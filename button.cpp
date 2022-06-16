#include "button.h"
#include <iostream>
Button::Button(){

}
Button::Button(sf::Vector2f size, sf::Vector2f pos,std::string napis_guzik,sf::Color kolor_guzika, sf::Color kolor_tekstu,int char_size)
    : RectangleShape(size)
{
    setPosition(pos);
    setFillColor(kolor_guzika);
    text_guzika.setCharacterSize(char_size);
    text_guzika.setPosition(pos.x,pos.y);
    text_guzika.setFillColor(kolor_tekstu);
    text_guzika.setString(napis_guzik);
    napis=napis_guzik;
}

//funkcja sprawdzająca czy myszka znajduje się wewnątrz guzika
bool Button::is_within(sf::RenderWindow &window){
    sf::Vector2i position = sf::Mouse::getPosition(window);
    sf::FloatRect rec_b = getGlobalBounds();
    if(position.x>=rec_b.left && position.x<=rec_b.left+rec_b.width && position.y>rec_b.top && position.y<rec_b.top+rec_b.height)
        return true;
    else
        return false;
}


//funkcja otwierająca okno w której jest "poradnik"
void Button::intro(){
    sf::RenderWindow widow(sf::VideoMode(800,600),"Poradnik");
    sf::Texture texture;
    //wczytywanie obrazka
    if(!texture.loadFromFile("Poradnik.png"))
        return;
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0,0);
    while (widow.isOpen()){

        //obsluga eventu
        sf::Event event;
        while (widow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                widow.close();
        }
        //rysowanie
        widow.clear(sf::Color::Black);
        widow.draw(sprite);
        //end current frame
        widow.display();
    }
}
//funkcja rysująca text (powstala bo bugi jakies losowe) na guziku (tak aby napis był "na" guziku, a nie "pod" nim)
void Button::draw_text(sf::RenderWindow &window,sf::Font &font){
    text_guzika.setFont(font);
    window.draw(text_guzika);
}
