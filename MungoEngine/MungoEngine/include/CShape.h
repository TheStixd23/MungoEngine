/**
 * @file CShape.h
 * @brief Define la clase CShape, un componente derivado que representa una figura gráfica en pantalla.
 * @author Hannin Abarca
 */

#pragma once
#include "Prerequisites.h"
#include "./ESC/Component.h"

 /**
  * @brief Declaración adelantada de la clase Window.
  */
class
	Window;

/**
 * @class CShape
 * @brief Componente derivado que representa una figura gráfica SFML.
 */
class
	CShape : public Component {

public:
	/**
	 * @brief Constructor por defecto.
	 */
	CShape() = default;

	/**
	 * @brief Constructor con inicialización del tipo de figura.
	 * @param shapeType Tipo de figura a crear.
	 */
	CShape(ShapeType shapeType) :
		m_shapePtr(nullptr),
		m_shapeType(ShapeType::EMPTY),
		Component(ComponentType::SHAPE) {
	}

	/**
	 * @brief Destructor.
	 */
	virtual
		~CShape() = default;

	/**
	 * @brief Crea la figura según el tipo especificado.
	 * @param shapeType Valor del enumerador que indica el tipo de figura.
	 */
	void
		createShape(ShapeType shapeType);

	/**
	 * @brief Método del ciclo de vida que se ejecuta al inicio.
	 */
	void
		start() override;

	/**
	 * @brief Actualiza el estado de la figura.
	 * @param deltaTime Tiempo transcurrido desde el último frame.
	 */
	void
		update(float deltaTime) override;

	/**
	 * @brief Dibuja la figura en la ventana proporcionada.
	 * @param window Puntero compartido a la ventana destino.
	 */
	void
		render(const EngineUtilities::TSharedPointer<Window>& window) override;

	/**
	 * @brief Libera recursos asociados a la figura.
	 */
	void
		destroy() override;

	/**
	 * @brief Establece la posición de la figura.
	 * @param x Coordenada X.
	 * @param y Coordenada Y.
	 */
	void
		setPosition(float x, float y);

	/**
	 * @brief Establece la posición de la figura usando un vector.
	 * @param position Vector 2D con la nueva posición.
	 */
	void
		setPosition(const sf::Vector2f& position);

	/**
	 * @brief Establece el color de relleno de la figura.
	 * @param color Color de tipo SFML.
	 */
	void
		setFillColor(const sf::Color& color);

	/**
	 * @brief Establece el ángulo de rotación de la figura.
	 * @param angle Ángulo de rotación en grados.
	 */
	void
		setRotation(float angle);

	/**
	 * @brief Establece la escala de la figura.
	 * @param scl Vector 2D de escala.
	 */
	void
		setScale(const sf::Vector2f& scl);

private:
	EngineUtilities::TSharedPointer<sf::Shape>
		m_shapePtr; ///< Puntero compartido a la instancia de forma SFML.
	ShapeType m_shapeType; ///< Enum que representa el tipo actual de la figura.
	sf::VertexArray* m_line; ///< Puntero para renderizado de líneas (opcional).
};
