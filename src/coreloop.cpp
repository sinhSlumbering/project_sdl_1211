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

      //initialize scrolling background
      ingamedim[0]={0, 0, screen_width, screen_height};
      ingamedim[1]={-(screen_width), 0, screen_width, screen_height};


      //initalize game variables from a file
      play(&score, &lives, &bosshealth, &walls.wall_number, &attack.bXvel, &attack.bYvel, &wallspeed, &diffThreshold, &phase);
      printf("%d %d %d\n", score, lives, bosshealth);

      //initializing to pre existing position
      player.xPos = xposition;
      player.yPos = yposition;
      walls.wall_number = 0;
      //timer for loading obstacles and attacks
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
                        //pauses the game
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
            //quit if the game has been terminated or ended
            if(!isrunning)break;
            score++;
            Uint32 diff = diffTimer.getTicks();
            //handling the scrolling background
            SDL_RenderCopy(ren, inGameBG, NULL, &ingamedim[0]);
            SDL_RenderCopy(ren, inGameBG, NULL, &ingamedim[1]);
            if (ingamedim[0].x >= screen_width){
                  ingamedim[0]={-screen_width, 0, screen_width, screen_height};
            }
            if (ingamedim[1].x >= screen_width){
                  ingamedim[1]={-screen_width, 0, screen_width, screen_height};
            }
            if(!timeStopped) ingamedim[0].x += screen_width/80, ingamedim[1].x += screen_width/80;

            //the player and enemy subroutines
            player.handleEvent();
            player.render();
            if(!timeStopped)plane.move();
            plane.render();
            player.bullet();

            //subroutine when Invincibility frames are running
            if (iFrame.running)
            {
                  if (iFrame.getTicks() > IFRAME_TIME){
                        iFrame.stop();
                        player.tex = 0;
                        Hinvincible = false;
                  }
                  else if (player.tex == prevtex)
                        player.tex = !prevtex;
                  prevtex = player.tex;
            }
            //handles iframes when dashing
            else if (cFrame.running)
            {
                  Uint32 f = cFrame.getTicks();
                  //handles the player tes
                  if (!Pinvincible){
                        player.tex = 2;
                  }
                  //spaces dashes to avoid spamming
                  if (f > DASH_INTERVAL)
                  {
                        cFrame.stop();
                        if (!Pinvincible){
                              player.tex = 0;
                        }
                  }
                  //handles iframes
                  else if (f > DASH_IFRAME_STOP){
                        Hinvincible = false;
                        dashdim = {screen_width, screen_height, 0, 0};
                  }
                  SDL_RenderCopy(ren, dashtex, NULL, &dashdim);
            }
            //begin powerup, attack and obstacle subroutine when its time
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
            //checks for collission between the enemy and player character
            if (player.col(&plane.htbx) == true)
            {
                  //printf("ouch\n");
                  lives--;
                  if (Mix_PausedMusic() == 0)
                  {
                        Mix_PlayChannel(-1, ghit, 0);
                  }
            }
            //quits when life runs out
            if (lives < 1){
                  screen = MAIN_MENU, isrunning = false, diffTimer.stop(), mainMenu.updateUI();
            }


            //handles game screen hud elements here, the lives score and the boss health
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
            
            //changes boss
            if (bosshealth <= 0)
            {
                  ingamedim[0]={0, 0, screen_width, screen_height};
                  ingamedim[1]={-(screen_width), 0, screen_width, screen_height};
                  boss_change_phase(plane.htbx, ingamedim[0]);
                  bosshealth = 9999;
                  diffThreshold = 9000;
            }
            //modulates difficulty
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
