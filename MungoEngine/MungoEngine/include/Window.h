/**
 * @file Window.h
 * @brief Define la clase Window que encapsula una ventana de renderizado SFML para uso interno del motor gráfico.
 * @author Hannin Abarca
 */

#pragma once
#include "Prerequisites.h"

 /**
  * @class Window
  * @brief Encapsula una ventana SFML para manejo de eventos, dibujo y visualización.
  */
class Window {
public:
	/**
	 * @brief Constructor por defecto.
	 */
	Window() = default;

	/**
	 * @brief Constructor que crea una ventana con dimensiones y título específicos.
	 * @param width Ancho de la ventana.
	 * @param height Alto de la ventana.
	 * @param title Título de la ventana.
	 */
	Window(int width, int height, const std::string& title);

	/**
	 * @brief Destructor. Libera recursos asociados a la ventana.
	 */
	~Window();

	/**
	 * @brief Procesa los eventos de la ventana (cerrar, teclado, etc.).
	 */
	void handleEvents();

	/**
	 * @brief Verifica si la ventana aún está abierta.
	 * @return true si la ventana está abierta, false si fue cerrada.
	 */
	bool isOpen() const;

	/**
	 * @brief Limpia la ventana con un color específico.
	 * @param color Color de fondo (por defecto negro opaco).
	 */
	void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

	/**
	 * @brief Dibuja un objeto SFML en la ventana.
	 * @param drawable Referencia al objeto dibujable (shape, sprite, texto, etc.).
	 * @param states Estados de renderizado opcionales (por defecto estado estándar).
	 */
	void draw(const sf::Drawable& drawable,
		const sf::RenderStates& states = sf::RenderStates::Default);

	/**
	 * @brief Muestra el contenido actual en la ventana.
	 */
	void display();

	/**
	 * @brief Destruye la ventana y libera sus recursos.
	 */
	void destroy();

private:
	EngineUtilities::TUniquePtr<sf::RenderWindow> m_windowPtr; ///< Puntero único a la ventana SFML.
	sf::View m_view; ///< Vista de la cámara utilizada para renderizar.
};
