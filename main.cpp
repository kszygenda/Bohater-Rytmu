#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "note.h"
#include <ctime>
#include <random>
#include "note.cpp"
#include <SFML/Audio.hpp>

//zrób Judgement który wyświetla se siema


void input(std::vector<Note> &vec)
{
    if(!vec.empty()){
    if(vec[0].check_range()||(!vec[0].check_range()&&vec[0].getGlobalBounds().top>800+vec[0].vy*0.3))
    {
    std::vector<Note>::iterator it=vec.begin();
    std::cout<<"Usunieto"<<std::endl;
    vec.erase(it);
    }
    }
}

sf::Music muzyka;



int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
    sf::Clock clock;
    //probne wczytanie piosenki, 
    if(!muzyka.openFromFile("johnxina.ogg"))
    {
        std::cerr <<"Could not load Music"<<std::endl;
        return 1;
    }
    muzyka.setVolume(1);
    muzyka.play();
    //Tworzenie obiektu test
    sf::RectangleShape vs(sf::Vector2f(644.0, 1080.0));
        vs.setPosition(640.0, 0.0);
        vs.setFillColor(sf::Color(0,0,0));

    //spamienie nut test
    std::vector<Note> vecD;
    for (int i=0;i<20;i++){
        sf::Vector2f position(650,-200*i);
        vecD.emplace_back(Note(position));
    }

    //background
    sf::Texture background;
    if(!background.loadFromFile("walecka.png")){
        std::cerr <<"Could not load texture"<<std::endl;
        return 1;
    }
    sf::Sprite sprite;
    sprite.setTexture(background);
    sf::Vector2f targetsize(1920.f,1080.f);
    sprite.setScale(targetsize.x / sprite.getLocalBounds().width, targetsize.y / sprite.getLocalBounds().height);
    sprite.setPosition(0,0);


    //Tworzenie Judgement line
    std::vector<sf::CircleShape> Judgement_Line;
    for (int i=0;i<4;i++)
    {
       Judgement_Line.emplace_back(sf::CircleShape(72));
       Judgement_Line[i].setOutlineThickness(4);
       Judgement_Line[i].setFillColor(sf::Color(0,0,0));
       Judgement_Line[i].setOutlineColor(sf::Color(105,105,105));
       Judgement_Line[i].setPosition((650+i*12+i*144),800);
    }

    //Tu jakiś zegar do animacji


    //no to co, ogłuszamy karpia młotkiem <-------------------------------------------------------------
    //hutsz izak5

    // run the program as long as the window is open
    while (window.isOpen()) {
    sf::Time elapsed = clock.restart();



        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type==sf::Event::KeyPressed)
                if(event.key.code==sf::Keyboard::D)
            {
                input(vecD);
            }
        }
        input(vecD);
        // clear the window with black color
        window.clear(sf::Color::Black);

        //animate


            for(auto &kola : vecD)
            kola.animate(elapsed);
        // draw everything here...
        window.draw(sprite);
        window.draw(vs);
        for(const auto &kola : Judgement_Line)
                window.draw(kola);
        for(const auto &kola : vecD)
        window.draw(kola);
        // end the current frame
        window.display();
    }

    return 0;
}

