#include "Poziom.h"
#include "note.h"
#include "button.h"
#include <iomanip>
#include <random>
#include <stdlib.h>
Poziom::Poziom(){

}
Poziom::Poziom(std::string nazwa_piosenki, std::string nazwa_pliku_piosenki, std::string backgr_name,std::string dif,float diff,int mult_input){
    //potrzebne nazwy
    song_name=nazwa_piosenki;
    song_file_name=nazwa_pliku_piosenki;
    difficulty=dif;
    bkgr.loadFromFile(backgr_name);
    diff_gen=diff;
    if(mult_input!=1){
        has_multi=1;
        multi_input=mult_input;
    }
}

//tutaj funkcje chyba "czysto optymalizacyjne", jezeli nie wybrany nie ma co wczytywac jego wszystkich danych
void Poziom::inicjalizacja(){
    if(!initialized){
        sprite.setTexture(bkgr);
        sf::Vector2f targetsize(300.f,300.f);
        sprite.setScale(targetsize.x / sprite.getLocalBounds().width, targetsize.y / sprite.getLocalBounds().height);
        sprite.setPosition(50,100);
        initialized=1;
    }
}
//funkcja wczytująca piosenkę (uzywana gdy rozpoczniemy poziom)
void Poziom::inicjalizacja_poziomu(){
    this->openFromFile(song_file_name);
    this->setVolume(5);
    if(multi_input>1)
        has_multi=1;
    else has_multi=0;
}


//funkcja do liczb losowych
int Poziom::radom(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(1,4);
    return dist4(rng);
}
//funckcje zwracające wartości (potrzebne do rysowania lub do wynikow)
void Poziom::Max_Combo(){
    if(combo>max_combo)
        max_combo=combo;
}
int Poziom::Combo(){
    return combo;
}
//funkcja potrzebna do update'owania hp_bar'u
float Poziom::give_hp(){
    return hp;
}

//funkcja zmieniajaca pattern poziomu
void Poziom::change_pattern(){
    if(multi_input<4)
        multi_input++;
    else multi_input=1;
}

float Poziom::Accuracy(){
    if(acc>1)
        return acc/input_number;
    else return 0;
}
void Poziom::set_hp(){
    if(hp>100){
        hp=100;
    }
}
//restart zeby po przegraniu mozna bylo na nowo rozpoczac poziom, teoretycznie mozna zrobic funkcje gra ktora dostaje kopie, proste rozwiazanie problemu.
void Poziom::reset_stats(){
    m=0;
    p=0;
    gr=0;
    go=0;
    ok=0;
    miss=0;
    combo=0;
    max_combo=0;
    acc=0;
    input_number=0;
    hp=100;
}
void Poziom::back_to_menu(){
    sf::Vector2f targetsize(300.f,300.f);
    sprite.setScale(targetsize.x / sprite.getLocalBounds().width, targetsize.y / sprite.getLocalBounds().height);
    sprite.setPosition(50,100);
}
//funkcja licząca nps ktory jest potrzebny do generacji (tak aby się zgadzał z actual nps)
float Poziom::calculate_nps(){
    float bonus=13/diff_gen;
    return 1/bonus;
}
//funkcja ktora oblicza faktyczny nps poziomu
float Poziom::calculate_actual_nps(){
    return multi_input*(13/diff_gen);
}

