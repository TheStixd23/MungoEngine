/**
 * @file BaseApp.h
 * @author Hannin Abarca
 * @brief Declaración de la clase BaseApp, que controla el ciclo de vida principal
 * de la aplicación, incluyendo inicialización, actualización,
 * renderizado y destrucción de recursos
 * @version 1.0
 * @date 2025-06-01
 */

#pragma once

#include "Prerequisites.h"
#include "Window.h"

/**
 * @class BaseApp
 * @brief Clase principal que controla el ciclo de vida de una aplicación.
 * Encargada de inicializar, actualizar, renderizar y destruir los componentes
 * principales. Contiene punteros a la ventana y objetos gráficos
 */
class BaseApp {
public:
    /**
     * @brief Constructor por defecto de la aplicación
     */
    BaseApp() = default;

    /**
     * @brief Destructor. Libera recursos utilizados por la aplicación
     */
    ~BaseApp();

    /**
     * @brief Ejecuta el ciclo principal de la aplicación.
     *
     * Este método es llamado desde `main()` y controla el flujo principal
     *
     * @return Código de salida de la aplicación
     */
    int
        run();

    /**
     * @brief Inicializa los recursos de la aplicación
     *
     * Debe llamarse antes del ciclo de actualización/renderizado
     *
     * @return true si la inicialización fue exitosa; false en caso contrario
     */
    bool
        init();

    /**
     * @brief Actualiza la lógica de la aplicación por fotograma
     */
    void
        update();

    /**
     * @brief Renderiza los elementos gráficos en pantalla
     */
    void
        render();

    /**
     * @brief Libera recursos y cierra correctamente la aplicación
     */
    void
        Destroy();

private:
    /**
     * @brief Puntero a la ventana principal de la aplicación
     */
    Window* m_window;

    /**
     * @brief Puntero a una forma de círculo usada para renderizado
     */
    sf::CircleShape* m_circle;
};
