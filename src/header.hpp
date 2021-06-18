#ifndef HEADER_H
#define HEADER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define POWERUP_N 2
#define POWERUP_INTERVAL 15000

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
extern int  lives;
 
extern bool quit;
extern screens screen;
extern bool isrunning;
extern bool mouseMode;
extern bool invincible;
 
bool init();
bool loadMedia();
bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey);
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim);
bool checkCol(SDL_Rect* a, SDL_Rect* b);
void titlescreen();
void gamestart();
void close();
void updatescreen();
void Cal_highscore(int a);
SDL_Texture *loadTex(std::string path);
void highscore_printing(int a,int x, int y);
void printText(SDL_Renderer *renderer, int x, int y, std::string point,
             TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect);


extern SDL_Renderer* ren;
extern SDL_Texture* titleBG;
extern SDL_Texture* mainMenuBG;
extern SDL_Texture* pauseBG;
extern SDL_Texture* aboutBG;
extern SDL_Texture* inGameBG;
extern SDL_Texture* backB;
extern SDL_Texture* highScoreB;
extern SDL_Texture* highScoreBG;
extern SDL_Texture* OptionsB;
extern SDL_Texture* FullScreenB;
extern SDL_Texture* MouseModeB;
extern SDL_Texture* pausenewB;
extern SDL_Texture* pauseexitB;
extern SDL_Texture* aboutB;
extern SDL_Texture* newGameB;
extern SDL_Texture* helpB;
extern SDL_Texture* resumeB;
extern SDL_Texture* exitB;
extern SDL_Texture* cursor;
extern SDL_Texture* playertex[2];
extern SDL_Texture* bosstex;
extern SDL_Texture* optionsToggle[2];
extern SDL_Texture* scoretex;
extern SDL_Texture* lifetex;
extern SDL_Texture* dashtex;
extern SDL_Texture* towertex;
extern SDL_Texture* poweruptex[POWERUP_N];

extern TTF_Font* font;

extern SDL_Rect area;

extern Mix_Music *gBackgroundMusic;
extern Mix_Chunk *gScratch; 
extern Mix_Chunk *gForward;
extern Mix_Chunk *gBackword;
extern Mix_Chunk *ghit;
extern Mix_Chunk *gdie;

struct upTimer 
{
      upTimer();

      bool running;
      Uint32 startTicks; 
      
      void start();
      Uint32 getTicks();
      void stop();
};

extern upTimer iFrame, cFrame, ptimer;

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
      bool tex;

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

struct Wall
{
      int width;
      int height;
      int xVel;
      int yVel;
      //double val[10];
      
      SDL_Rect htbx;

      int xPos;
      int yPos;
      int yGround;
      Wall();

      void move();
      void render();
};

struct Walls 
{
      int padding;
      int wall_number;
      Wall wallz[3];
      Walls();

      Walls(int pad);
      void move();
      void render();
      void colls();
};

extern Walls walls;

// struct Bullet 
// {
//       int xVel;
//       int yVel;
//       SDL_Rect dim;

//       Bullet(int xV, int yV, int w, int h);
//       void move();
//       void init();
//       void col();
// };

// struct Battack
// {
//       Bullet fireball(int xV, int yV, int w, int h);
//       upTimer interval;
//       bool fire;

//       Battack();
//       void execute();
// };

// extern Battack attack;

struct Entity
{
      int x;
      int y;
      int xVel;
      int yVel;

      void checkCol();
};

struct Powerup
{
      bool spawn;
      bool running;
      SDL_Rect powerupdim, initdim;
      int vel;
      enum pUP{
            LIFE,
            INVINCIBILE,
            WAIT
      };
      int current;

      Powerup();
      void move();
      void choose();
      void run();
};

extern Powerup powerup;

#endif