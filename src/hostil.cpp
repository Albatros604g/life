//
// Created by admin on 24.03.2023.
//

#include "hostil.h"

hostil::hostil() {
    m_Circle.setFillColor(sf::Color::Red);
}

hostil::~hostil() {

}

void hostil::update(sf::Time elapsed) {
    entity::update(elapsed);
    // ou tourne sur lui même
    //move(1, 0);
    //rotate(1);
    // Intelligence artificielle pour se déplacer
    rotate(10);
}
