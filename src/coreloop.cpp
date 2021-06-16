#include "header.hpp"
#include<time.h>

Wall wall;
Walls walls;

Player::Player()
{
      width = screen_width/10;
      height = screen_height/8;
      xStep = screen_width/100;
      yStep = screen_height/80;
      hbspX=screen_width/15, hbspY=screen_height/12;

      xPos = 0;
      yPos = screen_height/2-(width/2);
      angle = 0.0;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
      htbx = {screen_width/60, screen_height/50, width/15, height/12};
};

void Player::render()
{
      SDL_Rect renderQuad = {xPos, yPos, width, height};
      
      SDL_RenderCopyEx(ren, playertex, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);

}
void Player::move(int x, int y){
      xPos+=x*xStep;
      yPos+=y*yStep;
      if(xPos<0) xPos=0;
      else if(xPos+width>screen_width) xPos = screen_width-width;
      if(yPos<0) yPos=0;
      else if(yPos+height>screen_height) yPos=screen_height-height;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
}
void Player::handleEvent()
{
      if(!mouseMode)
      {
            angle=0.0;
            const Uint8* keyState = SDL_GetKeyboardState(NULL);
            if(keyState[SDL_SCANCODE_UP]) yPos-=yStep, angle=330.0;
            else if(keyState[SDL_SCANCODE_DOWN]) yPos+=yStep, angle=30.0;
            if(keyState[SDL_SCANCODE_RIGHT]) xPos+=xStep;
            else if(keyState[SDL_SCANCODE_LEFT]) xPos-=xStep;

            if(xPos<0) xPos=0;
            else if(xPos+width>screen_width) xPos = screen_width-width;
            if(yPos<0) yPos=0;
            else if(yPos+height>screen_height) yPos=screen_height-height;
            htbx.x = xPos + hbspX;
            htbx.y = yPos + hbspY;
      }
      else
      {
            int mousex, mousey;
            int mMouse = SDL_GetMouseState(&mousex, &mousey);
            xPos=mousex, yPos=mousey;
            if(xPos+width>screen_width) xPos = screen_width-width;
            else if(xPos<0) xPos=0; 
            if(yPos+height>screen_height) yPos=screen_height-height;
            else if(yPos<0) yPos=0;
            htbx.x = xPos + hbspX;
            htbx.y = yPos + hbspY;
      }
       
}

Boss::Boss()
{
      width = screen_width/8;
      height = screen_height/3;
      yVel = screen_height/100;
      scrolldir=1;
      
      xPos = screen_width-width;
      yPos = screen_height/3;
      htbx={xPos, yPos, width, height};
}
void Boss::move()
{
      if((yPos<0)||(yPos + height>screen_height))
            scrolldir*=-1;
      yPos+=scrolldir*yVel;
}
void Boss::render()
{
      SDL_Rect renderQuad = {xPos, yPos, width, height};
      SDL_RenderCopyEx(ren, bosstex, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

bool checkCol(SDL_Rect* a, SDL_Rect* b)
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
      if( downA <= topB )
      {
          return false;
      }     
      if( topA >= downB )
      {
          return false;
      }     
      if( rightA <= leftB )
      {
          return false;
      }     
      if( leftA >= rightB )
      {
          return false;
      }
      else return true;
}

Wall::Wall()
{
      width=screen_width/15;
      height=screen_height;
      xVel=10;
      yPos=screen_height/2;
      htbx={xPos, yPos, width, height};
}
void Wall::move()
{
      xPos-=xVel;
      if(xPos+width<=0)
      {
       xPos=screen_width+width;
       double val[10]={1.5, 1, 0.75, 1, 2, 1.2, 1, 1.6, 1.3, 0.8};
       srand(time(0)+wall.yPos);
       yPos=(screen_height/2)*val[rand()%10];
      }
      htbx.x=xPos;
      htbx.y=yPos;
}
void Wall::render()
{     
      SDL_Rect renderQuad = {xPos, yPos, width, height};
      SDL_RenderCopyEx(ren, resumeB, NULL, &htbx, 0.0, NULL, SDL_FLIP_NONE);
}
Walls::Walls()
{
      padding = screen_width/3;
      wall_number=3;
      wallz[0].xPos=screen_width;
      for(int i=0; i<wall_number; i++)
            wallz[i].xPos=wallz[i-1].xPos+padding;
}
void Walls::move()
{
      for(int i=0; i<wall_number; i++)
            wallz[i].move();
}
void Walls::render()
{
      for(int i=0; i<wall_number; i++)
            wallz[i].render();
}
void Walls::colls()
{
      for(int i=0; i<wall_number; i++)
            if(checkCol(&player.htbx, &wallz[i].htbx)) printf("lives should be global\n");
}
void gamestart() 
{
      int lives = 3;
      while (isrunning) {
            SDL_RenderClear(ren);
            SDL_Rect bgdim = {0, 0, screen_width, screen_height};
            //SDL_RenderCopy(ren, inGameBG, NULL, &bgdim);
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                  if (e.type == SDL_QUIT)
                        quit = true, isrunning = false;
                  if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                              case SDLK_ESCAPE:
                                    screen = PAUSE, isrunning = false;
                                    break;
                        }
                  }
            }
            player.handleEvent();
            if(lives<1) screen=MAIN_MENU, isrunning=false;
            player.render();
            plane.move();
            plane.render();
            walls.move();
            walls.render();
            walls.colls();
            if(checkCol(&player.htbx, &plane.htbx)==true) printf("ouch\n"), lives--;
            //if(checkCol(&player.htbx, &wall.htbx)==true) printf("that hurt\n"), lives--;
            SDL_RenderPresent(ren);
            SDL_Delay(1000 / 60);
      }
}
