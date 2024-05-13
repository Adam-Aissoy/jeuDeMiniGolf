/**
@brief Module Game gérant un niveau dans l'application MasterGolf

Un niveau dans l'application MasterGolf est un tableau 2D caractères dont la taille est DimX DimY.
Un niveau peut prendre les dimensions qu'il veut mais cela peut impacter les performances pour un terrain trop grand

@file Game.h
*/



#ifndef _GAME
#define _GAME

#include "Ball.h"
#include "Math.h"
#include "Sand.h"
#include "Wall.h"

#include <vector>
#include <assert.h>
#include <fstream>
#include <math.h>

/**
@brief Une 'Game' comporte donc :
- Un terrain (tableau 2D de caractère)
- Un tableau de murs (tableau 1D de Wall (cf Wall.h))
- Un tableau de sables (tableau 1D de Sand (cf Sand.h))
- Un troue (Hole -> Vec2f)
- Un entier level qui réprésente le numéro du niveau

- Un Vec2f de wallsize utile différent pour SDL et TXT
- Un entier ballsize représentant la taille de la balle
*/
class Game
{
public:
    int DimX, DimY, level;

    Ball B;
    Vec2f Hole;

    vector<Wall> Walls;
    vector<Sand> Sands;

    vector<vector<char>> Terrain;

    int ballsize;
    Vec2f wallsize;

    /**
    @brief <B>Construit</B> un objet Game.
    Le constructeur remplit uniquement level avec 0.
    */
    Game();

    /**
    @brief Renvoie la composante X du Vec2f wallsize
    */
    float getWSizeX() const;

    /**
    @brief Renvoie la composante Y du Vec2f wallsize
    */
    float getWSizeY() const;

    /**
    @brief Remplit toutes les données de Game en ouvrant un fichier extérieur
    @param filename : un const string représentant le chemin du fichier ou se trouve le niveau que l'on souhaite ouvrir
    @param Bsize : un entier représentant la taille de la balle (1 pour TXT et la taille du sprite en SDL)
    @param DX : la taille en X de l'affichage sur lequel on souhaite représenter ce niveau
    @param DY : la taille en Y de l'affichage sur lequel on souhaite représenter ce niveau
    */
    void load_level(const string &filename, int Bsize, int DX, int DY);

    /**
    @brief Update la Game donc la Balle en rentrant toutes les composantes de la Game dans B.update (cf Ball.h)
    @param deltaTime : Temps entre 2 frames (inutile pour txt donc mis à 1 en paramètre)
    */
    void update(double deltaTime);

    /**
    @brief Update le level (c'est ici que l'on définit les chemins des niveaux) les paramètres sont nécessaires à la fonction load_level on les entre donc ici
    @param Bsize : Taille de la balle
    @param DX : la taille en X de l'affichage sur lequel on souhaite représenter ce niveau
    @param DY : la taille en Y de l'affichage sur lequel on souhaite représenter ce niveau
    */
    void update_lvl(int Bsize, int DX, int DY);
};
#endif