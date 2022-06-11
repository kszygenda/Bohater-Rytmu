#ifndef NOTE_H
#define NOTE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

class Poziom : public sf::Music {
private:
    int combo, input_number, max_combo;
    float hp=100;
    int m,p,gr,go,ok,miss = 0;
    float acc;
    float diff_gen;
    std::string song_name,song_file_name,song_notes_name,difficulty,background_name;
    float czas_piosenki;
    sf::Texture bkgr;
    sf::Sprite sprite;
public:
    Poziom(){}
    Poziom(std::string nazwa_piosenki, std::string nazwa_pliku_piosenki,std::string nazwa_pliku_notes, std::string backgr_name,std::string dif){
        //potrzebne nazwy
        song_name=nazwa_piosenki;
        song_file_name=nazwa_pliku_piosenki;
        song_notes_name=nazwa_pliku_notes;
        difficulty=dif;
        background_name=backgr_name;
        std::cout<<"Utworzono poziom"<<std::endl;
    }
    friend class Note;

    //sf::Music nie pozwala mi zdefiniować kilku rzeczy w konstruktorze, jak wczytywanie piosenki itd. Rozwiązanie to zewnętrzne wczytywanie lmao
    void inicjalizacja(){
        if(!bkgr.loadFromFile(background_name)){
            std::cerr <<"Could not load texture"<<std::endl;
                    return;
        }
        sprite.setTexture(bkgr);
        sf::Vector2f targetsize(300.f,300.f);
        sprite.setScale(targetsize.x / sprite.getLocalBounds().width, targetsize.y / sprite.getLocalBounds().height);
        sprite.setPosition(50,100);

        this->openFromFile(song_file_name);
        this->setVolume(2);
    }
    float Combo(){
        if(combo>max_combo)
            max_combo=combo;
        return combo;
    }
    float Accuracy(){
        return acc/input_number;
    }
    //wolę update'ować tą funkcją, niż sprawdzać przez kilka warunków w judgement xD
    void set_hp(){
        if(hp>100){
            hp=100;
        }
    }
    void scoreboard(){
        //jezeli zdaze to bedzie hit error chart ale to by wymagalo zapisywanie do wektora kazdego "hit time'u"
        sf::RenderWindow window(sf::VideoMode(600,600), "Scoreboard");
        while (window.isOpen()){

        }
    }
    void generate_level(){

    }
    void lose(sf::RenderWindow &window){
        if(hp<=0){
            std::cout<<"Przegrałeś!"<<std::endl;
            window.close();
            scoreboard();
        }
    }

  friend void gra(Poziom &poz);
  friend void song_selection();

};

class Note : public sf::CircleShape
{
    friend class Poziom;
public:
    Note(sf::Vector2f pos) : CircleShape(72){
        setPosition(pos);
        setFillColor(sf::Color(255, 255, 255));
    }
    Note(){};
    void animate(sf::Time elapsed)
    {
        move(0,vy*elapsed.asSeconds());
    }
    //do skonczenia
    bool check_range()
    {
        sf::FloatRect circlebounds = getGlobalBounds();
        if(circlebounds.top<800+vy*0.3 && circlebounds.top>800-vy*0.3) {return true;}
        else {return false;}
    }


    void Judgement(sf::Text &text,Poziom &poz){
        text.setCharacterSize(50);
        text.setPosition(900,100);
        sf::FloatRect circlebounds = getGlobalBounds();
        if(circlebounds.top<800+vy*0.05 && circlebounds.top>800-vy*0.05){
            text.setString("Marvelous!");
            std::cout<<"Marvelous!"<<std::endl;
            text.setFillColor(sf::Color(227, 226, 225));
            poz.combo++;
            poz.input_number++;
            poz.hp+=3;
            poz.acc+=1;
            poz.m++;
            return;
        }
        if(circlebounds.top<800+vy*0.1 && circlebounds.top>800-vy*0.1){
            text.setString("Perfect!");
            text.setFillColor(sf::Color(252, 231, 0));
            std::cout<<"Perfect!"<<std::endl;
            poz.combo++;
            poz.input_number++;
            poz.hp+=1.5;
            poz.acc+=0.95;
            poz.p++;
            return;
        } if(circlebounds.top<800+vy*0.15 && circlebounds.top>800-vy*0.15){
            text.setString("Great");
            text.setFillColor(sf::Color(49, 145, 7));
            std::cout<<"Great"<<std::endl;
            poz.combo++;
            poz.input_number++;
            poz.hp+=0.1;
            poz.acc+=0.6;
            poz.gr++;
            return;
        }  if(circlebounds.top<800+vy*0.2 && circlebounds.top>800-vy*0.2){
            text.setString("Good");
            text.setFillColor(sf::Color(2, 178, 237));
            std::cout<<"Good"<<std::endl;
            poz.combo++;
            poz.input_number++;
            poz.hp-=0.5;
            poz.acc+=0.4;
            poz.go++;
            return;
        } if(circlebounds.top<800+vy*0.25 && circlebounds.top>800-vy*0.25){
            text.setString("Okay");
            text.setFillColor(sf::Color(147, 6, 194));
            std::cout<<"Okay"<<std::endl;
            poz.combo++;
            poz.input_number++;
            poz.hp-=2;
            poz.acc+=0.1;
            poz.ok++;
            return;
        } if(circlebounds.top<800+vy*0.3 && circlebounds.top>800-vy*0.3){
            text.setString("Miss");
            text.setFillColor(sf::Color(191, 4, 4));
            std::cout<<"Miss"<<std::endl;
            poz.combo=0;
            poz.input_number++;
            poz.hp-=7;
            poz.acc+=0;
            poz.miss++;
            return;
        }
    }

    friend sf::Text input(std::vector<Note> &vec,sf::Text &text);
    friend void gra();
    friend void song_selection();
private:
    float vy=700;
};

class Button : public sf::RectangleShape{
private:

public:
    Button(sf::Vector2f size, sf::Vector2f pos)
        : RectangleShape(size)
    {
        setPosition(pos);
        setFillColor(sf::Color(123,123,123));
    }
    bool is_within(sf::RenderWindow &window){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::FloatRect rec_b = getGlobalBounds();
        if(position.x>=rec_b.left && position.x<=rec_b.left+rec_b.width && position.y>rec_b.top && position.y<rec_b.top+rec_b.height)
            return true;
        else
            return false;
    }
};





#endif // NOTE_H
