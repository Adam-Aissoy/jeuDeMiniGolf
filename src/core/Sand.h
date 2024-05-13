/**
@brief Module gérant une case de Sable dans MasterGolf

Une case de sable dans MasterGolf est définie par sa position dans le tableau d'un niveau 
On multiplie donc plus tard ces 2 composantes par une autre pour obtenir le sable dans un terrain plus grand (SDL)

@file Sand.h
*/


#ifndef _SAND
#define _SAND

#include "Math.h"

/**
@brief La classe Sand contient un Vec2f de position (Vec2f définie dans Math.h)
*/
class Sand
{
private:
    Vec2f s_pos;

public:

    /**
    @brief <B>Construit</B> un objet Sand.
    */
    Sand();

    /**
    @brief <B>Construit</B> un objet Sand.
    Le constructeur remplit la position par X et Y
    @param x : abs de la position du sable
    @param y : ordonnée de la position du sable
    */
    Sand(float X, float Y);

    /**
    @brief Renvoie la composante X du Vec2f position du sable 
    */
    float getX() const;

    /**
    @brief Renvoie la composante Y du Vec2f position du sable 
    */
    float getY() const;
};

#endif