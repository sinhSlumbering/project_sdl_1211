#ifndef UTILLS_H
#define UTILLS_H
#include "preprocessor.hpp"



//initializes systems
bool init();

//grabs the current window dimensions
void updatescreen();

//checks to see if mouse is within a certain rectangular area
bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey);
//checks to see if the ingame cursor points to a particular button
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim);

void highscore_printing(int a,int x, int y);

void printText(SDL_Renderer *renderer, int x, int y, std::string point,
             SDL_Texture **texture, SDL_Rect *rect, SDL_Color white);

//uses previous frametimes to lock fps in case vsync is not available
void optimizeFPS(long *prevtime, float *remainder);
void save_game(int playerscore, int livesleft, int boss_health, int a, int b, int c, int d, int e, int f);
void play(int *a, int *b, int *c, int *d, int *e, int *f, int *g, int *h, int *i);

//scales a variable tied to screen width
void scaleIntX(int *x);
//scales a variable tied to screen height
void scaleIntY(int *y);
//scales a rectangle to changed screen size
void scaleRect(SDL_Rect* r);
//scales the game to current screen size
void scaleGame();
//initializes game variables
void initGame();
//clears the saved highscores
void highscoreclear();


#endif