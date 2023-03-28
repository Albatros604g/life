//
// Created by admin on 27.03.2023.
//

#include "guiEntity.h"

guiEntity::guiEntity() {
    m_Font.loadFromFile("C:\\Users\\admin\\CLionProjects\\life\\assets\\font\\Oswald-Medium.ttf");

    m_ADNText.setFont(m_Font);
    m_LifeText.setFont(m_Font);
    m_EnergyText.setFont(m_Font);
    m_SpeedText.setFont(m_Font);

    m_ADNText.setCharacterSize(20);
    m_LifeText.setCharacterSize(20);
    m_EnergyText.setCharacterSize(20);
    m_SpeedText.setCharacterSize(20);

    m_ADNText.setFillColor(sf::Color::White);
    m_LifeText.setFillColor(sf::Color::White);
    m_EnergyText.setFillColor(sf::Color::White);
    m_SpeedText.setFillColor(sf::Color::White);

    m_ADNText.setPosition(0, 0);
    m_LifeText.setPosition(0, 20);
    m_EnergyText.setPosition(0, 40);
    m_SpeedText.setPosition(0, 60);

    m_ADNText.setString("ADN : ");
    m_LifeText.setString("Life : ");
    m_EnergyText.setString("Energy : ");
    m_SpeedText.setString("Speed : ");
}

guiEntity::~guiEntity() {

}

void guiEntity::setADNText(std::string ADN) {
    m_ADNText.setString("ADN : " + ADN);
}

void guiEntity::setLifeText(int life) {
    m_LifeText.setString("Life : " + std::to_string(life));
}

void guiEntity::setEnergyText(int energy) {
    m_EnergyText.setString("Energy : " + std::to_string(energy));
}

void guiEntity::setSpeedText(int speed) {
    m_SpeedText.setString("Speed : " + std::to_string(speed));
}

void guiEntity::render(sf::RenderWindow &window) {
    window.draw(m_ADNText);
    window.draw(m_LifeText);
    window.draw(m_EnergyText);
    window.draw(m_SpeedText);
}

void guiEntity::setPos(sf::Vector2f pos) {
    m_ADNText.setPosition(pos);
    m_LifeText.setPosition(pos.x, pos.y + 20);
    m_EnergyText.setPosition(pos.x, pos.y + 40);
    m_SpeedText.setPosition(pos.x, pos.y + 60);
}
