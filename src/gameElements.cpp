#include "preprocessor.hpp"
#include "globalvars.hpp"
#include "utills.hpp"
#include "gameElements.hpp"
#include "gameUtills.hpp"
#include "textureMusic.hpp"

Walls walls;
Wall wall;
Boss plane;
Player player;
Powerup powerup;
Attack attack;

//Struct of player
Player::Player()
{
      width = screen_width / 10;
      height = screen_height / 8;
      xStep = screen_width / 100;
      yStep = screen_height / 80;
      hbspX = screen_width / 30, hbspY = screen_height / 30;

      bulletVel = screen_width / 40;
      bulletIndex = 0;
      bulletW = player.width / 3;
      bulletH = player.height / 4;
      fire = true;
      for (int i = 0; i < PLAYERBULLET_N; i++)
            bulletdim[i] = {-bulletW, -bulletH, bulletW, bulletH};

      tex = 0;

      xPos = 0;
      yPos = screen_height / 2 - (width / 2);
      angle = 0.0;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
      htbx.w = screen_width / 35;
      htbx.h = screen_height / 22;
}
//initializes played
void Player::init()
{
      width = screen_width / 10;
      height = screen_height / 8;
      xStep = screen_width / 100;
      yStep = screen_height / 80;
      hbspX = screen_width / 30, hbspY = screen_height / 30;

      bulletVel = screen_width / 40;
      bulletIndex = 0;
      bulletW = player.width / 3;
      bulletH = player.height / 4;
      fire = true;
      for (int i = 0; i < PLAYERBULLET_N; i++)
      {
            bulletdim[i] = {-bulletW, -bulletH, bulletW, bulletH};
      }

      tex = 0;

      xPos = 0;
      yPos = screen_height / 2 - (width / 2);
      angle = 0.0;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
      htbx.w = screen_width / 35;
      htbx.h = screen_height / 22;
}
//scale player to and from full-screen
void Player::scale()
{
      width = screen_width / 10;
      height = screen_height / 8;
      xStep = screen_width / 100;
      yStep = screen_height / 80;
      hbspX = screen_width / 30, hbspY = screen_height / 30;

      bulletVel = screen_width / 40;
      bulletIndex = 0;
      bulletW = player.width / 3;
      bulletH = player.height / 4;
      for (int i = 0; i < PLAYERBULLET_N; i++)
      {
            bulletdim[i] = {-bulletW, -bulletH, bulletW, bulletH};
      }

      scaleIntX(&xPos);
      scaleIntY(&yPos);

      angle = 0.0;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
      htbx.w = screen_width / 35;
      htbx.h = screen_height / 22;
}
//renders player
void Player::render()
{
      playerdim = {xPos, yPos, width, height};
      if (Pinvincible)
            tex = 1;
      SDL_RenderCopyEx(ren, playertex[tex], NULL, &playerdim, angle, NULL, SDL_FLIP_NONE);
}
//handles movement
void Player::handleEvent()
{
      if (!mouseMode)
      {
            angle = 0.0;
            const Uint8 *keyState = SDL_GetKeyboardState(NULL);
            if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W])
            {
                  yPos -= yStep, angle = 330.0;
                  if (Mix_PausedMusic() == 0)
                  {

                        Mix_PlayChannel(-1, gForward, 0);
                  }
            }
            else if (keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S])
            {
                  yPos += yStep, angle = 30.0;
                  if (Mix_PausedMusic() == 0)
                  {
                        Mix_PlayChannel(-1, gForward, 0);
                  }
            }
            if (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D])
            {
                  xPos += xStep;
                  if (Mix_PausedMusic() == 0)
                  {
                        Mix_PlayChannel(-1, gForward, 0);
                  }
            }
            else if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A])
            {
                  xPos -= xStep;
                  if (Mix_PausedMusic() == 0)
                  {
                        Mix_PlayChannel(-1, gForward, 0);
                  }
            }
            if (keyState[SDL_SCANCODE_SPACE] || keyState[SDL_SCANCODE_RCTRL])
            {
                  if (!cFrame.running)
                  {
                        dashdim = {player.xPos, player.yPos, player.width, player.height};
                        xPos += player.width * 2;
                        cFrame.start();
                        Hinvincible = true;
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

//Player weapon
void Player::bullet()
{
      if (btimer.running && btimer.getTicks() > PLAYERBULLET_RATE)
            fire = true, btimer.stop();
      if (fire)
      {
            if (bulletIndex == PLAYERBULLET_N)
                  bulletIndex = 0;
            bulletdim[bulletIndex].x = player.xPos + player.width;
            bulletdim[bulletIndex].y = player.yPos + player.height / 4;
            bulletIndex++;
            btimer.start();
            fire = false;
      }
      for (int i = 0; i < PLAYERBULLET_N; i++)
      {
            if (bulletdim[i].x > 0)
            {
                  bulletdim[i].x += bulletVel;
                  if (bulletdim[i].x > screen_width)
                        bulletdim[i].x = -bulletW, bulletdim[i].y = 0;
                  else
                  {
                        if (checkCol(&bulletdim[i], &plane.htbx))
                        {
                              bosshealth -= PLAYERBULLET_DAMMAGE;
                              hitdim = {plane.htbx.x + plane.htbx.w / 2, bulletdim[i].y, plane.htbx.w / 3, plane.htbx.w / 3};
                              bulletdim[i].x = -bulletW, bulletdim[i].y = 0;

                              SDL_RenderCopy(ren, hittex, NULL, &hitdim);
                        }
                        else
                              SDL_RenderCopy(ren, playerbullet, NULL, &bulletdim[i]);
                  }
            }
      }
}

//player collision detector
bool Player::col(SDL_Rect *projectile)
{
      bool ret = false;
      if (!Hinvincible && !Pinvincible)
      {
            ret = checkCol(&htbx, projectile);
            if (ret)
            {
                  iFrame.start();
                  Hinvincible = true;
                  player.tex = 1;
            }
      }
      return ret;
}

//Struct of boss
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

//initilization function of boss
void Boss::init()
{
      width = screen_width / 6;
      height = screen_height / 3;
      yVel = screen_height / 100;
      scrolldir = 1;

      xPos = screen_width - width;
      yPos = screen_height / 3;
      htbx = {xPos, yPos, width, height};
}
//scales to and from full-screen
void Boss::scale()
{
      htbx.w = screen_width / 6;
      htbx.h = screen_height / 3;
      yVel = screen_height / 100;
      htbx.x = screen_width - htbx.w;
      htbx.y = screen_height / 3;
}

//Boss movement
void Boss::move()
{
      if ((htbx.y < 0) || (htbx.y + htbx.h > screen_height))
      {
            scrolldir *= -1;
      }
      htbx.y += scrolldir * yVel;
}

//Boss rendering function
void Boss::render()
{
      SDL_RenderCopyEx(ren, bosstex[phase], NULL, &htbx, 0.0, NULL, SDL_FLIP_NONE);
}

//Obstacle struct
Wall::Wall()
{
      width = screen_width / 15;
      height = screen_height;
      yPos = screen_height / 2;
      xPos = screen_width;
      htbx = {xPos, yPos, width, height};
      mod = 10;
}

//movement dunction
void Wall::move()
{
      htbx.x -= wallspeed;
      if (htbx.x + htbx.w <= 0)
      {
            htbx.x = screen_width + htbx.w;
            double val[10] = {1, 1.5, 0.9, 1.6, 1.2, 2, 1.8, 0.3, 1.3, 0.8};
            srand(time(0) + yPos);
            double value = (double)(screen_height / 2) * val[rand() % mod];
            htbx.y = (int)value;
      }
      htbx.h = screen_height - htbx.y;
}
//renders obstacle
void Wall::render()
{
      SDL_RenderCopyEx(ren, towertex, NULL, &htbx, 0.0, NULL, SDL_FLIP_NONE);
}

//Struct for multiple walls
Walls::Walls()
{
      padding = screen_width / 3;
      wall_number = 0;
      wallz[0].htbx.x = screen_width;
      for (int i = 1; i < 3; i++)
      {
            wallz[i].htbx.x = wallz[i - 1].htbx.x + wallz[i - 1].htbx.w + padding;
      }
}

//initialization part
void Walls::init()
{
      padding = screen_width / 3;
      wall_number = 0;
      wallz[0].htbx = {screen_width, screen_height / 2, screen_width / 15, screen_height};

      for (int i = 1; i < 3; i++)
      {
            wallz[i].htbx = {wallz[i - 1].htbx.x + wallz[i - 1].htbx.w + padding, screen_height / 2, screen_width / 15, screen_height};
      }
}

//scales to and from full-screen
void Walls::scale()
{
      scaleIntX(&padding);
      for (int i = 0; i < 3; i++)
      {
            scaleRect(&wallz[i].htbx);
      }
}

//movement function
void Walls::move()
{
      for (int i = 0; i < 3; i++)
      {
            wallz[i].move();
      }
}
//renders all the walls
void Walls::render()
{
      for (int i = 0; i < wall_number; i++)
      {
            wallz[i].render();
      }
}

//collision with player checker
void Walls::colls()
{
      for (int i = 0; i < wall_number; i++)
      {
            if (player.col(&wallz[i].htbx))
            {
                  lives--;
                  if (Mix_PausedMusic() == 0)
                  {
                        Mix_PlayChannel(-1, ghit, 0);
                  }
            }
      }
}

//struct for power ups
Powerup::Powerup()
{
      int width = player.width / 2;
      powerupdim = initdim = {screen_width + width * 2, screen_height, width, width};
      vel = POWERUP_VELOCITY;
      spawn = true;
      running = false;
}

//initialization
void Powerup::init()
{
      int width = player.width / 2;
      powerupdim = initdim = {screen_width + width * 2, screen_height, width, width};
      vel = POWERUP_VELOCITY;
      spawn = true;
      running = false;
}

//for scaling to and from full-screen
void Powerup::scale()
{
      int wid = player.width / 2;

      scaleIntX(&powerupdim.x);
      scaleIntX(&initdim.x);
      scaleIntY(&powerupdim.y);
      scaleIntY(&initdim.y);

      powerupdim.h = powerupdim.w = initdim.h = initdim.w = wid;

      scaleIntX(&vel);
}

//movement controller
void Powerup::move()
{
      powerupdim.x -= vel;
      if (powerupdim.x + powerupdim.w < 0)
      {
            powerupdim = initdim;
            spawn = true;
            running = false;
      }
      SDL_RenderCopy(ren, poweruptex[current], NULL, &powerupdim);
}

//for randomly choosing a power up
void Powerup::choose()
{
      srand(time(0));
      current = rand();
      powerupdim.x = screen_width;
      powerupdim.y = current % (screen_height);
      current %= POWERUP_N;
      spawn = false;
      running = true;
}

//For running the power up with just a function
void Powerup::run()
{
      Uint32 time;
      if (spawn)
            choose();
      else if (Pinvincible)
      {
            time = ptimer.getTicks();
            if (time > 10000)
            {
                  Pinvincible = false;
                  player.tex = 0;
                  ptimer.stop();
                  iFrame.start();
                  Hinvincible = true;
            }
      }
      else if (timeStopped)
      {
            time = tstopTimer.getTicks();
            if (time > 5000)
            {
                  timeStopped = false;
                  tstopTimer.stop();
            }
      }
      else if (running == false)
            spawn = true;
      else if (running)
      {
            if (checkCol(&player.playerdim, &powerupdim))
            {
                  powerupdim = initdim;
                  ptimer.stop();
                  ptimer.start();
                  running = false;
                  if (current == LIFE)
                  {
                        lives++;
                        if (Mix_PausedMusic() == 0)
                        {
                              Mix_PlayChannel(-1, gpoint, 0);
                        }
                  }
                  else if (current == INVINCIBILE)
                  {
                        Pinvincible = true;
                        player.tex = 1;
                        if (Mix_PausedMusic() == 0)
                        {
                              Mix_PlayChannel(-1, gpoint, 0);
                        }
                        ptimer.start();
                  }
                  else if (current == TIMESTOP)
                  {
                        timeStopped = true;
                        tstopTimer.start();
                  }
            }
            else
                  move();
      }
}

//enemy attack struct
Attack::Attack()
{
      spawn = true;
      int side = screen_width / 20, arm = side / 1.42;
      bouncedim = homedim = {screen_width, screen_height, side, side};
      bhtbx = hhtbx = bombhtbx = {screen_width + arm / 2, screen_height + arm / 2, arm, arm};
      current = 0;
      bXvel = 5;
      bYvel = -5;
      hXvel = 5;
      hYvel = 5;
      angle = 0.0;
}

//initialization
void Attack::init()
{
      spawn = true;
      int side = screen_width / 20, arm = side / 1.42;
      bouncedim = homedim = bombdim = {screen_width, screen_height, side, side};
      bhtbx = hhtbx = {screen_width + arm / 2, screen_height + arm / 2, arm, arm};
      current = 0;
      bXvel = 5;
      bYvel = -5;
      hXvel = 5;
      hYvel = 5;
      angle = 0.0;
}

//for scaling to and from full-screen
void Attack::scale()
{
      int side = screen_width / 20, arm = side / 1.42;

      scaleIntX(&bouncedim.x);
      scaleIntY(&bouncedim.y);

      homedim.w = homedim.h = bouncedim.h = bouncedim.w = side;

      scaleIntX(&homedim.x);
      scaleIntY(&homedim.y);
      scaleIntX(&bhtbx.x);
      scaleIntY(&bhtbx.y);

      hhtbx.w = hhtbx.h = bhtbx.h = bhtbx.w = arm;

      scaleIntX(&hhtbx.x);
      scaleIntY(&hhtbx.y);
      scaleIntX(&bXvel);
      scaleIntX(&hXvel);
      scaleIntX(&bYvel);
      scaleIntX(&hYvel);
}

//Randomly choosing a attack type
void Attack::choose()
{
      srand(time(0));
      if (phase == 1)
      {
            current = rand() % 3;
      }
      else
            current = rand() % 2;
      spawn = false;
      homedim.y = bouncedim.y = bombdim.y = plane.htbx.y + plane.height / 2;
      homedim.x = bouncedim.x = bombdim.x = plane.htbx.x;
}

//this attack bounces
void Attack::bounce()
{
      angle++;
      if (angle > 360)
            angle = 0.0;
      if (bouncedim.y <= 0 || bouncedim.y >= screen_height)
            bYvel *= -1;
      if (bouncedim.x <= 0)
      {
            spawn = true;
            bouncedim.x = bouncedim.y = screen_width + bouncedim.w;
      }
      if (player.col(&bouncedim))
      {
            spawn = true;
            bouncedim.x = bouncedim.y = screen_width + bouncedim.w;
            lives--;
            if (Mix_PausedMusic() == 0)
            {
                  Mix_PlayChannel(-1, ghit, 0);
            }
      }
      if (!timeStopped)
      {
            bouncedim.x -= bXvel;
            bouncedim.y -= bYvel;
      }
      SDL_RenderCopyEx(ren, fireballtex, NULL, &bouncedim, angle, NULL, SDL_FLIP_NONE);
}

//This is a fast bomb
void Attack::bomb()
{
      if (bombdim.x <= 0)
      {
            spawn = true, bombdim = {0, 0, screen_width / 15, screen_width / 15};
      }
      if (player.col(&bombdim))
      {
            spawn = true, bombdim = {0, 0, screen_width / 15, screen_width / 15}, lives--;
            if (Mix_PausedMusic() == 0)
            {
                  Mix_PlayChannel(-1, ghit, 0);
            }
      }
      if (!timeStopped)
            bombdim.x -= 3 * bXvel;
      SDL_RenderCopyEx(ren, Bombtex, NULL, &bombdim, 0.0, NULL, SDL_FLIP_NONE);
}

//this projectile has homing
void Attack::home()
{
      angle++;
      if (angle > 360)
            angle = 0.0;

      if (!timeStopped)
      {
            if (homedim.y > player.htbx.y)
                  homedim.y -= hXvel;
            else if (homedim.y < player.htbx.y)
                  homedim.y += hXvel;
      }
      else if (homedim.y == player.htbx.y)
            ;
      if (homedim.x <= 0)
      {
            spawn = true;
            homedim.x = homedim.y = screen_width + homedim.w;
      }
      if (player.col(&homedim))
      {
            spawn = true;
            homedim.x = homedim.y = screen_width + homedim.w;
            lives--;
            if (Mix_PausedMusic() == 0)
            {
                  Mix_PlayChannel(-1, ghit, 0);
            }
      }
      if (!timeStopped)
            homedim.x -= bXvel;
      SDL_RenderCopyEx(ren, homingtex, NULL, &homedim, angle, NULL, SDL_FLIP_NONE);
}
void Attack::run()
{
      if (spawn)
            choose();
      else
      {
            if (current == BOUNCING)
                  bounce();
            else if (current == HOMING)
                  home();
            else
                  bomb();
      }
}