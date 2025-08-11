#pragma once
/**
 * @file Window.h
 * @brief Declaración de la clase Window, encargada de la gestión de la ventana principal de renderizado.
 *
 * Proporciona funciones para manejar eventos, dibujar objetos, actualizar y mostrar gráficos usando SFML.
 * Esta clase encapsula un `sf::RenderWindow` y gestiona el ciclo de vida y operaciones básicas de la ventana.
 *
 * @author Hannin Abarca
 */

#include "Prerequisites.h"

class EngineGUI;

/**
 * @class Window
 * @brief Clase que encapsula una ventana de renderizado SFML con utilidades para gestión de eventos, dibujo y tiempo.
 */
class Window {
public:
	/**
	 * @brief Constructor por defecto.
	 */
	Window() = default;

	/**
	 * @brief Constructor que inicializa la ventana.
	 * @param width Ancho de la ventana en píxeles.
	 * @param height Alto de la ventana en píxeles.
	 * @param title Título de la ventana.
	 */
	Window(int width, int height, const std::string& title);

	/**
	 * @brief Destructor de la ventana.
	 */
	~Window();

	/**
	 * @brief Maneja los eventos de la ventana y de la interfaz.
	 * @param engineGUI Referencia a la instancia de la interfaz gráfica.
	 */
	void handleEvents(EngineGUI& engineGUI);

	/**
	 * @brief Indica si la ventana sigue abierta.
	 * @return `true` si está abierta, `false` si fue cerrada.
	 */
	bool isOpen() const;

	/**
	 * @brief Limpia la ventana con un color de fondo.
	 * @param color Color con el que se limpiará el buffer.
	 */
	void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

	/**
	 * @brief Dibuja un objeto en la ventana.
	 * @param drawable Objeto dibujable (derivado de sf::Drawable).
	 * @param states Estados de renderizado opcionales.
	 */
	void draw(const sf::Drawable& drawable,
		const sf::RenderStates& states = sf::RenderStates::Default);

	/**
	 * @brief Muestra en pantalla todo lo que se ha dibujado desde el último `clear()`.
	 */
	void display();

	/**
	 * @brief Actualiza el estado de la ventana (cálculo de deltaTime, etc.).
	 */
	void update();

	/**
	 * @brief Renderiza el contenido de la ventana.
	 */
	void render();

	/**
	 * @brief Libera los recursos asociados a la ventana.
	 */
	void destroy();

private:
	/**
	 * @brief Vista utilizada para la proyección y escalado de la ventana.
	 */
	sf::View m_view;

public:
	/**
	 * @brief Tiempo transcurrido entre frames.
	 */
	sf::Time deltaTime;

	/**
	 * @brief Reloj para medir tiempos entre frames.
	 */
	sf::Clock m_clock;

	/**
	 * @brief Puntero a la ventana de renderizado de SFML.
	 */
	EngineUtilities::TUniquePtr<sf::RenderWindow> m_windowPtr;
};
