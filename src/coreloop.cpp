#include "preprocessor.hpp"
#include "textureMusic.hpp"
#include "globalvars.hpp"
#include "utills.hpp"
#include "menu.hpp"
#include "gameElements.hpp"
#include "gameUtills.hpp"

void gamestart()
{
      Hinvincible = Pinvincible = false;
      ingamedim[0]={0, 0, screen_width, screen_height};
      ingamedim[1]={-(screen_width), 0, screen_width, screen_height};
      play(&score, &lives, &bosshealth, &walls.wall_number, &attack.bXvel, &attack.bYvel, &wallspeed, &diffThreshold, &phase);
      printf("%d %d %d\n", score, lives, bosshealth);
      player.xPos = xposition;
      player.yPos = yposition;
      walls.wall_number = 0;
      diffTimer.start();
      Uint32 diff0 = diffTimer.getTicks();
      //initGame();
      while (isrunning)
      {
            SDL_RenderClear(ren);
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0)
            {
                  if (e.type == SDL_QUIT)
                  {
                        quit = true, isrunning = false;
                  }
                  else if (win.handleEvent(e))
                        scaleGame();
                  else if (e.type == SDL_KEYDOWN)
                  {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                              // screen = PAUSE, isrunning = false, pause.updateUI();
                              Pause_the_game();
                              break;
                        case SDLK_o:
                              if (Mix_PausedMusic() == 1)
                              {
                                    Mix_ResumeMusic();
                              }
                              else
                              {
                                    Mix_PauseMusic();
                              }
                              break;
                        }
                  }
            }
            if(!isrunning)break;
            score++;
            Uint32 diff = diffTimer.getTicks();
            SDL_RenderCopy(ren, inGameBG, NULL, &ingamedim[0]);
            SDL_RenderCopy(ren, inGameBG, NULL, &ingamedim[1]);
            if (ingamedim[0].x >= screen_width)
                  ingamedim[0]={-screen_width, 0, screen_width, screen_height};
            if (ingamedim[1].x >= screen_width)
                  ingamedim[1]={-screen_width, 0, screen_width, screen_height};
            if(!timeStopped) ingamedim[0].x += screen_width/80, ingamedim[1].x += screen_width/80;

            player.handleEvent();
            player.render();
            if(!timeStopped)plane.move();
            plane.render();
            player.bullet();

            if (iFrame.running)
            {
                  if (iFrame.getTicks() > 1500)
                        iFrame.stop(), player.tex = 0, Hinvincible = false;
                  else if (player.tex == prevtex)
                        player.tex = !prevtex;
                  prevtex = player.tex;
            }
            else if (cFrame.running)
            {
                  Uint32 f = cFrame.getTicks();
                  if (!Pinvincible)
                        player.tex = 2;
                  if (f > 500)
                  {
                        cFrame.stop();
                        if (!Pinvincible)
                              player.tex = 0;
                  }
                  else if (f > 300)
                        Hinvincible = false, dashdim = {screen_width, screen_height, 0, 0};
                  SDL_RenderCopy(ren, dashtex, NULL, &dashdim);
            }
            if (diff > POWERUP_START_TIME)
            {
                  powerup.run();
            }
            if (diff > ATTACK_START_TIME)
            {
                  attack.run();
            }
            if (diff > WALL_START_TIME)
            {
                  if(!timeStopped) walls.move();
                  walls.render();
                  walls.colls();
            }
            if (player.col(&plane.htbx) == true)
            {
                  //printf("ouch\n");
                  lives--;
                  if (Mix_PausedMusic() == 0)
                  {
                        Mix_PlayChannel(-1, ghit, 0);
                  }
            }
            if (lives < 1)
                  screen = MAIN_MENU, isrunning = false, diffTimer.stop(), mainMenu.updateUI();
            std::string show_score = "Score: " + std::to_string(score);
            printText(ren, 0, 0, show_score, &scoretex, &area, Megenta);
            SDL_RenderCopy(ren, scoretex, NULL, &area);
            std::string show_lives = "Lives: " + std::to_string(lives);
            printText(ren, 0, area.h, show_lives, &lifetex, &area, Megenta);
            SDL_RenderCopy(ren, lifetex, NULL, &area);
            std::string show_health = "Boss Health: " + std::to_string(bosshealth);
            printText(ren, screen_width - area.w * 3, 0, show_health, &lifetex, &area, Megenta);
            SDL_RenderCopy(ren, lifetex, NULL, &area);

            //debug hitbox
            //SDL_RenderDrawRect(ren, &player.htbx);
            if (bosshealth <= 0)
            {
                  // ingamedim[0]={0, 0, screen_width, screen_height};
                  // ingamedim[1]={-(screen_width), 0, screen_width, screen_height};
                  boss_change_phase(plane.htbx, ingamedim[0]);
                  bosshealth = 9999;
                  diffThreshold = 9000;
            }
            if (bosshealth < diffThreshold)
            {
                  difficulty();
                  diffThreshold -= diffStep;
            }

            SDL_RenderPresent(ren);
            optimizeFPS(&prevtime, &remaintime);
      }
      Cal_highscore(score);
      if (lives == 0)
      {
            save_game(0, 3, 9999, 0, 5, -5, 5, 9000, 0);
            screen = GAME_OVER;
            xposition = 0;
            yposition = screen_height / 2 - ( screen_width / 20 );
      }
      else
      {
            save_game(score, lives, bosshealth, walls.wall_number, attack.bXvel, attack.bYvel, wallspeed, diffThreshold, phase);
            xposition = player.xPos;
            yposition = player.yPos;
      }
}
