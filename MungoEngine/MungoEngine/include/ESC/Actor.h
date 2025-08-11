#pragma once
/**
 * @file Actor.h
 * @brief Interfaz base de actor del motor: entidad con ciclo de vida, renderizado y sistema de componentes.
 *
 * Un Actor es una Entity con nombre, capaz de iniciar, actualizar, renderizar y destruirse. Expone
 * acceso genérico a componentes mediante @ref getComponent<T>(), y utilidades para asociar texturas.
 * Sirve como clase base para objetos jugables y no jugables dentro de la escena.
 *
 * @author Hannin Abarca
 */

#include "../Prerequisites.h"
#include "Entity.h"
#include "Cshape.h"
#include "./Transform.h"

 /**
  * @class Actor
  * @brief Clase base para objetos del juego que poseen nombre, ciclo de vida y componentes.
  *
  * Provee el esqueleto de ejecución (start/update/render/destroy) y un método genérico para
  * recuperar componentes por tipo. Está pensada para heredar y extender su comportamiento.
  */
class Actor : Entity {
public:
	/** @brief Construye un Actor sin nombre explícito. */
	Actor() = default;

	/**
	 * @brief Construye un Actor con nombre.
	 * @param actorName Nombre lógico del actor (para depuración/inspector).
	 */
	Actor(const std::string& actorName);

	/** @brief Destructor virtual por defecto. */
	virtual ~Actor() = default;

	/**
	 * @brief Inicializa el actor y sus componentes. Se llama una vez al crearse/activarse.
	 * @note Útil para reservar recursos o cachear referencias a componentes.
	 */
	void start() override;

	/**
	 * @brief Actualiza la lógica del actor.
	 * @param deltaTime Tiempo transcurrido desde el último frame (segundos).
	 * @note Realiza aquí movimientos, física ligera o IA por frame.
	 */
	void update(float deltaTime) override;

	/**
	 * @brief Dibuja el actor en la ventana de render.
	 * @param window Ventana/target donde emitir draw calls.
	 * @note No realizar lógica pesada; solo operaciones de dibujo.
	 */
	void render(const EngineUtilities::TSharedPointer<Window>& window) override;

	/**
	 * @brief Libera recursos y desconecta referencias del actor.
	 * @note Se invoca al finalizar el ciclo de vida o al descargar la escena.
	 */
	void destroy() override;

	/**
	 * @brief Asigna una textura al actor (si su componente visual lo soporta).
	 * @param texture Textura compartida a vincular.
	 * @note Normalmente usada por componentes como @c CShape o equivalentes.
	 */
	void setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

	/**
	 * @brief Devuelve el nombre lógico del actor.
	 * @return Referencia constante al nombre.
	 */
	const std::string& getName() const { return m_name; }

	/**
	 * @brief Obtiene un componente por tipo, si existe adjunto al actor.
	 * @tparam T Tipo concreto del componente a buscar.
	 * @return Puntero compartido al componente encontrado; nulo si no existe.
	 * @warning La búsqueda realiza un @c dynamic_pointer_cast, por lo que depende del RTTI.
	 */
	template <typename T>
	EngineUtilities::TSharedPointer<T> getComponent();

private:
	/** @brief Nombre lógico del actor (para UI/inspector y logs). */
	std::string m_name = "Actor";
};

template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent() {
	for (auto& component : components) {
		EngineUtilities::TSharedPointer<T> specificComponent
			= component.template dynamic_pointer_cast<T>();
		if (specificComponent) {
			return specificComponent;
		}
	}
	return EngineUtilities::TSharedPointer<T>();
}
