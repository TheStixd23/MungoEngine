#pragma once
/**
 * @file Component.h
 * @brief Clase base abstracta para todos los componentes del motor, con ciclo de vida estándar y tipo identificador.
 *
 * Un componente encapsula datos y/o comportamiento que puede ser añadido a una entidad o actor.
 * Define una interfaz común para inicialización, actualización, renderizado y destrucción,
 * así como un tipo enumerado para identificar su función en el sistema.
 *
 * @author Hannin Abarca
 */

#include "../Prerequisites.h"

class Window;

/**
 * @enum ComponentType
 * @brief Identificadores de los tipos de componentes reconocidos por el motor.
 */
enum ComponentType {
	NONE = 0, /**< Tipo no definido. */
	TRANSFORM = 1, /**< Componente de transformación (posición, rotación, escala). */
	SPRITE = 2, /**< Componente para renderizar sprites. */
	RENDERER = 3, /**< Componente genérico de renderizado. */
	PHYSICS = 4, /**< Componente de física (colisiones, fuerzas). */
	AUDIOSOURCE = 5, /**< Componente de reproducción de audio. */
	SHAPE = 6, /**< Componente para renderizar formas geométricas. */
	TEXTURE = 7  /**< Componente de textura. */
};

/**
 * @class Component
 * @brief Clase base abstracta para todos los componentes.
 *
 * Define un contrato de ciclo de vida:
 * - @ref start() se invoca al inicializar el componente.
 * - @ref update() se ejecuta cada frame para actualizar su estado.
 * - @ref render() dibuja el componente en pantalla.
 * - @ref destroy() libera recursos antes de su eliminación.
 *
 * Cada componente se identifica con un @ref ComponentType.
 */
class Component {
public:
	/** @brief Constructor por defecto: tipo NONE. */
	Component() = default;

	/**
	 * @brief Constructor con tipo específico.
	 * @param type Tipo de componente según @ref ComponentType.
	 */
	Component(const ComponentType type) : m_type(type) {}

	/** @brief Destructor virtual por defecto. */
	virtual ~Component() = default;

	/** @brief Inicializa el componente. */
	virtual void start() = 0;

	/**
	 * @brief Actualiza el componente.
	 * @param deltaTime Tiempo en segundos desde el último frame.
	 */
	virtual void update(float deltaTime) = 0;

	/**
	 * @brief Renderiza el componente.
	 * @param window Ventana o surface de destino.
	 */
	virtual void render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

	/** @brief Libera recursos y referencias asociadas al componente. */
	virtual void destroy() = 0;

	/**
	 * @brief Obtiene el tipo de componente.
	 * @return Valor de @ref ComponentType.
	 */
	ComponentType getType() const { return m_type; }

protected:
	/** @brief Tipo del componente. */
	ComponentType m_type = ComponentType::NONE;
};
