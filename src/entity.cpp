//
// Created by admin on 24.03.2023.
//

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <valarray>
#include <iostream>
#include "entity.h"

//! \brief Constructeur de la classe entity
entity::entity() {
    m_Circle.setRadius(10);
    m_Circle.setFillColor(sf::Color::White);


    m_FieldOfView.setPointCount(3);
    m_FieldOfView.setPoint(0, sf::Vector2f((m_Circle.getRadius()), (m_Circle.getRadius())));
    m_FieldOfView.setPoint(1, sf::Vector2f((m_Circle.getRadius()) + 50, (m_Circle.getRadius()) - 100));
    m_FieldOfView.setPoint(2, sf::Vector2f((m_Circle.getRadius()) - 50, (m_Circle.getRadius()) - 100));
    m_FieldOfView.setFillColor(sf::Color(255, 255, 255, 128));

    setPositionFieldView();
}

//! \brief Destructeur de la classe entity
entity::~entity() {

}

//! \brief Retourne le cercle de l'entité
sf::CircleShape entity::getCircle() {
    return m_Circle;
}

//! \brief Défini la position de l'entité
void entity::setPos(sf::Vector2f position) {
    m_Circle.setPosition(position);

    // calcule la position
    sf::Vector2f pos = m_Circle.getPosition();

    setPositionFieldView();
}

//! \brief Défini la position de l'entité
void entity::setPos(float x, float y) {
    m_Circle.setPosition(x, y);
    setPositionFieldView();
}

//! \brief Tourne l'entité
void entity::rotate(int angle) {
    m_Circle.setOrigin(m_Circle.getRadius(), m_Circle.getRadius());
    m_Circle.rotate(angle);

    // rotate field of view en fonction de l'angle de l'entité

    m_FieldOfView.setOrigin(m_Circle.getRadius(), m_Circle.getRadius());
    m_FieldOfView.rotate(angle);

}

//! \brief Déplace l'entité
void entity::move(int x, int y) {
    m_Circle.move(x, y);
    m_FieldOfView.move(x, y);
}

//! \brief Met à jour l'entité
void entity::update(sf::Time elapsed){

}

//! \brief Affiche l'entité
void entity::render(sf::RenderWindow &window) {
    window.draw(m_Circle);
    window.draw(m_FieldOfView);
}

//! \brief Défini la position du champ de vision
void entity::setPositionFieldView() {
    // calcule la position
    sf::Vector2f pos = m_Circle.getPosition();

    // colle le point de vue au centre de l'entité
    m_FieldOfView.setPosition(pos);
}
