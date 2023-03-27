//
// Created by admin on 24.03.2023.
//

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include "friendly.h"

friendly::friendly() {
    m_Circle.setFillColor(sf::Color::Green);
}

friendly::~friendly() {

}

void friendly::update(sf::Time elapsed) {
    entity::update(elapsed);
    // ou tourne sur lui même
    //rotate(1);
}
