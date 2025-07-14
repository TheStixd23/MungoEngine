/**
 * @file Actor.cpp
 * @brief Implementaci�n de la clase Actor, que gestiona sus componentes y sincroniza su estado l�gico con su representaci�n gr�fica.
 * @author Hannin Abarca
 */

#include <ranges>
#include <ESC/Actor.h>
#include "Transform.h"

 /**
  * @brief Constructor del Actor. Inicializa su nombre y agrega componentes CShape y Transform por defecto.
  * @param actorName Nombre asignado al actor.
  */
Actor::Actor(const std::string& actorName) {
    m_name = actorName;

    EngineUtilities::TSharedPointer<CShape> shape = EngineUtilities::MakeShared<CShape>();
    addComponent(shape);

    EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);
}

/**
 * @brief Renderiza todos los componentes del actor.
 * @param window Puntero compartido a la ventana donde se dibujar�n los componentes.
 */
void Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {
    for (unsigned int i = 0; i < components.size(); i++) {
        auto component = components[i];
        if (component) {
            component->render(window);
        }
    }
}

/**
 * @brief M�todo vac�o llamado al inicio del ciclo de vida del actor.
 */
void Actor::start() {}

/**
 * @brief Actualiza la l�gica del actor sincronizando el componente gr�fico con su Transform.
 * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
 */
void Actor::update(float deltaTime) {
    auto transform = getComponent<Transform>();
    auto shape = getComponent<CShape>();

    if (transform && shape) {
        shape->setPosition(transform->getPosition());
        shape->setRotation(transform->getRotation().x);
        shape->setScale(transform->getScale());
    }
}

/**
 * @brief M�todo vac�o para destruir el actor y sus recursos.
 */
void Actor::destroy() {}
