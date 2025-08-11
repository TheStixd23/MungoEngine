#pragma once
/**
 * @file Entity.h
 * @brief Interfaz base para cualquier objeto que contenga y gestione componentes en el motor.
 *
 * Define un ciclo de vida estándar (start, update, render, destroy) y utilidades genéricas
 * para añadir y obtener componentes. Sirve como clase base para elementos como @c Actor
 * y otros objetos de juego.
 *
 * @author Hannin Abarca
 */

#include "../Prerequisites.h"
#include "Component.h"

class Window;

/**
 * @class Entity
 * @brief Clase base abstracta para objetos que contienen componentes y se actualizan/renderizan.
 *
 * Una Entity agrupa uno o varios @ref Component que implementan distintas responsabilidades
 * (transformación, renderizado, física, etc.). Su ciclo de vida se refleja en:
 * - @ref start()  : inicialización al activarse.
 * - @ref update() : lógica por frame.
 * - @ref render() : dibujo en pantalla.
 * - @ref destroy(): liberación de recursos.
 *
 * Además, expone métodos plantilla para añadir y recuperar componentes por tipo.
 */
class Entity {
public:
	/** @brief Destructor virtual por defecto. */
	virtual ~Entity() = default;

	/** @brief Inicializa la entidad y sus componentes. */
	virtual void start() = 0;

	/**
	 * @brief Actualiza la entidad y sus componentes.
	 * @param deltaTime Tiempo transcurrido desde el último frame (segundos).
	 */
	virtual void update(float deltaTime) = 0;

	/**
	 * @brief Renderiza la entidad en la ventana destino.
	 * @param window Puntero compartido a la ventana de render.
	 */
	virtual void render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

	/** @brief Libera recursos y referencias de la entidad y sus componentes. */
	virtual void destroy() = 0;

	/**
	 * @brief Añade un componente a la entidad.
	 * @tparam T Tipo del componente (debe derivar de @ref Component).
	 * @param component Puntero compartido al componente.
	 * @note El componente se almacena internamente como @c Component.
	 */
	template<typename T>
	void addComponent(EngineUtilities::TSharedPointer<T> component) {
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		components.push_back(component.template dynamic_pointer_cast<Component>());
	}

	/**
	 * @brief Obtiene un componente por tipo.
	 * @tparam T Tipo concreto del componente.
	 * @return Puntero compartido al componente encontrado o nulo si no existe.
	 * @note Utiliza @c dynamic_pointer_cast para comprobar el tipo.
	 */
	template<typename T>
	EngineUtilities::TSharedPointer<T> getComponent() {
		for (auto& component : components) {
			EngineUtilities::TSharedPointer<T> specificComponent =
				component.template dynamic_pointer_cast<T>();
			if (specificComponent) {
				return specificComponent;
			}
		}
		return EngineUtilities::TSharedPointer<T>();
	}

protected:
	/** @brief Indica si la entidad está activa. */
	bool isActive = true;

	/** @brief Identificador único de la entidad. */
	uint32_t id = 0;

	/** @brief Lista de componentes asociados a la entidad. */
	std::vector<EngineUtilities::TSharedPointer<Component>> components;
};
