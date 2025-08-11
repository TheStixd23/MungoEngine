#pragma once
/**
 * @file A_Player.h
 * @brief Declaración del actor controlable por el jugador con dos modos de control y parámetros básicos de movimiento.
 * @author Hannin Abarca
 */

#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "Prerequisites.h"
#include "./Actor.h"
#include "./Transform.h"

/**
 * @enum PlayerControlMode
 * @brief Modo de control que usará el sistema de entrada para mover al jugador.
 *
 * - @c Direct: aplica fuerzas/velocidades directamente (WASD, etc.).
 * - @c TargetSeek: el jugador intenta llegar a un @ref A_Player::target "objetivo".
 */
enum class PlayerControlMode {
    Direct,     /**< Control directo por entrada, con aceleración y fricción. */
    TargetSeek  /**< Movimiento calculado hacia un objetivo externo. */
};

/**
 * @class A_Player
 * @brief Actor controlable con aceleración, fricción y velocidad máxima. La posición real se guarda en su Transform.
 */
class A_Player : public Actor {
public:
    /**
     * @brief Crea un jugador con nombre y propiedades por defecto.
     * @param name Nombre lógico del actor.
     *
     * - @c acceleration = 600 px/s^2
     * - @c friction     = 6
     * - @c maxSpeed     = 250 px/s
     * - @c controlMode  = PlayerControlMode::Direct
     */
    A_Player(const std::string& name) : Actor(name) {}

    /** @name Modo de control */
    ///@{
    /**
     * @brief Establece el modo de control del jugador.
     * @param m Modo (Direct o TargetSeek).
     */
    void
    setControlMode(PlayerControlMode m) { controlMode = m; }

    /**
     * @brief Obtiene el modo de control actual.
     * @return Modo en uso.
     */
    PlayerControlMode
    getControlMode() const { return controlMode; }
    ///@}

    /** @name Parámetros de movimiento */
    ///@{
    /**
     * @brief Define la aceleración base (px/s²).
     * @param a Valor de aceleración.
     */
    void
    setAcceleration(float a) { acceleration = a; }

    /**
     * @brief Devuelve la aceleración (px/s²).
     */
    float
    getAcceleration() const { return acceleration; }

    /**
     * @brief Define la fricción por segundo.
     * @param f Factor de fricción.
     */
    void
    setFriction(float f) { friction = f; }

    /**
     * @brief Obtiene la fricción actual.
     * @return Factor de fricción.
     */
    float
    getFriction() const { return friction; }

    /**
     * @brief Establece la velocidad máxima (px/s).
     * @param s Velocidad tope.
     */
    void
    setMaxSpeed(float s) { maxSpeed = s; }

    /**
     * @brief Devuelve la velocidad máxima (px/s).
     */
    float
    getMaxSpeed() const { return maxSpeed; }
    ///@}

    /** @name Estado dinámico */
    ///@{
    /**
     * @brief Asigna la velocidad lineal (px/s).
     * @param v Velocidad.
     */
    void
    setVelocity(const sf::Vector2f& v) { velocity = v; }

    /**
     * @brief Devuelve la velocidad lineal (px/s).
     */
    sf::Vector2f
    getVelocity() const { return velocity; }
    ///@}

    /** @name Posición y objetivo (usa Transform) */
    ///@{
    /**
     * @brief Obtiene la posición mundial desde el Transform.
     * @return Posición (0,0) si no hay Transform.
     */
    sf::Vector2f
    getPosition() {
        if (auto tr = getComponent<Transform>()) return tr->getPosition();
        return {0.f, 0.f};
    }

    /**
     * @brief Establece la posición mundial en el Transform (si existe).
     * @param p Posición destino.
     */
    void
    setPosition(const sf::Vector2f& p) {
        if (auto tr = getComponent<Transform>()) tr->setPosition(p);
    }

    /**
     * @brief Define el objetivo hacia el cual moverse en TargetSeek.
     * @param t Punto objetivo.
     */
    void
    setTarget(const sf::Vector2f& t) { target = t; }

    /**
     * @brief Obtiene el objetivo actual.
     * @return Punto objetivo.
     */
    sf::Vector2f
    getTarget() const { return target; }
    ///@}

private:
    PlayerControlMode controlMode = PlayerControlMode::Direct; ///< Modo de control activo.
    sf::Vector2f      velocity{0.f, 0.f};                      ///< Velocidad (px/s).
    float             acceleration = 600.f;                    ///< Aceleración (px/s²).
    float             friction     = 6.f;                      ///< Fricción por segundo.
    float             maxSpeed     = 250.f;                    ///< Velocidad máxima (px/s).
    sf::Vector2f      target{0.f, 0.f};                        ///< Objetivo para TargetSeek.
};
