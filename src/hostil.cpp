//
// Created by admin on 24.03.2023.
//

#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include "hostil.h"

hostil::hostil() {
    setHostil();
}

hostil::~hostil() {

}

void hostil::update(sf::Time elapsed) {
    entity::update(elapsed);
    // ou tourne sur lui même
    //move(1, 0);
    //rotate(1);
    // Intelligence artificielle pour se déplacer
    // calcul la rotation en fonction du temps angle par défaut 180
    float angle = 1;

    // en fonction du temps écoulé on calcul la rotation
    angle = angle * elapsed.asMilliseconds();
    angle = angle / 10;

    // tourne l'entité
    rotate(angle);

}
