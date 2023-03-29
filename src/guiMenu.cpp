//
// Created by rufiala on 29.03.2023.
//

#include <cmath>
#include <iostream>
#include "guiMenu.h"

guiMenu::guiMenu() {
    m_Font.loadFromFile("C:\\Users\\rufiala\\CLionProjects\\life\\assets\\font\\Oswald-Medium.ttf");

    m_Text.setFont(m_Font);
    m_Text.setCharacterSize(50);
    m_Text.setFillColor(sf::Color::White);
    m_Text.setPosition(0, 0);
    m_Text.setString("Menu");

    m_Background.setSize(sf::Vector2f(200, 50));
    // couleur de fond bleu futuriste
    m_Background.setFillColor(sf::Color(0, 0, 255, 100));

    m_CircleF.setRadius(30);
    m_CircleF.setFillColor(sf::Color::Green);
    m_CircleF.setPosition(0, 0);
    m_CircleF.setOrigin(m_CircleF.getRadius(), m_CircleF.getRadius());

    m_CircleH.setRadius(30);
    m_CircleH.setFillColor(sf::Color::Red);
    m_CircleH.setPosition(0, 0);
    m_CircleH.setOrigin(m_CircleH.getRadius(), m_CircleH.getRadius());

    m_TextRemoveEntity.setFont(m_Font);
    m_TextRemoveEntity.setCharacterSize(50);
    m_TextRemoveEntity.setFillColor(sf::Color::White);
    m_TextRemoveEntity.setPosition(0, 0);
    m_TextRemoveEntity.setString("Remove");

    m_BackgroundRemoveEntity.setSize(sf::Vector2f(200, 50));
    // couleur de fond mauve futuriste
    m_BackgroundRemoveEntity.setFillColor(sf::Color(255, 0, 255, 0));

    m_CircleFIsSelected = false;
    m_CircleHIsSelected = false;
}

guiMenu::~guiMenu() {

}

void guiMenu::setPos() {
}

void guiMenu::render(sf::RenderWindow &window) {
    // viewport de la vue
    sf::FloatRect viewport = window.getView().getViewport();

    sf::View viewNow = window.getView();


    // la taille de la vue est la même que la fenêtre
    m_ViewMenu.setSize(window.getSize().x, window.getSize().y);
    // la position de la vue est le centre de la fenêtre
    m_ViewMenu.setCenter(window.getSize().x / 2, window.getSize().y / 2);

    // calcul les 100% de la hauteur de la fenêtre
    float percent = (m_ViewMenu.getSize().y / 100);

    // poistionne le rectangle au millieu
    m_Background.setPosition(0, m_ViewMenu.getSize().y - percent * 20);


    // la hauteur du rectangle est égale à 20% de la hauteur de la fenêtre
    m_Background.setSize(sf::Vector2f(m_ViewMenu.getSize().x, percent * 16));

    // positionne le texte dans le rectangle
    m_Text.setPosition(m_ViewMenu.getSize().x / 2 - m_Text.getGlobalBounds().width / 2, m_ViewMenu.getSize().y - percent * 20 + percent * 2);

    // la taille du texte est égale à 20% de la hauteur de la fenêtre
    m_Text.setCharacterSize(percent * 8);

    // positionne le cercle f a gauche du rectangle de fond
    m_CircleF.setPosition((m_Background.getPosition().x + percent * 6) + m_CircleH.getRadius(), m_Background.getPosition().y + percent * 5);

    // positionne le cercle h a droite du rectangle de fond mais a l'opposé
    m_CircleH.setPosition((m_Background.getPosition().x + m_Background.getSize().x - percent * 6) - m_CircleH.getRadius(), m_Background.getPosition().y + percent * 5);

    // applique la vue
    window.setView(m_ViewMenu);
    window.draw(m_Background);
    window.draw(m_Text);
    window.draw(m_CircleF);
    window.draw(m_CircleH);

    // dessine un contour autour du cercle f si il est sélectionné
    if (m_CircleFIsSelected) {
        sf::CircleShape circleFSelected;
        circleFSelected.setRadius(m_CircleF.getRadius() + 2);
        circleFSelected.setFillColor(sf::Color::Transparent);
        circleFSelected.setOutlineColor(sf::Color::White);
        circleFSelected.setOutlineThickness(2);
        circleFSelected.setPosition(m_CircleF.getPosition().x - circleFSelected.getRadius(), m_CircleF.getPosition().y - circleFSelected.getRadius());
        window.draw(circleFSelected);
    }

    // dessine un contour autour du cercle h si il est sélectionné
    if (m_CircleHIsSelected) {
        sf::CircleShape circleHSelected;
        circleHSelected.setRadius(m_CircleH.getRadius() + 2);
        circleHSelected.setFillColor(sf::Color::Transparent);
        circleHSelected.setOutlineColor(sf::Color::White);
        circleHSelected.setOutlineThickness(2);
        circleHSelected.setPosition(m_CircleH.getPosition().x - circleHSelected.getRadius(), m_CircleH.getPosition().y - circleHSelected.getRadius());
        window.draw(circleHSelected);
    }

    // réinitialise la vue
    window.setView(viewNow);
}

bool guiMenu::getCircleFIsSelected() {
    return m_CircleFIsSelected;
}

bool guiMenu::getCircleHIsSelected() {
    return m_CircleHIsSelected;
}

bool guiMenu::getRemoveEntityIsSelected() {
    return m_RemoveEntityIsSelected;
}

bool guiMenu::checkPositionIsInside(int x, int y) {
    bool result = false;


    // calcule la position du centre de l'entité
    int x_centre = m_CircleF.getPosition().x;
    int y_centre = m_CircleF.getPosition().y;
    int rayon = m_CircleF.getRadius();

    int distance = sqrt(pow(x - x_centre, 2) + pow(y - y_centre, 2));
    if (distance <= rayon) {
        result = true;
        m_CircleFIsSelected = !m_CircleFIsSelected;
        m_CircleHIsSelected = false;
    } else {
        result = false;
    }

    if (!result) {
        x_centre = m_CircleH.getPosition().x;
        y_centre = m_CircleH.getPosition().y;
        rayon = m_CircleH.getRadius();

        distance = sqrt(pow(x - x_centre, 2) + pow(y - y_centre, 2));
        if (distance <= rayon) {
            result = true;
            m_CircleHIsSelected = !m_CircleHIsSelected;
            m_CircleFIsSelected = false;
        } else {
            result = false;
        }
    }

    if (!result) {
        // test si la position est dans le rectangle du bouton m_BackgroundRemoveEntity
        if (x >= m_BackgroundRemoveEntity.getPosition().x && x <= m_BackgroundRemoveEntity.getPosition().x + m_BackgroundRemoveEntity.getSize().x) {
            if (y >= m_BackgroundRemoveEntity.getPosition().y && y <= m_BackgroundRemoveEntity.getPosition().y + m_BackgroundRemoveEntity.getSize().y) {
                result = true;
                m_RemoveEntityIsSelected = true;
            }
        }
    }

    return result;
}


