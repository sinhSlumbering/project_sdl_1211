#include "header.hpp"

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
      const Uint8* keyState = SDL_GetKeyboardState(NULL);
      if(keyState[SDL_SCANCODE_UP]) yPos-=yStep;
      else if(keyState[SDL_SCANCODE_DOWN]) yPos+=yStep;
      if(keyState[SDL_SCANCODE_RIGHT]) xPos+=xStep;
      else if(keyState[SDL_SCANCODE_LEFT]) xPos-=xStep;

      if(xPos<0) xPos=0;
      else if(xPos+width>screen_width) xPos = screen_width-width;
      if(yPos<0) yPos=0;
      else if(yPos+height>screen_height) yPos=screen_height-height;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
       
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


void gamestart() {
      int lives = 3;
      while (isrunning) {
            SDL_RenderClear(ren);
            SDL_Rect bgdim = {0, 0, screen_width, screen_height};
            SDL_RenderCopy(ren, inGameBG, NULL, &bgdim);
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                  if (e.type == SDL_QUIT)
                        quit = true, isrunning = false;
                  //player.handleEvent(&e);
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
            plane.render();
            plane.move();
            if(checkCol(&player.htbx, &plane.htbx)==true) printf("ouch\n"), lives--;
            SDL_RenderPresent(ren);
            SDL_Delay(1000 / 120);
      }
}
