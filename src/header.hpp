#ifndef HEADER_H
#define HEADER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
 
enum screens {
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
 
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
 
extern bool quit;
extern screens screen;
extern bool isrunning;
extern int cursorHalfway;
extern SDL_Rect cursorDim;
extern SDL_Rect pcursorDim;
extern int menumax, pmenumax;
 
extern int prevMousex, prevMousey;
 
bool init();
bool loadMedia();
bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey);
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim);
void cursorupdate(int step);
void cursorJump(int step);
void titlescreen();
void main_menue();
void high_score();
void help();
void pauseM();
void about();
void gamestart();
void close();
 
SDL_Texture* loadTex(std::string path);
 
extern SDL_Window* win;
extern SDL_Renderer* ren;
extern SDL_Texture* titleBG;
extern SDL_Texture* mainMenuBG;
extern SDL_Texture* pauseBG;
extern SDL_Texture* aboutBG;
extern SDL_Texture* inGameBG;
extern SDL_Texture* backB;
extern SDL_Texture* highScoreB;
extern SDL_Texture* aboutB;
extern SDL_Texture* newGameB;
extern SDL_Texture* helpB;
extern SDL_Texture* resumeB;
extern SDL_Texture* exitB;
extern SDL_Texture* cursor;
extern SDL_Texture* playertex;

struct Player
{
      static const int width = SCREEN_WIDTH/10;
      static const int height = SCREEN_HEIGHT/8;
      static const int xStep = SCREEN_WIDTH/35;
      static const int yStep = SCREEN_HEIGHT/15;

      SDL_Rect htbx;
      
      int xPos = 0;
      int yPos = SCREEN_HEIGHT/2-(width/2);
      double angle = 0.0;
      Player();

      void handleEvent(SDL_Event* e);
      void move(int x, int y);
      void render();
};

#endif