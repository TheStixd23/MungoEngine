// Estilo de codificaci�n:
// - camelCase para variables y m�todos
// - PascalCase para clases
// - Tabulaci�n: 2 espacios
// - L�neas de 80 a 90 caracteres m�ximo
// - Prefijo g_ para variables globales
// - Las clases y estructuras se definen con la llave de apertura en la misma l�nea
// - Los m�todos dentro de clases se declaran con salto de l�nea entre el tipo y el nombre
// - La apertura del cuerpo del m�todo se realiza en una nueva l�nea

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