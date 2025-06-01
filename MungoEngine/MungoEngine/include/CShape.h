/**
 * @file CShape.h
 * @author Hannin Abarca
 * @brief Declaraci�n de la clase Cshape para la definici�n de figuras geom�tricas
 * renderizables con SFML. Contiene la interfaz p�blica y privada para crear,
 * modificar y manipular figuras como c�rculos, rect�ngulos, tri�ngulos y pol�gonos
 * @version 1.0
 * @date 2025-06-01
 */

#pragma once

#include "Prerequisites.h"

class Window;

/**
 * @class Cshape
 * @brief Componente que representa una figura geom�trica renderizable.
 * Permite crear, actualizar y renderizar figuras SFML como c�rculos, rect�ngulos,
 * etc. Tambi�n da m�todos para manipular sus propiedades como posici�n,
 * rotaci�n, escala y color
 */
class Cshape {
public:
    /**
     * @brief Constructor por defecto
     */
    Cshape() = default;

    /**
     * @brief Constructor con tipo de figura
     *
     * @param shapeType Tipo de figura que se desea crear
     */
    Cshape(ShapeType shapeType) : m_shape(nullptr), m_shapeType(ShapeType::EMPTY)
    {
    }

    /**
     * @brief Destructor. Libera la memoria asignada a la figura
     */
    ~Cshape();

    /**
     * @brief Crea una nueva figura del tipo especificado
     *
     * @param shapeType Tipo de figura a crear
     * @return Puntero a la figura creada
     */
    sf::Shape*
        createShape(ShapeType shapeType);

    /**
     * @brief Actualiza la figura con base en el tiempo transcurrido
     *
     * @param deltaTime Tiempo desde el �ltimo fotograma
     */
    void
        update(float deltaTime);

    /**
     * @brief Renderiza la figura en la ventana activa
     */
    void
        render();

    /**
     * @brief Establece la posici�n de la figura
     *
     * @param x Coordenada X
     * @param y Coordenada Y
     */
    void
        setPosition(float x, float y);

    /**
     * @brief Establece la posici�n de la figura
     *
     * @param position Vector de posici�n
     */
    void
        setPosition(const sf::Vector2f& position);

    /**
     * @brief Establece el color de relleno de la figura
     *
     * @param color Color a aplicar
     */
    void
        setFillColor(const sf::Color& color);

    /**
     * @brief Establece el �ngulo de rotaci�n de la figura
     *
     * @param angle �ngulo en grados
     */
    void
        setRotation(float angle);

    /**
     * @brief Establece la escala de la figura
     *
     * @param scl Vector de escala
     */
    void
        setScale(const sf::Vector2f& scl);

    /**
     * @brief Obtiene el puntero a la figura
     *
     * @return Puntero a la figura SFML
     */
    sf::Shape*
        getShape()
    {
        return m_shape;
    }

private:
    /**
     * @brief Puntero a la figura actual (c�rculo, rect�ngulo, etc)
     */
    sf::Shape* m_shape;

    /**
     * @brief Tipo de figura actual
     */
    ShapeType m_shapeType;

    /**
     * @brief L�nea de v�rtices para representaci�n auxiliar (si se usa)
     */
    sf::VertexArray m_line;
};
