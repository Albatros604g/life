//
// Created by admin on 24.03.2023.
//

#ifndef LIFE_ENTITY_H
#define LIFE_ENTITY_H


#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/ConvexShape.hpp>


class entity {
public:
    entity();
    ~entity();

    void setPos(sf::Vector2f position);
    void setPos(float x, float y);

    void update(sf::Time elapsed);
    void render(sf::RenderWindow &window);
    void isSelected(bool isSelected);

    bool checkPositionIsInside(int x, int y);

    std::string getADN();
    int getLife();
    int getEnergy();
    int getSpeed();

    sf::CircleShape getCircle();

    sf::Vector2f getPosition();
    int getRadius();

protected:
    sf::CircleShape m_Circle;
    sf::ConvexShape m_FieldOfView;

    void rotate(int angle);
    void move(int x, int y);

    void setPositionFieldView();

private:
    void initADN();
    void initAttributes();
    std::string m_ADN;
    int m_Life;
    int m_LifeMax;
    int m_Energy;
    int m_EnergyMax;
    int m_Speed;
    int m_SpeedMax;

    sf::Time m_TimeBeforeDeath;
    sf::Time m_TimeBeforeReproduction;

    bool m_IsSelected;
};


#endif //LIFE_ENTITY_H