//funkcja wyswietlajaca dane poziomu (nazwa piosenki, poziom trudnosci, nps, pattern)
void Poziom::wyswietl_staty(sf::RenderWindow &window){
    //texty używane w menu
    //0-nazwa wybranej piosenki 1-poziom trudnosc 2-difficulty 3-NPS (ilosc nut na sekunde) 4-calculate_actual_nps(); 5-pattern type 6-(funkcja switch)
    std::vector<sf::Text> texty(7);
    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
        return;
    for (auto &t :texty){
        t.setFont(font);
        t.setCharacterSize(25);
        t.setFillColor(sf::Color::White);
    }
    texty[0].setString(song_name);
    texty[0].setPosition(50,50);
    texty[1].setString("Poziom trudnosci:");
    texty[1].setPosition(500,50);
    texty[2].setString(difficulty);
    texty[2].setPosition(550,80);
    texty[3].setString("NPS:");
    texty[3].setPosition(500,120);
    texty[4].setString(std::to_string(calculate_actual_nps()));
    texty[4].setPosition(530,150);
    texty[5].setString("Typ patternu:");
    texty[5].setPosition(500,190);
    texty[6].setPosition(500,220);
    //swtich
    switch(multi_input){
    case 1:
        texty[6].setString("Stream");
        break;
    case 2:
        texty[6].setString("Double stream");
        break;
    case 3:
        texty[6].setString("Jacks");
        break;
    case 4:
        texty[6].setString("Vibro");
        break;
    }
    for(auto &t:texty){
        window.draw(t);
    }

}
//funkcje manage'ujace czy poziom się skonczyl/wylaczyl/gracz przegral;
void Poziom::lose(sf::RenderWindow &window){
    if(hp<=0){
        system ("CLS");
        std::cout<<"Przegrales!"<<std::endl;
        back_to_menu();
        window.close();
        stop();
        scoreboard();
    }
}
void Poziom::end(sf::RenderWindow &window,sf::Clock &clock){
    if(getDuration().asMilliseconds()<clock.getElapsedTime().asMilliseconds()){
        system ("CLS");
        std::cout<<"Udalo ci sie przejsc poziom! "<<std::endl;
        back_to_menu();
        window.close();
        stop();
        scoreboard();
        animacja();
    }
}
//funkcja zwracajaca wyniki po ukonczeniu poziomu (lub po wyjsciu z niego lub przegranej)
void Poziom::scoreboard(){
    //jezeli zdaze to bedzie hit error chart ale to by wymagalo zapisywanie do wektora kazdego "hit time'u"
    std::cout<<"Poziom: "<<song_name<<std::endl;
    std::cout<<"Marvelous! : "<<m<<std::endl;
    std::cout<<"Perfect! : "<<p<<std::endl;
    std::cout<<"Great : "<<gr<<std::endl;
    std::cout<<"Good : "<<go<<std::endl;
    std::cout<<"Okay : "<<ok<<std::endl;
    std::cout<<"Miss : "<<miss<<std::endl;
    std::cout<<"Max combo : "<<max_combo<<std::endl;
    std::cout<<"Accuracy : "<<Accuracy()*100<<"%"<<std::endl;

}
//Funkcja wywolywana przy inpucie (sf::Text input dalej)
void Poziom::Judgement(sf::Text &text,Note &note){
    sf::FloatRect circlebounds = note.getGlobalBounds();
    if(circlebounds.top<800+note.return_speed()*0.02 && circlebounds.top>800-note.return_speed()*0.02){
        Marvelous(text);
        return;
    }
    if(circlebounds.top<800+note.return_speed()*0.05 && circlebounds.top>800-note.return_speed()*0.05){
        Perfect(text);
        return;
    }
    if(circlebounds.top<800+note.return_speed()*0.08 && circlebounds.top>800-note.return_speed()*0.08){
        Great(text);
        return;
    }
    if(circlebounds.top<800+note.return_speed()*0.1 && circlebounds.top>800-note.return_speed()*0.1){
        Good(text);
        return;
    }
    if(circlebounds.top<800+note.return_speed()*0.12 && circlebounds.top>800-note.return_speed()*0.12){
        Ok(text);
        return;
    }
    if(circlebounds.top>800+note.return_speed()*0.14){
        Miss(text);
    }
}
//funkcja input czyli reagująca na "granie" gracza
sf::Text Poziom::input(std::vector<Note> &vec,sf::Text &text)
{
    if(!vec.empty()){
        std::vector<Note>::iterator it=vec.begin();
        if(it->check_range()){
            {
                Judgement(text,*it);
                vec.erase(it);
                return text;
            }
        }
    }
    return text;
}
//funkcja input_miss czyli reagowanie czy obiekt nie wyszedł poza obszar oceny, jezeli tak to usuwa go i zwraca "Miss"
sf::Text Poziom::input_Miss(std::vector<Note> &vec,sf::Text &text)
{
    if(!vec.empty()){
        std::vector<Note>::iterator it=vec.begin();
        if(!it->check_range()&&it->getGlobalBounds().top>800+it->return_speed()*0.14)
        {
            Judgement(text,*it);
            vec.erase(it);
            return text;
        }
    }
    return text;
}
//funkcje judgementu, ocena gry w czasie rzeczywistym
void Poziom::Marvelous(sf::Text &text){
    text.setString("Marvelous!");
    text.setFillColor(sf::Color(227, 226, 225));
    combo++;
    input_number++;
    hp+=3;
    acc+=1;
    m++;
}
void Poziom::Perfect(sf::Text &text){
    text.setString("Perfect!");
    text.setFillColor(sf::Color(252, 231, 0));
    combo++;
    input_number++;
    hp+=1.5;
    acc+=0.925;
    p++;
}
void Poziom::Great(sf::Text &text){
    text.setString("Great");
    text.setFillColor(sf::Color(49, 145, 7));
    combo++;
    input_number++;
    hp+=0.1;
    acc+=0.4;
    gr++;
}
void Poziom::Good(sf::Text &text){
    text.setString("Good");
    text.setFillColor(sf::Color(2, 178, 237));
    combo++;
    input_number++;
    hp-=0.5;
    acc+=0;
    go++;
}
void Poziom::Ok(sf::Text &text){
    text.setString("Okay");
    text.setFillColor(sf::Color(147, 6, 194));
    combo++;
    input_number++;
    hp-=2;
    acc+=-1;
    ok++;
}
void Poziom::Miss(sf::Text &text){
    text.setString("Miss");
    text.setFillColor(sf::Color(191, 4, 4));
    combo=0;
    input_number++;
    hp-=7;
    acc+=-0.5;
    miss++;
}

