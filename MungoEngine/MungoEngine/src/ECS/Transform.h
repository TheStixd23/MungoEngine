#pragma once 

#include "Prerequisites.h"
#include "ECS/Component.h"

class Transform : public Component {
public:

    Transform()
        : Component(ComponentType::TRANSFORM),
        m_position(0.f, 0.f),
        m_rotation(0.f),
        m_scale(1.f, 1.f) {
    }

    virtual ~Transform() = default;

    void start() override {}

    void update(float deltaTime) override {}

    void render(const EngineUtilities::TSharedPointer<Window>& window) override {}

    void destroy() override {}

    void setPosition(const sf::Vector2f& position)
    {
        m_position = position;
    }

    void setRotation(float rotation)
    {
        m_rotation = rotation;
    }

    void setScale(const sf::Vector2f& scale)
    {
        m_scale = scale;
    }

    const sf::Vector2f& getPosition() const
    {
        return m_position;
    }

    float getRotation() const
    {
        return m_rotation;
    }

    const sf::Vector2f& getScale() const
    {
        return m_scale;
    }

private:
    sf::Vector2f m_position;
    float m_rotation;
    sf::Vector2f m_scale;
};
