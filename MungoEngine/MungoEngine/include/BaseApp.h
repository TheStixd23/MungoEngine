// Estilo de codificación:
// - camelCase para variables y métodos
// - PascalCase para clases
// - Tabulación: 2 espacios
// - Líneas de 80 a 90 caracteres máximo
// - Prefijo g_ para variables globales
// - Las clases y estructuras se definen con la llave de apertura en la misma línea
// - Los métodos dentro de clases se declaran con salto de línea entre el tipo y el nombre
// - La apertura del cuerpo del método se realiza en una nueva línea

#pragma once
#include "Prerequisites.h"
#include "Window.h"
class BaseApp
{
public:
	BaseApp() = default;
	~BaseApp();

	//execution of the app in main
	int
		run();

	//initialization function
	bool
		init();

	//per-frame update function
	void
		update();

	//rendering function
	void
		render();

	void
		Destroy();

private:
	Window* m_window;
	sf::CircleShape* m_circle;
};