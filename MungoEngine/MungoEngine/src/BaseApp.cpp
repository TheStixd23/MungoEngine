/**
 * @file BaseApp.cpp
 * @author Hannin Abarca
 * @brief Implementaci�n de la clase BaseApp que maneja el ciclo principal de la aplicaci�n
 * @version 1.0
 * @date 2025-06-01
 */

#include "BaseApp.h"

BaseApp::~BaseApp() {
    Destroy();
}

int BaseApp::run() {
    if (!init()) {
        ERROR("BaseApp",
            "run",
            "Initializes result on a false statement, check method validations");
        return -1; // Salir si falla la inicializaci�n
    }

    while (m_window && m_window->isOpen()) {
        m_window->handleEvents();
        update();
        render();
    }

    Destroy();
    return 0;
}

bool BaseApp::init() {
    m_window = new Window(800, 600, "MungoEngine");

    m_circle = new sf::CircleShape(100.0f);  // Crea un c�rculo con radio 100
    m_circle->setFillColor(sf::Color::Magenta);
    m_circle->setPosition(200.f, 150.f);

    return true;
}

void BaseApp::update() {
    // Aqu� va la l�gica de actualizaci�n si se necesita
}

void BaseApp::render() {
    if (m_window) {
        m_window->clear();
        if (m_circle) {
            m_window->draw(*m_circle);
        }
        m_window->display();
    }
}

void BaseApp::Destroy() {
    if (m_circle) {
        delete m_circle;
        m_circle = nullptr;
    }
    if (m_window) {
        m_window->destroy();
        delete m_window;
        m_window = nullptr;
    }
}
