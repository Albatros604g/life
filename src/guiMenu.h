//
// Created by rufiala on 29.03.2023.
//

#ifndef LIFE_GUIMENU_H
#define LIFE_GUIMENU_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class guiMenu {
public:
    guiMenu();
    ~guiMenu();

    void render(sf::RenderWindow &window);

    bool checkPositionIsInside(int x, int y);

    bool getCircleFIsSelected();
    bool getCircleHIsSelected();
    bool getRemoveEntityIsSelected();

private:
    sf::Font m_Font;

    sf::Text m_Text;
    sf::Text m_TextRemoveEntity;

    void setPos();

    // rectangle de fond du menu
    sf::RectangleShape m_Background;

    // rectangle de fond pour le bouton remove entity
    sf::RectangleShape m_BackgroundRemoveEntity;

    sf::CircleShape m_CircleF;
    sf::CircleShape m_CircleH;

    bool m_CircleFIsSelected;
    bool m_CircleHIsSelected;
    bool m_RemoveEntityIsSelected;

    // créer un nouvel vu
    sf::View m_ViewMenu;
};


#endif //LIFE_GUIMENU_H
