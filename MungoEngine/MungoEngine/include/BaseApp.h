/**
 * @file BaseApp.h
 * @author Hannin Abarca
 * @brief Declaraci�n de la clase BaseApp, que controla el ciclo de vida principal
 * de la aplicaci�n, incluyendo inicializaci�n, actualizaci�n,
 * renderizado y destrucci�n de recursos
 * @version 1.0
 * @date 2025-06-01
 */

#pragma once

#include "Prerequisites.h"
#include "Window.h"

/**
 * @class BaseApp
 * @brief Clase principal que controla el ciclo de vida de una aplicaci�n.
 * Encargada de inicializar, actualizar, renderizar y destruir los componentes
 * principales. Contiene punteros a la ventana y objetos gr�ficos
 */
class BaseApp {
public:
    /**
     * @brief Constructor por defecto de la aplicaci�n
     */
    BaseApp() = default;

    /**
     * @brief Destructor. Libera recursos utilizados por la aplicaci�n
     */
    ~BaseApp();

    /**
     * @brief Ejecuta el ciclo principal de la aplicaci�n.
     *
     * Este m�todo es llamado desde `main()` y controla el flujo principal
     *
     * @return C�digo de salida de la aplicaci�n
     */
    int
        run();

    /**
     * @brief Inicializa los recursos de la aplicaci�n
     *
     * Debe llamarse antes del ciclo de actualizaci�n/renderizado
     *
     * @return true si la inicializaci�n fue exitosa; false en caso contrario
     */
    bool
        init();

    /**
     * @brief Actualiza la l�gica de la aplicaci�n por fotograma
     */
    void
        update();

    /**
     * @brief Renderiza los elementos gr�ficos en pantalla
     */
    void
        render();

    /**
     * @brief Libera recursos y cierra correctamente la aplicaci�n
     */
    void
        Destroy();

private:
    /**
     * @brief Puntero a la ventana principal de la aplicaci�n
     */
    Window* m_window;

    /**
     * @brief Puntero a una forma de c�rculo usada para renderizado
     */
    sf::CircleShape* m_circle;
};