void Poziom::animacja(){
    sf::RenderWindow window(sf::VideoMode(600,600),"Wygrana! " +song_name);
    sf::Texture texture;
    if(!texture.loadFromFile("walltalking.png"))
        return;
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::IntRect spriteRect(0,0,320,180);
    sprite.setTextureRect(spriteRect);
    sprite.setPosition(140,210);
    sf::Clock clock;
    std::vector<sf::Text> texty(2);
    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
        return;
    for(auto &t : texty){
        t.setFont(font);
        t.setFillColor(sf::Color::Black);
        t.setOutlineColor(sf::Color::Green);
        t.setOutlineThickness(2);
        t.setCharacterSize(40);
    }
    texty[0].setString("Wygrales!");
    texty[0].setPosition(220,120);
    texty[1].setString("Wyniki poziomu sa w konsoli");
    texty[1].setPosition(50,420);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        if(clock.getElapsedTime().asMilliseconds() > 150){
            if(spriteRect.left==4800) {spriteRect.left=0;}
            else spriteRect.left+=320;
            sprite.setTextureRect(spriteRect);
            clock.restart();
        }
        window.clear(sf::Color::Black);
        window.draw(sprite);
        for(auto &t:texty)
            window.draw(t);
        window.display();
    }
}
//funkcja generująca poziom

