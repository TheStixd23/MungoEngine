#include "./A_Racer.h"
#include <cmath>

A_Racer::A_Racer(const std::string& name)
    : Actor(name), place(0), speed(100.f),
    logicPosition(sf::Vector2f(0.f, 0.f)),
    logicTarget(sf::Vector2f(0.f, 0.f)),
    steeringEnabled(true),
    arriveRadius(10.f)
{
}

void A_Racer::update(float deltaTime) {
    if (steeringEnabled) {
        sf::Vector2f toTarget = logicTarget - logicPosition;
        float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

        if (distance > arriveRadius) {
            sf::Vector2f direction = toTarget / distance;
            logicPosition += direction * speed * deltaTime;
        }
    }

    auto transform = getComponent<Transform>();
    if (transform) {
        transform->setPosition(logicPosition);
    }

    Actor::update(deltaTime);
}

void A_Racer::setPlace(int newPlace) { place = newPlace; }
int A_Racer::getPlace() const { return place; }

void A_Racer::setPosition(const sf::Vector2f& pos) { logicPosition = pos; }
sf::Vector2f A_Racer::getPosition() const { return logicPosition; }

void A_Racer::setSpeed(float s) { speed = s; }
float A_Racer::getSpeed() const { return speed; }

void A_Racer::setTarget(const sf::Vector2f& waypoint) { logicTarget = waypoint; }
sf::Vector2f A_Racer::getTarget() const { return logicTarget; }

void A_Racer::enableSteering(bool enabled) { steeringEnabled = enabled; }
void A_Racer::setArriveRadius(float radius) { arriveRadius = radius; }
