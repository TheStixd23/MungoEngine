/**
 * @file CShape.h
 * @author Hannin Abarca
 * @brief Declaración de la clase Cshape para la definición de figuras geométricas
 * renderizables con SFML. Contiene la interfaz pública y privada para crear,
 * modificar y manipular figuras como círculos, rectángulos, triángulos y polígonos
 * @version 1.0
 * @date 2025-06-01
 */

#pragma once

#include "Prerequisites.h"

class Window;

/**
 * @class Cshape
 * @brief Componente que representa una figura geométrica renderizable.
 * Permite crear, actualizar y renderizar figuras SFML como círculos, rectángulos,
 * etc. También da métodos para manipular sus propiedades como posición,
 * rotación, escala y color
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
     * @param deltaTime Tiempo desde el último fotograma
     */
    void
        update(float deltaTime);

    /**
     * @brief Renderiza la figura en la ventana activa
     */
    void
        render();

    /**
     * @brief Establece la posición de la figura
     *
     * @param x Coordenada X
     * @param y Coordenada Y
     */
    void
        setPosition(float x, float y);

    /**
     * @brief Establece la posición de la figura
     *
     * @param position Vector de posición
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
     * @brief Establece el ángulo de rotación de la figura
     *
     * @param angle Ángulo en grados
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
     * @brief Puntero a la figura actual (círculo, rectángulo, etc)
     */
    sf::Shape* m_shape;

    /**
     * @brief Tipo de figura actual
     */
    ShapeType m_shapeType;

    /**
     * @brief Línea de vértices para representación auxiliar (si se usa)
     */
    sf::VertexArray m_line;
};
