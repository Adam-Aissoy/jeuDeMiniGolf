#include "MasterGolf.h"

////////////////////////////////////////////////
//////            IMAGE CLASS             //////
////////////////////////////////////////////////

Image::Image()
{
    texture = NULL;
}

void Image::loadFromFile(SDL_Renderer *renderer, const char *filename)
{
    texture = IMG_LoadTexture(renderer, filename);

    if (texture == NULL)
    {
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    }
}

void Image::draw(SDL_Renderer *renderer, int x, int y)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);

    ok = SDL_RenderCopy(renderer, texture, NULL, &r);
    assert(ok == 0);
}

void Image::draw(SDL_Renderer *renderer, int x, int y, float sizeX, float sizeY)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = sizeX;
    r.h = sizeY;

    ok = SDL_RenderCopy(renderer, texture, NULL, &r);
    assert(ok == 0);
}

void Image::draw_scale(SDL_Renderer *renderer, int x, int y, float scale)
{
    int ok;
    SDL_Rect r;

    SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);

    r.x = x + (r.w - r.w * scale) / 2;
    r.y = y + (r.h - r.h * scale) / 2;
    r.w *= scale;
    r.h *= scale;

    ok = SDL_RenderCopy(renderer, texture, NULL, &r);
    assert(ok == 0);
}

void Image::draw_indicator(SDL_Renderer *renderer, int x, int y, float scale)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
    r.h = r.h * abs(scale - 1); // We need to inverse it so when the strength is at 1 we show the entire texture

    ok = SDL_RenderCopy(renderer, texture, NULL, &r);
    assert(ok == 0);
}

SDL_Rect Image::getrectangle(int x, int y)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);

    return r;
}

////////////////////////////////////////////////
//////          MASTER GOLF CLASS         //////
////////////////////////////////////////////////

MGolf::MGolf(int DIMX, int DIMY)
{
    // Init state (0 -> Title Screen, 1 -> In a level)
    state = 0;
    MPressed = false;
    quit = false;
    currentTick = SDL_GetPerformanceCounter();
    lastTick = 0;
    deltaTime = 0;
    ScreenX = DIMX;
    ScreenY = DIMY;

    // Setup SDL
    window = SDL_CreateWindow("Master Golf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DIMX, DIMY, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Setup images for the titlescreen
    im_loadingbg.loadFromFile(renderer, "./data/gfx/loading.png");
    im_titlescreenbg.loadFromFile(renderer, "./data/gfx/titlescreenbg.png");

    // Setup images for the game
    im_ball.loadFromFile(renderer, "./data/gfx/ball.png");
    im_wall.loadFromFile(renderer, "./data/gfx/wall.png");
    im_wall_shadow.loadFromFile(renderer, "./data/gfx/wall_shadow.png");
    im_bg1.loadFromFile(renderer, "./data/gfx/background1.png");
    im_bg2.loadFromFile(renderer, "./data/gfx/background2.png");
    im_hole.loadFromFile(renderer, "./data/gfx/hole.png");
    im_sand.loadFromFile(renderer, "./data/gfx/sand.png");
    im_strength_bar.loadFromFile(renderer, "./data/gfx/strength_bar.png");
    im_strength_indicator.loadFromFile(renderer, "./data/gfx/strength_indicator.png");
    im_plus.loadFromFile(renderer, "./data/gfx/plus.png");

    // Setup fonts

    // Setup Sounds (Future)
}

MGolf::~MGolf()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void MGolf::titleScreen()
{
    if (SDL_GetTicks() < 2000)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

        im_loadingbg.draw(renderer, 0, 0, ScreenX, ScreenY);
        SDL_RenderPresent(renderer);
    }
    else
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT)
                {
                    state = 1;
                }
                break;
            }
        }

        im_titlescreenbg.draw(renderer, 0, 0, ScreenX, ScreenY);
        SDL_RenderPresent(renderer);
    }
}

void MGolf::swing_sdl(int SMX, int SMY, float strength) // Function to transform the sdl way of shooting to 4 values
{   // We input the second click and the strength value (between 0 and 1)

    float opposite, adjacent, alpha;
    int DirX, DirY;

    // Trigonometry is used to transform two axis values and 1 strength into a power X and Y and a direction X and Y
    opposite = abs(G.B.getPositionX() - SMX); 
    adjacent = abs(G.B.getPositionY() - SMY);

    alpha = atan(opposite / adjacent); 

    if (G.B.getPositionX() - SMX <= 0)
    {
        DirX = -1;
    }
    else
    {
        DirX = 1;
    }

    if (G.B.getPositionY() - SMY <= 0)
    {
        DirY = -1;
    }
    else
    {
        DirY = 1;
    }

    // These calculations are to make a reel shoot range in a circle
    G.B.swing(sin(alpha) * strength / 2, cos(alpha) * strength / 2, DirX, DirY);
}

