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
    int multi_input=1;
    bool has_multi=0;
public:
    friend class Note;
    Poziom();
    Poziom(std::string nazwa_piosenki, std::string nazwa_pliku_piosenki,std::string backgr_name,std::string dif,float diff,int mult_input);
    void inicjalizacja();
    void inicjalizacja_poziomu();
    //tutaj funkcje zwracajace/liczace proste wartosci
    void Max_Combo();
    int Combo();
    float Accuracy();
    float give_hp();
    void set_hp();
    //funkcje managementu miedzy poziomami, wyswietlanie statystyk, konczenie poziomu,zmiana patternu
    void reset_stats();
    void scoreboard();
    void back_to_menu();
    void change_pattern();
    //Funkcje kończące poziom jeżeli Gracz skonczy poziom/przegra.
    void end(sf::RenderWindow &window,sf::Clock &clock);
    void lose(sf::RenderWindow &window);
    //funkcje kalkulujące potrzebne do generacji poziomu/wyswietlenia danych poziomu
    float calculate_nps();
    float calculate_actual_nps();
    //do zrobienia, wyswietla w menu te wszystkie nazwy i te inne drobnostki
    void wyswietl_staty(sf::RenderWindow &window);
    //metoda oceniajaca postepy gracza
    void Judgement(sf::Text &text, Note &note, sf::Shape &circle, sf::Shape &rectangle);
    //Funkcje Judgement zmieniające prywatne skladowe poziomu
    void Marvelous(sf::Text &text,sf::Shape &circle,sf::Shape &rectangle);
    void Perfect(sf::Text &text,sf::Shape &circle,sf::Shape &rectangle);
    void Great(sf::Text &text,sf::Shape &circle,sf::Shape &rectangle);
    void Good(sf::Text &text,sf::Shape &circle,sf::Shape &rectangle);
    void Ok(sf::Text &text,sf::Shape &circle,sf::Shape &rectangle);
    void Miss(sf::Text &text,sf::Shape &circle,sf::Shape &rectangle);
    //funkcje inputowe, management obiektow
    sf::Text input(std::vector<Note> &vec, sf::Text &text, sf::Shape &circle, std::vector<std::unique_ptr<sf::Shape> > &recs);
    sf::Text input_Miss(std::vector<Note> &vec, sf::Text &text, sf::Shape &circle, std::vector<std::unique_ptr<sf::Shape> > &recs);
    //random number generator
    int radom();
    //tutaj funkcje tworzenia poziomu + gra
    void create_shapes(std::vector<std::unique_ptr<sf::Shape>> &vecptr);
    void generate_level(std::vector<std::vector<Note>> &WekDFJK,float nps,sf::Clock &clock,sf::Clock &leveltimer);
    void gra();
    void animacja();
    friend void song_selection();


};




#endif // POZIOM_H
