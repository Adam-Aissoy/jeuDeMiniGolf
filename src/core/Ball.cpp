#include "Ball.h"

Ball::Ball()
{
    Velocity.setX(0);
    Velocity.setY(0);
    Dir.setX(1);
    Dir.setY(1);
    Win = true;
}

float Ball::getVelocityX() const { return Velocity.getX(); }
float Ball::getVelocityY() const { return Velocity.getY(); }

float Ball::getPositionX() const { return b_pos.getX(); }
float Ball::getPositionY() const { return b_pos.getY(); }

void Ball::setVelocityX(float X) { Velocity.setX(X); }
void Ball::setVelocityY(float Y) { Velocity.setY(Y); }

void Ball::setPositionX(float X) { b_pos.setX(X); }
void Ball::setPositionY(float Y) { b_pos.setY(Y); }

void Ball::setDirX(float X) { Dir.setX(X); }
void Ball::setDirY(float Y) { Dir.setY(Y); }

bool Ball::canMove() const { return Move; }

bool Ball::isWin() const { return Win; }
void Ball::setWin(bool W) { Win = W; }

float Ball::getScale() const { return scale; }
void Ball::setScale(float S) { scale = S; }

float Ball::getVelocity1D() const
{
    return sqrt(pow(Velocity.getX(), 2) + pow(Velocity.getY(), 2));
}

void Ball::wallscollision(vector<Wall> &Walls, double deltaTime, Vec2f wsizes, int bsize)
{
    for (Wall &w : Walls) // Walls collision
    {
        float newX = getPositionX() + Dir.getX() * getVelocityX() * deltaTime; // We take the next frame of the Ball for X
        float newY = getPositionY() + Dir.getY() * getVelocityY() * deltaTime; // And Y

        bool CollisionY = (getPositionY() > w.getY() * wsizes.getY() && getPositionY() < (w.getY() + 1) * wsizes.getY());        // Frame 1 of the ball aligned with a wall on the Y axis
        bool CollisionX = (getPositionX() > w.getX() * wsizes.getX() && getPositionX() < (w.getX() + 1) * wsizes.getX());        // Frame 1 of the ball aligned with a wall on the X axis
        bool NewCollisionX = (newX + bsize / 2 > w.getX() * wsizes.getX() && newX - bsize / 2 < (w.getX() + 1) * wsizes.getX()); // Frame 2 of the ball aligned with a wall on the X axis
        bool NewCollisionY = (newY + bsize / 2 > w.getY() * wsizes.getY() && newY - bsize / 2 < (w.getY() + 1) * wsizes.getY()); // Frame 2 of the ball aligned with a wall on the Y axis

        if (CollisionY && NewCollisionX) // We check if the ball is inside the square of the wall with the next frame of X
        {
            if (newX < w.getX() * wsizes.getX()) // We do one more check to have the direction of the bounce and we update the ball direction
            {
                setDirX(-1);
            }
            else
            {
                setDirX(1);
            }
        }

        if (CollisionX && NewCollisionY) // We check if the ball is inside the square of the wall with the next frame of Y
        {
            if (newY < w.getY() * wsizes.getY())
            {
                setDirY(-1);
            }
            else
            {
                setDirY(1);
            }
        }
    }
}

void Ball::sandscollision(vector<Sand> &Sands, Vec2f wsizes, int bsize)
{
    for (Sand &s : Sands)
    {
        bool CollisionY = (getPositionY() > s.getY() * wsizes.getY() && getPositionY() < (s.getY() + 1) * wsizes.getY()); // We check if the ball is aligned with a sand on the Y axis
        bool CollisionX = (getPositionX() > s.getX() * wsizes.getX() && getPositionX() < (s.getX() + 1) * wsizes.getX()); // Then we check for the X axis

        if (CollisionX && CollisionY) // If the ball is in a square of sand we slow the ball speed
        {
            setVelocityX(getVelocityX() * 0.985);
            setVelocityY(getVelocityY() * 0.985);
        }
    }
}

