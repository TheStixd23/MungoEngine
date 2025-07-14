/**
 * @file Component.h
 * @brief Define la clase base abstracta Component y el enumerador ComponentType.
 * @author Hannin Abarca
 */

#pragma once
#include "../Prerequisites.h"

 /**
  * @brief Declaración adelantada de la clase Window.
  */
class
	Window;

/**
 * @enum ComponentType
 * @brief Enumera los tipos posibles de componentes que pueden existir dentro de una entidad.
 */
enum
	ComponentType {
	NONE = 0,       /**< Tipo indefinido o sin asignar. */
	TRANSFORM = 1,  /**< Componente de transformación espacial. */
	SPRITE = 2,     /**< Componente de sprite (imagen 2D). */
	RENDERER = 3,   /**< Componente encargado de la representación visual. */
	PHYSICS = 4,    /**< Componente que maneja la física. */
	AUDIOSOURCE = 5,/**< Componente de reproducción de audio. */
	SHAPE = 6,      /**< Componente de forma geométrica. */
	TEXTURE = 7     /**< Componente de textura. */
};

/**
 * @class Component
 * @brief Clase base abstracta para todos los componentes que pueden ser añadidos a una entidad.
 */
class
	Component {
public:

	/**
	 * @brief Constructor por defecto del componente.
	 */
	Component() = default;

	/**
	 * @brief Constructor que inicializa el tipo de componente.
	 * @param type Tipo del componente.
	 */
	Component(const ComponentType type) : m_type(type) {}

	/**
	 * @brief Destructor virtual.
	 */
	virtual
		~Component() = default;

	/**
	 * @brief Método abstracto llamado al iniciar el componente.
	 */
	virtual void
		start() = 0;

	/**
	 * @brief Método abstracto que actualiza el componente cada frame.
	 * @param deltaTime Tiempo transcurrido desde el último frame.
	 */
	virtual void
		update(float deltaTime) = 0;

	/**
	 * @brief Método abstracto para renderizar el componente.
	 * @param window Puntero a la ventana donde se debe dibujar.
	 */
	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

	/**
	 * @brief Método abstracto que libera los recursos del componente.
	 */
	virtual void
		destroy() = 0;

	/**
	 * @brief Obtiene el tipo del componente.
	 * @return El tipo del componente como ComponentType.
	 */
	ComponentType
		getType() const { return m_type; }

protected:
	/** @brief Tipo del componente. */
	ComponentType m_type;
};
