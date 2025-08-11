/**
 * @file CShape.cpp
 * @brief Implementación del componente CShape para crear y renderizar formas SFML.
 *
 * Administra una `sf::Shape` subyacente (círculo, rectángulo, triángulo, polígono),
 * y expone utilidades de posicionamiento, color, rotación, escala y textura.
 *
 * Autor: Hannin Abarca
 */

#include "CShape.h"
#include "Window.h"

 /**
  * @brief Crea una forma SFML del tipo solicitado y la almacena en @c m_shapePtr.
  * @param type Tipo de forma a instanciar (CIRCLE, RECTANGLE, TRIANGLE, POLYGON).
  * @note En caso de tipo desconocido, limpia el puntero y emite un ERROR().
  */
void
CShape::createShape(ShapeType type) {
	m_shapeType = type;
	switch (type) {
	case ShapeType::CIRCLE: {
		auto circleSP = EngineUtilities::MakeShared<sf::CircleShape>(10.f);
		circleSP->setFillColor(sf::Color::White);
		m_shapePtr = circleSP.dynamic_pointer_cast<sf::Shape>();
		break;
	}
	case ShapeType::RECTANGLE: {
		auto rectSP = EngineUtilities::MakeShared<sf::RectangleShape>(sf::Vector2f(100.f, 50.f));
		rectSP->setFillColor(sf::Color::White);
		m_shapePtr = rectSP.dynamic_pointer_cast<sf::Shape>();
		break;
	}
	case ShapeType::TRIANGLE: {
		auto triSP = EngineUtilities::MakeShared<sf::ConvexShape>(3);
		triSP->setPoint(0, { 0,0 });
		triSP->setPoint(1, { 50,100 });
		triSP->setPoint(2, { 100,0 });
		triSP->setFillColor(sf::Color::White);
		m_shapePtr = triSP.dynamic_pointer_cast<sf::Shape>();
		break;
	}
	case ShapeType::POLYGON: {
		auto polySP = EngineUtilities::MakeShared<sf::ConvexShape>(5);
		polySP->setPoint(0, { 0,0 });
		polySP->setPoint(1, { 50,100 });
		polySP->setPoint(2, { 100,0 });
		polySP->setPoint(3, { 75,-50 });
		polySP->setPoint(4, { -25,-50 });
		polySP->setFillColor(sf::Color::White);
		m_shapePtr = polySP.dynamic_pointer_cast<sf::Shape>();
		break;
	}
	default:
		m_shapePtr.reset();
		ERROR("CShape", "createShape", "Tipo desconocido");
		return;
	}
}

/**
 * @brief Hook de inicio del componente (actualmente sin lógica).
 */
void
CShape::start() {
}

/**
 * @brief Actualización por frame del componente (actualmente sin lógica).
 * @param deltaTime Tiempo en segundos desde el último frame.
 */
void
CShape::update(float deltaTime) {
}

/**
 * @brief Dibuja la forma en la ventana, si existe.
 * @param window Ventana destino de render.
 */
void
CShape::render(const EngineUtilities::TSharedPointer<Window>& window) {
	if (m_shapePtr) {
		window->draw(*m_shapePtr);
	}
}

/**
 * @brief Hook de destrucción del componente (actualmente sin lógica).
 */
void
CShape::destroy() {
}

/**
 * @brief Establece la posición de la forma (sobrecarga por componentes X/Y).
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @warning Emite ERROR() si la forma no fue creada previamente.
 */
void CShape::setPosition(float x, float y) {
	if (m_shapePtr) {
		m_shapePtr->setPosition({ x, y });
	}
	else {
		ERROR("CShape", "setPosition", "Shape no inicializado");
	}
}

/**
 * @brief Establece la posición de la forma (sobrecarga por vector).
 * @param position Posición 2D.
 * @warning Emite ERROR() si la forma no fue creada previamente.
 */
void CShape::setPosition(const sf::Vector2f& position) {
	if (m_shapePtr) {
		m_shapePtr->setPosition(position);
	}
	else {
		ERROR("CShape", "setPosition", "Shape no inicializado");
	}
}

/**
 * @brief Cambia el color de relleno de la forma.
 * @param color Color SFML.
 * @warning Emite ERROR() si la forma no fue creada previamente.
 */
void CShape::setFillColor(const sf::Color& color) {
	if (m_shapePtr) m_shapePtr->setFillColor(color);
	else ERROR("CShape", "setFillColor", "Shape no inicializado");
}

/**
 * @brief Ajusta la rotación de la forma.
 * @param angle Ángulo en grados.
 * @warning Emite ERROR() si la forma no fue creada previamente.
 */
void CShape::setRotation(float angle) {
	if (m_shapePtr) m_shapePtr->setRotation(sf::degrees(angle));
	else ERROR("CShape", "setRotation", "Shape no inicializado");
}

/**
 * @brief Aplica un factor de escala a la forma.
 * @param scale Escala en ejes X e Y.
 * @warning Emite ERROR() si la forma no fue creada previamente.
 */
void CShape::setScale(const sf::Vector2f& scale) {
	if (m_shapePtr) m_shapePtr->setScale(scale);
	else ERROR("CShape", "setScale", "Shape no inicializado");
}

/**
 * @brief Asigna una textura SFML a la forma interna.
 * @param texture Puntero compartido a la textura del motor.
 * @note No valida @c m_shapePtr; asume que la forma ya existe.
 */
void
CShape::setTexture(const EngineUtilities::TSharedPointer<Texture>& texture) {
	if (!texture.isNull()) {
		m_shapePtr->setTexture(&texture->getTexture());
	}
}
