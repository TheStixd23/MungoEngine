/**
 * @file BaseApp.h
 * @brief Define la clase BaseApp que act�a como punto de entrada para la aplicaci�n principal.
 * @author Hannin Abarca
 */

#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include <ESC/Actor.h>

 /**
  * @class BaseApp
  * @brief Clase principal de la aplicaci�n que controla el ciclo de vida completo.
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
	 * @brief Destructor de la aplicaci�n. Libera recursos usados.
	 */
	~BaseApp();

	/**
	 * @brief Ejecuta la aplicaci�n.
	 * @return C�digo de salida de la aplicaci�n (0 si fue exitoso).
	 */
	int
		run();

	/**
	 * @brief Inicializa todos los subsistemas necesarios.
	 * @return true si la inicializaci�n fue exitosa, false en caso contrario.
	 */
	bool
		init();

	/**
	 * @brief Actualiza el estado l�gico de la aplicaci�n.
	 */
	void
		update();

	/**
	 * @brief Renderiza todos los elementos visibles de la aplicaci�n.
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

	/** @brief Puntero compartido al Actor que representa un c�rculo en la escena. */
	EngineUtilities::TSharedPointer<Actor>
		m_ACircle;
};
