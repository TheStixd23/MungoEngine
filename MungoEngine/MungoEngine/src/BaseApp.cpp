/**
 * @file BaseApp.cpp
 * @author Hannin Abarca
 * @brief Implementaci�n de la clase BaseApp que maneja el ciclo principal de la aplicaci�n
 * @version 1.0
 * @date 2025-06-01
 */

#include "BaseApp.h"

 /**
  * @brief Destructor de BaseApp, libera recursos
  */
BaseApp::~BaseApp()
{
}

/**
 * @brief M�todo principal que ejecuta el ciclo de la aplicaci�n
 *
 * Inicializa, procesa eventos, actualiza y renderiza hasta que se cierra la ventana
 *
 */
int
BaseApp::run()
{
    if (!init()) {
        ERROR("BaseApp",
            "run",
            "Initializes result on a false statement, check method validations");
    }

    while (m_window->isOpen()) {
        m_window->handleEvents();
        update();
        render();
    }

    Destroy();
    return 0;
}

/**
 * @brief Inicializa la aplicaci�n creando la ventana y configurando elementos
 *
 * @return true Si la inicializaci�n fue exitosa
 * @return false Si hubo alg�n error
 */
bool
BaseApp::init()
{
    m_window = new Window(800, 600, "MungoEngine");

    m_circle = new sf::CircleShape(100.0f);  ///< Crea un c�rculo con radio 100
    m_circle->setFillColor(sf::Color::Magenta);
    m_circle->setPosition(200.f, 150.f);

    return true;
}

/**
 * @brief Actualiza el estado de la aplicaci�n por frame
 */
void
BaseApp::update()
{
}

/**
 * @brief Renderiza los elementos en la ventana
 */
void
BaseApp::render()
{
    m_window->clear();
    m_window->draw(*m_circle);
    m_window->display();
}

/**
 * @brief Destruye y libera recursos usados por la aplicaci�n
 */
void
BaseApp::Destroy()
{
    delete m_circle;
    m_window->destroy();
}
