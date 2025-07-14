/**
 * @file Actor.h
 * @brief Define la clase Actor que representa una entidad con componentes renderizables.
 * @author Hannin Abarca
 */

#pragma once
#include "../Prerequisites.h"
#include "Entity.h"
#include "Cshape.h"
#include "../Transform.h"

 /**
  * @class Actor
  * @brief Clase que representa una entidad activa dentro de la escena.
  *
  * Hereda de Entity y contiene componentes como transformaciones y formas visuales.
  */
class
	Actor : Entity {
public:

	/**
	 * @brief Constructor por defecto del Actor.
	 */
	Actor() = default;

	/**
	 * @brief Constructor que inicializa el Actor con un nombre.
	 * @param actorName Nombre del actor.
	 */
	Actor(const std::string& actorName);

	/**
	 * @brief Destructor virtual.
	 */
	virtual
		~Actor() = default;

	/**
	 * @brief Método llamado al inicio del ciclo de vida del Actor.
	 */
	void
		start() override;

	/**
	 * @brief Método de actualización que se ejecuta cada frame.
	 * @param deltaTime Tiempo transcurrido desde el último frame.
	 */
	void
		update(float deltaTime) override;

	/**
	 * @brief Dibuja al actor en la ventana.
	 * @param window Puntero compartido a la ventana donde se renderiza.
	 */
	void
		render(const EngineUtilities::TSharedPointer<Window>& window) override;

	/**
	 * @brief Elimina los recursos asociados al actor.
	 */
	void
		destroy() override;

	/**
	 * @brief Obtiene un componente del tipo especificado si existe.
	 *
	 * @tparam T Tipo del componente buscado.
	 * @return Puntero compartido al componente si se encuentra, o un puntero nulo.
	 */
	template <typename T>
	EngineUtilities::TSharedPointer<T>
		getComponent();

private:
	/** @brief Nombre del actor. */
	std::string m_name = "Actor";

};

/// Implementación del método template getComponent().
template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
	for (auto& component : components) {
		EngineUtilities::TSharedPointer<T> specificComponent
			= component.template dynamic_pointer_cast<T>();
		if (specificComponent) {
			return specificComponent;
		}
	}
	return EngineUtilities::TSharedPointer<T>();
}
