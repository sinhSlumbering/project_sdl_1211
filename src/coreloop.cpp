#include "header.hpp"
#include<time.h>

Walls walls;
Wall wall;
Boss plane;
Player player;
Powerup powerup;
Attack attack;
int lives = 3;
int hits=0;
bool Hinvincible = false, Pinvincible=false;
int wallspeed=5;
int diffThreshold=8000, diffStep=500;
SDL_Texture* scoretex;
SDL_Texture* lifetex;
SDL_Rect dashdim;
// TTF_Font* font;

// char* font_path = "assets/Sans/Sans.ttf";
int score;
int bosshealth = 9999; 
SDL_Color white = {255, 255, 255, 0};
SDL_Rect area;

Player::Player()
{
      width = screen_width / 10;
      height = screen_height / 8;
      xStep = screen_width / 100;
      yStep = screen_height / 80;
      hbspX = screen_width / 30, hbspY = screen_height / 30;
      
      bulletVel = 20;
      bulletIndex = 0;
      bulletW=player.width/3;
      bulletH=player.height/4;
      fire=true;
      for(int i=0; i<PLAYERBULLET_N; i++) bulletdim[i]={-bulletW, -bulletH, bulletW, bulletH};

      tex=0;

      xPos = 0;
      yPos = screen_height / 2 - ( width / 2 );
      angle = 0.0;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
      htbx.w = screen_width / 35;
      htbx.h = screen_height / 22;
};

