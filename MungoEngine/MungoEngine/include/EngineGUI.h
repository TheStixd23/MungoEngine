#pragma once
/**
 * @file EngineGUI.h
 * @brief Interfaz gráfica del motor, incluyendo jerarquía de actores, inspector, consola y menús.
 *
 * Esta clase encapsula todas las funciones relacionadas con la interfaz gráfica del motor,
 * permitiendo inspeccionar y modificar actores en tiempo de ejecución, manejar eventos de entrada
 * y renderizar elementos GUI utilizando bibliotecas gráficas como ImGui.
 *
 * @author Hannin Abarca
 */

#include "Prerequisites.h"
#include <vector>
class Window;
class Actor;

/**
 * @class EngineGUI
 * @brief Clase para gestionar y renderizar la interfaz gráfica del motor de juego.
 *
 * Permite mostrar menús, jerarquía de actores, inspector de propiedades, consola de depuración
 * y herramientas adicionales como el administrador de archivos o resaltado de selección.
 */
class EngineGUI {
public:
    /** @brief Constructor por defecto. */
    EngineGUI() = default;

    /** @brief Destructor por defecto. */
    ~EngineGUI() = default;

    /**
     * @brief Inicializa la interfaz gráfica.
     * @param window Puntero compartido a la ventana principal.
     */
    void
    init(const EngineUtilities::TSharedPointer<Window>& window);

    /**
     * @brief Actualiza el estado de la interfaz gráfica.
     * @param window Puntero compartido a la ventana principal.
     * @param deltaTime Tiempo transcurrido desde el último frame.
     */
    void
    update(const EngineUtilities::TSharedPointer<Window>& window, sf::Time deltaTime);

    /**
     * @brief Renderiza los elementos de la interfaz.
     * @param window Puntero compartido a la ventana principal.
     */
    void
    render(const EngineUtilities::TSharedPointer<Window>& window);

    /**
     * @brief Libera los recursos de la interfaz.
     */
    void
    destroy();

    /**
     * @brief Procesa un evento de entrada.
     * @param window Referencia a la ventana SFML.
     * @param event Evento recibido (teclado, ratón, etc.).
     */
    void
    processEvent(const sf::Window& window, const sf::Event& event);

    /**
     * @brief Configura el estilo visual de la interfaz.
     */
    void
    SetupMungoEngineGUIStyle();

    /**
     * @brief Dibuja la barra de menú principal.
     */
    void
    menuBar();

    /**
     * @brief Muestra la jerarquía de actores.
     * @param actors Vector de actores presentes en la escena.
     */
    void
    hierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

    /**
     * @brief Muestra el inspector de propiedades del actor seleccionado.
     * @param actors Vector de actores presentes en la escena.
     */
    void
    inspector(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

    /**
     * @brief Muestra la consola de depuración.
     */
    void
    console();

    /**
     * @brief Dibuja un contorno alrededor del actor seleccionado.
     * @param renderWindow Puntero a la ventana SFML.
     * @param actors Vector de actores presentes en la escena.
     */
    void 
    drawSelectedOutline
    (sf::RenderWindow* renderWindow, const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

    /**
     * @brief Muestra el panel del administrador de archivos.
     * @param actors Vector de actores que se pueden gestionar.
     */
    void 
    fileManagerPanel(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

    int selectedActorIndex = -1; ///< Índice del actor actualmente seleccionado.
};
