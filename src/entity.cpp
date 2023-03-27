//
// Created by admin on 24.03.2023.
//

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <valarray>
#include <iostream>
#include "entity.h"
#include <string>
#include <random>
#include <SFML/Window/Mouse.hpp>

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
    initADN();
    initAttributes();
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

//! \brief Initialise l'ADN de l'entité
void entity::initADN() {
    m_ADN = "";
    std::string pattern = "ACGT"; // patron
    // A = Adénine
    // C = Cytosine
    // G = Guanine
    // T = Thymine
    // ses 4 lettres sont les bases de l'ADN et sont les seules à être utilisées
    int patternLength = pattern.length();
    std::random_device rd; // initialisation du générateur aléatoire
    std::mt19937 gen(rd()); // initialisation du générateur aléatoire
    std::uniform_int_distribution<> dis(0, patternLength - 1); // distribution uniforme sur l'intervalle [0, patternLength - 1]
    int length = 100; // longueur de la séquence
    for (int i = 0; i < length; i++) {
        m_ADN += pattern[dis(gen)]; // ajouter un caractère aléatoire du patron
    }
}

void entity::initAttributes() {
    // détermine les attributs de l'entité en fonction de son ADN
    m_LifeMax = 100;
    m_EnergyMax = 100;
    m_Speed = 1;
    m_SpeedMax = 10;

    for (int i = 0; i < m_ADN.length(); i++) {
        // Utilisez la valeur de l'ADN pour calculer la valeur de chaque attribut
        if (m_ADN[i] == 'A') {
            m_LifeMax += 1;
        } else if (m_ADN[i] == 'C') {
            m_EnergyMax += 1;
        } else if (m_ADN[i] == 'G') {
            m_SpeedMax += 1;
        } else if (m_ADN[i] == 'T') {
            m_EnergyMax += 1;
        }
    }

    m_Life = m_LifeMax;
    m_Energy = m_EnergyMax;
}

bool entity::checkPositionIsInside(int x, int y) {
    // calcule la position du centre de l'entité
    int x_centre = m_Circle.getPosition().x + m_Circle.getRadius();
    int y_centre = m_Circle.getPosition().y + m_Circle.getRadius();
    int rayon = m_Circle.getRadius();

    int distance = sqrt(pow(x - x_centre, 2) + pow(y - y_centre, 2));
    if (distance <= rayon)
        return true;
    else
        return false;
}

std::string entity::getADN() {
    return m_ADN;
}

int entity::getLife() {
    return m_Life;
}

int entity::getEnergy() {
    return m_Energy;
}

int entity::getSpeed() {
    return m_Speed;
}
