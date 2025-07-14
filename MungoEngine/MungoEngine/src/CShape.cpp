#include "CShape.h"
#include "Window.h"

/**
 * @brief Crea una figura de tipo Shape utilizando el tipo especificado.
 *
 * @param type Tipo de figura a crear (CIRCLE, RECTANGLE, TRIANGLE, POLYGON).
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
        auto rectSP = EngineUtilities::MakeShared<sf::RectangleShape>
            (sf::Vector2f(100.f, 50.f));
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
 * @brief Método llamado al iniciar el componente. (Vacío por ahora)
 */
void
CShape::start() {
}

/**
 * @brief Actualiza la figura en cada frame.
 *
 * @param deltaTime Tiempo transcurrido desde el último frame.
 */
void
CShape::update(float deltaTime) {
}

/**
 * @brief Dibuja la figura en la ventana.
 *
 * @param window Puntero compartido a la ventana donde se dibujará.
 */
void
CShape::render(const EngineUtilities::TSharedPointer<Window>& window) {
    if (m_shapePtr) {
        window->draw(*m_shapePtr);
    }
}

/**
 * @brief Elimina la figura actual y libera los recursos.
 */
void
CShape::destroy() {
    m_shapePtr.reset();
}

/**
 * @brief Establece la posición de la figura.
 *
 * @param x Coordenada X.
 * @param y Coordenada Y.
 */
void
CShape::setPosition(float x, float y) {
    if (m_shapePtr) m_shapePtr->setPosition(x, y);
    else ERROR("CShape", "setPosition", "Shape no inicializado");
}

/**
 * @brief Establece la posición de la figura.
 *
 * @param pos Vector 2D con las coordenadas de posición.
 */
void
CShape::setPosition(const sf::Vector2f& pos) {
    if (m_shapePtr) m_shapePtr->setPosition(pos);
    else ERROR("CShape", "setPosition", "Shape no inicializado");
}

/**
 * @brief Establece el color de relleno de la figura.
 *
 * @param color Color de relleno.
 */
void
CShape::setFillColor(const sf::Color& color) {
    if (m_shapePtr) m_shapePtr->setFillColor(color);
    else ERROR("CShape", "setFillColor", "Shape no inicializado");
}

/**
 * @brief Establece la rotación de la figura.
 *
 * @param angle Ángulo en grados.
 */
void
CShape::setRotation(float angle) {
    if (m_shapePtr) m_shapePtr->setRotation(angle);
    else ERROR("CShape", "setRotation", "Shape no inicializado");
}

/**
 * @brief Establece la escala de la figura.
 *
 * @param scale Vector 2D que representa el escalado en X e Y.
 */
void
CShape::setScale(const sf::Vector2f& scale) {
    if (m_shapePtr) m_shapePtr->setScale(scale);
    else ERROR("CShape", "setScale", "Shape no inicializado");
}
