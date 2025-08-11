#pragma once
/**
 * @file A_Racer.h
 * @brief Declaración de un actor tipo corredor (NPC o jugador) con soporte para steering behaviors.
 *
 * La clase A_Racer almacena estado lógico de movimiento (posición, objetivo, velocidad) y parámetros
 * para controlar su comportamiento de steering, como Seek, Arrive o Pursuit. Incluye utilidades para
 * configurar velocidad, radios de llegada y objetivos de persecución.
 *
 * @author Hannin Abarca
 */

#include "Actor.h"
#include <SFML/System/Vector2.hpp>
#include "Prerequisites.h"

 /**
  * @enum SteeringMode
  * @brief Modos de steering disponibles para el corredor.
  *
  * - @c Seek: movimiento hacia un punto objetivo a velocidad constante.
  * - @c Arrive: movimiento hacia un objetivo reduciendo velocidad al acercarse.
  * - @c Pursuit: persecución de otro corredor usando predicción de posición.
  */
enum class SteeringMode { Seek, Arrive, Pursuit };

/**
 * @class A_Racer
 * @brief Actor corredor con lógica de steering y estado de carrera.
 *
 * Permite definir su posición y objetivo lógicos, velocidad, modo de steering y parámetros de llegada.
 * Puede configurarse para perseguir otro corredor, con un tiempo máximo de predicción configurable.
 */
class A_Racer : public Actor {
public:
    /**
     * @brief Construye un corredor con nombre y valores por defecto.
     * @param name Nombre lógico del actor.
     */
    A_Racer(const std::string& name);

    /**
     * @brief Actualiza la lógica del corredor.
     * @param deltaTime Tiempo transcurrido desde el último frame (segundos).
     */
    void update(float deltaTime) override;

    /** @name Posición en carrera */
    ///@{
    /**
     * @brief Establece la posición en la clasificación de carrera.
     * @param newPlace Lugar actual (1 = primero).
     */
    void setPlace(int newPlace) { place = newPlace; }

    /**
     * @brief Obtiene la posición actual en la clasificación.
     * @return Lugar actual.
     */
    int getPlace() const { return place; }
    ///@}

    /** @name Estado lógico de movimiento */
    ///@{
    /**
     * @brief Define la posición lógica del corredor.
     * @param pos Posición en coordenadas mundiales.
     */
    void setPosition(const sf::Vector2f& pos) { logicPosition = pos; }

    /**
     * @brief Obtiene la posición lógica del corredor.
     * @return Posición en coordenadas mundiales.
     */
    sf::Vector2f getPosition() const { return logicPosition; }

    /**
     * @brief Define el objetivo lógico del corredor.
     * @param waypoint Coordenadas del objetivo.
     */
    void setTarget(const sf::Vector2f& waypoint) { logicTarget = waypoint; }

    /**
     * @brief Obtiene el objetivo lógico del corredor.
     * @return Coordenadas del objetivo.
     */
    sf::Vector2f getTarget() const { return logicTarget; }

    /**
     * @brief Establece la velocidad de movimiento.
     * @param s Velocidad en px/s.
     */
    void setSpeed(float s) { speed = s; }

    /**
     * @brief Obtiene la velocidad actual.
     * @return Velocidad en px/s.
     */
    float getSpeed() const { return speed; }
    ///@}

    /** @name Configuración de steering */
    ///@{
    /**
     * @brief Activa o desactiva la lógica de steering.
     * @param enabled Si es falso, el movimiento se detiene.
     */
    void enableSteering(bool enabled) { steeringEnabled = enabled; }

    /**
     * @brief Verifica si el steering está habilitado.
     * @return true si está habilitado.
     */
    bool isSteeringEnabled() const { return steeringEnabled; }

    /**
     * @brief Establece el radio de llegada para el modo Arrive.
     * @param radius Distancia a la que se empieza a frenar.
     */
    void setArriveRadius(float radius) { arriveRadius = radius; }

    /**
     * @brief Obtiene el radio de llegada actual.
     * @return Radio en píxeles.
     */
    float getArriveRadius() const { return arriveRadius; }

    /**
     * @brief Establece el modo de steering.
     * @param m Modo deseado.
     */
    void setMode(SteeringMode m) { mode = m; }

    /**
     * @brief Obtiene el modo de steering actual.
     * @return Modo configurado.
     */
    SteeringMode getMode() const { return mode; }
    ///@}

    /** @name Configuración de Pursuit */
    ///@{
    /**
     * @brief Establece el objetivo de persecución.
     * @param t Puntero débil al corredor objetivo.
     */
    void setPursuitTarget(const EngineUtilities::TWeakPointer<A_Racer>& t) { pursuitTarget = t; }

    /**
     * @brief Obtiene el objetivo de persecución.
     * @return Puntero débil al corredor objetivo.
     */
    EngineUtilities::TWeakPointer<A_Racer> getPursuitTarget() const { return pursuitTarget; }

    /**
     * @brief Define el tiempo máximo de predicción para Pursuit.
     * @param p Tiempo en segundos.
     */
    void setMaxPrediction(float p) { maxPrediction = p; }

    /**
     * @brief Obtiene el tiempo máximo de predicción para Pursuit.
     * @return Tiempo en segundos.
     */
    float getMaxPrediction() const { return maxPrediction; }
    ///@}

private:
    int place = 0; ///< Posición en la clasificación.

    sf::Vector2f logicPosition{ 0.f, 0.f }; ///< Posición lógica actual.
    sf::Vector2f logicTarget{ 0.f, 0.f };   ///< Objetivo lógico actual.
    float        speed = 100.f;           ///< Velocidad de movimiento.

    bool         steeringEnabled = true;  ///< Indica si el steering está activo.
    float        arriveRadius = 10.f;     ///< Radio de llegada para Arrive.
    SteeringMode mode = SteeringMode::Seek; ///< Modo de steering actual.

    EngineUtilities::TWeakPointer<A_Racer> pursuitTarget; ///< Objetivo de Pursuit.
    float        maxPrediction = 0.5f; ///< Tiempo máximo de predicción en Pursuit (segundos).
};
