/**
 * @file Entity.h
 * @brief Define la clase base abstracta Entity que representa un objeto en la escena con componentes. 
 * @author Hannin Abarca
 */

#pragma once
#include "../Prerequisites.h"
#include "Component.h"

/**
 * @brief Declaración adelantada de la clase Window.
 */
class
	Window;

/**
 * @class Entity
 * @brief Clase abstracta que representa una entidad del sistema.
 * 
 * Las entidades pueden tener múltiples componentes y deben implementar los métodos de ciclo de vida.
 */
class
	Entity {
public:

	/**
	 * @brief Destructor virtual.
	 */
	virtual
		~Entity() = default;

	/**
	 * @brief Método abstracto llamado al iniciar la entidad.
	 */
	virtual void
		start() = 0;

	/**
	 * @brief Método abstracto que actualiza la entidad cada frame.
	 * @param deltaTime Tiempo transcurrido desde el último frame.
	 */
	virtual void
		update(float deltaTime) = 0;

	/**
	 * @brief Método abstracto que renderiza la entidad.
	 * @param window Puntero a la ventana donde se dibuja la entidad.
	 */
	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

	/**
	 * @brief Método abstracto que destruye la entidad y libera sus recursos.
	 */
	virtual void
		destroy() = 0;

	/**
	 * @brief Agrega un componente a la entidad.
	 * 
	 * @tparam T Tipo de componente que hereda de Component.
	 * @param component Puntero compartido al componente que se va a agregar.
	 */
	template<typename T> void
		addComponent(EngineUtilities::TSharedPointer<T> component) {
		static_assert(std::is_base_of<Component, T>
			::value, "T must be derived from Component");
		components.push_back
		(component.template dynamic_pointer_cast<Component>());
	}

	/**
	 * @brief Obtiene el primer componente del tipo solicitado.
	 * 
	 * @tparam T Tipo del componente buscado.
	 * @return Puntero compartido al componente si se encuentra, o nulo si no existe.
	 */
	template<typename T>
	EngineUtilities::TSharedPointer<T>
		getComponent() {
		for (auto& component : components) {
			EngineUtilities::TSharedPointer<T> specificComponent
				= component.template dynamic_pointer_cast<T>();
			if (specificComponent) {
				return specificComponent;
			}
		}

		return EngineUtilities::TSharedPointer<T>();
	}

protected:
	/** @brief Indica si la entidad está activa. */
	bool isActive;

	/** @brief Identificador único de la entidad. */
	uint32_t id;

	/** @brief Lista de componentes asociados a la entidad. */
	std::vector<EngineUtilities::TSharedPointer<Component>> components;
};
