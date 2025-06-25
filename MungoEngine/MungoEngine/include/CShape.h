/**
 * @file CShape.h
 * @author Hannin Abarca
 * @brief Declaración de la clase CShape para la definición de figuras geométricas
 * renderizables con SFML. Contiene la interfaz pública y privada para crear,
 * modificar y manipular figuras como círculos, rectángulos, triángulos y polígonos
 * @version 1.0
 * @date 2025-06-01
 */

#pragma once

#include "Prerequisites.h"
#include "ECS/Component.h"

class Window;

enum ShapeType {
    EMPTY = 0,
    CIRCLE,
    RECTANGLE,
    TRIANGLE,
    POLYGON
};

/**
 * @class CShape
 * @brief Componente que representa una figura geométrica renderizable.
 * Permite crear, actualizar y renderizar figuras SFML como círculos, rectángulos,
 * etc. También da métodos para manipular sus propiedades como posición,
 * rotación, escala y color
 */
class CShape : public Component {
public:
    CShape()
        : m_shapePtr(nullptr),
        m_shapeType(ShapeType::EMPTY),
        Component(ComponentType::SHAPE) {
    }

    CShape(ShapeType shapeType)
        : m_shapePtr(nullptr),
        m_shapeType(ShapeType::EMPTY),
        Component(ComponentType::SHAPE) {
        createShape(shapeType);
    }

    virtual ~CShape() = default;

    void createShape(ShapeType shapeType);

    virtual void start() override;
    virtual void update(float deltaTime) override;
    virtual void render(const EngineUtilities::TSharedPointer<Window>& window) override;
    virtual void destroy() override;

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);

    void setFillColor(const sf::Color& color);
    void setRotation(float angle);
    void setScale(const sf::Vector2f& scl);

    sf::Shape* getShape() { return m_shapePtr; }

private:
    sf::Shape* m_shapePtr;
    ShapeType m_shapeType;
    sf::VertexArray m_line;
};
