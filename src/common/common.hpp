#pragma once
#include <iostream>
#include <memory>
#include <vector>

struct vec2
{
    float x;
    float y;

    // OPERATOR VEC <-> VEC
    vec2& operator +=(vec2 const& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    vec2 operator+(vec2 const& rhs){
        return vec2{this->x + rhs.x, this->y + rhs.y};
    }

    vec2& operator -=(vec2 const& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }

    vec2 operator-(vec2 const& rhs){
        return vec2{this->x - rhs.x, this->y - rhs.y};
    }

    vec2& operator *=(vec2 const& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }

    vec2 operator*(vec2 const& rhs){
        return vec2{this->x * rhs.x, this->y * rhs.y};
    }

    vec2& operator /=(vec2 const& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }

    vec2 operator/(vec2 const& rhs){
        return vec2{this->x / rhs.x, this->y / rhs.y};
    }

    // OPERATOR VEC <-> SCALAR
    vec2& operator *=(float const& rhs)
    {
        this->x *= rhs;
        this->y *= rhs;
        return *this;
    }

    friend vec2 operator *=(float const& f, vec2 const& other)
    {
        return vec2{f*other.x, f*other.y};
    }

    vec2 operator*(float const& rhs){
        return vec2{this->x*rhs, this->y*rhs};
    }

    friend vec2 operator*(float const& lhs, vec2 const& rhs){
        return vec2{lhs*rhs.x, lhs*rhs.y};
    }

    friend vec2& operator*(float& lhs, vec2 & rhs){
        lhs *= rhs;
        return rhs;
    }

    vec2 operator/(float const& rhs){
        return vec2{this->x/rhs,this->y/rhs};
    }

    vec2& operator /=(float const& rhs)
    {
        this->x /= rhs;
        this->y /= rhs;
        return *this;
    }

    vec2& operator -=(float const& other)
    {
        x -= other;
        y -= other;
        return *this;
    }

    friend vec2 operator-(vec2 lhs, float const& rhs){
        lhs -= rhs;
        return lhs;
    }


    vec2& operator +=(float const& other)
    {
        x -= other;
        y -= other;
        return *this;
    }

    friend vec2 operator+(vec2 lhs, float const& rhs){
        lhs -= rhs;
        return lhs;
    }


    bool operator <(float const& rhs)
    {
        return this->x<rhs && this->y < rhs;
    }
};

inline std::ostream& operator<<(std::ostream& os, const vec2& v)
{
    os << "{" << v.x << ", " << v.y << "}";
    return os;
}

struct physics_body
{
    vec2 pos;
    float radius;

    virtual void update(float) = 0;
    virtual void add_force(vec2) = 0;

    physics_body(float x, float y, float r) : pos(vec2{x, y}), radius(r){}

    virtual ~physics_body() = default;
};

struct physics_solver
{
    std::vector<std::shared_ptr<physics_body>> bodies;

    virtual void update(float) = 0;
    virtual void add_item(float x, float y, float radius = 10) = 0;
};
