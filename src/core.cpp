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
    m_IsAddEntity = false;
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

    m_Window.create(sf::VideoMode( desktop.width, desktop.height), "Life", sf::Style::Close | sf::Style::Resize);
    //m_Window.create(sf::VideoMode( 800, 600), "Life", sf::Style::Close | sf::Style::Titlebar);

    m_Window.setFramerateLimit(60);
    m_View = m_Window.getDefaultView();
    m_View.setCenter(0, 0);
    m_Window.setView(m_View);
}

void core::pollEvents() {
    sf::Event event;
    while (m_Window.pollEvent(event)) {
        // récupère la position de la souris
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_Window);
        // converti les coordonnées de la souris en coordonnées de la vue
        sf::Vector2f mousePosView = m_Window.mapPixelToCoords(mousePos);
        // récupère la position de la vue
        sf::Vector2f viewPos = m_View.getCenter();

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
            // si on appuie sur delete on supprime l'entité sélectionnée
            if (event.key.code == sf::Keyboard::Delete) {
                m_IsRemoveEntity = true;
            }
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            // zoom la vue si la molette de la souris est utilisée
            if (event.mouseWheelScroll.delta > 0) {
                m_View.zoom(0.9);
                // calcule la différence entre la position de la souris et la position de la vue
                sf::Vector2f delta = mousePosView - viewPos;
                // divise le delta par 10
                delta.x /= 10;
                delta.y /= 10;
                // déplace la vue
                m_View.move(delta);
                m_Window.setView(m_View);

            } else {
                m_View.zoom(1.1);
                m_Window.setView(m_View);
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            // test si on clique sur le bouton gauche de la souris
            if (event.mouseButton.button == sf::Mouse::Left) {
                m_IsEntitySelected = false;
                m_IsAddEntity = true;
                // test si on clique sur une entité amicale
                for (auto &entity: m_FriendlyEntities) {
                    entity.isSelected(false);
                    if (entity.checkPositionIsInside(mousePosView.x, mousePosView.y)) {
                        std::cout << "click on friendly" << std::endl;
                        m_SelectedEntity = &entity;
                        m_IsEntitySelected = true;
                        entity.isSelected(true);
                        m_IsAddEntity = false;
                        // ajoute l'entité à la liste des entités sélectionnées
                        m_SelectedEntities.push_back(&entity);
                    }
                }
                for (auto &entity: m_HostilesEntities) {
                    entity.isSelected(false);
                    if (entity.checkPositionIsInside(mousePosView.x, mousePosView.y)) {
                        std::cout << "click on hostil" << std::endl;
                        m_SelectedEntity = &entity;
                        m_IsEntitySelected = true;
                        entity.isSelected(true);
                        m_IsAddEntity = false;
                        // ajoute l'entité à la liste des entités sélectionnées
                        m_SelectedEntities.push_back(&entity);
                    }
                }

                if (m_GuiMenu.checkPositionIsInside(mousePos.x, mousePos.y)) {
                    std::cout << "click on menu" << std::endl;
                    m_IsAddEntity = false;
                }

                if (m_IsAddEntity) {
                    if (m_GuiMenu.getCircleFIsSelected()) {
                        // ajoute une entité amicale
                        friendly friendly;
                        friendly.setPos(mousePosView.x, mousePosView.y);
                        m_FriendlyEntities.push_back(friendly);
                    }

                    if (m_GuiMenu.getCircleHIsSelected()) {
                        // ajoute une entité hostile
                        hostil hostil;
                        hostil.setPos(mousePosView.x, mousePosView.y);
                        m_HostilesEntities.push_back(hostil);
                    }
                }

                if (m_GuiMenu.getRemoveEntityIsSelected()) {
                    m_IsRemoveEntity = true;
                }


            }
            if (event.mouseButton.button == sf::Mouse::Right) {
                // test si m_IsViewDragged est vrai
                if (!m_IsViewDragged) {
                    // Aggripe la vue a cette position
                    m_IsViewDragged = true;
                    m_MousePosDragged = mousePosView;
                }
            }
        }
    }
    // si il n'y a pas de clic droit
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        // déaggripe la vue
        m_IsViewDragged = false;
    }
}

void core::update(sf::Time elapsed) {
    // si la vue est agrippée
    if (m_IsViewDragged) {
        // calcule la différence entre la position de la souris actuelle et la position de la souris quand la vue a été agrippée m_MousePos
        sf::Vector2f delta = m_MousePosDragged - m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
        // déplace la vue
        m_View.move(delta);
        m_Window.setView(m_View);

    }

    // parcours la liste des entités hostiles
    for (auto &entity : m_HostilesEntities) {
        entity.update(elapsed);

    }

    // parcours la liste des entités amicales
    for (auto &entity : m_FriendlyEntities) {
        entity.update(elapsed);
    }


    if (m_IsEntitySelected) {
        if (m_IsRemoveEntity) {
            // Boucle sur la liste des entités sélectionnées
            for (auto &entity : m_SelectedEntities) {
                // si l'entité est amicale
                if (entity->getType() == entity::Type::Friendly) {
                    // parcours la liste des entités amicales
                    for (auto it = m_FriendlyEntities.begin(); it != m_FriendlyEntities.end(); it++) {
                        // si l'entité est sélectionnée on la supprime
                        if (it->getIsSelected()) {
                            m_FriendlyEntities.erase(it);
                            m_IsEntitySelected = false;
                            break;
                        }
                    }
                } else {
                    // parcours la liste des entités hostiles
                    for (auto it = m_HostilesEntities.begin(); it != m_HostilesEntities.end(); it++) {
                        // si l'entité est sélectionnée on la supprime
                        if (it->getIsSelected()) {
                            m_HostilesEntities.erase(it);
                            m_IsEntitySelected = false;
                            break;
                        }
                    }
                }
            }
        } else {
            m_GuiEntity.setADNText(m_SelectedEntity->getADN());
            m_GuiEntity.setLifeText(m_SelectedEntity->getLife());
            m_GuiEntity.setEnergyText(m_SelectedEntity->getEnergy());
            m_GuiEntity.setSpeedText(m_SelectedEntity->getSpeed());
            sf::Vector2f pos = m_SelectedEntity->getPosition();
            pos.x += m_SelectedEntity->getRadius() - 50;
            pos.y += m_SelectedEntity->getRadius() + 20;
            m_GuiEntity.setPos(pos);
        }
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

    if (m_IsEntitySelected) {
        m_GuiEntity.render(m_Window);
    }

    m_IsRemoveEntity = false;
    m_GuiMenu.render(m_Window);
}
