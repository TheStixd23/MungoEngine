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
    BaseApp() = default;
    ~BaseApp();

    int run();
    bool init();
    void update();
    void render();
    void Destroy();

private:
    Window* m_window = nullptr;
    sf::CircleShape* m_circle = nullptr;
};
