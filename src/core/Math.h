/**
@brief Module gérant la structure Vec2f dans l'application MasterGolf

Pour ce jeu nous aurrons besoin de multiples fois d'un vecteur de 2 composants de float
Il seras aussi utilisée pour définir un vecteur de 2 entiers

@file Math.h
*/

#ifndef _MATH
#define _MATH

#include <iostream>

/**
@brief La classe Vec2f contient 2 floats : x et y
*/
class Vec2f
{
private:
    float x, y;

public:

    /**
    @brief <B>Construit</B> un objet Vec2f.
    Le constructeur remplit x et y avec 0, 0
    */
    Vec2f();

    /**
    @brief <B>Construit</B> un objet Vec2f.
    Le constructeur remplit x et y avec X et Y
    @param X : float, x devient X
    @param Y : float, y devient Y
    */
    Vec2f(float X, float Y);

    /**
    @brief Renvoie la composante X du Vec2f 
    */
    float getX() const;

    /**
    @brief Renvoie la composante Y du Vec2f 
    */
    float getY() const;

    /**
    @brief Change la composante x du Vec2f par un float en entrée 
    @param x : Un float (futur valeur de Vec2f.x)
    */
    void setX(float x);

    /**
    @brief Change la composante y du Vec2f par un float en entrée 
    @param y : Un float (futur valeur de Vec2f.y)
    */
    void setY(float y);

    /**
    @brief Affiche dans la console le Vec2f
    */
    void print() const;
};

#endif