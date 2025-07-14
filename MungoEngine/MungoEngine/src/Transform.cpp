/**
 * @file Transform.cpp
 * @brief Implementación del componente Transform, encargado de manejar la posición, rotación y escala de una entidad.
 * @author Hannin Abarca
 */

#include "Transform.h"
#include <BaseApp.h>

 /**
  * @brief Método llamado al iniciar el componente. (Actualmente vacío)
  */
void
Transform::start() {
}

/**
 * @brief Actualiza el estado del componente. (Actualmente sin lógica)
 * @param deltaTime Tiempo transcurrido desde el último frame.
 */
void
Transform::update(float deltaTime) {

}

/**
 * @brief Método de renderizado del componente Transform. No realiza acciones ya que no tiene representación visual.
 * @param window Puntero compartido a la ventana.
 */
void
Transform::render(const EngineUtilities::TSharedPointer<Window>& window) {
}

/**
 * @brief Libera recursos del componente. (Actualmente sin lógica)
 */
void
Transform::destroy() {
}
