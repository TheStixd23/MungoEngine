/**
 * @file Window.cpp
 * @brief Implementación de la clase Window, responsable de la creación y gestión de una ventana SFML para renderizado gráfico.
 * @author Hannin Abarca
 */

#include "window.h"

 /**
  * @brief Constructor que crea una ventana SFML con las dimensiones y título especificados.
  * @param width Ancho de la ventana en píxeles.
  * @param height Alto de la ventana en píxeles.
  * @param title Título de la ventana.
  */
Window::Window(int width, int height, const std::string& title) {

	m_windowPtr = EngineUtilities
		::MakeUnique<sf::RenderWindow>(sf::VideoMode(width, height), title);

	if (!m_windowPtr.isNull()) {
		m_windowPtr->setFramerateLimit(60);
		MESSAGE("Window", "Window", "Window created successfully");
	}
	else {
		ERROR("Window", "Window", "Failed to create window");
	}
}

/**
 * @brief Destructor de la ventana. Libera el recurso si aún existe.
 */
Window::~Window() {
	m_windowPtr.release();
}

/**
 * @brief Procesa los eventos del sistema, como el cierre de la ventana.
 */
void
Window::handleEvents() {
	sf::Event event;
	while (m_windowPtr->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_windowPtr->close();
		}
	}
}

/**
 * @brief Verifica si la ventana está abierta.
 * @return true si la ventana sigue activa, false si fue cerrada o no existe.
 */
bool
Window::isOpen() const {
	if (!m_windowPtr.isNull()) {
		return m_windowPtr->isOpen();
	}
	else {
		ERROR("Window", "isOpen", "Window is null");
		return false;
	}
}

/**
 * @brief Limpia la ventana con el color especificado.
 * @param color Color con el que se limpia la ventana.
 */
void
Window::clear(const sf::Color& color) {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->clear(color);
	}
	else {
		ERROR("Window", "clear", "Window is null");
	}
}

/**
 * @brief Dibuja un objeto sobre la ventana.
 * @param drawable Objeto SFML que se desea dibujar.
 * @param states Estados de renderizado opcionales.
 */
void
Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->draw(drawable, states);
	}
	else {
		ERROR("Window", "draw", "Window is null");
	}
}

/**
 * @brief Muestra en pantalla el contenido actual del búfer de dibujo.
 */
void
Window::display() {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->display();
	}
	else {
		ERROR("Window", "display", "Window is null");
	}
}

/**
 * @brief Libera manualmente el recurso de la ventana.
 */
void
Window::destroy() {
	m_windowPtr.release();
}
