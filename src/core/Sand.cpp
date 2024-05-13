#include "Sand.h"
#include "Math.h"

Sand::Sand()
{
}

Sand::Sand(float X, float Y)
{
    s_pos.setX(X);
    s_pos.setY(Y);
}

float Sand::getX() const { return s_pos.getX(); }
float Sand::getY() const { return s_pos.getY(); }