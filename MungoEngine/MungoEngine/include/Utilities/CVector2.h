#pragma once
#include "../Prerequisites.h"
#include <iostream>

class Vector2 {
public:
    float x, y;

    Vector2() { x = 0;  y = 0; }
    Vector2(float X, float Y) { x = X;  y = Y; }

    Vector2 operator+(const Vector2& o) const
    {
        return Vector2(x + o.x, y + o.y);
    }
    Vector2 operator-(const Vector2& o) const
    {
        return Vector2(x - o.x, y - o.y);
    }
    Vector2 operator*(float s) const
    {
        return Vector2(x * s, y * s);
    }
    Vector2 operator/(float s) const
    {
        return Vector2(x / s, y / s);
    }
    Vector2 operator-() const
    {
        return Vector2(-x, -y);
    }

    Vector2& operator+=(const Vector2& o)
    {
        x += o.x; y += o.y;
        return *this;
    }
    Vector2& operator-=(const Vector2& o)
    {
        x -= o.x; y -= o.y;
        return *this;
    }
    Vector2& operator*=(float s)
    {
        x *= s; y *= s;
        return *this;
    }
    Vector2& operator/=(float s)
    {
        x /= s; y /= s;
        return *this;
    }

    bool operator==(const Vector2& o) const
    {
        return x == o.x && y == o.y;
    }
    bool operator!=(const Vector2& o) const
    {
        return !(*this == o);
    }

    float lengthSq() const
    {
        return x * x + y * y;
    }
    float length() const
    {
        return std::sqrt(x * x + y * y);
    }

    float dot(const Vector2& o) const
    {
        return x * o.x + y * o.y;
    }
    float cross(const Vector2& o) const
    {
        return x * o.y - y * o.x;
    }

    Vector2 normalized() const
    {
        float L = length();
        return (L > 0) ? Vector2(x / L, y / L) : Vector2();
    }
    void normalize()
    {
        float L = length();
        if (L > 0) { x /= L; y /= L; }
    }

    static Vector2 zero()
    {
        return Vector2(0, 0);
    }
    static Vector2 one()
    {
        return Vector2(1, 1);
    }
    static float distance(const Vector2& a, const Vector2& b)
    {
        return (b - a).length();
    }
    static Vector2 lerp(const Vector2& a, const Vector2& b, float t)
    {
        return Vector2(
            a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t
        );
    }
};

inline std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
    return os << "(" << v.x << ", " << v.y << ")";
}
