#include "note.h"
#include "Poziom.h"
#include "button.h"
#include <random>
#include <iomanip>
//generator liczb losowych do funkcji, potrzebny do funkcji generującej na bieżąco poziom.
int radom(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(1,4);
    return dist4(rng);
}
//okno zawierające obrazek z "instrukcją"
void intro(){
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

void song_selection(){
    sf::RenderWindow window(sf::VideoMode(800, 630), "Bohater rytmu");
    window.setFramerateLimit(60);
    //Tworzymy kontener na poziomy oraz same poziomy.
    std::vector<std::unique_ptr<Poziom>> Wybor_Poziomow;
    std::unique_ptr<Poziom> poz1 = std::make_unique<Poziom>("McMental at his best - McMental","McMental.ogg","McMental.png","Szalony",1.8);
    Wybor_Poziomow.emplace_back(move(poz1));
    std::unique_ptr<Poziom> poz2 = std::make_unique<Poziom>("Super idol remix - Memnicus","johnxina.ogg","johnxina.png","Latwy",7);
    Wybor_Poziomow.emplace_back(move(poz2));
    std::unique_ptr<Poziom> poz3 = std::make_unique<Poziom>("Egzamin z Psio","egzamin.ogg","egzamin.png","Pojebany",0.05);
    Wybor_Poziomow.emplace_back(move(poz3));
    std::unique_ptr<Poziom> poz4 = std::make_unique<Poziom>("Macius Level","Macius.ogg","Macius.png","Średni",6.1904761904761904761904761904762);
    Wybor_Poziomow.emplace_back(move(poz4));


    //wczytywanie fontu do textów używanych w menu
    //teoretycznie mozna zamiast textow zrobic 1 duzy obrazek z ktorego grafika przycisku była by wykorzystywana. Do przemyślenia
    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
        return;

    //"iterator" XD - do zmiany na elegancki iterator wektorowy
    int i=0;
    Wybor_Poziomow[i]->inicjalizacja();
    //przyciski do wymiany, modyfikacja klasy tak żeby wszystko od razu zrobila jak wrzuce mu te dane do konstruktora
    //przycisk lewy, scroll piosenek w lewo
    Button buttonL({20,20},{20,250});
    sf::Text buttonL_text;
    buttonL_text.setFont(font);
    buttonL_text.setCharacterSize(20);
    buttonL_text.setFillColor(sf::Color::White);
    buttonL_text.setPosition(24,247);
    buttonL_text.setString("<");
    //przycisk prawy scroll piosenek w prawo
    Button buttonP({20,20},{360,250});
    sf::Text buttonP_text;
    buttonP_text.setFont(font);
    buttonP_text.setCharacterSize(20);
    buttonP_text.setFillColor(sf::Color::White);
    buttonP_text.setPosition(364,247);
    buttonP_text.setString(">");
    //button poradnik
    Button buttonU({90,60},{325,500});
    sf::Text buttonU_text;
    buttonU_text.setFont(font);
    buttonU_text.setCharacterSize(45);
    buttonU_text.setFillColor(sf::Color::Yellow);
    buttonU_text.setPosition(325,500);
    buttonU_text.setString("Intro");
    //przycisk wyjdź, wyjdzie z programy
    Button buttonExit({90,60},{50,500});
    //przycisk Play, rozpocznie poziom
    Button buttonPlay({90,60},{600,500});
    //texty używane w menu
    //tu też niektóre napewno do wymiany, te które "dynamicznie się dostosywują" zostaną.
    //0-wyjdz 1-play 2-nazwa wybranej piosenki; 3-Poziom trudnosci 4->trudnosc wybranej piosenki 5->Najlepszy wynik 6->W.I.P(wczytywanie i zapisywanie best score) 7->Average NPS(Notes per seconds) 8->vec[i]->calculate_nps();
    std::vector<sf::Text> texty(9);
    for (auto &t : texty){
        t.setFont(font);
    }
    //text przycisku wyjdz
    texty[0].setCharacterSize(45);
    texty[0].setFillColor(sf::Color::Red);
    texty[0].setString("Wyjdz");
    texty[0].setPosition(50,500);
    //text przycisku play
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
    //do zrobienia zapisywanie najlepszego wyniku do pliku txt i wczytywanie go.
    texty[6].setString("W.I.P");
    texty[6].setPosition(550,170);
    texty[7].setString("Average NPS");
    texty[7].setPosition(500,210);

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
                if(buttonL.is_within(window) && i!=0){
                    i--;
                    Wybor_Poziomow[i]->inicjalizacja();
                }
                if(buttonP.is_within(window) && i<(int)Wybor_Poziomow.size()-1){
                    i++;
                    Wybor_Poziomow[i]->inicjalizacja();
                }
                if(buttonU.is_within(window))
                    intro();
                if(buttonExit.is_within(window))
                    window.close();
                if(buttonPlay.is_within(window))
                    gra(*(Wybor_Poziomow[i]));
            }
        }
        //edycja tekstow tutaj bo iterator w petli zeby mi update'owalo
        texty[2].setString(Wybor_Poziomow[i]->song_name);
        texty[4].setString(Wybor_Poziomow[i]->difficulty);
        std::setprecision(2);
        texty[8].setString(std::to_string(Wybor_Poziomow[i]->calculate_actual_nps()));
        //odpalenie piosenki test

        //rysowanie przyciskow
        window.clear(sf::Color::Black);
        window.draw(buttonL);
        window.draw(buttonL_text);
        window.draw(buttonP);
        window.draw(buttonP_text);
        window.draw(buttonU);
        window.draw(buttonU_text);
        window.draw(Wybor_Poziomow[i]->sprite);
        for(auto &t : texty)
            window.draw(t);
        window.display();
    }
}

