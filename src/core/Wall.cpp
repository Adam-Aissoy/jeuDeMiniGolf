#include "Wall.h"

Wall::Wall()
{
}

Wall::Wall(float X, float Y)
{
    w_pos.setX(X);
    w_pos.setY(Y);
}

float Wall::getX() const { return w_pos.getX(); }
float Wall::getY() const { return w_pos.getY(); }

