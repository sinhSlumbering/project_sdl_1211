#ifndef HEADER_H
#define HEADER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
 
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
 
extern int  screen_width;
extern int  screen_height;
 
extern bool quit;
extern screens screen;
extern bool isrunning;
extern bool mouseMode;
 
bool init();
bool loadMedia();
bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey);
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim);
bool checkCol(SDL_Rect* a, SDL_Rect* b);
void titlescreen();
void gamestart();
void close();
void updatescreen();

 
SDL_Texture* loadTex(std::string path);
 
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
extern SDL_Texture* bosstex;
extern SDL_Texture* optionsToggle[2];


struct gWindow
{
      gWindow();
      
      bool init();

      SDL_Renderer* createRenderer();

      bool handleEvent(SDL_Event &e);

      void free();
      void toggleFullscreen();

      int width;
      int height;

      bool mouseFocus;
      bool keyboardFocus;
      bool fullScreen;
      bool minimized;
      
      SDL_Window* window;
};

extern gWindow win;

struct MainMenue
{
      MainMenue();
      int yVal;
      int xVal;
      int step;
      int buttonW;
      int buttonH;
      int menumin;
      int menumax;
      int prevMousex, prevMousey;


      SDL_Rect bgdim;
      SDL_Rect newGameDim;
      SDL_Rect highScoreDim;
      SDL_Rect aboutDim;
      SDL_Rect optionsDim;
      SDL_Rect helpDim;
      SDL_Rect exitDim;
      SDL_Rect cursorDim;
      //SDL_Rect continueDim;

      void run();
      void updateUI();
      void handleEvent();
      void cursorUpdate(int i);
      void cursorJump(SDL_Rect* r);

};

extern MainMenue mainMenu;

struct About
{
      About();
      SDL_Rect backDim;
      void run();
      void handleEvents();
      void updateUI();
};
extern About about;

struct Help
{
      Help();
      SDL_Rect backDim;
      void run();
      void handleEvents();
      void updateUI();
};
extern Help help;

struct HighScore
{
      HighScore();
      SDL_Rect backDim;
      void run();
      void handleEvents();
      void updateUI();
};
extern HighScore highScore;

struct Options
{
      Options();
      int yVal;
      int xVal;
      int step;
      int buttonW;
      int buttonH;
      int menumin;
      int menumax;
      int prevMousex, prevMousey;


      SDL_Rect cursorDim;
      SDL_Rect bgdim;
      SDL_Rect fullScreenDim;
      SDL_Rect mouseModeDim;
      SDL_Rect backDim;
      
      void run();
      void updateUI();
      void handleEvent();
      void cursorUpdate(int step);
      void cursorJump(SDL_Rect* r);
};    
extern Options options;

struct Pause
{
      Pause();
      int yVal;
      int xVal;
      int step;
      int buttonW;
      int buttonH;
      int menumin;
      int menumax;
      int prevMousex, prevMousey;


      SDL_Rect cursorDim;
      SDL_Rect bgdim;
      SDL_Rect resumeDim;
      SDL_Rect mainMenueDim;
      SDL_Rect exitDim;
      
      void run();
      void updateUI();
      void handleEvent();
      void cursorUpdate(int i);
      void cursorJump(SDL_Rect* r);
};    
extern Pause pause;

struct Player
{
      int width = screen_width/10;
      int height = screen_height/8;
      int xStep = screen_width/50;
      int yStep = screen_height/25;
      int hbspX=screen_width/60, hbspY=screen_height/50;

      SDL_Rect htbx;
      
      int xPos = 0;
      int yPos = screen_height/2-(width/2);
      double angle = 0.0;
      Player();

      void handleEvent();
      void move(int x, int y);
      void render();
};
extern Player player;

struct Boss
{
      int width = screen_width/8;
      int height = screen_height/3;
      int xVel;
      int yVel = screen_height/100;
      int scrolldir=1;

      SDL_Rect htbx;
      
      int xPos = screen_width-width;
      int yPos = screen_height/3;
      Boss();

      void move();
      void render();
};

extern Boss plane;

typedef struct Wall
{
      int width;
      int height;
      int xVel;
      int yVel;
      
      SDL_Rect htbx;

      int xPos;
      int yPos;
      Wall();

      void move();
      void render();
};

extern Wall wall;

struct Walls 
{
      int padding;
      int wall_number;
      Wall wallz[3];
      Walls();
      void move();
      void render();
      void colls();
};

extern Walls walls;

#endif