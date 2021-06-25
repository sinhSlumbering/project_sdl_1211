#ifndef HEADER_H
#define HEADER_H
//Using sdl, sdl image, sdl true type fonts, sdl mixer
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>
//preprocessors
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define POWERUP_N 2
#define POWERUP_INTERVAL 15000
#define PLAYERBULLET_N 5
#define PLAYERBULLET_RATE 300
#define WALL_START_TIME 5000
#define ATTACK_START_TIME 10000
#define POWERUP_START_TIME 3000

//used to keep track of screens
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
 
//screen dimensions
extern int  screen_width;
extern int  screen_height;

//screen dimension multipliers in case of a change in window size
extern float screen_x_frac;
extern float screen_y_frac;

//frametimes to stabilize fps
extern long prevtime;
extern float remaintime;

//player lives
extern int  lives;
//bosshealth
extern int bosshealth;
//game score
extern int score;
//boss phase
extern int phase;

//variable to run main loop
extern bool quit;
//keeps track of current screen
extern screens screen;
//to run core-gameloop
extern bool isrunning;
//to check if the game is running in mouse mode
extern bool mouseMode;
//invinsibility frames on hit and powerup respectively
extern bool Hinvincible, Pinvincible;
//speed of the walls coming at the player
extern int wallspeed;

//initializes the systems
bool init();
//loads texure and sound
bool loadMedia();

//checks to see if mouse is within a certain rectangular area
bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey);
//checks to see if the ingame cursor points to a particular button
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim);

//checks colission
bool checkCol(SDL_Rect* a, SDL_Rect* b);

//runs the titlescreen
void titlescreen();
//runs the gameover screen
void gameoverscreen();
//core gameplay loop
void gamestart();

//destroys texture and files from memory, closes all systems and shuts down
void close();

//grabs the current window dimensions
void updatescreen();

//calculates highscore
void Cal_highscore(int a);

//loads texuture
SDL_Texture *loadTex(std::string path);
void highscore_printing(int a,int x, int y);
void printText(SDL_Renderer *renderer, int x, int y, std::string point,
             SDL_Texture **texture, SDL_Rect *rect, SDL_Color white);

//uses previous frametimes to lock fps in case vsync is not available
void optimizeFPS(long *prevtime, float *remainder);
void save_game(int playerscore, int livesleft, int boss_health, int a, int b, int c, int d, int e, int f);
void play(int *a, int *b, int *c, int *d, int *e, int *f, int *g, int *h, int *i);
void difficulty();

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
void highscoreclear();
void boss_change_phase(SDL_Rect r, SDL_Rect background);

//the game renderer
extern SDL_Renderer* ren;

/*
textures used in the game follow a naming scheme
BG refers to background texture
B refers to button textures
tex is the suffix of game objects
text is the suffix of text rendered on menus
the notable exception being the options toggle and cursor which are self explanatory
and tscreentex used for displaying text on screen
*/
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
extern SDL_Texture* continueB;
extern SDL_Texture* helpB;
extern SDL_Texture* inhelp;
extern SDL_Texture* resumeB;
extern SDL_Texture* exitB;
extern SDL_Texture* cursor;
extern SDL_Texture* playertex[3];
extern SDL_Texture* playerbullet;
extern SDL_Texture* bosstex[2];
extern SDL_Texture* optionsToggle[2];
extern SDL_Texture* cleartex;
extern SDL_Texture* scoretex;
extern SDL_Texture* lifetex;
extern SDL_Texture* dashtex;
extern SDL_Texture* towertex;
extern SDL_Texture* poweruptex[POWERUP_N];
extern SDL_Texture* fireballtex;
extern SDL_Texture* homingtex;
extern SDL_Texture* tscreentex;
extern SDL_Texture* fullScreenText;
extern SDL_Texture* mouseModeText;

extern TTF_Font* font;

extern SDL_Color White;
extern SDL_Color Megenta;

extern SDL_Rect area;
//dimensions of the text on the titlescreen
extern SDL_Rect tscreentextdim;

extern Mix_Music *gBackgroundMusic;
extern Mix_Chunk *gpoint; 
extern Mix_Chunk *gForward;
extern Mix_Chunk *gBackword;
extern Mix_Chunk *ghit;
extern Mix_Chunk *gdie;

//timer that counts up
struct upTimer 
{
      //constructor
      upTimer();
      //used to check if timer is running
      bool running;
      //stores the starting ticks
      Uint32 startTicks; 
      
      //starts the timer
      void start();
      //returns current ticks
      Uint32 getTicks();
      //stops the timer
      void stop();
};
//timers for Invinsibility frames on hit, on dash, on powerup respcetively, followed by timers for player bullets and difficulty
extern upTimer iFrame, cFrame, ptimer, btimer, diffTimer;

//a structure for the window
struct gWindow
{
      //constructor
      gWindow();
      //initializer for the window
      bool init();
      
      //a function to create renderer
      SDL_Renderer* createRenderer();

      //a function to handle window events
      bool handleEvent(SDL_Event &e);
      //frees memory and quits
      void free();
      //toggles fullscreen
      void toggleFullscreen();

      bool mouseFocus;
      bool keyboardFocus;
      bool fullScreen;
      bool minimized;
      
      //window dimensions
      int width;
      int height;
      
      //the window itself      
      SDL_Window* window;
};

//the game window
extern gWindow win;

