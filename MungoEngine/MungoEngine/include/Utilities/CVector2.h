#pragma once
#include "../Prerequisites.h"
#include <iostream>

class CVector2 {
public:
    float x, y;

    CVector2() { x = 0;  y = 0; }
    CVector2(float X, float Y) { x = X;  y = Y; }

    CVector2 operator+(const CVector2& o) const
    {
        return CVector2(x + o.x, y + o.y);
    }
    CVector2 operator-(const CVector2& o) const
    {
        return CVector2(x - o.x, y - o.y);
    }
    CVector2 operator*(float s) const
    {
        return CVector2(x * s, y * s);
    }
    CVector2 operator/(float s) const
    {
        return CVector2(x / s, y / s);
    }
    CVector2 operator-() const
    {
        return CVector2(-x, -y);
    }

    CVector2& operator+=(const CVector2& o)
    {
        x += o.x; y += o.y;
        return *this;
    }
    CVector2& operator-=(const CVector2& o)
    {
        x -= o.x; y -= o.y;
        return *this;
    }
    CVector2& operator*=(float s)
    {
        x *= s; y *= s;
        return *this;
    }
    CVector2& operator/=(float s)
    {
        x /= s; y /= s;
        return *this;
    }

    bool operator==(const CVector2& o) const
    {
        return x == o.x && y == o.y;
    }
    bool operator!=(const CVector2& o) const
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

    float dot(const CVector2& o) const
    {
        return x * o.x + y * o.y;
    }
    float cross(const CVector2& o) const
    {
        return x * o.y - y * o.x;
    }

    CVector2 normalized() const
    {
        float L = length();
        return (L > 0) ? CVector2(x / L, y / L) : CVector2();
    }
    void normalize()
    {
        float L = length();
        if (L > 0) { x /= L; y /= L; }
    }

    static CVector2 zero()
    {
        return CVector2(0, 0);
    }
    static CVector2 one()
    {
        return CVector2(1, 1);
    }
    static float distance(const CVector2& a, const CVector2& b)
    {
        return (b - a).length();
    }
    static CVector2 lerp(const CVector2& a, const CVector2& b, float t)
    {
        return CVector2(
            a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t
        );
    }
};

inline std::ostream& operator<<(std::ostream& os, const CVector2& v)
{
    return os << "(" << v.x << ", " << v.y << ")";
}
