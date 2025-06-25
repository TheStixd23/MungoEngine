/**
 * @file Window.h
 * @author Hannin Abarca
 * @brief Declaración de la clase Window para gestionar una ventana SFML
 * @version 1.0
 * @date 2025-06-01
 */

#pragma once
#include "Prerequisites.h"

 /**
  * @class Window
  * @brief Clase que encapsula una ventana utilizando SFML
  *
  * Permite manejar eventos, dibujar elementos, limpiar y mostrar contenido
  */
class Window {
public:
    Window() = default;
    Window(int width, int height, const std::string& title);
    ~Window();

    void handleEvents();
    bool isOpen() const;
    void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));
    void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
    void display();
    void destroy();

private:
    sf::RenderWindow* m_window = nullptr;
    sf::View m_view;
};