/*
      Menus have a naming scheme
      
      yVal refers to the height offset for the buttons
      xVal refers to the height offset for the buttons
      step is the the padding between buttons
      buttonW is the width of the buttons
      buttonH is the height of the buttons
      menumin refers to the minimum y value of the buttons, menumax refers to the maximum
      prevMousex, prevMousey are used to record the previous frames mouse position

      SDL_Rects are used to assign dimensions and position to the buttons and the background hence the dim modifier
      
      functions
      the run function runs the current menu
      handleEvent handles keyboard, mouse and window event
      updateUI scales the menus to the current screen size
      cursorUpdate and cursorJump  updates the cursor position

      Any deviations from this will be noted 
      and the 1st one is labled

*/
//The main menu
struct MainMenue
{
      //constructor
      MainMenue();
      //height offset for the 1st button
      int yVal;
      //width offset for the 1st button
      int xVal;
      //the padding between buttons
      int step;
      //button dimensions
      int buttonW;
      int buttonH;
      //menu minimum and maximum heights
      int menumin;
      int menumax;
      //the previous mouse positions
      int prevMousex, prevMousey;

      //dim refers to the dimensions of the buttons
      SDL_Rect bgdim;
      SDL_Rect newGameDim;
      SDL_Rect highScoreDim;
      SDL_Rect aboutDim;
      SDL_Rect optionsDim;
      SDL_Rect helpDim;
      SDL_Rect exitDim;
      SDL_Rect cursorDim;
      SDL_Rect continueDim;

      //runs mainmenu 
      void run();
      //scales UI
      void updateUI();
      //handles window, keyboard and mouse event
      void handleEvent();
      //updates cursor
      void cursorUpdate(int i);
      void cursorJump(SDL_Rect* r);

};
//the main menu
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
      SDL_Rect fullScreenTextDim;
      SDL_Rect mouseModeDim;
      SDL_Rect mouseModeTextDim;
      SDL_Rect clearDim;
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

struct Bulletpos
{
      int x;
      int y;
};

//the player character
struct Player
{
      //dimensions of the player character
      int width;
      int height;
      //movement of the player per frame in both directions
      int xStep;
      int yStep;
      //the spacing of the hitbox inside the player
      int hbspX, hbspY;
      //the current player texture number
      int tex;
      //velocity of of the player bullet and the number
      int bulletVel, bulletIndex;
      //bullet dimensions
      int bulletW, bulletH;
      //controlls bullet fire
      bool fire;

      //Hitbox, player and bullet dimensions and position 
      SDL_Rect htbx;
      SDL_Rect playerdim;
      SDL_Rect bulletdim[PLAYERBULLET_N];
      
      //player position
      int xPos;
      int yPos;
      //player angle
      double angle;
      //constructor
      Player();

      //initalizer
      void init();
      //scales to the current screen size
      void scale();
      //handles the keyboard inputs to move the player
      void handleEvent();
      //moves the player
      void move(int x, int y);
      //player bullet subroutine
      void bullet();
      //renders the player
      void render();
      //checks for collission with the player
      bool col(SDL_Rect*);
};
extern Player player;
/*
      ingame elements also follow a naming scheme
      width and height refers to that elements with and height
      xVel and yVel refers to velocities in the x and y direction
      xPos and yPos refers to positions along the axes
      htbx refers to hitboxes
      all have a Constructor function
      init initalizes the struct
      scale scales the struct to the current screen size
      render renders the elements
      and move moves the elements 

      any deviation or addition is explicitly stated
*/
struct Boss
{
      int width;
      int height;
      int xVel;
      int yVel;
      //determines the direction in which the boss will move
      int scrolldir;
      int xPos;
      int yPos;
      //hitbox itself is used for rendering
      SDL_Rect htbx;
      
      Boss();

      void init();
      void scale();
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
      //used for regulation of difficulty
      int mod;
      //hitbox itself is used for rendering
      SDL_Rect htbx;

      int xPos;
      int yPos;

      Wall();

      void move();
      void render();
};


struct Walls 
{
      //padding between two walls
      int padding;
      //number of wall
      int wall_number;
      //an array of inidividual walls;
      Wall wallz[3];
      Walls();

      void init();
      void scale();
      void move();
      void render();
      //checks collision with walls
      void colls();
};

extern Walls walls;

struct Powerup
{
      //signals spawing 
      bool spawn;
      //signals if a powerup is on screen
      bool running;
      //dimension of a powerup midflight and initially
      SDL_Rect powerupdim, initdim;
      //velocity of the powerup
      int vel;
      //enumerated to help randomization
      enum pUP{
            LIFE,
            INVINCIBILE,
            WAIT
      };
      //current powerup
      int current;

      Powerup();
      
      void init();
      void scale();
      void move();
      //chooses which powerup is active
      void choose();
      //runs the powerup subroutine
      void run();
};

extern Powerup powerup;

//enemy attacks
struct Attack
{
      //controls the spawing of a new attack
      bool spawn;
      //dimension and position of attacks and their hitboxes
      SDL_Rect bouncedim, homedim;
      SDL_Rect bhtbx, hhtbx;
      //velocites in both axes of attacks
      int bXvel, bYvel, hXvel, hYvel;
      //angle of the attack texture
      double angle;
      //enumerated to help randomiztion
      enum att
      {
            BOUNCING,
            HOMING
      };
      //current attack
      int current;

      Attack();
      
      void init();
      void scale();
      void choose();
      //bouncing attack subroutine
      void bounce();
      //homing attack subroutine
      void home();
      //runs the attack subroutine
      void run();
};

extern Attack attack;

#endif