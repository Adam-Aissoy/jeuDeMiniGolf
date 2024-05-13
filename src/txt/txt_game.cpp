#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"
#include "Ball.h"
#include "Game.h"
#include "txt_game.h"

using namespace std;

txtGame :: txtGame()
{
    numberTries = 0;
}

txtGame :: txtGame(int x)
{
    sizeTerrain = x;
    numberTries = 0;
}

void txtGame :: txtDisplay (WinTXT & win)
{
    win.clear();

    char temp;

    // we set up a scale depending on the parameter chosen that will make the terrain displayed larger
    int scaleTerrainX = int(sizeTerrain/G.DimX);
    int scaleTerrainY = int(sizeTerrain/G.DimY);

    unsigned int max;

    //for each character in the tab, we print a specific character a certain number of times
    for (unsigned int i(0); i < G.DimX; i++)
    {
        for (unsigned int j(0); j < G.DimY; j++)
        {
            max=0;
            if (G.Terrain[j][i]=='o' || G.Terrain[j][i]=='_')
            {
                temp = ' ';
            }
            else if (G.Terrain[j][i]=='/' || G.Terrain[j][i]=='#')
            {
                temp = '#';
            }
            else if (G.Terrain[j][i]=='O')
            {
                //we only want to print one hole
                win.print(i*scaleTerrainX,j*scaleTerrainY, '0');
                temp = ' ';
                max = 1;
            }
            else if (G.Terrain[j][i]=='S')
            {
                temp = '~';
            }
            for (unsigned int k = max; k < scaleTerrainX; k++)
            {
                for (unsigned int l = max; l < scaleTerrainY; l++)
                {
                    win.print(i*scaleTerrainX+k,j*scaleTerrainY+l, temp);
                }
            }
        }
    }

    // same as for the hole
    int ballPosX = int(G.B.getPositionX());
    int ballPosY = int(G.B.getPositionY());

    win.print( ballPosX , ballPosY, 'o');

    win.draw();

    
    // we print the number of tries
    char charNumberTries = numberTries+'0';
    string tries= "Vous êtes à ";
    tries.push_back(charNumberTries);
    tries+=" essais";
    displayString(tries, win, 2);
}

// A loop to display characters from a string
void txtGame :: displayString(const string & stringToShow, WinTXT & win, int y)
{
    for (int i = 0; i<stringToShow.length(); i++)
    {
        win.print(i+sizeTerrain+5,y, stringToShow[i]);
    }
    win.draw();
}

// Main loop
int txtGame :: txtLoop ()
{
    WinTXT win (sizeTerrain+100, sizeTerrain+1);

    bool ok = true;
    bool okDir, okVit;
    int c;
    int d;
    int xtemp, ytemp, vtemp;


    while (ok) 
    {
        // We display the game
        txtDisplay(win);
        
        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000);
        #endif // we wait 100ms

        if (win.getCh()=='q') //if the player pressed 'q', we end the loop
        {
            return 0;
        }

        // if the ball is in the hole, we move on to the next level, and display the number of tries
        if (G.B.getPositionX() == G.Hole.getX() && G.B.getPositionY() == G.Hole.getY())
        {

            string textEnd = "niveau terminé en ";
            textEnd.push_back(numberTries);
            textEnd+= " essais.";  
            displayString (textEnd, win, 2);
            G.update_lvl(1,sizeTerrain,sizeTerrain);
        }
        
        // we update the ball movements and the game
        G.update(1);

        //if the ball is too slow we stop it
        if(G.B.getVelocity1D() < 0.2)
        {
            G.B.setVelocityX(0);
            G.B.setVelocityY(0);
        }

        if (G.B.canMove())                
        //if the ball is stopped
        {

            okDir = okVit = false;
            termClear();
            string text1 = "choisissez la direction avec le pavé numérique";
            displayString (text1, win, 5);
            do
            {
                c=win.getCh();                                                  
                //we fetch the last typed char
                switch (c)                                                          
                //depending on the input we set up directions
                {
                    case '1' :
                        xtemp = 1;
                        ytemp = -1;
                        okDir = true;
                        break;
                    case '4' :
                        xtemp = 1;
                        ytemp = 0;
                        okDir = true;
                        break;
                    case '7' :
                        xtemp = 1;
                        ytemp = 1;
                        okDir = true;
                        break;
                    case '8' :
                        xtemp = 0;
                        ytemp = 1;
                        okDir = true;
                        break;
                    case '9' :
                        xtemp = -1;
                        ytemp = 1;
                        okDir = true;
                        break;
                    case '6' :
                        xtemp = -1;
                        ytemp = 0;
                        okDir = true;
                        break;
                    case '3' :
                        xtemp = -1;
                        ytemp = -1;
                        okDir = true;
                        break;
                    case '2' :
                        xtemp = 0;
                        ytemp = -1;
                        okDir = true;
                        break;
                    case 'q' :
                        return(0);
                        break;
                }
            }
            while (okDir == false);
            win.clear();
            txtDisplay(win);
            string text = "entrez une vitesse entre 1 et 9";
            displayString (text, win, 5);
            win.pause();
            do
            {
                d=win.getCh();
                if (d == 'q')
                {
                    return(0);
                }
                else
                {
                    vtemp = d-48;                           
                    // converting char to int
                    G.B.swing(sqrt(vtemp)/5,sqrt(vtemp)/5,-xtemp,-ytemp); //updating speed
                    numberTries +=1;        // update the number of tries
                    okVit=true;
                }
            }
            while (okVit == false);
            win.clear();
        }
        termClear();
    }
}

// The first menu displayed when opening the game
char txtGame :: txtMenu ()
{

    cout<<"Bienvenue sur Master Golf !"<<endl
    <<"Entrez un numero de niveau pour commencer"<<endl
    <<"Ou entrez Q pour quitter"<<endl;

    bool niv = false;
    char ch;
    string levelNameStart = "./data/lvl/Level";
    string levelNameEnd = ".ppm";
    // we fetch the level number
    cin>>ch;
    if (ch == 'q') //if q => end
    {
        return('q');
    }
    else {
        //we merge the strings to get the right file name
        levelNameStart.push_back(ch);
        levelNameStart+=levelNameEnd;
        //and load the level
        G.load_level(levelNameStart,1,sizeTerrain,sizeTerrain);
        return('o');
    }
}

