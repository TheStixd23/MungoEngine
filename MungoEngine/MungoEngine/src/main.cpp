/**
 * @file main.cpp
 * @brief Punto de entrada de la aplicación. Inicializa y ejecuta BaseApp.
 */

#include "BaseApp.h"

 /**
  * @brief Función principal del programa.
  *
  * Crea una instancia de BaseApp y llama a su método run(),
  * que gestiona el ciclo principal de la aplicación/juego.
  *
  * @return int Código de salida (0 si termina correctamente).
  */
int main() {
    BaseApp app;
    return app.run();
}
