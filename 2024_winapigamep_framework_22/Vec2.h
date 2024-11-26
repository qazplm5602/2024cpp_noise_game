#pragma once
#include <assert.h>
#include <cmath>

struct Vec2
{
public:
    Vec2() = default;
    Vec2(float _x, float _y) : x(_x), y(_y) {}
    Vec2(POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}
    Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
    Vec2(const Vec2& _other) : x(_other.x), y(_other.y) {}

public:
    // Vec2 + Vec2
    Vec2 operator + (const Vec2& _vOther) const
    {
        return Vec2(x + _vOther.x, y + _vOther.y);
    }

    // Vec2 - Vec2
    Vec2 operator - (const Vec2& _vOther) const
    {
        return Vec2(x - _vOther.x, y - _vOther.y);
    }

    // Vec2 * Vec2
    Vec2 operator * (const Vec2& _vOther) const
    {
        return Vec2(x * _vOther.x, y * _vOther.y);
    }

    // Vec2 / Vec2
    Vec2 operator / (const Vec2& _vOther) const
    {
        assert(!(0.f == _vOther.x || 0.f == _vOther.y));
        return Vec2(x / _vOther.x, y / _vOther.y);
    }

    // Vec2 * float
    Vec2 operator * (float _val) const
    {
        return Vec2(x * _val, y * _val);
    }

    // Vec2 / float
    Vec2 operator / (float _val) const
    {
        assert(_val != 0.f);
        return Vec2(x / _val, y / _val);
    }

    // Vec2 * int
    Vec2 operator * (int _val) const
    {
        return Vec2(x * static_cast<float>(_val), y * static_cast<float>(_val));
    }

    // Vec2 / int
    Vec2 operator / (int _val) const
    {
        assert(_val != 0);
        return Vec2(x / static_cast<float>(_val), y / static_cast<float>(_val));
    }

    // Compound assignment operators
    void operator+=(const Vec2& _other)
    {
        x += _other.x;
        y += _other.y;
    }

    void operator-=(const Vec2& _other)
    {
        x -= _other.x;
        y -= _other.y;
    }

    void operator*=(float _val)
    {
        x *= _val;
        y *= _val;
    }

    void operator/=(float _val)
    {
        assert(_val != 0.f);
        x /= _val;
        y /= _val;
    }

    void operator*=(int _val)
    {
        x *= static_cast<float>(_val);
        y *= static_cast<float>(_val);
    }

    void operator/=(int _val)
    {
        assert(_val != 0);
        x /= static_cast<float>(_val);
        y /= static_cast<float>(_val);
    }

    // Utility functions
    float LengthSquared() const
    {
        return x * x + y * y;
    }

    float Length() const
    {
        return std::sqrt(LengthSquared());
    }

    void Normalize()
    {
        float len = Length();
        if (len < FLT_EPSILON)
            return;
        x /= len;
        y /= len;
    }

    Vec2 GetNormalized()
    {
        float len = Length();
        if (len < FLT_EPSILON)
            return Vec2(x, y);
        return Vec2(x/len, y/len);
    }

    float Dot(const Vec2& _other) const
    {
        return x * _other.x + y * _other.y;
    }

    float Cross(const Vec2& _other) const
    {
        return x * _other.y - y * _other.x;
    }

public:
    float x = 0.f;
    float y = 0.f;
};
