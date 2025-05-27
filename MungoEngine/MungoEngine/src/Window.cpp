// Estilo de codificaci�n:
// - camelCase para variables y m�todos
// - PascalCase para clases
// - Tabulaci�n: 2 espacios
// - L�neas de 80 a 90 caracteres m�ximo
// - Prefijo g_ para variables globales
// - Las clases y estructuras se definen con la llave de apertura en la misma l�nea
// - Los m�todos dentro de clases se declaran con salto de l�nea entre el tipo y el nombre
// - La apertura del cuerpo del m�todo se realiza en una nueva l�nea

#include "window.h"

Window::Window(int width, int height, const std::string& title)
{
	// Initialize the window
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	if (m_window) {
		m_window->setFramerateLimit(60); // Set the frame rate limit to 60 FPS
		MESSAGE("Window", "Window", "window created successfully");
	}
	else {
		ERROR("Window", "Window", "window creation failed");
	}
}

Window::~Window()
{
	SAFE_PTR_RELEASE(m_window);
}

void
Window::handleEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event)) {
		// Cerrar la ventana si el usuario lo indica
		if (event.type == sf::Event::Closed)
			m_window->close();
	}
}
bool
Window::isOpen() const {
	// Check that window is not null
	if (m_window) {
		m_window->isOpen();
	}
	else {
		ERROR("Window", "isOpen", "Window is null");
		return false;
	}
}

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
void
Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	if (m_window) {
		m_window->draw(drawable, states);
	}
	else {
		ERROR("Window", "draw", "Window is null");
	}
}

void
Window::display() {
	if (m_window) {
		m_window->display();
	}
	else {
		ERROR("Window", "display", "Window is null");
	}
}
void
Window::destroy() {
	SAFE_PTR_RELEASE(m_window);
}