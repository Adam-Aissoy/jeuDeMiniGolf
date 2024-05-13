#ifndef _TXT_GAME_H
#define _TXT_GAME_H

#include "winTxt.h"
#include "Ball.h"
#include "Game.h"

/**
    @brief La classe txtGame contient les données et fonctions pour l'affichage TXT du jeu :
    - une instance de Game
    - un entier pour la taille du terrain lors de l'affichage
    - un entier pour le nombre d'essais
    */
class txtGame 
{
public :
    Game G;
    int sizeTerrain;
    int numberTries;
    
    /**
    @brief <B>Construit</B> un objet txtGame.
    Le constructeur remplit le nombre d'essais à 0.
    */
    txtGame();

    /**
    @brief <B>Construit</B> un objet txtGame.
    Le constructeur remplit le nombre d'essais à 0 et la taille du terrain
    par la valeur en paramètre ou 40 par défaut.
    */
    txtGame(int x = 40);

    /**
    @brief Lance la boucle de jeu, qui appelle l'affichage et les fonctions de Game et Ball
    Renvoie 0 si la boucle s'est terminée par une action du joueur.
    */
    int txtLoop();

    /**
    @brief Affiche le menu et charge les niveaux
    Renvoie le char entré par l'utilisateur pour la selection de niveau.
    */
    char txtMenu();

    /**
    @brief Affiche une chaine de caractères à l'écran
    @param stringToShow : la string a afficher
    @param win : la fenetre sur laquelle on l'affiche
    @param y : la ligne à laquelle on l'affiche
    */
    void displayString(const string & stringToShow, WinTXT & win, int y);

    /**
    @brief Affiche l'état du jeu (niveau + balle + compteur de tirs) à chaque pas
    @param win : la fenetre sur laquelle on affiche
    */
    void txtDisplay (WinTXT & win);
};
    
#endif