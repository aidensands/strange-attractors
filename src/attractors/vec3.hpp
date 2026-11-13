#pragma once

// This header contains all of the utils for the structure that contains our coordinates for particles
// Operator overloading is so we can do simple vector arithmetic

struct Vec3
{
    float x;
    float y;
    float z;

    Vec3 &operator+=(const Vec3 &other)
    {
        x += other.x;
        y += other.y;
        z +=other.z;

        return *this;
    }

    Vec3 &operator*=(const float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;

        return *this;
    }
   
    Vec3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vec3(float x, float y, float z)
        : x(x), y(y), z(z)
    {

    }
};

inline Vec3 operator+(Vec3 a, const Vec3 &b)
{
    return a += b;
}

inline Vec3 operator*(Vec3 v, float s){
    return v *= s;
}

inline Vec3 operator*(float s, Vec3 v)
{
    return v *= s;
}
