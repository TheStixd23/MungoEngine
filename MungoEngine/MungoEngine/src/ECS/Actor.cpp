#include <BaseApp.h>
#include <ESC/Entity.h>
#include <ESC/Actor.h>
#include "ESC/Transform.h"

/**
 * @brief Constructor de Actor.
 *
 * Inicializa el actor con el nombre dado y agrega por defecto
 * un componente de tipo CShape y un componente Transform.
 *
 * @param actorName Nombre lógico del actor.
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
 * @param window Puntero compartido a la ventana donde se dibujará.
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
 * @brief Método de inicialización llamado al iniciar el actor.
 *
 * Actualmente vacío; puede ser sobrescrito para inicialización personalizada.
 */
void Actor::start() {}

/**
 * @brief Actualiza el estado del actor.
 *
 * Sincroniza la posición, rotación y escala del componente CShape
 * con los valores del componente Transform.
 *
 * @param deltaTime Tiempo transcurrido desde el último frame (en segundos).
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
 * @brief Lógica de destrucción del actor.
 *
 * Actualmente vacío; puede ser sobrescrito para liberar recursos.
 */
void Actor::destroy() {}

/**
 * @brief Asigna una textura al componente CShape del actor.
 *
 * Si el componente CShape existe y la textura no es nula,
 * se asigna la textura y se agrega como componente al actor.
 *
 * @param texture Puntero compartido a la textura.
 */
void Actor::setTexture(const EngineUtilities::TSharedPointer<Texture>& texture) {
	auto shape = getComponent<CShape>();
	if (shape && !texture.isNull()) {
		shape->setTexture(texture);
		addComponent(texture);
	}
}
