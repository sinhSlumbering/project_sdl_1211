#ifndef GLOBALVARS_H
#define GLOBALVARS_H


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

//the game renderer
extern SDL_Renderer* ren;

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

extern TTF_Font* font;

extern SDL_Color White;
extern SDL_Color Megenta;

extern SDL_Rect area;
//dimensions of the text on the titlescreen
extern SDL_Rect tscreentextdim;

//core gameplay loop
void gamestart();

#endif