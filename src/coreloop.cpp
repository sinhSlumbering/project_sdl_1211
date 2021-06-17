#include "header.hpp"
#include<time.h>

Walls walls;
Boss plane;
Player player;
SDL_Rect dashdim;
//Battack attack;
int lives = 3;
int hits=0;
bool invincible = false;
SDL_Texture* scoretex;
SDL_Texture* lifetex;
TTF_Font* font;

char* font_path = "assets/Sans/Sans.ttf";
int score = 0; 
SDL_Color white = {255, 255, 255, 0};
SDL_Rect area;

Player::Player()
{
      width = screen_width / 10;
      height = screen_height / 8;
      xStep = screen_width / 100;
      yStep = screen_height / 80;
      hbspX = screen_width / 15, hbspY = screen_height / 12;

      tex=0;
      xPos = 0;

      yPos = screen_height / 2 - ( width / 2 );
      angle = 0.0;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
      htbx = { screen_width / 60, screen_height / 50, width / 15, height / 12 };
};

void Player::render()
{
      SDL_Rect renderQuad = { xPos, yPos, width, height };
      SDL_RenderCopyEx(ren, playertex[tex], NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
}
void Player::move(int x, int y)
{
      xPos += x * xStep;
      yPos += y * yStep;
      if (xPos < 0)
            xPos = 0;
      else if (xPos + width > screen_width)
            xPos = screen_width - width;
      if (yPos < 0)
            yPos = 0;
      else if (yPos + height > screen_height)
            yPos = screen_height - height;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
}
void Player::handleEvent()
{
      if ( !mouseMode )
      {
            angle=0.0;
            const Uint8 *keyState = SDL_GetKeyboardState(NULL);
            if (keyState[SDL_SCANCODE_UP]||keyState[SDL_SCANCODE_W])
                  yPos -= yStep, angle=330.0;
            else if (keyState[SDL_SCANCODE_DOWN]||keyState[SDL_SCANCODE_S])
                  yPos += yStep, angle=30.0;
            if (keyState[SDL_SCANCODE_RIGHT]||keyState[SDL_SCANCODE_D])
                  xPos += xStep;
            else if (keyState[SDL_SCANCODE_LEFT]||keyState[SDL_SCANCODE_A])
                  xPos -= xStep;
            if (keyState[SDL_SCANCODE_SPACE]||keyState[SDL_SCANCODE_0]) 
                  if(!cFrame.running)
                       {
                              dashdim = {player.xPos, player.yPos, player.width, player.height}; 
                              xPos+=player.width*3/2;
                              cFrame.start();
                              invincible=true;
                       }

            if (xPos < 0)
                  xPos = 0;
            else if (xPos + width > screen_width)
                  xPos = screen_width - width;
            if (yPos < 0)
                  yPos = 0;
            else if (yPos + height > screen_height)
                  yPos = screen_height - height;

            htbx.x = xPos + hbspX;
            htbx.y = yPos + hbspY;
      }
      else
      {
            int mousex, mousey;
            int mMouse = SDL_GetMouseState(&mousex, &mousey);
            xPos = mousex, yPos = mousey;
            if (xPos + width > screen_width)
                  xPos = screen_width - width;
            else if (xPos < 0)
                  xPos = 0;
            if (yPos + height > screen_height)
                  yPos = screen_height - height;
            else if (yPos < 0)
                  yPos = 0;
            htbx.x = xPos + hbspX;
            htbx.y = yPos + hbspY;
      }
       
}

Boss::Boss()
{
      width = screen_width / 8;
      height = screen_height / 3;
      yVel = screen_height / 100;
      scrolldir = 1;

      xPos = screen_width - width;
      yPos = screen_height / 3;
      htbx = {xPos, yPos, width, height};
}
void Boss::move()
{
      if ((yPos < 0) || (yPos + height > screen_height))
            scrolldir *= -1;
      htbx.y = yPos += scrolldir*yVel;
}
void Boss::render()
{
      SDL_Rect renderQuad = {xPos, yPos, width, height};
      SDL_RenderCopyEx(ren, bosstex, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

// void Scoring(SDL_Renderer *renderer, int x, int y, std::string point,
//         TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
//     int text_width;
//     int text_height;
//     SDL_Surface *surface;
//     SDL_Color white = {255, 255, 255, 0};
//     surface = TTF_RenderText_Solid(font, point.c_str(), white);
//     *texture = SDL_CreateTextureFromSurface(renderer, surface);
//     text_width = surface->w;
//     text_height = surface->h;
//     SDL_FreeSurface(surface);
//     rect->x = x;
//     rect->y = y;
//     rect->w = text_width;
//     rect->h = text_height;
// }

bool checkCol(SDL_Rect* a, SDL_Rect* b)
{

      bool ret=false;
      if(!invincible)
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
            ret=false;
            }     
            else if( topA >= downB )
            {
            ret=false;
            }     
            else if( rightA <= leftB )
            {
            ret=false;
            }     
            else if( leftA >= rightB )
            {
            ret=false;
            }
            else ret=true;
            
      }
      if(ret) iFrame.start(), invincible=true;
      return ret;
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
       double val[10]={1.3, 1.5, 0.75, 0.6, 2, 1.6, 0.85, 0.9, 1.2, 0.8};
       srand(time(0)+yPos);
       yPos=(screen_height/2)*val[rand()%10];
      }
      htbx.x=xPos;
      htbx.y=yPos;
      htbx.h=screen_height-htbx.y;
}
void Wall::render()
{     
      SDL_RenderCopyEx(ren, towertex, NULL, &htbx, 0.0, NULL, SDL_FLIP_NONE);
}
Walls::Walls()
{
      padding = screen_width/3;
      wall_number=3;
      wallz[0].xPos=screen_width;
      for(int i=0; i<wall_number; i++)
            wallz[i].xPos=wallz[i-1].xPos+padding;
}
// Walls::Walls(int pad)
// {
//       padding = pad;
//       wall_number=3;
//       wallz[0].xPos=screen_width;
//       for(int i=0; i<wall_number; i++)
//             wallz[i].xPos=wallz[i-1].xPos+padding;
// }
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
            if(checkCol(&player.htbx, &wallz[i].htbx)) printf("lives should be global %d\n", hits++);
}
// Bullet::Bullet(int xV, int yV, int w, int h)
// {
//       dim={screen_width, screen_height, w, h};
//       xVel=xV;
//       yVel=yV;
// }
// void Bullet::move()
// {
//       dim.x-=xVel;
//       dim.y-=yVel;
// }
// Battack::Battack()
// {
//       fireball(10, 10, screen_width/60, screen_width/60);
//       fire=true;
// }
// void Battack::execute()
// {
//       if(fire)
//       {
//             fireball->dim.y=plane.xPos+plane.height/2;
//       }
// }
void gamestart() 
{
      font = TTF_OpenFont(font_path,24);
      SDL_Rect ingamedim;
      ingamedim.h = screen_height;
      ingamedim.w = screen_width;
      ingamedim.x = 0;
      ingamedim.y = 0;

      while (isrunning) {
            SDL_RenderClear(ren);
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
            score++;
            if(ingamedim.x>=2560) ingamedim.x =0;
            ingamedim.x+=5;
            SDL_RenderCopy(ren, inGameBG, &ingamedim, NULL);
            player.handleEvent();
            player.render();
            plane.move();
            plane.render();
            walls.move();
            walls.render();
            walls.colls();
            if(checkCol(&player.htbx, &plane.htbx)==true) printf("ouch\n"), lives--;
            if(iFrame.running)
            {
                  if(iFrame.getTicks()>1500) iFrame.stop(), player.tex=0, invincible=false;
                  else player.tex=(!player.tex);
            }
            if(cFrame.running) {
                  if(cFrame.getTicks()>300) cFrame.stop();
                  invincible=false;
                  SDL_RenderCopy(ren, dashtex, NULL, &dashdim);
            }
            if(lives<1) screen=MAIN_MENU, isrunning=false;
            std::string show_score = "Score: "+std::to_string(score);
            textCreate(ren, 0, 0, show_score, font, &scoretex, &area);
            SDL_RenderCopy(ren, scoretex, NULL, &area);
            std::string show_lives = "Lives: "+std::to_string(lives);
            textCreate(ren, 0, area.h, show_lives, font, &lifetex, &area);
            SDL_RenderCopy(ren, lifetex, NULL, &area);

            SDL_RenderPresent(ren);
            SDL_Delay(1000 / 60);
      }
}
