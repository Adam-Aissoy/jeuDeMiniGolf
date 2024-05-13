#include "Game.h"


Game::Game()
{
    level = 0;
}

float Game::getWSizeX() const { return wallsize.getX(); }
float Game::getWSizeY() const { return wallsize.getY(); }

// Fonction to load a level,
// A level have to take his dimension (x and y) in the first line
// Then we can draw the level with :
// a / for all the edges
// a # for a wall
// a S for a sand square
// a o for the ball
// a O for the hole  
void Game::load_level(const string &filename, int Bsize, int DX, int DY)
{
    // We open the file with is direction/filename
    ifstream fichier(filename.c_str());
    assert(fichier.is_open());
    
    // We get the two dimensions 
    fichier >> DimX >> DimY;
    assert(DimX > 0 && DimY > 0);

    // We create a char and a row of char
    char C;
    vector<char> row;

    // We clear the different vector because we're gonna refill them
    Terrain.clear();
    Walls.clear();
    Sands.clear();

    // We put the ball size and the 2 wallsizes input in our game (it changes depending on the size of the field)
    ballsize = Bsize;
    wallsize.setX(DX / DimX);
    wallsize.setY(DY / DimY);

    // And we set the scale to 1 because if we use this fonction after a win the scale must be < 0.3
    B.setScale(1);

    // Double loop to go for each char of our terrain
    for (int j = 0; j < DimY; j++)
    {
        for (int i = 0; i < DimX; i++)
        {
            fichier >> C; // We put the terrain char in C

            row.push_back(C); // Then we put this char in our row

            // Here we dont use a switch because we can't initiate things in a switch
            if (C == '#') // First case : a wall
            {
                Wall W(i, j); // We create a wall with the i and j coords
                Walls.push_back(W); // Then we put it in our walls vector
            }

            else if (C == 'S') // Second case : a sand square (same as the wall)
            {
                Sand S(i, j);
                Sands.push_back(S);
            }

            else if (C == 'O') // Third case : the hole
            {
                Hole.setX((i + 0.5) * wallsize.getX()); // We set the coords of the hole in the middle of this place in the terrain
                Hole.setY((j + 0.5) * wallsize.getY()); // So we need the wallsizes to put it in the middle
            }

            else if (C == 'o') // Fourth case : the ball (same as the hole)
            {
                B.setPositionX((i + 0.5) * wallsize.getX());
                B.setPositionY((j + 0.5) * wallsize.getY());
            }
        }

        Terrain.push_back(row); // Finally we put our row in our terrain : vector<vector<char>>
        row.clear(); // We clear our row to use it again for the next line
    }
}

// We make an update fonction here so we can get all the game objects in the ball update
// + we don't need an deltaTime for the txt so we put it to 1 in the txt class
void Game::update(double deltaTime) 
{
    B.update(Walls, Sands, DimX, DimY, Hole, deltaTime, wallsize, ballsize);
}

// Update level witch takes the ball size and the dimension of the screen
// Because we're using it in the loading level we input them in this function
// For the txt BSize is 1 and DX and DY are the same as the dimension of the terrain
void Game::update_lvl(int BSize, int DX, int DY)
{
    if (B.isWin())
    {
        switch (level) // The level is defined by an int initialised at 1
        {
        case 0:
            load_level("./data/lvl/Level1.ppm", BSize, DX, DY);
            break;
        case 1:
            load_level("./data/lvl/Level2.ppm", BSize, DX, DY);
            break;
        case 2:
            load_level("./data/lvl/Level3.ppm", BSize, DX, DY);
            break;
        case 3: // When we go to the fourth level we're redirected to the first so it never end
            level = -1;
            break;
        }

        level++; // When we've load the level we increase level by 1
        B.setWin(false); // And we reset the win value 
    }
}