/**
@brief Module gérant une case de mur dans MasterGolf

Une case de mur dans MasterGolf est définie par sa position dans le tableau d'un niveau 
On multiplie donc plus tard ces 2 composantes par une autre pour obtenir le mur dans un terrain plus grand (SDL)

@file wall.h
*/

#ifndef _WALL
#define _WALL

#include "Math.h"

/**
@brief La classe Wall contient un Vec2f de position (Vec2f définie dans Math.h)
*/
class Wall
{
private:
    Vec2f w_pos;

public:

    /**
    @brief <B>Construit</B> un objet Wall.
    */
    Wall();

    /**
    @brief <B>Construit</B> un objet Wall.
    Le constructeur remplit la position par X et Y
    @param x : abs de la position du mur
    @param y : ordonnée de la position du mur
    */
    Wall(float X, float Y);

    /**
    @brief Renvoie la composante X du Vec2f de position du mur 
    */
    float getX() const;

    /**
    @brief Renvoie la composante Y du Vec2f de position du mur 
    */
    float getY() const;
};

#endif