void Ball::holecollision(Vec2f Hole, double deltaTime, int bsize)
{
    // A bool to see if the ball is touching the center of the hole (we use a ballsize of 16 for sdl and 1 for txt)
    // + we check if the velocity 1d of the ball is not too fast
    if (getPositionX() >= Hole.getX() - bsize / 2 && getPositionX() <= Hole.getX() + bsize / 2 && getPositionY() >= Hole.getY() - bsize / 2 && getPositionY() <= Hole.getY() + bsize / 2 && getVelocity1D() <= 2 || scale < 1) // Hole collsion
    {
        // The ball is in the hole we stop the velocity and we make so we can't move the ball
        Move = false;
        setVelocityX(0);
        setVelocityY(0);

        // Next par is for the ball in the hole animation we start with a scale factor of 1
        // Each time we enter we lower the scale by 0.01 and we render the ball with the scale factor
        // We make the ball go to the middle
        // When the scale factor is < 0.3 we set the win on true
        if (scale > 0.3 )
        {
            if (getPositionX() > Hole.getX())
            {
                setPositionX(getPositionX() - (0.01 * deltaTime));
            }
            else
            {
                setPositionX(getPositionX() + (0.01 * deltaTime));
            }

            if (getPositionY() > Hole.getY())
            {
                setPositionY(getPositionY() - (0.01 * deltaTime));
            }
            else
            {
                setPositionY(getPositionY() + (0.01 * deltaTime));
            }

            scale -= 0.01;
        }
        else
        {
            setWin(true);
        }
    }
}

// Update :
//- Edges collision
// - Wall collision
// - Sand collision
// - Hole collision
// - Update ball position with velocity
// - Update velocity with friction

void Ball::update(vector<Wall> &Walls, vector<Sand> &Sands, int DimX, int DimY, Vec2f Hole, double deltaTime, Vec2f wsizes, int bsize)
{
    // Start of the function, we put Move to false (we will change it later if we are allowed to move the ball)
    Move = false;

    // The 4 edges collisions
    if (getPositionX() < wsizes.getX() + bsize / 2) // Bounce Top
    {
        setDirX(1);
    }
    else if (getPositionX() > (DimX - 1) * wsizes.getX() - bsize / 2) // Bounce Bot
    {
        setDirX(-1);
    }

    if (getPositionY() < wsizes.getY() + bsize / 2) // Bounce Left
    {
        setDirY(1);
    }
    else if (getPositionY() > (DimY - 1) * wsizes.getY() - bsize / 2) // Bounce Right
    {
        setDirY(-1);
    }

    // 3 level objects collisions
    wallscollision(Walls, deltaTime, wsizes, bsize);
    sandscollision(Sands, wsizes, bsize);
    holecollision(Hole, deltaTime, bsize);

    // Here we set the velocity to 0 if tiny and we put move to true because if the velocity is null we can move the ball
    if (getVelocityX() < 0.01 && getVelocityY() < 0.01)
    {
        setVelocityX(0);
        setVelocityY(0);
        Move = true;
    }

    // Here the 4 equation for movement
    // We update the X and Y position by adding the velocity (always positive) multiplied by the direction (1 or -1) and we multiply the whole by deltatime
    // to make the movement smoother
    setPositionX(getPositionX() + Dir.getX() * getVelocityX() * deltaTime);
    setPositionY(getPositionY() + Dir.getY() * getVelocityY() * deltaTime);

    // We just reduce the velocity by a friction factor (here 0.99)
    setVelocityX(getVelocityX() * 0.99);
    setVelocityY(getVelocityY() * 0.99);
}

void Ball::swing(float PX, float PY, int Dx, int Dy)
{
    // If the ball can move we update the velocity and the direction
    // So the power and the direction is calculated in sdl and in txt
    if (canMove())
    {
        setVelocityX(PX);
        setVelocityY(PY);
        setDirX(Dx);
        setDirY(Dy);
    }
}
