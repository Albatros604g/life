//
// Created by admin on 24.03.2023.
//

#include <cmath>
#include <iostream>
#include "core.h"

core::core() {
    initWindow();

    m_Friendly.setPos(0, 0);
    m_Hostil.setPos(200, 200);
    // Ajoute les entités à la liste
    m_HostilesEntities.push_back(m_Hostil);
    m_FriendlyEntities.push_back(m_Friendly);

    m_IsEntitySelected = false;
}

core::~core() {
    m_Window.close();
}

void core::run() {
    sf::Time elapsed;
    while (m_Window.isOpen()) {
        elapsed = m_Clock.restart();
        pollEvents();
        update(elapsed);
        m_Window.clear(sf::Color::Black);
        render();
        m_Window.display();
    }
}

void core::initWindow() {
    // récurer la taille de l'écran
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    //m_Window.create(sf::VideoMode( desktop.width, desktop.height), "Life", sf::Style::Close | sf::Style::Titlebar);
    m_Window.create(sf::VideoMode( 800, 600), "Life", sf::Style::Close | sf::Style::Titlebar);

    m_Window.setFramerateLimit(60);
    m_View = m_Window.getDefaultView();
    m_View.setCenter(0, 0);
    m_Window.setView(m_View);
}

void core::pollEvents() {
    sf::Event event;
    while (m_Window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_Window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            // bouge la vue vers le haut si la touche "w" est pressée
            if (event.key.code == sf::Keyboard::W) {
                m_View.move(0, -10);
                m_Window.setView(m_View);
            }
            // bouge la vue vers le bas si la touche "s" est pressée
            if (event.key.code == sf::Keyboard::S) {
                m_View.move(0, 10);
                m_Window.setView(m_View);
            }
            // bouge la vue vers la gauche si la touche "a" est pressée
            if (event.key.code == sf::Keyboard::A) {
                m_View.move(-10, 0);
                m_Window.setView(m_View);
            }
            // bouge la vue vers la droite si la touche "d" est pressée
            if (event.key.code == sf::Keyboard::D) {
                m_View.move(10, 0);
                m_Window.setView(m_View);
            }
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            // zoom la vue si la molette de la souris est utilisée
            if (event.mouseWheelScroll.delta > 0) {
                m_View.zoom(0.9);
                m_Window.setView(m_View);
            } else {
                m_View.zoom(1.1);
                m_Window.setView(m_View);
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            // test si on clique sur le bouton gauche de la souris
            if (event.mouseButton.button == sf::Mouse::Left) {
                // converti les coordonnées de la souris en coordonnées de la vue
                sf::Vector2f mousePos = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));

                m_IsEntitySelected = false;
                // test si on clique sur une entité amicale
                for (auto &entity : m_FriendlyEntities) {
                    if (entity.checkPositionIsInside(mousePos.x, mousePos.y)) {
                        std::cout << "click on friendly" << std::endl;
                        m_SelectedEntity = &entity;
                        m_IsEntitySelected = true;
                    }
                }
                for (auto &entity : m_HostilesEntities) {
                    if (entity.checkPositionIsInside(mousePos.x, mousePos.y)) {
                        std::cout << "click on hostil" << std::endl;
                        m_SelectedEntity = &entity;
                        m_IsEntitySelected = true;
                    }
                }
            }
        }
    }
}

void core::update(sf::Time elapsed) {
    // parcours la liste des entités hostiles
    for (auto &entity : m_HostilesEntities) {
        entity.update(elapsed);

    }

    // parcours la liste des entités amicales
    for (auto &entity : m_FriendlyEntities) {
        entity.update(elapsed);
    }

    if (m_IsEntitySelected) {
        std::string adn = m_SelectedEntity->getADN();
        int life = m_SelectedEntity->getLife();
        int energy = m_SelectedEntity->getEnergy();
        int speed = m_SelectedEntity->getSpeed();
        std::cout << "ADN: " << adn << " life: " << life << " energy: " << energy << " speed: " << speed << std::endl;
    }

/*
    // bouge le rond m_CircleHostile en direction de m_CircleFrendly
    sf::Vector2f direction = m_CircleFrendly.getPosition() - m_CircleHostile.getPosition();
    float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }
    m_CircleHostile.move(direction * 100.f * elapsed.asSeconds());

    // si le rond m_CircleHostile est trop proche du rond m_CircleFrendly, le rond m_CircleHostile change de couleur
    if (length < 20) {
        m_CircleHostile.setFillColor(sf::Color::Blue);
    } else {
        m_CircleHostile.setFillColor(sf::Color::Red);
    }
*/

}

void core::render() {
    // parcours la liste des entités hostiles
    for (auto &entity : m_HostilesEntities) {
        m_Window.draw(entity.getCircle());
    }

    // parcours la liste des entités amicales
    for (auto &entity : m_FriendlyEntities) {
        entity.render(m_Window);
    }

    // parcours la liste des entités hostiles
    for (auto &entity : m_HostilesEntities) {
        entity.render(m_Window);
    }

}
