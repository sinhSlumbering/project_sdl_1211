#include "preprocessor.hpp"
#include "globalvars.hpp"
#include "utills.hpp"
#include "gameElements.hpp"
#include "gameUtills.hpp"
#include "textureMusic.hpp"


upTimer iFrame, cFrame, ptimer, btimer, diffTimer, tstopTimer;

int lives = 3;
bool Hinvincible = false, Pinvincible=false, timeStopped=false;
bool prevtex = 0;
int wallspeed = 5;
int diffThreshold = 9000, diffStep = 1000;
SDL_Texture* scoretex;
SDL_Texture* lifetex;
SDL_Rect dashdim;
SDL_Rect hitdim;

int score;
int bosshealth = 9999; 
SDL_Color white = {255, 255, 255, 0};
SDL_Rect area;

upTimer::upTimer()
{
      running=false;
}
void upTimer::start()
{
      running = true;
      startTicks=SDL_GetTicks();
}
Uint32 upTimer::getTicks()
{
      return SDL_GetTicks() - startTicks;
}
void upTimer::stop()
{
      running=false;
      startTicks=0;
}

//collisiong checker
bool checkCol(SDL_Rect *a, SDL_Rect *b)
{
      int leftA, leftB;
      int rightA, rightB;
      int topA, topB;
      int downA, downB;
      leftA = a->x;
      rightA = a->x + a->w;
      topA = a->y;
      downA = a->y + a->h;
      leftB = b->x;
      rightB = b->x + b->w;
      topB = b->y;
      downB = b->y + b->h;
      if (downA <= topB)
      {
            return false;
      }
      else if (topA >= downB)
      {
            return false;
      }
      else if (rightA <= leftB)
      {
            return false;
      }
      else if (leftA >= rightB)
      {
            return false;
      }
      else
            return true;
}
// Stores top 10 scores in a file
void Cal_highscore(int a)
{
      FILE *fptr;
      int num[11];

      num[10] = a;
      int b;
      fptr = fopen("assets/highscore.txt", "r");
      int i = 0;
      while ((b = getw(fptr)) != EOF)
      {
            num[i] = b;
            // printf("%d ",num[i]);
            i++;
      }
      int num2[10];
      for (int i = 0; i < 10; i++)
      {
            for (int j = 0; j < 10 - i; j++)
            {
                  if (num[j] > num[j + 1])
                  {
                        int swap = num[j];
                        num[j] = num[j + 1];
                        num[j + 1] = swap;
                  }
            }
      }
      for (i = 0; i < 10; i++)
      {
            num2[i] = num[10 - i];
      }
      fclose(fptr);
      remove("assets/highscore.txt");
      fptr = fopen("assets/highscore.txt", "w");
      for (int i = 0; i < 10; i++)
      {
            putw(num2[i], fptr);
      }
      fclose(fptr);
}
//Prints highscores using printtext
void highscore_printing(int a, int x, int y)
{

      std::string show = std::to_string(a);
      printText(ren, x, y, show, &scoretex, &area, White);
      SDL_RenderCopy(ren, scoretex, NULL, &area);
}
//increases difficulty as boss health decreases
void difficulty(){
      if(walls.wall_number >= 3)
      {
            wallspeed += 1;
      }
      else walls.wall_number++, walls.wallz[walls.wall_number-1].xPos=walls.wallz[walls.wall_number-2].xPos+walls.padding;
      if(attack.bXvel < 0){
            attack.bXvel -= 2;
      }
      else{
            attack.bXvel += 2;
      }
      if(attack.bYvel < 0){
            attack.bYvel -= 2;
      }
      else{
            attack.bYvel += 2;
      } 
      //printf("\nwall %d\n", walls.wall_number);
}
void boss_change_phase(SDL_Rect r, SDL_Rect background){
      SDL_Rect source = {0,0,441, 689};
      int speed = screen_width/160;
      int step = (133+speed-1)/speed;
      int speed2 = 441/step;
      while (r.x < 800)
      {
            SDL_RenderClear(ren);
            SDL_RenderCopy(ren, inGameBG, &background, NULL);
            SDL_RenderCopy(ren,bosstex[phase],&source,&r);
            SDL_RenderPresent(ren);
            r.x+=speed;
            r.w-=speed;
            source.w-=speed2;
            if(r.x >= 800){
                  r.x = 800;
                  r.w = 0;
            }
            if(source.w <= 0){
                  source.w = 0;
            }
            SDL_Delay(60);
      }
      phase = 1;
      while (r.x > 667)
      {
            SDL_RenderClear(ren);
            player.render();
            SDL_RenderCopy(ren, inGameBG, &background, NULL);
            walls.render();
            SDL_RenderCopy(ren,bosstex[phase],&source,&r);
            SDL_RenderPresent(ren);
            r.x-=speed;
            r.w+=speed;
            source.w+=speed2;
            if(r.x <= 667){
                  r.x = 667;
                  r.w = 133;
            }
            if(source.w >= 441){
                  source.w = 441;
            }
            SDL_Delay(60);
      }
}
//scales the game.
void scaleGame()
{
      player.scale();
      plane.scale();
      walls.scale();
      powerup.scale();
      attack.scale();
      //ingamedim={0,0, screen_width, screen_height};
}
void initGame()
{
      plane.init();
      player.init();
      powerup.init();
      walls.init();
      attack.init();
}