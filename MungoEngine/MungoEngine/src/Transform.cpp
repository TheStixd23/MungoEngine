/**
 * @file Transform.cpp
 * @brief Implementaci�n del componente Transform, encargado de manejar la posici�n, rotaci�n y escala de una entidad.
 * @author Hannin Abarca
 */

#include "Transform.h"
#include <BaseApp.h>

 /**
  * @brief M�todo llamado al iniciar el componente. (Actualmente vac�o)
  */
void
Transform::start() {
}

/**
 * @brief Actualiza el estado del componente. (Actualmente sin l�gica)
 * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
 */
void
Transform::update(float deltaTime) {

}

/**
 * @brief M�todo de renderizado del componente Transform. No realiza acciones ya que no tiene representaci�n visual.
 * @param window Puntero compartido a la ventana.
 */
void
Transform::render(const EngineUtilities::TSharedPointer<Window>& window) {
}

/**
 * @brief Libera recursos del componente. (Actualmente sin l�gica)
 */
void
Transform::destroy() {
}
