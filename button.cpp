#include "button.h"




bool Button::is_within(sf::RenderWindow &window){
    sf::Vector2i position = sf::Mouse::getPosition(window);
    sf::FloatRect rec_b = getGlobalBounds();
    if(position.x>=rec_b.left && position.x<=rec_b.left+rec_b.width && position.y>rec_b.top && position.y<rec_b.top+rec_b.height)
        return true;
    else
        return false;
}
