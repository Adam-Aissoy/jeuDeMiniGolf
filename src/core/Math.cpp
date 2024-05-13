#include "Math.h"

Vec2f::Vec2f()
{
    x = 0;
    y = 0;
}

Vec2f::Vec2f(float X, float Y)
{
    x = X;
    y = Y;
}

float Vec2f::getX() const { return x; }

float Vec2f::getY() const { return y; }

void Vec2f::setX(float X) { x = X; }

void Vec2f::setY(float Y) { y = Y; }

void Vec2f::print() const
{
    std::cout << "X : " << x << " | Y : " << y << std::endl;
}