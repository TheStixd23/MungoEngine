/**
 * @file Window.cpp
 * @brief Implementación de la clase Window para la gestión de la ventana principal y sus eventos.
 *
 * Encapsula un `sf::RenderWindow` de SFML para ofrecer funciones de inicialización,
 * renderizado, limpieza y control de eventos, integrando además con el sistema de GUI.
 */

#include "window.h"
#include "EngineGUI.h"

 /**
  * @brief Constructor que crea una ventana SFML.
  *
  * Inicializa un `sf::RenderWindow` con las dimensiones y título especificados.
  * Establece un límite de fotogramas a 60 FPS.
  * Si la creación falla, genera un mensaje de error.
  *
  * @param width Ancho de la ventana en píxeles.
  * @param height Alto de la ventana en píxeles.
  * @param title Título de la ventana.
  */
Window::Window(int width, int height, const std::string& title) {

	m_windowPtr = EngineUtilities::MakeUnique<sf::RenderWindow>(
		sf::VideoMode({ static_cast<unsigned int>(width),
										static_cast<unsigned int>(height) }),
		title,
		sf::Style::Default
	);

	if (!m_windowPtr.isNull()) {
		m_windowPtr->setFramerateLimit(60);
		MESSAGE("Window", "Window", "Window created successfully");
	}
	else {
		ERROR("Window", "Window", "Failed to create window");
	}
}

/**
 * @brief Destructor que libera los recursos asociados a la ventana.
 */
Window::~Window() {
	m_windowPtr.release();
}

/**
 * @brief Maneja los eventos de la ventana e integra con la interfaz de usuario.
 *
 * Procesa eventos de entrada y cierra la ventana si recibe un evento de cierre.
 *
 * @param engineGUI Referencia al sistema de GUI para procesar eventos.
 */
void
Window::handleEvents(EngineGUI& engineGUI) {

	while (const std::optional event = m_windowPtr->pollEvent())
	{
		engineGUI.processEvent(*m_windowPtr, *event);
		// Cerrar ventana al recibir evento de cierre
		if (event->is<sf::Event::Closed>())
			m_windowPtr->close();
	}
}

/**
 * @brief Verifica si la ventana está abierta.
 * @return `true` si la ventana está abierta, `false` en caso contrario.
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
 * @brief Limpia el contenido actual de la ventana con un color específico.
 * @param color Color de limpieza (por defecto negro si no se especifica).
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
 * @brief Dibuja un objeto en la ventana.
 *
 * @param drawable Referencia al objeto SFML dibujable.
 * @param states Estados de renderizado opcionales (por defecto `sf::RenderStates::Default`).
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
 * @brief Muestra en pantalla el contenido actualmente renderizado.
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
 * @brief Actualiza el tiempo delta (`deltaTime`) desde el último frame.
 */
void
Window::update() {
	deltaTime = m_clock.restart();
}

/**
 * @brief Método de renderizado vacío (puede sobreescribirse para lógica personalizada).
 */
void
Window::render() {
}

/**
 * @brief Libera explícitamente los recursos asociados a la ventana.
 */
void
Window::destroy() {
	m_windowPtr.release();
}
