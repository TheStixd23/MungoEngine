#pragma once
#include "Prerequisites.h"
#include <./ESC/Component.h>
#include "./ESC/Texture.h"

class Window;

class CShape : public Component {
public:
    CShape()
        : m_shapePtr(nullptr),
        m_shapeType(ShapeType::EMPTY),
        m_line(nullptr),
        Component(ComponentType::SHAPE) {
    }

    CShape(ShapeType shapeType)
        : m_shapePtr(nullptr),
        m_shapeType(shapeType),
        m_line(nullptr),
        Component(ComponentType::SHAPE) {
    }

    virtual ~CShape() = default;

    void createShape(ShapeType shapeType);
    void start() override;
    void update(float deltaTime) override;
    void render(const EngineUtilities::TSharedPointer<Window>& window) override;
    void destroy() override;

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    void setFillColor(const sf::Color& color);
    void setRotation(float angle);
    void setScale(const sf::Vector2f& scl);
    void setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

private:
    EngineUtilities::TSharedPointer<sf::Shape> m_shapePtr;
    ShapeType m_shapeType;
    sf::VertexArray* m_line;
};
