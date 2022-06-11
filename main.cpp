#include "note.h"
#include <ctime>
#include <random>

sf::Text input(std::vector<Note> &vec,sf::Text &text)
{
    text.setString("");

    if(!vec.empty()){

        if(!vec[0].check_range()&&vec[0].getGlobalBounds().top>800+vec[0].vy*0.3)
        {
            std::vector<Note>::iterator it=vec.begin();
            //vec[0].Judgement(text);
            vec.erase(it);
            return text;
        } if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&vec[0].check_range()){
            std::vector<Note>::iterator it=vec.begin();
            //vec[0].Judgement(text);
            vec.erase(it);
            return text;
        }
    }
    return text;
}

void gra(Poziom &poz){
sf::RenderWindow window(sf::VideoMode(1920, 1080), poz.song_name);

}

void song_selection(){
    sf::RenderWindow window(sf::VideoMode(800, 630), "Bohater rytmu");
    window.setFramerateLimit(60);
    //Sf::Music oraz jego klasy dziedziczące, muszą być używane za pomocą wskaźników
    std::vector<std::unique_ptr<Poziom>> Wybor_Poziomow;
    std::unique_ptr<Poziom> poz1 = std::make_unique<Poziom>("McMental at his best - McMental","McMental.ogg","McMental.txt","McMental.png","Szalony");
    Wybor_Poziomow.emplace_back(move(poz1));
    std::unique_ptr<Poziom> poz2 = std::make_unique<Poziom>("Super idol remix - Memnicus","johnxina.ogg","johnxina.txt","johnxina.png","Latwy");
    Wybor_Poziomow.emplace_back(move(poz2));

    std::cout<<"rozmiar kontenera"<<(int)Wybor_Poziomow.size()<<std::endl;
    for(const auto &s : Wybor_Poziomow)
        s->inicjalizacja();
    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
        return;

    //"iterator" XD
    int i=0;
    //przycisk lewy
    Button buttonL({20,20},{20,250});
    sf::Text buttonL_text;
    buttonL_text.setFont(font);
    buttonL_text.setCharacterSize(20);
    buttonL_text.setFillColor(sf::Color::White);
    buttonL_text.setPosition(24,247);
    buttonL_text.setString("<");
    //przycisk prawy
    Button buttonP({20,20},{360,250});
    sf::Text buttonP_text;
    buttonP_text.setFont(font);
    buttonP_text.setCharacterSize(20);
    buttonP_text.setFillColor(sf::Color::White);
    buttonP_text.setPosition(364,247);
    buttonP_text.setString(">");
    //przycisk wyjdź
    Button buttonExit({90,60},{50,550});
    //przycisk Play
    Button buttonPlay({90,60},{600,550});
    //texty używane w menu
    //0-wyjdz 1-play 2-vec[i]->song_name; 3-Poziom trudnosci 4->vec[i]->difficulty 5->Najlepszy wynik 6->W.I.P 7->Average NPS(Notes per seconds) 8->vec[i]->calculate_nps();
    std::vector<sf::Text> texty(9);
    for (auto &t : texty){
        t.setFont(font);
    }
    //przycisk wyjdz
    texty[0].setCharacterSize(45);
    texty[0].setFillColor(sf::Color::Red);
    texty[0].setString("Wyjdz");
    texty[0].setPosition(50,500);
    //przycisk play
    texty[1].setCharacterSize(45);
    texty[1].setFillColor(sf::Color::Green);
    texty[1].setString("Play!");
    texty[1].setPosition(600,500);

    for (int a=2;a<8;a++){
        texty[a].setCharacterSize(25);
        texty[a].setFillColor(sf::Color::White);
    }

    texty[2].setPosition(50,50);
    texty[3].setString("Poziom trudnosci");
    texty[3].setPosition(500,50);

    texty[4].setPosition(550,90);
    texty[5].setString("Najlepszy wynik");
    texty[5].setPosition(500,130);
    texty[6].setString("W.I.P");
    texty[6].setPosition(550,170);
    texty[7].setString("Average NPS");
    texty[7].setPosition(500,210);
    //do zrobienia float calculate_nps();
    texty[8].setString("15");
    texty[8].setPosition(550,250);

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    if(buttonL.is_within(window) && i!=0)
                        i--;
                    if(buttonP.is_within(window) && i<(int)Wybor_Poziomow.size()-1)
                        i++;
                    if(buttonExit.is_within(window))
                        window.close();
                    if(buttonPlay.is_within(window))
                        gra(*(Wybor_Poziomow[i]));
                }
            }
        //edycja tekstow tutaj bo iterator w petli
        texty[2].setString(Wybor_Poziomow[i]->song_name);
        texty[4].setString(Wybor_Poziomow[i]->difficulty);



        //odpalenie piosenki test

        //rysowanie przyciskow
        window.clear(sf::Color::Black);
        window.draw(buttonL);
        window.draw(buttonL_text);
        window.draw(buttonP);
        window.draw(buttonP_text);
        window.draw(Wybor_Poziomow[i]->sprite);
        for(auto &t : texty)
            window.draw(t);
        window.display();
    }
}


int main() {
song_selection();
}

