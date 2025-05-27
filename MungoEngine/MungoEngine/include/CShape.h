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

class Window;

class Cshape
{
public:
	Cshape() = default;

	Cshape(ShapeType shapeType) : m_shape(nullptr), m_shapeType(ShapeType::EMPTY)
	{

	}

	~Cshape();

	sf::Shape*
		createShape(ShapeType shapeType);

	void
		update(float deltaTime);

	void
		render();

	void
		setPosition(float x, float y);

	void
		setPosition(const sf::Vector2f& position);

	void
		setFillColor(const sf::Color& color);

	void
		setRotation(float angle);

	void
		setScale(const sf::Vector2f& scl);

	sf::Shape*
		getShape()
	{
		return m_shape;
	}

private:
	sf::Shape* m_shape;
	ShapeType m_shapeType;
	sf::VertexArray m_line;
};
#pragma once