void Poziom::generate_level(std::vector<std::vector<Note>> &WekDFJK, float nps, sf::Clock &clock,sf::Clock &leveltimer){
    //tu warunek czasowy, że jeżeli czas sie pokrywa to dodaje obiekt do wektora + warunek czasowy który przestanie generowac obiekty jezeli czas zbliza sie do konca
    if(nps*1000<=clock.getElapsedTime().asMilliseconds() && getDuration().asMilliseconds()>leveltimer.getElapsedTime().asMilliseconds()+800){
        //losowanie do którego wektora zostanie dodany, czyli in game w której linii nam się pojawi (D,F,J,K)
        int losowy=radom();
        //ten float powstał tylko dlatego, że nie pozwala mi wrzucić mnożenia w konstruktorze
        float generacja = 650+(losowy-1)*156;
        //tutaj warunek generacji poziomu typu double/jacks/vibro (to są nazwy konkretnych patternów w grze, oznaczają odpowiednio podwójne,potrójne i poczwórne multihity)
        if(!has_multi){
            WekDFJK[losowy-1].emplace_back(Note({generacja,-200}));
        }
        if(has_multi) {
            int losowy2=radom();
            int losowy3=radom();
            float generacja2,generacja3;
            while (losowy==losowy2) {losowy2=radom();}
            switch(multi_input){
            //double stream
            case 2:
            {
                generacja2 = 650+(losowy2-1)*156;
                WekDFJK[losowy-1].emplace_back(Note({generacja,-200}));
                WekDFJK[losowy2-1].emplace_back(Note({generacja2,-200}));
                //do napisania dodawanie do tych wektorów
                break;
            }
                //jacks
            case 3:
            {
                while(losowy==losowy3 || losowy2==losowy3){losowy3=radom();}
                generacja2 = 650+(losowy2-1)*156;
                generacja3 = 650+(losowy3-1)*156;
                WekDFJK[losowy-1].emplace_back(Note({generacja,-200}));
                WekDFJK[losowy2-1].emplace_back(Note({generacja2,-200}));
                WekDFJK[losowy3-1].emplace_back(Note({generacja3,-200}));
                break;
            }
                //vibro
            case 4:
            {
                int iteratorXD=0;
                float generatorXD;
                for (auto &t : WekDFJK){
                    generatorXD=650+iteratorXD*156;
                    t.emplace_back(Note({generatorXD,-200}));
                    iteratorXD++;
                }
                iteratorXD=0;
                generatorXD=0;
                break;
            }
            }
        }
        clock.restart();
    }
}

