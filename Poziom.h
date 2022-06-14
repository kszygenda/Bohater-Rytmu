#ifndef POZIOM_H
#define POZIOM_H
#include "note.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


class Poziom : public sf::Music {
private:

    bool initialized=0;
    float diff_gen;
    std::string song_name,song_file_name,song_notes_name,difficulty,background_name;
    sf::Texture bkgr;
    sf::Sprite sprite;
    int m,p,gr,go,ok,miss = 0;
    int combo, input_number, max_combo;
    float hp=100;
    float acc;
public:
    friend class Note;
    Poziom();
    Poziom(std::string nazwa_piosenki, std::string nazwa_pliku_piosenki,std::string backgr_name,std::string dif,float diff);
    void inicjalizacja();
    void Max_Combo();
    int Combo();
    float Accuracy();
    int give_hp();
    void set_hp();
    void reset_stats();
    void scoreboard();
    void inicjalizacja_poziomu();
    void back_to_menu();
    float calculate_nps();
    float calculate_actual_nps();
    //Funkcje Judgement zmienające prywatne skladowe poziomu
    void Marvelous(sf::Text &text);
    void Perfect(sf::Text &text);
    void Great(sf::Text &text);
    void Good(sf::Text &text);
    void Ok(sf::Text &text);
    void Miss(sf::Text &text);
    //Funkcje kończące poziom jeżeli Gracz skonczy poziom/przegra/wyjdzie z poziomu
    //do zrobienia wyjście z poziomu
    void end(sf::RenderWindow &window,sf::Clock &clock);
    void lose(sf::RenderWindow &window);
    friend void gra(Poziom &poz);
    friend void song_selection();


};




#endif // POZIOM_H
