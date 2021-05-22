#ifdef UTILS_H
#define UTILS_H
//using stdio, iostream, sdl and sdl_image
#include<stdio.h>
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

//enumerating the screens for redability
enum screens
{
      TITLE_SCREEN,
      MAIN_MENU,
      IN_GAME,
      OPTIONS,
      HIGH_SCORES,
      HELP,
      ABOUT,
      PAUSE,
      GAME_OVER,
      EXIT
};

//screen constants
extern const int SCREEN_WIDTH = 800;
extern const int SCREEN_HEIGHT = 600;

//misc 
extern bool quit=false;
extern screens screen=TITLE_SCREEN;
extern bool isrunning=true;
extern int cursorHalfway=(SCREEN_WIDTH-(SCREEN_WIDTH/20)-SCREEN_WIDTH/6-SCREEN_WIDTH/40);
extern SDL_Rect cursorDim={cursorHalfway, SCREEN_HEIGHT/20, SCREEN_WIDTH/40, SCREEN_HEIGHT/20};
extern SDL_Rect pcursorDim={SCREEN_WIDTH/2-SCREEN_WIDTH/12-SCREEN_WIDTH/40, SCREEN_HEIGHT/3, SCREEN_WIDTH/40, SCREEN_HEIGHT/20};
extern int menumax=4*SCREEN_HEIGHT/10, pmenumax=SCREEN_HEIGHT/3+2*SCREEN_HEIGHT/10;

//jank mouse handler
extern int prevMousex=0, prevMousey=0;

/**functions**/
//initializtion 
extern bool init();

//loads media
extern bool loadMedia();

//to check if mouse is on a specific element
extern bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey);

//to check if cursor points to element
extern bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim);
extern void cursorupdate(int step);
extern void cursorJump(int step);

//title screen function;
void titlescreen();

//main menue
void main_menue();

//highscore
void high_score();

//help
void help();

//pause
void pauseM();

//about
void about();

//void game
void gamestart();

//close subsystems and exit
void close();

//load texture
SDL_Texture* loadTex(std::string path);


/***window, renderer and textures***/
//window
extern SDL_Window* win = NULL;

//rederer
extern SDL_Renderer* ren = NULL;

//screen background textures
extern SDL_Texture* titleBG = NULL;
extern SDL_Texture* mainMenuBG = NULL;
extern SDL_Texture* pauseBG = NULL; 
extern SDL_Texture* aboutBG = NULL;
extern SDL_Texture* inGameBG = NULL;

//buttons

extern SDL_Texture* backB = NULL;
extern SDL_Texture* highScoreB = NULL;
extern SDL_Texture* aboutB = NULL;
extern SDL_Texture* newGameB = NULL;
extern SDL_Texture* helpB = NULL;
extern SDL_Texture* resumeB = NULL;
extern SDL_Texture* exitB = NULL;

//cursor
extern SDL_Texture* cursor=NULL;

#endif