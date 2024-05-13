/**
@brief Module gérant la balle dans MasterGolf

Une balle dans l'application MasterGolf est composée de 3 vecteurs de 2 floats : une vitesse, une direction et une position
La balle est aussi composée de 2 bools : Move et Win qui nous indique si la balle peut bouger ou est tombé dans le trou
Un facteur scale qui est utile pour SDL

@file Ball.h
*/

#ifndef _BALL
#define _BALL

#include "Math.h"
#include "Wall.h"
#include "Sand.h"

#include <vector>
#include <cmath>

using namespace std;

class Ball
{
private:
    Vec2f Velocity;
    Vec2f b_pos;
    Vec2f Dir;
    bool Move, Win;
    float scale;

public:
    /**
    @brief <B>Construit</B> un objet Ball.
    Le constructeur remplit la vitesse à 0
    Un vecteur direction de base
    Et met le booléen Win à true (utile pour la fonction update_lvl)
    */
    Ball();

    /**
    @brief Renvoie la valeur de la vitesse en X
    */
    float getVelocityX() const;

    /**
    @brief Renvoie la valeur de la vitesse en Y
    */
    float getVelocityY() const;

    /**
    @brief Renvoie la valeur de la position en X
    */
    float getPositionX() const;

    /**
    @brief Renvoie la valeur de la position en Y
    */
    float getPositionY() const;

    /**
    @brief change la valeur de la vitesse en X
    @param x : un float
    */
    void setVelocityX(float X);

    /**
    @brief change la valeur de la vitesse en Y
    @param x : un float
    */
    void setVelocityY(float Y);

    /**
    @brief change la valeur de la position en X
    @param x : un float
    */
    void setPositionX(float X);

    /**
    @brief change la valeur de la position en Y
    @param x : un float
    */
    void setPositionY(float Y);

    /**
    @brief change la valeur de la direction en X
    @param x : un float (normalement soit 1 ou -1)
    */
    void setDirX(float X);

    /**
    @brief change la valeur de la direction en Y
    @param x : un float (normalement soit 1 ou -1)
    */
    void setDirY(float Y);

    /**
    @brief Renvoie la valeur du booleen Move
    */
    bool canMove() const;

    /**
    @brief Renvoie la valeur du booleen Win
    */
    bool isWin() const;

    /**
    @brief change la valeur du booleen Win
    @param W : la valeur de Win que l'on veux avoir
    */
    void setWin(bool W);

    /**
    @brief Renvoie la valeur du facteur scale
    */
    float getScale() const;

    /**
    @brief change la valeur du facteur scale
    @param S : la valeur de scale que l'on veux avoir
    */
    void setScale(float S);

    /**
    @brief Renvoie un float étant la composée du vecteur de vitesse (grâce à Pythagore)
    */
    float getVelocity1D() const;

    /**
    @brief Gère la collision avec les murs du terrain
    @param Walls : Le vecteur comportant tous les murs du niveau
    @param deltaTime : La différence de temps entre 2 frames (importante pour calculer la position de la balle dans la frame suivante)
    @param wsizes : Un vecteur de 2 floats comportant la taille des murs en X et en Y (qui peut changer en fonction du niveau)
    @param bsize : La taille (carré) de la balle
    */
    void wallscollision(vector<Wall> &Walls, double deltaTime, Vec2f wsizes, int bsize);

    /**
    @brief Gère la collision avec les sables du terrain (ralentie la vitesse si on se situe sur une case de sable)
    @param Sands : Le vecteur comportant tous les sables du niveau
    @param wsizes : Un vecteur de 2 floats comportant la taille des murs en X et en Y (qui peut changer en fonction du niveau)
    @param bsize : La taille (carré) de la balle
    */
    void sandscollision(vector<Sand> &Sands, Vec2f wsizes, int bsize);

    /**
    @brief Gère la collision avec le trou du terrain (+ petite animation quand la balle tombe dedans)
    @param Hole : Vecteur de la position du trou du niveau
    @param deltaTime : La différence de temps entre 2 frames (importante ici pour déplacer la balle pour une animation)
    @param bsize : La taille (carré) de la balle
    */
    void holecollision(Vec2f Hole, double deltaTime, int bsize);

    /**
    @brief Gère toute la physique de la balle et inclue (wallscollision, sandscollision, holecollision)
    @param Walls : Le vecteur comportant tous les murs du niveau
    @param Sands : Le vecteur comportant tous les sables du niveau
    @param Hole : Vecteur de la position du trou du niveau
    @param DimX : La dimension en X du niveau
    @param DimY : La dimension en Y du niveau
    @param deltaTime : La différence de temps entre 2 frames (calculés plus haut dans la chaine des classes)
    @param wsizes : Un vecteur de 2 floats comportant la taille des murs en X et en Y (qui peut changer en fonction du niveau)
    @param bsize : La taille (carré) de la balle
    */
    void update(vector<Wall> &Walls, vector<Sand> &Sands, int DimX, int DimY, Vec2f Hole, double deltaTime, Vec2f wsizes, int bsize);


    /** 
    @brief Une fonction générale pour tirer (les paramètres sont calculés différemment pour sdl et txt)
    @param PX : Une float représentant la puissance en X
    @param PY : Une float représentant la puissance en Y
    @param Dx : Un entier représentant la direction en X
    @param Dy : Un entier représentant la direction en Y
    */
    void swing(float PX, float PY, int Dx, int Dy);
};

#endif