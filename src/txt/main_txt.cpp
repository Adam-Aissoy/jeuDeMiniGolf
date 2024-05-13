#include "winTxt.h"
#include "txt_game.h"
#include "Game.h"

int main ( int argc, char** argv ) {
    txtGame t(40);
    termClear();
    char end = t.txtMenu();
    if (end == 'q')
    {
        return 0;
    }
    termClear();
    int endloop = t.txtLoop();
    termClear();
    return 0;
}
