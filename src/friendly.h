//
// Created by admin on 24.03.2023.
//

#ifndef LIFE_FRIENDLY_H
#define LIFE_FRIENDLY_H


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "entity.h"

class friendly : public entity {
public:
    friendly();
    ~friendly();
    void update(sf::Time elapsed);

private:

    sf::Texture m_Texture;

};


#endif //LIFE_FRIENDLY_H
