# Projet MasterGolf

## Description
MasterGolf est un jeu de golf développé dans le cadre du projet de soutenance LIFAP4. Le jeu propose une expérience immersive où les joueurs peuvent parcourir des terrains de golf, surmonter des obstacles et essayer d'atteindre le trou en utilisant le moins de coups possible.

## Équipe de développement
- Lucas VIOLENT
- Oumar Adam Adam
- Héloïs BIHRY

## Modules
### Math.h
Ce module gère la structure Vec2f, un vecteur 2D utilisé pour représenter les positions et les directions dans le jeu.

### Ball.h
Ce module gère la balle de golf. Il inclut la logique pour déplacer la balle, gérer les collisions avec les murs, le sable et le trou, ainsi que la physique de la balle.

### Game.h
Ce module gère les niveaux du jeu. Il charge les niveaux à partir de fichiers externes, met à jour la logique du jeu et les niveaux en fonction de la progression du joueur.

### Sand.h
Ce module gère les cases de sable sur le terrain de golf. Il contient la logique pour définir la position des cases de sable.

### Wall.h
Ce module gère les murs sur le terrain de golf. Il contient la logique pour définir la position des murs.

## Instructions d'utilisation
1. Cloner le dépôt Git sur votre machine locale.
2. Compiler le code source à l'aide d'un compilateur compatible C++.
3. Exécuter l'application résultante pour commencer à jouer à MasterGolf.

## Contributions
Les contributions à ce projet sont les bienvenues. Si vous souhaitez contribuer, veuillez créer une nouvelle branche à partir de la branche principale, effectuer vos modifications et soumettre une demande de fusion lorsque vous avez terminé.

## Licence
Ce projet est sous licence MIT. Consultez le fichier LICENSE pour plus d'informations.