void MGolf::Display() // Used to display when playing a game
{
    // Background + 4 walls surounding
    im_bg1.draw(renderer, 0, 0, ScreenX, ScreenY);
    im_bg2.draw(renderer, G.getWSizeX(), G.getWSizeY(), ScreenX - 2 * G.getWSizeX(), ScreenY - 2 * G.getWSizeY());

    for (Sand &s : G.Sands) // All the sand squares
    {
        im_sand.draw(renderer, s.getX() * G.getWSizeX(), s.getY() * G.getWSizeY(), G.getWSizeX(), G.getWSizeY());
    }

    for (Wall &w : G.Walls) // All the walls
    {
        im_wall_shadow.draw(renderer, w.getX() * G.getWSizeX(), (w.getY() + 1) * G.getWSizeY(), G.getWSizeX(), 6);
        im_wall.draw(renderer, w.getX() * G.getWSizeX(), w.getY() * G.getWSizeY(), G.getWSizeX(), G.getWSizeY());
    }

    im_hole.draw(renderer, G.Hole.getX() - 8, G.Hole.getY() - 9.5); // The hole
    im_ball.draw_scale(renderer, G.B.getPositionX() - 8, G.B.getPositionY() - 8, G.B.getScale()); // The ball with the scale factor

    if (MPressed) // If the click is on the ball we draw the power indicator
    {
        im_strength_bar.draw(renderer, G.B.getPositionX() + 25, G.B.getPositionY() - 25);
        im_strength_indicator.draw_indicator(renderer, G.B.getPositionX() + 28, G.B.getPositionY() - 22, strength);
    }

    im_plus.draw(renderer, ScreenX - 35, ScreenY - 35); // The + in the bottom right corner

    SDL_RenderPresent(renderer); // We update the renderer to show it on screen
}

void MGolf::Play() // Playing a game :
{
    lastTick = currentTick; // Delta time calculation = time between 2 frames / used to multiplie to the velocity to get smoother movements
    currentTick = SDL_GetPerformanceCounter(); 
    deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (MPressed && events.button.button == SDL_BUTTON_LEFT) // If we release the left click
            {
                MPressed = false;
                SDL_GetMouseState(&LMouseUP.x, &LMouseUP.y); // We get the second position of the cursor
                swing_sdl(LMouseUP.x, LMouseUP.y, strength); // We sent them in the swing function 
                strength = 0; // We reset the strength value
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (!MPressed && events.button.button == SDL_BUTTON_LEFT) // if we left click
            {
                rec_ball = im_ball.getrectangle(G.B.getPositionX() - 8, G.B.getPositionY() - 8); // We get the rectangle of the ball (will be usefull for the SDL_PointInRect function)
                rec_plus = im_plus.getrectangle(ScreenX - 35, ScreenY - 35); // We get the rectangle of the +

                SDL_GetMouseState(&LMouseDown.x, &LMouseDown.y); // We get the cursor position

                if (SDL_PointInRect(&LMouseDown, &rec_ball) && G.B.canMove()) // If we click on the ball
                {
                    MPressed = true;
                }
                else if (SDL_PointInRect(&LMouseDown, &rec_plus)) // If we click on the + we just simulate winning the game and pass to the next game
                {
                    G.B.setVelocityX(0);
                    G.B.setVelocityY(0);
                    G.B.setWin(true);
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (MPressed) // If MPressed involves the first click is on the ball
            {
                mouseMotion = {events.motion.x, events.motion.y}; // We get the mouse position (while we've not release the click)
                strength = sqrt(pow(LMouseDown.x - mouseMotion.x, 2) + pow(LMouseDown.y - mouseMotion.y, 2)) / 200; // We are calculating the power with the motion of the mouse

                if (strength > 1) // Who's limited by 200
                {
                    strength = 1;
                }
            }
            break;
        }
    }

    G.update_lvl(16, ScreenX, ScreenY); // We look if the level is updatable
    G.update(deltaTime); // We update the ball with the delta time

    Display(); // We display the game
    SDL_Delay(10); // Wait 10 ms
}

void MGolf::loop() // Final loop
{
    while (!quit)
    {
        if (state == 0)
        {
            titleScreen();
        }
        else
        {
            Play();
        }
    }
}
