/**
 * @file Window.cpp
 * @author Hannin Abarca
 * @brief Implementación de la clase Window para manejo de ventanas SFML
 * @version 1.0
 * @date 2025-06-01
 */

#include "Window.h"

Window::Window(int width, int height, const std::string& title) {
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    if (m_window) {
        m_window->setFramerateLimit(60);
        MESSAGE("Window", "Window", "window created successfully");
    }
    else {
        ERROR("Window", "Window", "window creation failed");
    }
}

Window::~Window() {
    SAFE_PTR_RELEASE(m_window);
}

void Window::handleEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window->close();
    }
}

bool Window::isOpen() const {
    if (m_window) {
        return m_window->isOpen();
    }
    else {
        ERROR("Window", "isOpen", "Window is null");
        return false;
    }
}

void Window::clear(const sf::Color& color) {
    if (m_window) {
        m_window->clear(color);
    }
    else {
        ERROR("Window", "clear", "Window is null");
    }
}

void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
    if (m_window) {
        m_window->draw(drawable, states);
    }
    else {
        ERROR("Window", "draw", "Window is null");
    }
}

void Window::display() {
    if (m_window) {
        m_window->display();
    }
    else {
        ERROR("Window", "display", "Window is null");
    }
}

void Window::destroy() {
    SAFE_PTR_RELEASE(m_window);
}