void Poziom::create_shapes(std::vector<std::unique_ptr<sf::Shape>> &vecptr){
    //funkcja edytująca wektor(dodajaca obiekty) aby mial wszystkie potrzebne figury
    vecptr.emplace_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(644.0,1080.0)));
    vecptr.emplace_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(300.0,200.0)));
    vecptr.emplace_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(280.0,30.0)));
    for(int i=0;i<4;i++)
        vecptr.emplace_back(std::make_unique<sf::CircleShape>(72));
    //inicjalizacja kół
    for(int i=3;i<7;i++){
        (*vecptr[i]).setOutlineThickness(4);
        (*vecptr[i]).setFillColor(sf::Color::Black);
        (*vecptr[i]).setOutlineColor(sf::Color(105,105,105));
        (*vecptr[i]).setPosition((640+156*(i-3)),800);
    }
    //kolor vsrg bckgr
    for(int i=0;i<2;i++){
        (*vecptr[i]).setFillColor(sf::Color::Black);
    }
    //0-vsrg 1-bckgr 2-hp
    (*vecptr[2]).setFillColor(sf::Color::Red);
    (*vecptr[0]).setPosition(640,0);
    (*vecptr[1]).setPosition(1620,0);
    (*vecptr[2]).setPosition(1630,130);
}
//funkcja gameplayu
void Poziom::gra(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080),song_name);
    //restartujemy statystyki poziomu, ponieważ są one cały czas w pamięci
    reset_stats();
    //clock do animacji,tworzenia obiektow,konczenia poziomu
    sf::Clock clock,notes_clock,music_time;
    //tworzenie line'ów
    std::vector<Note> vecD,vecF,vecJ,vecK;
    //jako argument funkcji generate level (po zmianie) potrzeba wektora wektorów
    std::vector<std::vector<Note>> vecDFJK;
    vecDFJK.emplace_back(vecD);
    vecDFJK.emplace_back(vecF);
    vecDFJK.emplace_back(vecJ);
    vecDFJK.emplace_back(vecK);
    //szczerze nie mam narazie pomyslu jak to zoptymalizowac

    //zamiana danych obrazka poziomu, tak żeby był on "w tle"
    sf::Vector2f targetsize(1920.f,1080.f);
    sprite.setScale(targetsize.x / sprite.getLocalBounds().width, targetsize.y / sprite.getLocalBounds().height);
    sprite.setPosition(0,0);

    //testowy polimorfizm (Judgement Line, box vsrg, box na bckgr accuracy;
    std::vector<std::unique_ptr<sf::Shape>> shapes;
    create_shapes(shapes);

    //tworzenie textow (Ocena gry + combo + accuracy)
    std::vector<sf::Text> texty(3);
    sf::Font font;
    if(!font.loadFromFile("arial.ttf")) {return;}
    for (auto &t: texty){
        t.setFont(font);
        t.setCharacterSize(45);

    }
    texty[0].setPosition(850,350); //text Judge
    texty[1].setPosition(910,390); //combo
    texty[2].setPosition(1650,60); //accuracy
    //rozpoczacie poziomu
    //wczytanie potrzebnych danych
    inicjalizacja_poziomu();
    //rozpoczecie grania piosenki,restart "timerów"
    music_time.restart();
    play();
    notes_clock.restart();
    //tutaj petla otwartego okna
    while (window.isOpen()) {
        //czas do animacji obiektu
        sf::Time elapsed = clock.restart();
        //funkcja dodająca obiekty do poszczególnych wektorów w zalezności od trudnosci poziomu.
        generate_level(vecDFJK,calculate_nps(),notes_clock,music_time);


        // Poziom management, sprawdzenie czy gracz przegrał/ukonczył/wyszedł/zapauzował //do zrobienia pauza
        lose(window);
        set_hp();
        end(window,music_time);
        Max_Combo();
        //tutaj kolejne texty itd


        //sprawdzanie eventu
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                std::cout<<"wyjscie z poziomu"<<std::endl;
                scoreboard();
                back_to_menu();
                window.close();
                stop();
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::D){
                    input(vecDFJK[0],texty[0]);

                }
                if(event.key.code==sf::Keyboard::F){
                    input(vecDFJK[1],texty[0]);

                }
                if(event.key.code==sf::Keyboard::J){
                    input(vecDFJK[2],texty[0]);

                }
                if(event.key.code==sf::Keyboard::K){
                    input(vecDFJK[3],texty[0]);

                }

            }

        }
        //sprawdzanie judgementu czy nie wylazła z zakresu, czyli dalej sam element gry oceniający rozgrywke gracza
        input_Miss(vecDFJK[0],texty[0]);
        input_Miss(vecDFJK[1],texty[0]);
        input_Miss(vecDFJK[2],texty[0]);
        input_Miss(vecDFJK[3],texty[0]);
        //tutaj zaczynamy rysowanie + zmiane textu w zaleznosci od wykonanych funkcji
        texty[1].setString(std::to_string(Combo()));
        texty[2].setString(std::to_string(100*Accuracy())+"%");
        if(hp>0)
            (*shapes[2]).setScale(give_hp()/100,1);
        //animacja
        window.clear(sf::Color::Black);
        for(auto &vec : vecDFJK)
            for(auto &vecc : vec)
                vecc.animate(elapsed);

        //rysowanie

        window.draw(sprite);
        for(const auto &s :shapes)
            window.draw(*s);


        //tak, mozna by wrzucić wektory w jeden wektor i podwójną pętlę machnąć.
        //zaawansowana podwójna pętla lmao
        for(auto &vec : vecDFJK)
            for(auto &vecc : vec)
                window.draw(vecc);

        for(auto &t : texty)
            window.draw(t);
        //end current frame
        window.display();

    }


}
//funkcja menu gry
void song_selection(){
    sf::RenderWindow window(sf::VideoMode(800, 630), "Bohater rytmu");
    window.setFramerateLimit(60);
    //Tworzymy kontener na poziomy oraz same poziomy.
    std::vector<std::unique_ptr<Poziom>> Wybor_Poziomow;
    std::unique_ptr<Poziom> poz1 = std::make_unique<Poziom>("Super idol remix - Memnicus","johnxina.ogg","johnxina.png","Latwy",3.12,1);
    Wybor_Poziomow.emplace_back(move(poz1));
    std::unique_ptr<Poziom> poz2 = std::make_unique<Poziom>("24kGoldn - Mood ft. Iann Dior","Mood.ogg","mood.png","Bardzo trudny",4.28,3);
    Wybor_Poziomow.emplace_back(move(poz2));
    std::unique_ptr<Poziom> poz3 = std::make_unique<Poziom>("McMental at his best - McMental","McMental.ogg","McMental.png","Szalony",2.216,2);
    Wybor_Poziomow.emplace_back(move(poz3));
    std::unique_ptr<Poziom> poz4 = std::make_unique<Poziom>("Egzamin z Psio","egzamin.ogg","egzamin.png","Niemozliwy",1,4);
    Wybor_Poziomow.emplace_back(move(poz4));

    //"iterator" XD - do zmiany na elegancki iterator wektorowy
    int i=0;
    //inicjalizacja danych 1 poziomu
    Wybor_Poziomow[i]->inicjalizacja();
    //przyciski do wymiany, modyfikacja klasy tak żeby wszystko od razu zrobila jak wrzuce mu te dane do konstruktora
    std::vector<Button> przyciski;
    //przycisk 0, scroll piosenek w lewo
    przyciski.emplace_back(Button({20,20},{20,250},"<",sf::Color(123,123,123),sf::Color::White,15));
    //przycisk 1 scroll piosenek w prawo
    przyciski.emplace_back(Button({20,20},{360,250},">",sf::Color(123,123,123),sf::Color::White,15));
    //przycisk 2, intro();
    przyciski.emplace_back(Button({90,60},{325,500},"Intro",sf::Color(123,123,123),sf::Color::Yellow,30));
    //przycisk 3, wyjdzie z programy
    przyciski.emplace_back(Button({90,60},{50,500},"Wyjdz",sf::Color(123,123,123),sf::Color::Red,30));
    //przycisk 4 Play, rozpocznie poziom
    przyciski.emplace_back(Button({90,60},{600,500},"Play!",sf::Color(123,123,123),sf::Color::Green,30));
    //przycisk 5 zmiany patternu:
    przyciski.emplace_back(Button({90,60},{510,270},"Zmien",sf::Color::Black,sf::Color::Yellow,20));

    //ze wzgledu na bugi napotkane podczas takiego generowania textu, font musi byc zdefiniowany odgórnie, nie mogę go wczytać "w obiekcie"
    sf::Font font;
    if(!font.loadFromFile("arial.ttf")){
        std::cout<<"nie wczytano fontu"<<std::endl;
        return;
    }
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }
            //event handler dla konkretnych przycisków w menu głównym
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if(przyciski[0].is_within(window) && i!=0){
                    i--;
                    Wybor_Poziomow[i]->inicjalizacja();
                }
                if(przyciski[1].is_within(window) && i<(int)Wybor_Poziomow.size()-1){
                    i++;
                    Wybor_Poziomow[i]->inicjalizacja();
                }
                if(przyciski[2].is_within(window))
                    przyciski[2].intro();
                if(przyciski[3].is_within(window))
                    window.close();
                if(przyciski[4].is_within(window))
                    Wybor_Poziomow[i]->gra();
                if(przyciski[5].is_within(window))
                    Wybor_Poziomow[i]->change_pattern();
            }
        }


        window.clear(sf::Color::Black);
        //rysowanie background poziomu
        window.draw(Wybor_Poziomow[i]->sprite);
        //rysowanie przyciskow
        for(auto &p : przyciski){

            window.draw(p);
            p.draw_text(window,font);
        }
        //rysowanie danych poziomu
        Wybor_Poziomow[i]->wyswietl_staty(window);
        window.display();
    }
}
