/**
@brief Module gérant l'affichage et le Jeu SDL de l'application MasterGolf

@file MasterGolf.h
*/

#ifndef _RENDERER
#define _RENDERER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Game.h"

#include <cassert>

/**
@brief La classe Image contient une texture SDL
*/
class Image
{
private:
    SDL_Texture *texture;

public:

    /**
    @brief <B>Construit</B> un objet Image.
    Le constructeur remplit la texture par NULL.
    */
    Image();

    /**
    @brief Change la valeur de la texture par celle comprise dans le fichier
    @param renderer : le renderer
    @param filename : un string contenant le chemin et le nom de l'image que l'on souhaite charger
    */
    void loadFromFile(SDL_Renderer *renderer, const char *filename);

    /**
    @brief Affiche la texture entière à l'écran a partir des coordonnées en haut a gauche de l'image
    @param renderer : le renderer
    @param x : abs du coin haut gauche de l'image
    @param y : ordonnée du coin haut gauche de l'image
    */
    void draw(SDL_Renderer *renderer, int x, int y);

    /**
    @brief Affiche la texture redimensionnée à l'écran à partir des coordonnées en haut à gauche de l'image
    @param renderer : le renderer
    @param x : abs du coin haut gauche de l'image
    @param y : ordonnée du coin haut gauche de l'image
    @param sizeX : taille abs de l'image
    @param sizeY : taille ordonnée de l'image    
    */
    void draw(SDL_Renderer *renderer, int x, int y, float sizeX, float sizeY);

    /**
    @brief Affiche la texture redimensionnée à l'aide d'un facteur scale (1 = image entière, 0 = vide)
    @param renderer : le renderer
    @param x : abs du coin haut gauche de l'image
    @param y : ordonnée du coin haut gauche de l'image
    @param scale : facteur de réduction de l'image (compris entre 0 et 1)
    */
    void draw_scale(SDL_Renderer *renderer, int x, int y, float scale);

    /**
    @brief Affiche la texture redimensionnée juste en ordonnée à l'aide d'un facteur scale (0 = image entière, 1 = vide)
    Uniquement utilisé pour dessiner le cache sur l'indicateur de puissance
    @param renderer : le renderer
    @param x : abs du coin haut gauche de l'image
    @param y : ordonnée du coin haut gauche de l'image
    @param scale : facteur de réduction de l'image (compris entre 0 et 1)
    */
    void draw_indicator(SDL_Renderer *renderer, int x, int y, float scale);

    /**
    @brief Renvoie le rectangle correspondant a la texture d'une image (utile pour la fonction SDL_PointInRect)
    @param x : abs du coin haut gauche de l'image
    @param y : ordonnée du coin haut gauche de l'image
    */
    SDL_Rect getrectangle(int x, int y);
};


/**
@brief La classe MGolf contient :
- Une window, un renderer
- Toutes les images nécessaires à l'affichage
- Le delta Time
- 1 Game
- Les entiers correspondant à la taille de la fenêtre
- Une variable state (0 pour title Screen 1 pour Play)
- Un booléen MPressed correspondant au clic gauche de la souris
- Des SDL_Point pour les différentes positions de la souris
- Des SDL_Rect pour pouvoir clicker sur des images.
- Un booléen quit qui reste false tant que l'on n'a pas quitté la fenêtre
*/
class MGolf
{
public:
    bool quit;
    SDL_Event events;

    Game G;

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Point LMouseDown, LMouseUP, mouseMotion;
    SDL_Rect rec_ball, rec_plus;

    Image im_loadingbg;
    Image im_titlescreenbg;


    Image im_ball;
    Image im_wall;
    Image im_wall_shadow;
    Image im_bg1;
    Image im_bg2;
    Image im_hole;
    Image im_sand;
    Image im_strength_bar;
    Image im_strength_indicator;
    Image im_btwall;
    Image im_rlwall;
    Image im_plus;

    Uint64 currentTick;
    Uint64 lastTick;
    double deltaTime;

    int ScreenX, ScreenY, state;

    float strength;

    bool MPressed;

public:
    /**
    @brief <B>Construit</B> un objet MGolf.
    Le constructeur remplit toutes les valeurs par défaut de la class MGolf
    Créer une fenêtre et un renderer
    Charge toutes les images
    @param DimX : Dimension X de la fenêtre
    @param DimY : Dimension Y de la fenêtre
    */
    MGolf(int DimX, int DimY);

    /**
    @brief <B>Detruit</B> un objet MGolf.
    Détruit la window
    Détruit le renderer
    Quitte SDL
    */
    ~MGolf();

    /**
    @brief Fonction de titleScreen montre une première image pendant 2 secondes puis montre une autre image en attendant un clic gauche pour commencer
    */
    void titleScreen();

    /**
    @brief Fonction de tir : transforme le tir SDL en 4 valeurs pour utiliser la fonction B.swing() (cf Ball.h) 
    @param SMX : entier correspondant à la position en X du relâchement de la souris après avoir clicker sur la balle
    @param SMY : entier correspondant à la position en Y du relâchement de la souris après avoir clicker sur la balle
    @param strength : float compris entre 0 et 1 correspondant à la force du relâchement par rapport à un cercle autour de la balle
    */
    void swing_sdl(int SMX, int SMY, float strength);

    /**
    @brief Procédure d'affichage, affiche à l'écran une Game (cf Game.h)
    */
    void Display();

    /**
    @brief Procédure de jeu, joue une Game récupère les clics et update la balle et les niveaux en conséquence
    */
    void Play();

    /**
    @brief Boucle finale, agit en fonction de l'entier state (0 pour title Screen, 1 pour jouer)
    */
    void loop();
};


#endif