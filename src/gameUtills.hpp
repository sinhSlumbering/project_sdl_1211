#ifndef GAMEUTILLS_H
#define GAMEUTILLS_H

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
extern upTimer iFrame, cFrame, ptimer, btimer, diffTimer, tstopTimer;


extern int diffThreshold, diffStep;
extern bool prevtex;
extern bool timeStopped;
extern SDL_Rect dashdim;
extern SDL_Rect hitdim;
extern SDL_Rect ingamedim[2];
//calculates highscore
void Cal_highscore(int a);
//prints highscore
void highscore_printing(int a,int x, int y);
//handles game difficulty
void difficulty();
//changes boss phase
void boss_change_phase(SDL_Rect r, SDL_Rect background);
//checks colission
bool checkCol(SDL_Rect* a, SDL_Rect* b);
//scales game elements
void scaleGame();
//initializes game elements
void initGame();

#endif