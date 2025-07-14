/**
 * @file Transform.h
 * @brief Define el componente Transform, encargado de almacenar la posici�n, rotaci�n y escala de una entidad.
 * @author Hannin Abarca
 */

#pragma once

#include "./ESC/Component.h"
#include <SFML/System/Vector2.hpp>

 /**
  * @brief Declaraci�n adelantada de la clase Window.
  */
class Window;

/**
 * @class Transform
 * @brief Componente que maneja la posici�n, rotaci�n y escala de una entidad.
 */
class Transform : public Component {
public:
	/**
	 * @brief Constructor por defecto que inicializa posici�n en (0,0), rotaci�n en (0,0) y escala en (1,1).
	 */
	Transform() :
		m_position(0.f, 0.f),
		m_rotation(0.f, 0.f),
		m_scale(1.f, 1.f),
		Component(ComponentType::TRANSFORM) {
	}

	/**
	 * @brief Destructor virtual.
	 */
	virtual ~Transform() = default;

	/**
	 * @brief M�todo llamado al iniciar el componente.
	 */
	void start() override;

	/**
	 * @brief Actualiza el componente cada frame.
	 * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
	 */
	void update(float deltaTime) override;

	/**
	 * @brief Renderiza el componente (no tiene representaci�n visual, implementaci�n vac�a).
	 * @param window Puntero a la ventana de renderizado.
	 */
	void render(const EngineUtilities::TSharedPointer<Window>& window) override;

	/**
	 * @brief Libera recursos asociados al componente.
	 */
	void destroy() override;

	/**
	 * @brief Establece la posici�n del componente.
	 * @param _position Vector con la nueva posici�n (x, y).
	 */
	void setPosition(const sf::Vector2f& _position) {
		m_position = _position;
	}

	/**
	 * @brief Establece la rotaci�n del componente.
	 * @param _rotation Vector con la rotaci�n (x, y).
	 */
	void setRotation(const sf::Vector2f& _rotation) {
		m_rotation = _rotation;
	}

	/**
	 * @brief Establece la escala del componente.
	 * @param _scale Vector con el nuevo escalado (x, y).
	 */
	void setScale(const sf::Vector2f& _scale) {
		m_scale = _scale;
	}

	/**
	 * @brief Obtiene una referencia a la posici�n.
	 * @return Referencia al vector de posici�n.
	 */
	sf::Vector2f& getPosition() {
		return m_position;
	}

	/**
	 * @brief Obtiene una referencia a la rotaci�n.
	 * @return Referencia al vector de rotaci�n.
	 */
	sf::Vector2f& getRotation() {
		return m_rotation;
	}

	/**
	 * @brief Obtiene una referencia a la escala.
	 * @return Referencia al vector de escala.
	 */
	sf::Vector2f& getScale() {
		return m_scale;
	}

private:
	sf::Vector2f m_position; ///< Posici�n de la entidad (x, y).
	sf::Vector2f m_rotation; ///< Rotaci�n de la entidad (x, y).
	sf::Vector2f m_scale;    ///< Escala de la entidad (x, y).
};