void Player::render()
{
      playerdim = { xPos, yPos, width, height };
      SDL_RenderCopyEx(ren, playertex[tex], NULL, &playerdim, angle, NULL, SDL_FLIP_NONE);
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
            if (keyState[SDL_SCANCODE_UP]||keyState[SDL_SCANCODE_W]){
                  yPos -= yStep, angle=330.0;
                  Mix_PlayChannel(-1,gForward,0);
            }
            else if (keyState[SDL_SCANCODE_DOWN]||keyState[SDL_SCANCODE_S]){
                  yPos += yStep, angle=30.0;
                  Mix_PlayChannel(-1,gForward,0);
            }
            if (keyState[SDL_SCANCODE_RIGHT]||keyState[SDL_SCANCODE_D]){
                  xPos += xStep;
                  Mix_PlayChannel(-1,gForward,0);
            }
            else if (keyState[SDL_SCANCODE_LEFT]||keyState[SDL_SCANCODE_A]){
                  xPos -= xStep;
                  Mix_PlayChannel(-1,gForward,0);
            }
            if (keyState[SDL_SCANCODE_SPACE]||keyState[SDL_SCANCODE_0]){ 
                  if(!cFrame.running)
                  {
                        dashdim = {player.xPos, player.yPos, player.width, player.height}; 
                        xPos+=player.width*2;
                        cFrame.start();
                        Hinvincible=true;
                  }
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
void Player::bullet()
{
      if(btimer.running&&btimer.getTicks()>PLAYERBULLET_RATE) fire=true, btimer.stop();
      if(fire)
      {
            if(bulletIndex==PLAYERBULLET_N) bulletIndex=0; 
            bulletdim[bulletIndex].x = player.xPos+player.width;
            bulletdim[bulletIndex].y = player.yPos+player.height/4;
            bulletIndex++;
            btimer.start();
            fire=false;
      }
      for(int i=0; i<PLAYERBULLET_N; i++)
      {
            if(bulletdim[i].x>0)
            {
                  bulletdim[i].x+=bulletVel;
                  if(bulletdim[i].x>screen_width) bulletdim[i].x=-bulletW, bulletdim[i].y=0;
                  else {
                        SDL_RenderCopy(ren, playerbullet, NULL, &bulletdim[i]);
                        if(checkCol(&bulletdim[i], &plane.htbx)) {
                              // printf("enemyhit\n");
                              bosshealth-=5;
                        }
                  }
            }
      }
}
bool Player::col(SDL_Rect* projectile)
{
      bool ret=false;
      if(!Hinvincible&&!Pinvincible){
            ret=checkCol(&htbx, projectile);
            if(ret) iFrame.start(), Hinvincible=true;
      }
      return ret;
}

Boss::Boss()
{
      width = screen_width / 6;
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
      else if( topA >= downB )
      {
      return false;
      }     
      else if( rightA <= leftB )
      {
      return false;
      }     
      else if( leftA >= rightB )
      {
      return false;
      }
      else return true;          
}

Wall::Wall()
{
      width=screen_width/15;
      height=screen_height;
      yPos=screen_height/2;
      htbx={xPos, yPos, width, height};
      mod=5;  
}
void Wall::move()
{
      xPos-=wallspeed;
      if(xPos+width<=0)
      {
            xPos=screen_width+width;
            double val[10]={1.3, 1.5, 2, 1.6, 1.2, 0.9, 0.75, 0.6, 0.85,0.8};
            srand(time(0)+yPos);
            yPos=(screen_height/2)*val[rand()%mod];
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
      wall_number=0;
      wallz[0].xPos=screen_width;
      for(int i=1; i<wall_number; i++)
            wallz[i].xPos=wallz[i-1].xPos+padding;
}

void Walls::move()
{
      for(int i=0; i<wall_number; i++)
            wallz[i].move(), wallz[i].mod=10;
}
void Walls::render()
{
      for(int i=0; i<wall_number; i++)
            wallz[i].render();
}
void Walls::colls()
{
      for(int i=0; i<wall_number; i++)
            if(player.col(&wallz[i].htbx)){
                  lives--;
                  Mix_PlayChannel(-1,ghit,0);
            }
}

Powerup::Powerup()
{
      int width=player.width/2;
      powerupdim = initdim = {screen_width+width*2, screen_height, width, width};
      vel = 5;
      spawn = true;
      running = false;
}
void Powerup::move()
{
      powerupdim.x-=vel;
      if(powerupdim.x+powerupdim.w<0) powerupdim=initdim, spawn=true, running=false, ptimer.start();
      SDL_RenderCopy(ren, poweruptex[current], NULL, &powerupdim);
}

void Powerup::choose()
{
      srand(time(0));
      current = rand();
      powerupdim.y=current%(screen_height);
      current%=POWERUP_N;
      spawn=false;
      running = true;
}

void Powerup::run()
{
      Uint32 time=ptimer.getTicks();
      if(spawn) choose();
      else if(Pinvincible)
      {
            // printf("jsdhfg");
            if(time>10000) Pinvincible=false, player.tex=1, ptimer.stop(), ptimer.start();
      }
      else if(time>POWERUP_INTERVAL) spawn=true, ptimer.stop();
      if(running)
      {
            if(checkCol(&player.playerdim, &powerupdim))
                  {
                        powerupdim=initdim;
                        ptimer.stop();
                        ptimer.start();
                        running=false;
                        if(current==LIFE) {
                              lives++;
                              Mix_PlayChannel(-1,gpoint,0);
                        }
                        if(current==INVINCIBILE){
                              Pinvincible=true;
                              player.tex=1;
                              Mix_PlayChannel(-1,gpoint,0);
                        }

                  }
            else move();
      }
      
}
Attack::Attack()
{
      spawn = true;
      spawned = false;
      int side=screen_width/20, arm=side/1.42;
      bouncedim = homedim = { screen_width, screen_height, side, side };
      bhtbx = hhtbx = {screen_width+arm/2, screen_height+arm/2, arm, arm};
      current = 0;
      bXvel= 5;
      bYvel=-5;
      hXvel=5;
      hYvel=5;
      angle=0.0;
}
void Attack::choose()
{
      srand(time(0));
      current=rand()%2;
      spawn=false;
      spawned = true;
      bouncedim.y=plane.yPos+plane.height/2;
      homedim.y=plane.yPos+plane.height/2;
}
void Attack::bounce()
{
      angle++;
      if(angle>360) angle=0.0;
      if (bouncedim.y<=0||bouncedim.y>=screen_height) bYvel*=-1;
      if (bouncedim.x<=0) 
            spawn=true, bouncedim.x=bouncedim.y=screen_width+bouncedim.w;
      if(player.col(&bouncedim)){
            spawn=true, bouncedim.x=bouncedim.y=screen_width+bouncedim.w, lives--;
            Mix_PlayChannel(-1,ghit,0);
      }
      bouncedim.x-=bXvel, bouncedim.y-=bYvel;
      SDL_RenderCopyEx(ren, fireballtex, NULL, &bouncedim, angle, NULL, SDL_FLIP_NONE);       
}
void Attack::home()
{
      angle++;
      if(angle>360) angle=0.0;
      if (homedim.y>player.htbx.y) homedim.y-=hXvel;
      else if (homedim.y<player.htbx.y) homedim.y+=hXvel;
      else if(homedim.y==player.htbx.y);
      if (homedim.x<=0) 
            spawn=true, homedim.x=homedim.y=screen_width+homedim.w;
      if(player.col(&homedim)){
            spawn=true, homedim.x=homedim.y=screen_width+homedim.w, lives--;
      }
      homedim.x-=bXvel;
      SDL_RenderCopyEx(ren, homingtex, NULL, &homedim, angle, NULL, SDL_FLIP_NONE);       
}
void Attack::run()
{
      if(spawn) choose();
      else if(spawned){
      if(current==BOUNCING) bounce();
      else if(current==HOMING) home();
      }
}
void gamestart() 
{
      // font = TTF_OpenFont(font_path,24);
      SDL_Rect ingamedim;
      ingamedim.h = screen_height;
      ingamedim.w = screen_width;
      ingamedim.x = 0;
      ingamedim.y = 0;

      play(&score, &lives, &bosshealth, &walls.wall_number, &attack.bXvel, &attack.bYvel, &wallspeed);
      printf("%d %d %d\n",score,lives,bosshealth);
      walls.wall_number = 0;
      diffTimer.start();
      Uint32 diff0 = diffTimer.getTicks();
      while (isrunning) {
            SDL_RenderClear(ren);
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                  if (e.type == SDL_QUIT){
                        quit = true, isrunning = false;
                  }
                  if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                              case SDLK_ESCAPE:
                                    screen = PAUSE, isrunning = false, pause.updateUI();
                                    break;
                        }
                  }
            }
            score++;
            Uint32 diff=diffTimer.getTicks();
            if(ingamedim.x>=2124) ingamedim.x =0;
            ingamedim.x+=5;
            SDL_RenderCopy(ren, inGameBG, &ingamedim, NULL);
            player.handleEvent();
            player.render();
            player.bullet();
            if(diff>POWERUP_START_TIME){
                  powerup.run();
            }
            if(diff>ATTACK_START_TIME){
                  attack.run();
            }
            plane.move();
            plane.render();
            if(diff-diff0>WALL_START_TIME){
                  walls.move();
                  walls.render();
                  walls.colls();
            }
            
            if(iFrame.running)
            {
                  if(iFrame.getTicks()>1500) iFrame.stop(), player.tex=0, Hinvincible=false;
                  else if(player.tex==1) player.tex=0;
                  else player.tex=0;
            }
            if(cFrame.running) {
                  Uint32 f=cFrame.getTicks();
                  player.tex=2;
                  if(f>500) 
                        cFrame.stop(), player.tex=0;
                  else if(f>300) Hinvincible=false, dashdim={screen_width,screen_height,0,0};
                  SDL_RenderCopy(ren, dashtex, NULL, &dashdim);
            }
            if(player.col(&plane.htbx)==true){ 
                  printf("ouch\n");
                  lives--;
                  Mix_PlayChannel(-1,ghit,0);
            }
            if(!Pinvincible){
                  player.tex = 0;
            }
            if(lives<1) screen=MAIN_MENU, isrunning=false, diffTimer.stop(), mainMenu.updateUI();
            std::string show_score = "Score: "+std::to_string(score);
            printText(ren, 0, 0, show_score, &scoretex, &area,Megenta);
            SDL_RenderCopy(ren, scoretex, NULL, &area);
            std::string show_lives = "Lives: "+std::to_string(lives);
            printText(ren, 0, area.h, show_lives, &lifetex, &area,Megenta);
            SDL_RenderCopy(ren, lifetex, NULL, &area);
            std::string show_health = "Boss Health: "+std::to_string(bosshealth);
            printText(ren, screen_width-area.w*3, 0, show_health, &lifetex, &area,Megenta);
            SDL_RenderCopy(ren, lifetex, NULL, &area);
            
            //debug hitbox
            //SDL_RenderDrawRect(ren, &player.htbx);
            if(bosshealth<diffThreshold){
                  difficulty();
                  diffThreshold-=diffStep;
            }

            SDL_RenderPresent(ren);
            optimizeFPS(&prevtime, &remaintime);
      }
      Cal_highscore(score);
      player.xPos = 0;
      player.yPos = screen_height/5;
      if(lives==0){
      save_game(0,3,9999,0, 5,-5, 5);
      }
      else{
            save_game(score,lives,bosshealth, walls.wall_number, attack.bXvel,attack.bYvel, wallspeed);
      }
}
