#pragma once
/**
 * @file Transform.h
 * @brief Componente que gestiona la posición, rotación y escala de una entidad.
 *
 * Proporciona métodos para establecer y obtener las transformaciones,
 * así como una función simple de "seek" para mover la entidad hacia
 * un objetivo con velocidad controlada.
 *
 * @author Hannin Abarca
 */

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

 /**
  * @class Transform
  * @brief Componente que almacena y modifica la posición, rotación y escala de una entidad.
  *
  * Es utilizado como la fuente de verdad de la ubicación y dimensiones de un Actor.
  * Permite modificar sus valores directamente o usar funciones auxiliares como @ref seek().
  */
class Transform : public Component {
public:
	/**
	 * @brief Constructor por defecto.
	 *
	 * Inicializa la posición en (0,0), la rotación en (0,0) y la escala en (1,1).
	 * Se registra como componente de tipo TRANSFORM.
	 */
	Transform() :
		m_position(0.f, 0.f),
		m_rotation(0.f, 0.f),
		m_scale(1.f, 1.f),
		Component(ComponentType::TRANSFORM) {
	}

	/** @brief Destructor virtual por defecto. */
	virtual ~Transform() = default;

	/** @brief Inicialización del componente (sin implementación). */
	void start() override {}

	/** @brief Actualización del componente (sin implementación). */
	void update(float deltaTime) override {}

	/** @brief Renderizado del componente (sin implementación). */
	void render(const EngineUtilities::TSharedPointer<Window>& window) override {}

	/** @brief Destrucción del componente (sin implementación). */
	void destroy() {}

	/**
	 * @brief Mueve la entidad hacia una posición objetivo.
	 * @param targetPosition Posición a la que dirigirse.
	 * @param speed Velocidad de movimiento (px/s).
	 * @param deltaTime Tiempo transcurrido desde el último frame (s).
	 * @param range Distancia mínima para detenerse antes de llegar al objetivo.
	 *
	 * Calcula la dirección hacia el objetivo y mueve la posición en línea recta,
	 * deteniéndose cuando entra en el rango especificado.
	 */
	void seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range) {
		sf::Vector2f direction = targetPosition - m_position;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length > range) {
			direction.x /= length;
			direction.y /= length;
			m_position += direction * speed * deltaTime;
		}
	}

	/** @brief Establece la posición absoluta. */
	void setPosition(const sf::Vector2f& _position) { m_position = _position; }

	/** @brief Establece la rotación (en grados). */
	void setRotation(const sf::Vector2f& _rotation) { m_rotation = _rotation; }

	/** @brief Establece la escala relativa. */
	void setScale(const sf::Vector2f& _scale) { m_scale = _scale; }

	/** @brief Obtiene la posición actual. */
	sf::Vector2f& getPosition() { return m_position; }

	/** @brief Obtiene la rotación actual. */
	sf::Vector2f& getRotation() { return m_rotation; }

	/** @brief Obtiene la escala actual. */
	sf::Vector2f& getScale() { return m_scale; }

private:
	sf::Vector2f m_position;  ///< Posición de la entidad en coordenadas del mundo.
	sf::Vector2f m_rotation;  ///< Rotación en grados (puede representarse como ángulo 2D o vector).
	sf::Vector2f m_scale;     ///< Escala relativa respecto al tamaño original.
};
