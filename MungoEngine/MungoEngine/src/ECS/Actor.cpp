#include <ranges>
#include <ESC/Actor.h>
#include "Transform.h"

Actor::Actor(const std::string& actorName) {
    m_name = actorName;

    EngineUtilities::TSharedPointer<CShape> shape = EngineUtilities::MakeShared<CShape>();
    addComponent(shape);

    EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);
}

void Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {
    for (unsigned int i = 0; i < components.size(); i++) {
        auto component = components[i];
        if (component) {
            component->render(window);
        }
    }
}

void Actor::start() {}

void Actor::update(float deltaTime) {
    auto transform = getComponent<Transform>();
    auto shape = getComponent<CShape>();

    if (transform && shape) {
        shape->setPosition(transform->getPosition());
        shape->setRotation(transform->getRotation().x);
        shape->setScale(transform->getScale());
    }
}

void Actor::destroy() {}
