//
// Created by admin on 27.03.2023.
//

#ifndef LIFE_GUIENTITY_H
#define LIFE_GUIENTITY_H


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class guiEntity {
public:
    guiEntity();
    ~guiEntity();

    void setADNText(std::string ADN);
    void setLifeText(int life);
    void setEnergyText(int energy);
    void setSpeedText(int speed);

    void setPos(sf::Vector2f pos);

    void render(sf::RenderWindow &window);
private:
    // texte pour l'affichage de l'ADN
    sf::Text m_ADNText;
    // texte pour l'affichage de la vie
    sf::Text m_LifeText;
    // texte pour l'affichage de l'énergie
    sf::Text m_EnergyText;
    // texte pour l'affichage de la vitesse
    sf::Text m_SpeedText;

    sf::Font m_Font;
};


#endif //LIFE_GUIENTITY_H
