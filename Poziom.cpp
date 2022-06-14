#include "Poziom.h"
#include "note.h"
#include <iomanip>
Poziom::Poziom(){

}
Poziom::Poziom(std::string nazwa_piosenki, std::string nazwa_pliku_piosenki, std::string backgr_name,std::string dif,float diff){
    //potrzebne nazwy
    song_name=nazwa_piosenki;
    song_file_name=nazwa_pliku_piosenki;
    difficulty=dif;
    bkgr.loadFromFile(backgr_name);
    diff_gen=diff;
}

void Poziom::inicjalizacja(){
    if(!initialized){
    sprite.setTexture(bkgr);
    sf::Vector2f targetsize(300.f,300.f);
    sprite.setScale(targetsize.x / sprite.getLocalBounds().width, targetsize.y / sprite.getLocalBounds().height);
    sprite.setPosition(50,100);
    initialized=1;
    }
}

void Poziom::inicjalizacja_poziomu(){
    this->openFromFile(song_file_name);
    this->setVolume(2);
}

void Poziom::back_to_menu(){
    sf::Vector2f targetsize(300.f,300.f);
    sprite.setScale(targetsize.x / sprite.getLocalBounds().width, targetsize.y / sprite.getLocalBounds().height);
    sprite.setPosition(50,100);
}

void Poziom::Max_Combo(){
    if(combo>max_combo)
        max_combo=combo;
}
int Poziom::Combo(){
    return combo;
}

int Poziom::give_hp(){
    return hp;
}


float Poziom::Accuracy(){
    if(acc>0)
    return acc/input_number;
    else return 0;
}

void Poziom::set_hp(){
    if(hp>100){
        hp=100;
    }
}

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
hp=100;
}

float Poziom::calculate_nps(){
    float bonus=13/diff_gen;
    return 1/bonus;
}
float Poziom::calculate_actual_nps(){
    std::setprecision(2);
    return 13/diff_gen;
}
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

void Poziom::lose(sf::RenderWindow &window){
    if(hp<=0){
        std::cout<<"Przegrales!"<<std::endl; 
        back_to_menu();
        window.close();
        stop();
        scoreboard();
    }
}
void Poziom::end(sf::RenderWindow &window,sf::Clock &clock){
    if(getDuration().asMilliseconds()<clock.getElapsedTime().asMilliseconds()){
        back_to_menu();
        window.close();
        stop();
        scoreboard();
    }
}

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
    //do pominiecia bo dodaje 0
    //acc+=0;
    go++;
}
void Poziom::Ok(sf::Text &text){
    text.setString("Okay");
    text.setFillColor(sf::Color(147, 6, 194));
    combo++;
    input_number++;
    hp-=2;
    acc-=1;
    ok++;
}
void Poziom::Miss(sf::Text &text){
    text.setString("Miss");
    text.setFillColor(sf::Color(191, 4, 4));
    combo=0;
    input_number++;
    hp-=7;
    acc-=0.5;
    miss++;
}
