#pragma once
/**
 * @file SteeringSystem.h
 * @brief Sistema encargado de aplicar comportamientos de steering a corredores (seek, arrive, pursuit).
 *
 * Este sistema procesa a todos los corredores configurados y ajusta sus direcciones
 * y velocidades según el modo de steering activo.
 *
 * @author Hannin Abarca
 */

#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "Prerequisites.h"
#include "../ESC/A_Racer.h"
#include "../ESC/Transform.h"

 /**
  * @struct SteeringConfig
  * @brief Configuración para inicializar el sistema de steering.
  */
struct SteeringConfig {
    std::vector<EngineUtilities::TSharedPointer<A_Racer>> racers; ///< Lista de corredores controlados por el sistema.
    float seekRange = 10.f; ///< Distancia mínima para considerar que se ha llegado al objetivo en modo Seek.
};

/**
 * @class SteeringSystem
 * @brief Sistema que gestiona el movimiento de corredores usando algoritmos de steering.
 *
 * Implementa comportamientos como:
 * - **Arrive**: desacelerar al acercarse a un objetivo.
 * - **Pursuit**: interceptar un objetivo en movimiento prediciendo su posición futura.
 */
class SteeringSystem {
public:
    /**
     * @brief Constructor del sistema de steering.
     * @param cfg Configuración inicial con corredores y parámetros.
     */
    SteeringSystem(const SteeringConfig& cfg) : cfg(cfg) {}

    /** @brief Destructor por defecto. */
    ~SteeringSystem() = default;

    /**
     * @brief Actualiza el estado de steering de todos los corredores.
     * @param dt Tiempo transcurrido desde el último frame (segundos).
     */
    void update(float dt);

private:
    SteeringConfig cfg; ///< Configuración y referencias a corredores.

    /**
     * @brief Comportamiento de llegada (Arrive).
     * @param pos Posición actual.
     * @param target Posición objetivo.
     * @param speed Velocidad máxima permitida.
     * @param arriveRadius Radio dentro del cual se desacelera hasta detenerse.
     * @return Vector dirección y magnitud a aplicar.
     */
    sf::Vector2f arrive_L(const sf::Vector2f& pos,
        const sf::Vector2f& target,
        float speed, float arriveRadius);

    /**
     * @brief Comportamiento de persecución (Pursuit).
     * @param self Corredor que persigue.
     * @param target Corredor objetivo.
     * @param speed Velocidad máxima permitida.
     * @param maxPrediction Tiempo máximo para predecir la posición futura del objetivo.
     * @return Vector dirección y magnitud a aplicar.
     */
    sf::Vector2f pursuit_L(const A_Racer& self,
        const A_Racer& target,
        float speed, float maxPrediction);
};
