//
// Created by admin on 24.03.2023.
//

#ifndef LIFE_CORE_H
#define LIFE_CORE_H

#include <SFML/Graphics.hpp>
#include <list>
#include "friendly.h"
#include "hostil.h"

class core {
public:
    core();
    ~core();

    void run();

private:
    void initWindow();
    void update(sf::Time elapsed);
    void render();
    void pollEvents();

    sf::RenderWindow m_Window;
    sf::View m_View;
    sf::Clock m_Clock;

    // rond
    friendly m_Friendly;
    hostil m_Hostil;

    // Liste des entités hostiles
    std::list<hostil> m_HostilesEntities;

    // Liste des entités amicales
    std::list<friendly> m_FriendlyEntities;
};


#endif //LIFE_CORE_H