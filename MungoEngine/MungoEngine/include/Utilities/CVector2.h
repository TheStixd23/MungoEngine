/**
 * @file CVector2.h
 * @brief Clase para representar y operar con vectores 2D.
 *
 * Esta clase implementa operaciones aritméticas, utilitarias y funciones
 * comunes en álgebra vectorial en dos dimensiones. Proporciona sobrecarga
 * de operadores para facilitar su uso como tipo matemático.
 */

#pragma once
#include "../Prerequisites.h"
#include <iostream>
#include <cmath>

 /**
  * @class CVector2
  * @brief Representa un vector bidimensional con componentes en punto flotante.
  */
class CVector2 {
public:
    float x; ///< Componente X del vector.
    float y; ///< Componente Y del vector.

    /**
     * @brief Constructor por defecto. Inicializa a (0, 0).
     */
    CVector2() : x(0), y(0) {}

    /**
     * @brief Constructor con valores iniciales.
     * @param X Valor para la componente X.
     * @param Y Valor para la componente Y.
     */
    CVector2(float X, float Y) : x(X), y(Y) {}

    /** @name Operadores aritméticos binarios */
    ///@{
    CVector2 operator+(const CVector2& o) const { return CVector2(x + o.x, y + o.y); }
    CVector2 operator-(const CVector2& o) const { return CVector2(x - o.x, y - o.y); }
    CVector2 operator*(float s) const { return CVector2(x * s, y * s); }
    CVector2 operator/(float s) const { return CVector2(x / s, y / s); }
    ///@}

    /**
     * @brief Operador unario de negación.
     * @return Un nuevo vector con ambas componentes negadas.
     */
    CVector2 operator-() const { return CVector2(-x, -y); }

    /** @name Operadores de asignación compuesta */
    ///@{
    CVector2& operator+=(const CVector2& o) { x += o.x; y += o.y; return *this; }
    CVector2& operator-=(const CVector2& o) { x -= o.x; y -= o.y; return *this; }
    CVector2& operator*=(float s) { x *= s; y *= s; return *this; }
    CVector2& operator/=(float s) { x /= s; y /= s; return *this; }
    ///@}

    /** @name Comparación */
    ///@{
    bool operator==(const CVector2& o) const { return x == o.x && y == o.y; }
    bool operator!=(const CVector2& o) const { return !(*this == o); }
    ///@}

    /**
     * @brief Calcula la longitud al cuadrado del vector.
     * @return Magnitud al cuadrado.
     */
    float lengthSq() const { return x * x + y * y; }

    /**
     * @brief Calcula la longitud (magnitud) del vector.
     * @return Magnitud como flotante.
     */
    float length() const { return std::sqrt(lengthSq()); }

    /**
     * @brief Devuelve una versión normalizada del vector.
     * @return Vector normalizado o (0,0) si su longitud es cero.
     */
    CVector2 normalized() const {
        float len = length();
        return len != 0 ? CVector2(x / len, y / len) : CVector2(0, 0);
    }

    /**
     * @brief Normaliza el vector en el lugar.
     */
    void normalize() {
        float len = length();
        if (len != 0) {
            x /= len;
            y /= len;
        }
    }

    /**
     * @brief Calcula el producto punto entre dos vectores.
     * @param o Otro vector.
     * @return Producto escalar.
     */
    float dot(const CVector2& o) const { return x * o.x + y * o.y; }

    /**
     * @brief Calcula el producto cruzado (en 2D es un escalar).
     * @param o Otro vector.
     * @return Valor escalar del producto cruzado.
     */
    float cross(const CVector2& o) const { return x * o.y - y * o.x; }

    /** @name Constructores estáticos */
    ///@{
    static CVector2 zero() { return CVector2(0, 0); }
    static CVector2 one() { return CVector2(1, 1); }
    ///@}

    /**
     * @brief Calcula la distancia entre dos vectores.
     * @param a Primer vector.
     * @param b Segundo vector.
     * @return Distancia como flotante.
     */
    static float distance(const CVector2& a, const CVector2& b) {
        return (a - b).length();
    }

    /**
     * @brief Interpolación lineal entre dos vectores.
     * @param a Vector inicial.
     * @param b Vector final.
     * @param t Factor de interpolación [0,1].
     * @return Vector interpolado.
     */
    static CVector2 lerp(const CVector2& a, const CVector2& b, float t) {
        return a + (b - a) * t;
    }
};

/**
 * @brief Operador de salida para imprimir vectores en un flujo de salida.
 * @param os Flujo de salida.
 * @param v Vector a imprimir.
 * @return Referencia al flujo modificado.
 */
inline std::ostream& operator<<(std::ostream& os, const CVector2& v) {
    return os << "(" << v.x << ", " << v.y << ")";
}
