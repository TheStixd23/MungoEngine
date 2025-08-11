#pragma once
/**
 * @file BaseApp.h
 * @brief Clase principal de la aplicación/juego que gestiona inicialización, actualización, renderizado y destrucción.
 *
 * Coordina la creación de la ventana, carga de actores, inicialización de sistemas
 * (entrada de jugador, IA de steering, seguimiento de waypoints, sistema de carrera)
 * y lógica de control de la carrera.
 *
 * @author Hannin Abarca
 */

#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include <vector>
#include <ESC/Actor.h>
#include "EngineGUI.h"
#include "./ESC/A_Racer.h"
#include "./ESC/A_Player.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/SteeringSystem.h"
#include "Systems/WaypointFollowSystem.h"
#include "Systems/RaceSystem.h"
#include "Components/Countdown.h"

 /**
  * @class BaseApp
  * @brief Clase principal que administra el ciclo de vida de la aplicación.
  *
  * Contiene los recursos principales (ventana, actores, sistemas) y ejecuta
  * el bucle de juego, controlando la lógica y renderizado de la escena.
  */
class BaseApp {
public:
	/**
	 * @brief Constructor por defecto.
	 */
	BaseApp() = default;

	/**
	 * @brief Destructor: libera recursos.
	 */
	~BaseApp();

	/**
	 * @brief Ejecuta el bucle principal de la aplicación.
	 * @return Código de salida.
	 */
	int run();

	/**
	 * @brief Inicializa la ventana, actores y sistemas.
	 * @return `true` si la inicialización fue exitosa.
	 */
	bool init();

	/**
	 * @brief Actualiza la lógica de juego en cada frame.
	 */
	void update();

	/**
	 * @brief Renderiza todos los elementos de la escena.
	 */
	void render();

	/**
	 * @brief Libera recursos y finaliza la aplicación.
	 */
	void destroy();

private:
	EngineUtilities::TSharedPointer<Window>   m_windowPtr;             ///< Ventana principal de la aplicación.
	EngineUtilities::TSharedPointer<Actor>    m_ACircle;               ///< Actor de prueba (círculo).
	EngineUtilities::TSharedPointer<Actor>    m_ATrack;                ///< Actor de la pista.
	EngineUtilities::TSharedPointer<A_Racer>  m_racerNPC;              ///< Corredor controlado por IA.
	EngineUtilities::TSharedPointer<A_Player> m_player;                ///< Jugador controlado por usuario.
	std::vector<EngineUtilities::TSharedPointer<A_Racer>> m_npcs;      ///< Lista de NPCs.
	std::vector<EngineUtilities::TSharedPointer<Actor>> actorsVector;  ///< Lista de todos los actores en escena.
	EngineGUI m_engineGUI;                                             ///< Interfaz gráfica del motor.
	std::vector<sf::Vector2f> m_waypoints;                             ///< Lista de puntos de la pista.
	EngineUtilities::TUniquePtr<PlayerInputSystem>    m_playerInputSystem;    ///< Sistema de control de jugador.
	EngineUtilities::TUniquePtr<SteeringSystem>       m_steeringSystem;       ///< Sistema de steering para NPCs.
	EngineUtilities::TUniquePtr<WaypointFollowSystem> m_waypointFollowSystem; ///< Sistema de seguimiento de waypoints.
	EngineUtilities::TUniquePtr<RaceSystem>           m_raceSystem;           ///< Sistema de gestión de la carrera.
	Countdown m_countdown{ 3.f };                                             ///< Cuenta regresiva para inicio.
	bool m_raceArmed = false;                                                  ///< Indica si la carrera está armada para iniciar.
	bool m_raceLive = false;                                                   ///< Indica si la carrera está en curso.
	bool m_raceFinished = false;                                               ///< Indica si la carrera terminó.
	int  m_finalPlace = -1;                                                     ///< Lugar final del jugador.
	int  m_lapsToWin = 3;                                                       ///< Número de vueltas para ganar.
	bool m_npcFinished = false;                                                 ///< Si los NPC han terminado la carrera.
	float m_sharedMaxSpeed = 260.f;                                             ///< Velocidad máxima compartida.
	float m_npcSpeedFactor = 0.95f;                                             ///< Factor de velocidad de NPC.

	/**
	 * @brief Reinicia el estado de la carrera para una nueva partida.
	 */
	void resetRace();
};
