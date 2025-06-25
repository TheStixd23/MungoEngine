#include "ECS/Actor.h"
#include <ESC/Actor.h>

Actor::Actor(const std::string& actorName) {
    // Setup Actor Name
    m_name = actorName;

    // Setup Shape
    EngineUtilities::TSharedPointer<CShape> shape = EngineUtilities::MakeShared<CShape>();
    addComponent(shape);

    // Setup Transform (comentado, lo dejo así para que actives si quieres)
    // EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    // addComponent(transform);
}

void Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {
    // Implementar renderizado si es necesario
}

void Actor::start() {
    // Código para iniciar el actor
}

void Actor::update(float deltaTime) {
    // Código para actualizar el actor
}

void Actor::destroy() {
    // Código para limpiar o destruir el actor
}