void Judgement(sf::Text &text,Poziom &poz,Note &note){
    sf::FloatRect circlebounds = note.getGlobalBounds();
    if(circlebounds.top<800+note.return_speed()*0.02 && circlebounds.top>800-note.return_speed()*0.02){
        poz.Marvelous(text);
        return;
    }
    if(circlebounds.top<800+note.return_speed()*0.05 && circlebounds.top>800-note.return_speed()*0.05){
        poz.Perfect(text);
        return;
    }
    if(circlebounds.top<800+note.return_speed()*0.08 && circlebounds.top>800-note.return_speed()*0.08){
        poz.Great(text);
        return;
    }
    if(circlebounds.top<800+note.return_speed()*0.1 && circlebounds.top>800-note.return_speed()*0.1){
        poz.Good(text);
        return;
    }
    if(circlebounds.top<800+note.return_speed()*0.12 && circlebounds.top>800-note.return_speed()*0.12){
        poz.Ok(text);
        return;
    }
    if(circlebounds.top>800+note.return_speed()*0.14){
        poz.Miss(text);
    }
}
sf::Text input(std::vector<Note> &vec,sf::Text &text,Poziom &poz)
{
    if(!vec.empty()){
        std::vector<Note>::iterator it=vec.begin();
        if(it->check_range()){
            {
                Judgement(text,poz,*it);
                vec.erase(it);
                return text;
            }
        }
    }
    return text;
}
sf::Text input_Miss(std::vector<Note> &vec,sf::Text &text,Poziom &poz)
{
    if(!vec.empty()){
        std::vector<Note>::iterator it=vec.begin();
        if(!it->check_range()&&it->getGlobalBounds().top>800+it->return_speed()*0.14)
        {
            Judgement(text,poz,*it);
            vec.erase(it);
            return text;
        }
    }
    return text;
}
void generate_level(std::vector<Note> &LineD,std::vector<Note> &LineF,std::vector<Note> &LineJ,std::vector<Note> &LineK,float nps,sf::Clock &clock){
    //tu warunek czasowy, że jeżeli czas sie pokrywa to siema
    if(nps*1000<=clock.getElapsedTime().asMilliseconds()){
        int losowy=radom();
        if(losowy==1){
            LineD.emplace_back(Note({650,-200}));

        }
        if(losowy==2){
            LineF.emplace_back(Note({806,-200}));

        }
        if(losowy==3){
            LineJ.emplace_back(Note({962,-200}));

        }
        if(losowy==4){
            LineK.emplace_back(Note({1118,-200}));

        }
        clock.restart();
    }
}
void gra(Poziom &poz){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), poz.song_name);
    poz.reset_stats();
    //clock do animacji
    sf::Clock clock;
    //clock do pomiaru czasu poziomu;
    sf::Clock notes_clock;
    sf::Clock music_time;
    //tworzenie line'ów
    std::vector<Note> vecD,vecF,vecJ,vecK;

    //Tutaj tworzenie obiektów samej gry

    //zamiana danych obrazka poziomu, tak żeby był on "w tle"
    sf::Vector2f targetsize(1920.f,1080.f);
    poz.sprite.setScale(targetsize.x / poz.sprite.getLocalBounds().width, targetsize.y / poz.sprite.getLocalBounds().height);
    poz.sprite.setPosition(0,0);

    //tworzenie textow (Ocena gry + combo)
    std::vector<sf::Text> texty(2);
    sf::Font font;
    if(!font.loadFromFile("arial.ttf")) {return;}
    for (auto &t: texty){
        t.setFont(font);
        t.setCharacterSize(45);
        t.setPosition(776,500);
    }
    texty[1].setPosition(899,520);
    //vsrg czyli czarny prostokat w tle + background dla wynikow ingame
    sf::RectangleShape vs(sf::Vector2f(644.0, 1080.0));
    vs.setPosition(640,0);
    vs.setFillColor(sf::Color(0,0,0));
    sf::RectangleShape siema(sf::Vector2f(300.0,200.0));
    siema.setPosition(window.getSize().x-siema.getGlobalBounds().width,0);
    siema.setFillColor(sf::Color::Black);
    //Tworzenie judgement line
    std::vector<sf::CircleShape> Judgement_Line;
    for (int i=0;i<4;i++)
    {
        Judgement_Line.emplace_back(sf::CircleShape(72));
        Judgement_Line[i].setOutlineThickness(4);
        Judgement_Line[i].setFillColor(sf::Color(0,0,0));
        Judgement_Line[i].setOutlineColor(sf::Color(105,105,105));
        Judgement_Line[i].setPosition((650+i*12+i*144),800);
    }
    //rozpoczacie poziomu
    //wczytanie potrzebnych danych
    poz.inicjalizacja_poziomu();
    //rozpoczecie grania piosenki,restart "timerów"
    music_time.restart();
    poz.play();
    notes_clock.restart();
    //tutaj petla otwartego okna
    while (window.isOpen()) {
        //czas do animacji obiektu
        sf::Time elapsed = clock.restart();
        //funkcja dodająca obiekty do poszczególnych wektorów w zalezności od trudnosci poziomu.
        generate_level(vecD,vecF,vecJ,vecK,poz.calculate_nps(),notes_clock);


        // Poziom management, sprawdzenie czy gracz przegrał/ukonczył/wyszedł/zapauzował //do zrobienia pauza
        poz.lose(window);
        poz.set_hp();
        poz.end(window,music_time);
        //tutaj kolejne texty itd


        //sprawdzanie eventu
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                poz.scoreboard();
                poz.back_to_menu();
                window.close();
                poz.stop();
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::D){
                    input(vecD,texty[0],poz);

                }
                if(event.key.code==sf::Keyboard::F){
                    input(vecF,texty[0],poz);

                }
                if(event.key.code==sf::Keyboard::J){
                    input(vecJ,texty[0],poz);

                }
                if(event.key.code==sf::Keyboard::K){
                    input(vecK,texty[0],poz);

                }

            }

        }
        //sprawdzanie judgementu czy nie wylazła z zakresu, czyli dalej sam element gry oceniający rozgrywke gracza
        input_Miss(vecD,texty[0],poz);
        input_Miss(vecF,texty[0],poz);
        input_Miss(vecJ,texty[0],poz);
        input_Miss(vecK,texty[0],poz);
        //tutaj zaczynamy rysowanie + zmiane textu w zaleznosci od wykonanych funkcji

        texty[1].setString(std::to_string(poz.Combo()));
        //animacja
        window.clear(sf::Color::Black);
        for(auto &kola : vecD)
            kola.animate(elapsed);
        for(auto &kola : vecF)
            kola.animate(elapsed);
        for(auto &kola : vecJ)
            kola.animate(elapsed);
        for(auto &kola : vecK)
            kola.animate(elapsed);

        //rysowanie

        window.draw(poz.sprite);
        window.draw(vs);
        window.draw(siema);


        //tak, mozna by wrzucić wektory w jeden wektor i podwójną pętlę machnąć.
        for(auto &kola : Judgement_Line)
            window.draw(kola);
        for(auto &kola : vecD)
            window.draw(kola);
        for(auto &kola : vecF)
            window.draw(kola);
        for(auto &kola : vecJ)
            window.draw(kola);
        for(auto &kola : vecK)
            window.draw(kola);
        for(auto &t : texty)
            window.draw(t);
        //end current frame
        window.display();

    }


}
