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

    sf::CircleShape getCircle();

protected:
    sf::CircleShape m_Circle;
    sf::ConvexShape m_FieldOfView;

    void rotate(int angle);
    void move(int x, int y);

    void setPositionFieldView();
private:


};


#endif //LIFE_ENTITY_H