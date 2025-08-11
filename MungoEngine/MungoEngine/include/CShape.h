#pragma once
/**
 * @file CShape.h
 * @brief Componente encargado de manejar y renderizar una forma SFML dentro de un Actor.
 *
 * Este componente permite crear, modificar y dibujar formas 2D (rectángulos, círculos, etc.)
 * y admite configuración de posición, escala, rotación, color y textura.
 *
 * @author Hannin Abarca
 */

#include "Prerequisites.h"
#include <./ESC/Component.h>
#include "./ESC/Texture.h"

class Window;

/**
 * @class CShape
 * @brief Componente para renderizar formas geométricas utilizando SFML.
 *
 * Se integra dentro de un Actor para representar visualmente un objeto.
 * Administra un puntero compartido a `sf::Shape` y provee métodos para modificar
 * sus propiedades gráficas.
 */
class CShape : public Component {
public:
	/**
	 * @brief Constructor por defecto. No inicializa ninguna forma.
	 */
	CShape() = default;

	/**
	 * @brief Constructor que inicializa el componente con un tipo de forma.
	 * @param shapeType Tipo de forma a crear (Circle, Rectangle, etc.).
	 */
	CShape(ShapeType shapeType) :
		m_shapePtr(nullptr),
		m_shapeType(ShapeType::EMPTY),
		Component(ComponentType::SHAPE) {
	}

	virtual ~CShape() = default;

	/**
	 * @brief Crea una forma del tipo especificado.
	 * @param shapeType Tipo de forma SFML a instanciar.
	 */
	void createShape(ShapeType shapeType);

	/// @copydoc Component::start
	void start() override;

	/// @copydoc Component::update
	void update(float deltaTime) override;

	/// @copydoc Component::render
	void render(const EngineUtilities::TSharedPointer<Window>& window) override;

	/// @copydoc Component::destroy
	void destroy() override;

	/**
	 * @brief Define la posición de la forma.
	 * @param x Coordenada X.
	 * @param y Coordenada Y.
	 */
	void setPosition(float x, float y);

	/**
	 * @brief Define la posición de la forma.
	 * @param position Vector 2D con coordenadas (X,Y).
	 */
	void setPosition(const sf::Vector2f& position);

	/**
	 * @brief Cambia el color de relleno de la forma.
	 * @param color Color SFML.
	 */
	void setFillColor(const sf::Color& color);

	/**
	 * @brief Rota la forma.
	 * @param angle Ángulo en grados.
	 */
	void setRotation(float angle);

	/**
	 * @brief Escala la forma.
	 * @param scl Vector de escala (X,Y).
	 */
	void setScale(const sf::Vector2f& scl);

	/**
	 * @brief Aplica una textura a la forma.
	 * @param texture Puntero compartido a la textura.
	 */
	void setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

	/**
	 * @brief Obtiene un puntero a la forma interna de SFML.
	 * @return Puntero compartido a `sf::Shape`.
	 */
	EngineUtilities::TSharedPointer<sf::Shape> getShapePtr() { return m_shapePtr; }

private:
	EngineUtilities::TSharedPointer<sf::Shape> m_shapePtr; ///< Puntero compartido a la forma SFML.
	ShapeType m_shapeType; ///< Tipo de forma (círculo, rectángulo, etc.).
	sf::VertexArray* m_line; ///< Puntero opcional para formas de línea.
};
