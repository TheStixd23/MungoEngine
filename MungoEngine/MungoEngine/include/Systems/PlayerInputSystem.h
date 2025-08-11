#pragma once
/**
 * @file PlayerInputSystem.h
 * @brief Sistema encargado de procesar la entrada del jugador y aplicarla al actor controlable.
 *
 * Permite manejar el movimiento del jugador en diferentes modos de control (Direct o TargetSeek),
 * obteniendo entradas desde un `sf::RenderWindow`.
 *
 * @author Hannin Abarca
 */

#include "Prerequisites.h"
#include "../ESC/A_Player.h"

 /**
  * @struct PlayerInputConfig
  * @brief Configuración necesaria para inicializar el sistema de entrada del jugador.
  */
struct PlayerInputConfig {
	EngineUtilities::TSharedPointer<A_Player> player; ///< Referencia al actor jugador.
	sf::RenderWindow* renderWindow = nullptr;         ///< Puntero a la ventana donde se capturan entradas.
};

/**
 * @class PlayerInputSystem
 * @brief Sistema que procesa la entrada del jugador y la traduce en movimiento o acciones.
 *
 * Soporta modos de control directo y por objetivo, actualizando la posición o estado del jugador
 * en cada frame según las entradas recibidas.
 */
class PlayerInputSystem {
public:
	/**
	 * @brief Constructor que recibe la configuración del sistema.
	 * @param cfg Estructura con referencias al jugador y ventana.
	 */
	PlayerInputSystem(const PlayerInputConfig& cfg) : cfg(cfg) {}

	/** @brief Destructor por defecto. */
	~PlayerInputSystem() = default;

	/**
	 * @brief Actualiza la entrada del jugador.
	 * @param dt Tiempo en segundos desde el último frame.
	 */
	void update(float dt);

private:
	PlayerInputConfig cfg; ///< Configuración y referencias necesarias.

	/**
	 * @brief Procesa entradas en modo de control directo.
	 * @param dt Tiempo en segundos desde el último frame.
	 */
	void updateDirect(float dt);

	/** @brief Procesa entradas en modo TargetSeek. */
	void updateTargetSeek();
};
