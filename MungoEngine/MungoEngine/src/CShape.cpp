/**
 * @file CShape.cpp
 * @author Hannin Abarca
 * @brief Implementación de la clase Cshape para la creación y manejo de figuras
 *        geométricas (círculo, rectángulo, triángulo, polígono) utilizando SFML.
 * @version 1.0
 * @date 2025-06-01
 */

#include "CShape.h"
#include "Window.h"

/**
 * @brief Destructor de Cshape. Libera memoria de la figura si es necesario
 */
Cshape::~Cshape()
{
}

/**
 * @brief Crea una figura del tipo especificado
 *
 * @param shapeType Tipo de figura (círculo, rectángulo, triángulo, etc)
 * @return Puntero a la figura creada (derivada de sf::Shape)
 */
sf::Shape*
Cshape::createShape(ShapeType shapeType)
{
    switch (shapeType)
    {
    case ShapeType::CIRCLE:
    {
        sf::CircleShape* circle = new sf::CircleShape(10.0f);
        circle->setFillColor(sf::Color::Green);
        m_shape = circle;
        return circle;
    }
    case ShapeType::RECTANGLE:
    {
        sf::RectangleShape* rectangle =
            new sf::RectangleShape(sf::Vector2f(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::Red);
        m_shape = rectangle;
        return rectangle;
    }
    case ShapeType::TRIANGLE:
    {
        sf::ConvexShape* triangle = new sf::ConvexShape(3);
        triangle->setPointCount(3);
        triangle->setPoint(0, sf::Vector2f(0.0f, 0.0f));
        triangle->setPoint(1, sf::Vector2f(50.0f, 100.0f));
        triangle->setPoint(2, sf::Vector2f(100.0f, 0.0f));
        triangle->setFillColor(sf::Color::Blue);
        m_shape = triangle;
        return triangle;
    }
    case ShapeType::POLYGON:
    {
        sf::ConvexShape* polygon = new sf::ConvexShape(5);
        polygon->setPoint(0, sf::Vector2f(0.0f, 0.0f));
        polygon->setPoint(1, sf::Vector2f(50.0f, 100.0f));
        polygon->setPoint(2, sf::Vector2f(100.0f, 50.0f));
        polygon->setPoint(3, sf::Vector2f(150.0f, 100.0f));
        polygon->setPoint(4, sf::Vector2f(200.0f, 50.0f));
        polygon->setFillColor(sf::Color::Yellow);
        m_shape = polygon;
        return polygon;
    }
    default:
        break;
    }

    return nullptr;
}

/**
 * @brief Actualiza la figura por fotograma
 *
 * @param deltaTime Tiempo transcurrido desde el último fotograma
 */
void
Cshape::update(float deltaTime)
{
}

/**
 * @brief Establece la posición de la figura
 *
 * @param x Coordenada X.
 * @param y Coordenada Y.
 */
void
Cshape::setPosition(float x, float y)
{
    if (m_shape)
    {
        m_shape->setPosition(x, y);
    }
    else
    {
        ERROR("Cshape", "setPosition", "Shape is null");
    }
}

/**
 * @brief Establece la posición de la figura (vector)
 *
 * @param position Vector de posición
 */
void
Cshape::setPosition(const sf::Vector2f& position)
{
    if (m_shape)
    {
        m_shape->setPosition(position);
    }
    else
    {
        ERROR("Cshape", "setPosition", "Shape is null");
    }
}

/**
 * @brief Cambia el color de relleno de la figura
 *
 * @param color Color SFML a aplicar
 */
void
Cshape::setFillColor(const sf::Color& color)
{
    if (m_shape)
    {
        m_shape->setFillColor(color);
    }
    else
    {
        ERROR("Cshape", "setFillColor", "Shape is null");
    }
}

/**
 * @brief Establece el ángulo de rotación de la figura
 *
 * @param angle Ángulo en grados
 */
void
Cshape::setRotation(float angle)
{
    if (m_shape)
    {
        m_shape->setRotation(angle);
    }
    else
    {
        ERROR("Cshape", "setRotation", "Shape is null");
    }
}

/**
 * @brief Cambia la escala de la figura
 *
 * @param scl Vector de escala (x, y)
 */
void
Cshape::setScale(const sf::Vector2f& scl)
{
    if (m_shape)
    {
        m_shape->setScale(scl);
    }
    else
    {
        ERROR("Cshape", "setScale", "Shape is null");
    }
}
