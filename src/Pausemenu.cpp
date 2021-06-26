#include "preprocessor.hpp"
#include "textureMusic.hpp"
#include "globalvars.hpp"
#include "utills.hpp"
#include "menu.hpp"
#include "gameElements.hpp"
#include "gameUtills.hpp"

SDL_Rect cursorDim;
SDL_Rect resumeDim;
SDL_Rect mainMenueDim;
SDL_Rect exitDim;
SDL_Rect bgdim;

void cursorjump(SDL_Rect *b)
{
    cursorDim.y = b->y;
}
void cursorupdate(int step)
{
    if (cursorDim.y + step < screen_height / 3)
        cursorjump(&exitDim);
    else if (cursorDim.y + step > (screen_height / 3) + 2 * (screen_height / 10))
        cursorjump(&resumeDim);
    else
        cursorDim.y += step;
}
void Pause_the_game()
{
    bool return_to_game = false;
    int xVal = (screen_width / 2) - screen_width / 12;
    int yVal = screen_height / 3;
    int buttonH = screen_height / 20;
    int buttonW = screen_width / 6;
    int step = screen_height / 10;

    return_to_game = false;

    bgdim = {0, 0, screen_width, screen_height};
    cursorDim.w = screen_width / 40;
    cursorDim.h = screen_height / 20;
    cursorDim.x = xVal - cursorDim.w;
    cursorDim.y = yVal;

    resumeDim = {xVal, yVal, buttonW, buttonH};
    yVal += step;
    mainMenueDim = {xVal, yVal, buttonW, buttonH};
    yVal += step;
    exitDim = {xVal, yVal, buttonW, buttonH};

    int prevMousex = 0;
    int prevMousey = 0;
    while (!return_to_game)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true, return_to_game = true, isrunning = false;
            if (win.handleEvent(e))
                scaleGame(), walls.init();
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_BACKSPACE:
                    return_to_game = true;
                    break;
                case SDLK_m:
                    win.toggleFullscreen();
                    break;
                case SDLK_UP:
                    cursorupdate(-(step));
                    break;
                case SDLK_DOWN:
                    cursorupdate(step);
                    break;
                case SDLK_o:
                    if (Mix_PausedMusic() == 1)
                    {
                        Mix_ResumeMusic();
                    }
                    else
                    {
                        Mix_PauseMusic();
                    }
                    break;
                case SDLK_RETURN:
                {
                    if (cursorpoints(&resumeDim, &cursorDim))
                        return_to_game = true;
                    else if (cursorpoints(&mainMenueDim, &cursorDim))
                        screen = MAIN_MENU, mainMenu.updateUI(), diffTimer.stop(),return_to_game = true, isrunning = false;
                    else if (cursorpoints(&exitDim, &cursorDim))
                        quit = true, return_to_game = true, isrunning = false;
                }
                }
            }
        }

        int mousex, mousey;
        int mbutton = SDL_GetMouseState(&mousex, &mousey);
        if (prevMousex != 0 && prevMousey != mousey)
        {
            if (mousey < mainMenueDim.y)
                cursorjump(&resumeDim);
            else if (mousey >= mainMenueDim.y && mousey < mainMenueDim.y + mainMenueDim.h + 1)
                cursorjump(&mainMenueDim);
            else if (mousey >= exitDim.y)
                cursorjump(&exitDim);
        }
        if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT))
        {

            if (mouseIsInside(&resumeDim, mousex, mousey))
                return_to_game = true;
            else if (mouseIsInside(&mainMenueDim, mousex, mousey))
                screen = MAIN_MENU, mainMenu.updateUI(), diffTimer.stop(),return_to_game = true,isrunning = false;
            else if (mouseIsInside(&exitDim, mousex, mousey))
                quit = true, return_to_game = true, isrunning = false;
        }
        prevMousex = mousex, prevMousey = mousey;
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, pauseBG, NULL, &bgdim);
        SDL_RenderCopy(ren, pausenewB, NULL, &mainMenueDim);
        SDL_RenderCopy(ren, resumeB, NULL, &resumeDim);
        SDL_RenderCopy(ren, pauseexitB, NULL, &exitDim);
        SDL_RenderCopy(ren, cursor, NULL, &cursorDim);
        SDL_RenderPresent(ren);
        SDL_Delay(1000 / 60);
    }
}