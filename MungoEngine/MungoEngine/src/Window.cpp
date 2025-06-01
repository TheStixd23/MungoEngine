/**
 * @file Window.cpp
 * @author Hannin Abarca
 * @brief Implementación de la clase Window para manejo de ventanas SFML
 * @version 1.0
 * @date 2025-06-01
 */

#include "window.h"

 /**
  * @brief Constructor que crea una nueva ventana con dimensiones y título
  *
  * @param width  Ancho de la ventana
  * @param height Alto de la ventana
  * @param title  Título de la ventana
  */
Window::Window(int width, int height, const std::string& title)
{
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    if (m_window) {
        m_window->setFramerateLimit(60);
        MESSAGE("Window", "Window", "window created successfully");
    }
    else {
        ERROR("Window", "Window", "window creation failed");
    }
}

/**
 * @brief Destructor. Libera la memoria de la ventana
 */
Window::~Window()
{
    SAFE_PTR_RELEASE(m_window);
}

/**
 * @brief Maneja eventos de la ventana (como cerrar)
 */
void
Window::handleEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window->close();
    }
}

/**
 * @brief Verifica si la ventana está abierta
 *
 * @return true si la ventana está abierta, false si es nula o cerrada
 */
bool
Window::isOpen() const
{
    if (m_window) {
        m_window->isOpen();
    }
    else {
        ERROR("Window", "isOpen", "Window is null");
        return false;
    }
}

/**
 * @brief Limpia la ventana con un color dado
 *
 * @param color Color de fondo para limpiar la ventana
 */
void
Window::clear(const sf::Color& color)
{
    if (m_window) {
        m_window->clear(color);
    }
    else {
        ERROR("Window", "clear", "Window is null");
    }
}

/**
 * @brief Dibuja un objeto renderizable en la ventana
 *
 * @param drawable Objeto a dibujar (como shape, sprite, texto)
 * @param states   Estados de renderizado opcionales
 */
void
Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
    if (m_window) {
        m_window->draw(drawable, states);
    }
    else {
        ERROR("Window", "draw", "Window is null");
    }
}

/**
 * @brief Muestra el contenido renderizado en la ventana
 */
void
Window::display()
{
    if (m_window) {
        m_window->display();
    }
    else {
        ERROR("Window", "display", "Window is null");
    }
}

/**
 * @brief Cierra y libera la memoria de la ventana
 */
void
Window::destroy()
{
    SAFE_PTR_RELEASE(m_window);
}
