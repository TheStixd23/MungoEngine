/**
 * @file CVector2.h
 * @brief Define la estructura de vector 2D con operaciones b�sicas de �lgebra vectorial para motores gr�ficos y simulaciones.
 * @author Hannin Abarca
 */

#pragma once
#include "../Prerequisites.h"
#include <iostream>

 /**
  * @class CVector2
  * @brief Representa un vector bidimensional con operaciones matem�ticas comunes.
  */
class CVector2 {
public:
    float x, y; ///< Componentes X e Y del vector.

    /**
     * @brief Constructor por defecto, inicializa a (0, 0).
     */
    CVector2() { x = 0;  y = 0; }

    /**
     * @brief Constructor con componentes personalizadas.
     * @param X Componente X.
     * @param Y Componente Y.
     */
    CVector2(float X, float Y) { x = X;  y = Y; }

    /// @name Operadores aritm�ticos
    /// @{

    CVector2 operator+(const CVector2& o) const;
    CVector2 operator-(const CVector2& o) const;
    CVector2 operator*(float s) const;
    CVector2 operator/(float s) const;
    CVector2 operator-() const;

    CVector2& operator+=(const CVector2& o);
    CVector2& operator-=(const CVector2& o);
    CVector2& operator*=(float s);
    CVector2& operator/=(float s);

    /// @}

    /// @name Operadores de comparaci�n
    /// @{

    bool operator==(const CVector2& o) const;
    bool operator!=(const CVector2& o) const;

    /// @}

    /// @name Magnitudes y normalizaci�n
    /// @{

    float lengthSq() const;       ///< Retorna la magnitud al cuadrado del vector.
    float length() const;         ///< Retorna la magnitud (longitud) del vector.
    CVector2 normalized() const;  ///< Retorna una copia normalizada del vector.
    void normalize();             ///< Normaliza el vector actual in-place.

    /// @}

    /// @name Producto escalar y cruzado
    /// @{

    float dot(const CVector2& o) const;    ///< Producto punto.
    float cross(const CVector2& o) const;  ///< Producto cruzado (en 2D, da un escalar).

    /// @}

    /// @name Utilidades est�ticas
    /// @{

    static CVector2 zero();                          ///< Vector (0, 0).
    static CVector2 one();                           ///< Vector (1, 1).
    static float distance(const CVector2& a, const CVector2& b); ///< Distancia entre dos vectores.
    static CVector2 lerp(const CVector2& a, const CVector2& b, float t); ///< Interpolaci�n lineal.

    /// @}
};

// === Implementaci�n de operadores en l�nea ===

/**
 * @brief Operador de inserci�n para imprimir el vector.
 * @param os Flujo de salida.
 * @param v Vector a imprimir.
 * @return Flujo modificado.
 */
inline std::ostream& operator<<(std::ostream& os, const CVector2& v)
{
    return os << "(" << v.x << ", " << v.y << ")";
}
