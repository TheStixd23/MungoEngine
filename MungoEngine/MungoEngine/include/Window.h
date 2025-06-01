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
class
    Window {
public:
    /**
     * @brief Constructor por defecto
     */
    Window() = default;

    /**
     * @brief Constructor que crea una ventana con tamaño y título
     *
     * @param width  Ancho de la ventana
     * @param height Alto de la ventana
     * @param title  Título de la ventana
     */
    Window(int width, int height, const std::string& title);

    /**
     * @brief Destructor. Libera recursos asociados a la ventana
     */
    ~Window();

    /**
     * @brief Maneja los eventos de la ventana
     */
    void
        handleEvents();

    /**
     * @brief Verifica si la ventana está abierta
     *
     * @return true si la ventana sigue abierta, false si se ha cerrado
     */
    bool
        isOpen() const;

    /**
     * @brief Limpia la ventana con un color específico
     *
     * @param color Color de limpieza
     */
    void
        clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

    /**
     * @brief Dibuja un objeto en la ventana
     *
     * @param drawable Objeto drawable (como formas, texto, sprites)
     * @param states   Estados de render opcionales (por defecto estan vacíos)
     */
    void
        draw(const sf::Drawable& drawable,
            const sf::RenderStates& states = sf::RenderStates::Default);

    /**
     * @brief Muestra en pantalla todo lo que se ha dibujado hasta ahora
     */
    void
        display();

    /**
     * @brief Cierra y destruye la ventana
     */
    void
        destroy();

private:
    sf::RenderWindow* m_window; 
    sf::View m_view;            
};
