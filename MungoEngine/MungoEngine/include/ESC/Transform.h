#pragma once

#include "Prerequisites.h"
#include "./ESC/Component.h"
#include "Window.h"
#include <cmath> // Para std::sqrt

class Window;

/**
 * @class Transform
 * @brief Component managing position, rotation, and scale of an entity.
 *
 * This component handles the spatial transformation of an entity,
 * including position, rotation, and scale in 2D space.
 */
class Transform : public Component {
public:
    /**
     * @brief Default constructor initializes position (0,0),
     * rotation (0,0), and scale (1,1).
     */
    Transform()
        : m_position(0.f, 0.f),
        m_rotation(0.f, 0.f),
        m_scale(1.f, 1.f),
        Component(ComponentType::TRANSFORM) {
    }

    /**
     * @brief Virtual destructor.
     */
    virtual ~Transform() = default;

    /**
     * @brief Called once when the component starts.
     *
     * Typically used to perform initialization logic.
     */
    void start() override {}

    /**
     * @brief Called every frame to update the component.
     * @param deltaTime Time elapsed since last frame in seconds.
     */
    void update(float deltaTime) override {}

    /**
     * @brief Called to render the component.
     * @param window Shared pointer to the rendering window.
     */
    void render(const EngineUtilities::TSharedPointer<Window>& window) override {}

    /**
     * @brief Called when the component is destroyed for cleanup.
     */
    void destroy() {}

    /**
     * @brief Moves the entity toward a target position at a given speed.
     * @param targetPosition Target destination.
     * @param speed Movement speed.
     * @param deltaTime Time step.
     * @param range Minimum distance to start moving.
     */
    void seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range) {
        sf::Vector2f direction = targetPosition - m_position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > range) {
            direction /= length;  // Normaliza el vector
            m_position += direction * speed * deltaTime;
        }
    }

    // Setters
    void setPosition(const sf::Vector2f& _position) { m_position = _position; }
    void setRotation(const sf::Vector2f& _rotation) { m_rotation = _rotation; }
    void setScale(const sf::Vector2f& _scale) { m_scale = _scale; }

    // Getters
    sf::Vector2f& getPosition() { return m_position; }
    sf::Vector2f& getRotation() { return m_rotation; }
    sf::Vector2f& getScale() { return m_scale; }

private:
    sf::Vector2f m_position; //< Position vector representing the entity's position in 2D space.
    sf::Vector2f m_rotation; //< Rotation vector representing the entity's rotation in degrees.
    sf::Vector2f m_scale;    //< Scale vector representing the entity's scale factors.
};
