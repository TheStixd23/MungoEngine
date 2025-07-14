/**
 * @file BaseApp.h
 * @brief Define la clase BaseApp que actúa como punto de entrada para la aplicación principal.
 * @author Hannin Abarca
 */

#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include <ESC/Actor.h>

 /**
  * @class BaseApp
  * @brief Clase principal de la aplicación que controla el ciclo de vida completo.
  *
  * Se encarga de inicializar, ejecutar, actualizar, renderizar y destruir los recursos del motor.
  */
class
	BaseApp {
public:

	/**
	 * @brief Constructor por defecto.
	 */
	BaseApp() = default;

	/**
	 * @brief Destructor de la aplicación. Libera recursos usados.
	 */
	~BaseApp();

	/**
	 * @brief Ejecuta la aplicación.
	 * @return Código de salida de la aplicación (0 si fue exitoso).
	 */
	int
		run();

	/**
	 * @brief Inicializa todos los subsistemas necesarios.
	 * @return true si la inicialización fue exitosa, false en caso contrario.
	 */
	bool
		init();

	/**
	 * @brief Actualiza el estado lógico de la aplicación.
	 */
	void
		update();

	/**
	 * @brief Renderiza todos los elementos visibles de la aplicación.
	 */
	void
		render();

	/**
	 * @brief Libera todos los recursos utilizados.
	 */
	void
		destroy();

private:
	/** @brief Puntero compartido a la ventana principal. */
	EngineUtilities::TSharedPointer<Window>
		m_windowPtr;

	/** @brief Puntero compartido a una figura CShape usada en la escena. */
	EngineUtilities::TSharedPointer<CShape>
		m_shapePtr;

	/** @brief Puntero compartido al Actor que representa un círculo en la escena. */
	EngineUtilities::TSharedPointer<Actor>
		m_ACircle;
};
