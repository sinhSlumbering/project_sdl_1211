#ifndef MENU_H
#define MENU_H

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
      SDL_Rect musicDim;
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
//checks if mouse is inside the given rect
bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey);
//checks if the cursor points to the given rect
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim);
//runs the titlescreen
void titlescreen();
//runs the gameover screen
void gameoverscreen();

#endif