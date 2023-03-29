//
// Created by admin on 24.03.2023.
//

#ifndef LIFE_CORE_H
#define LIFE_CORE_H

#include <SFML/Graphics.hpp>
#include <list>
#include "friendly.h"
#include "hostil.h"
#include "guiEntity.h"
#include "guiMenu.h"

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

    // entité sélectionnée
    entity *m_SelectedEntity;
    bool m_IsEntitySelected;
    bool m_IsViewDragged;
    bool m_IsAddEntity;

    sf::Vector2f m_MousePosDragged;

    guiEntity m_GuiEntity;
    guiMenu m_GuiMenu;
};


#endif //LIFE_CORE_H
