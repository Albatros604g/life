//
// Created by admin on 24.03.2023.
//

#ifndef LIFE_HOSTIL_H
#define LIFE_HOSTIL_H


#include <SFML/System/Time.hpp>
#include "entity.h"

class hostil : public entity {
public:
    hostil();
    ~hostil();

    void update(sf::Time elapsed);

private:

};


#endif //LIFE_HOSTIL_H
