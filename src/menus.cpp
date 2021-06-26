#include "preprocessor.hpp"
#include "menu.hpp"
#include "textureMusic.hpp"
#include "globalvars.hpp"
#include "utills.hpp"
#include "gameElements.hpp"
#include "gameUtills.hpp"

int xposition = 0;
int yposition = screen_height / 2 - ( screen_width / 20 );

About about;
Help help;
HighScore highScore;
Pause pause;
MainMenue mainMenu;
Options options;

SDL_Rect tscreentextdim={screen_width/3, screen_height-(screen_height/8)*2, screen_width/2, screen_height/8};

bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey) {
      return (mousex >= rect->x && mousex <= rect->x + rect->w) && (mousey >= rect->y && mousey <= rect->y + rect->h);
}
 
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim) {
      return (cursorDim->y >= rect->y) && ((cursorDim->h + cursorDim->y) <= (rect->y + rect->h));
}

void titlescreen() {
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, titleBG, NULL, NULL);
      font = TTF_OpenFont("assets/Sans/Sans.ttf", 24);
      printText(ren, screen_width/3, screen_height-screen_height/4, "Press any key to continue", &tscreentex, &tscreentextdim, White); 
      SDL_RenderCopy(ren, tscreentex, NULL, &tscreentextdim);
      SDL_RenderPresent(ren);
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN)
                  screen = MAIN_MENU, mainMenu.updateUI();
            else if (e.type == SDL_MOUSEBUTTONDOWN)
                  screen = MAIN_MENU, mainMenu.updateUI();
      }
}

void gameoverscreen()
{
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN)
                  screen = MAIN_MENU, mainMenu.updateUI();
            else if (e.type == SDL_MOUSEBUTTONDOWN)
                  screen = MAIN_MENU, mainMenu.updateUI();
      }
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, gameoverBG, NULL, NULL);
      std::string yourscore = "Your Score: "+ std::to_string(score);
      printText(ren,screen_width/2 - screen_width/10, screen_height/2 - screen_height/20, yourscore, &tscreentex, &tscreentextdim,White);
      SDL_RenderCopy(ren,tscreentex, NULL, &tscreentextdim);
      printText(ren, screen_width/3, screen_height-screen_height/4, "Press any key to continue", &tscreentex, &tscreentextdim, Megenta); 
      SDL_RenderCopy(ren, tscreentex, NULL, &tscreentextdim);
      SDL_RenderPresent(ren);
      SDL_Delay(1000/60);
}


MainMenue::MainMenue()
{
      //1st button y position and menus minimum position
      yVal = menumin = screen_height / 20; 
      //the padding between the buttons
      step = screen_height / 10;
      // printf("%d\n",yVal);
      //button dimensions
      buttonH = screen_height / 20;
      buttonW = screen_width / 6;
      //the buttons xvalues 
      xVal=screen_width-buttonW-buttonW/3;
      //max value of the menue found by multiplying the padding with the number of elements
      menumax = 7 * screen_height / 10;
      //background dimension
      bgdim = {0, 0, screen_width, screen_height};
      //cursordimensions
      cursorDim.w = screen_width / 40;
      cursorDim.h = screen_height / 20;
      cursorDim.x = xVal-cursorDim.w;
      cursorDim.y = yVal;
      //button dimensions
      newGameDim = {xVal, yVal, buttonW, buttonH};
      //offset by padding and continued
      yVal+=step;
      continueDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      highScoreDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      optionsDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      helpDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      aboutDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      exitDim = {xVal, yVal, buttonW, buttonH};
      // mouse values 
      prevMousex = prevMousey = 0;
}
void MainMenue::updateUI()
{
      updatescreen();
      yVal = menumin = screen_height / 20; 
      step = screen_height / 10;
      buttonH = screen_height / 20;
      buttonW = screen_width / 6;
      xVal=screen_width-buttonW-buttonW/3;
      cursorDim.w = screen_width / 40;
      cursorDim.h = screen_height / 20;
      cursorDim.x = xVal-cursorDim.w;
      cursorDim.y = yVal;
      bgdim = {0, 0, screen_width, screen_height};
      newGameDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      continueDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      highScoreDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      optionsDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      helpDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      aboutDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      exitDim = {xVal, yVal, buttonW, buttonH};
}
void MainMenue::cursorJump(SDL_Rect* r)
{
      cursorDim.y=r->y;
}
void MainMenue::cursorUpdate(int step)
{
      //jumps to the bottom on negative input from the 1st element
       if (cursorDim.y + step < menumin) cursorJump(&exitDim);
            //jumps to the top on positive input from the last element
             else if (cursorDim.y + step > menumax) cursorJump(&newGameDim);
             else cursorDim.y += step;
}
void MainMenue::handleEvent()
{
      SDL_Event e;
      //polls event
      while (SDL_PollEvent(&e) != 0) {
            //quits on clicking the quit button
            if (e.type == SDL_QUIT)
                  quit = true;
            //updates the ui on window envent
            if(win.handleEvent(e)) updateUI();
            //checks keyboard event
            if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        //window event
                        case SDLK_m:
                              win.toggleFullscreen();
                              updateUI();
                              break;
                        //navigation
                        case SDLK_UP:
                              cursorUpdate(-step);
                              break;
                        case SDLK_DOWN:
                              cursorUpdate(step); 
                              break;
                        //music
                        case SDLK_o:
                              if(Mix_PausedMusic()==1){
                                    Mix_ResumeMusic();
                              }
                              else{
                                    Mix_PauseMusic();
                              }
                              break;
                        //on hiting return key checks for the button currently in and executes functions accordingly
                        case SDLK_RETURN: {
                              if (cursorpoints(&newGameDim, &cursorDim)){
                                    // printf("%d\n",newGameDim.x);
                                    screen = IN_GAME, isrunning = true;
                                    save_game(0,3,9999,0,5,-5, 5, 9000,0);
                                    xposition = 0;
                                    yposition = screen_height / 2 - ( screen_width / 20 );
                                    updatescreen();
                                    initGame();
                              }
                              else if(cursorpoints(&continueDim, &cursorDim)){
                                    screen = IN_GAME;
                                    isrunning = true;
                                    updatescreen();
                                    initGame();
                              }
                              else if(cursorpoints(&highScoreDim, &cursorDim))
                                    screen=HIGH_SCORES, highScore.updateUI();
                              else if (cursorpoints(&optionsDim, &cursorDim))
                                    screen=OPTIONS, options.updateUI();
                              else if (cursorpoints(&helpDim, &cursorDim))
                                    screen = HELP, help.updateUI();
                              else if (cursorpoints(&aboutDim, &cursorDim))
                                    screen=ABOUT, about.updateUI();      
                              else if (cursorpoints(&exitDim, &cursorDim))
                                    quit = true;
                        }
                  }
            }
            
      }
 
      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      //only updates on movement of mouse
      if (prevMousex != 0 && prevMousey != mousey) {
            //checks if the y value of the mouse is inside a certain threshold and updates cursor
            if (mousey <= newGameDim.y||mousey<=newGameDim.y+newGameDim.h)
                  cursorJump(&newGameDim);
            else if (mousey <= continueDim.y||mousey<= continueDim.y+ continueDim.h)
                  cursorJump(&continueDim);
            else if (mousey >= highScoreDim.y && mousey < highScoreDim.y + highScoreDim.h + 1)
                  cursorJump(&highScoreDim);
            else if (mousey >= optionsDim.y && mousey < optionsDim.y + optionsDim.h + 1)
                  cursorJump(&optionsDim);
            else if (mousey >= helpDim.y && mousey < helpDim.y + helpDim.h + 1)
                  cursorJump(&helpDim);
            else if (mousey >= aboutDim.y && mousey < aboutDim.y + aboutDim.h + 1)
                  cursorJump(&aboutDim);
            else if (mousey >= exitDim.y)
                  cursorJump(&exitDim);
      }
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            //on left press checks where the mouse is and executes functions accordingly

            if (mouseIsInside(&newGameDim, mousex, mousey)){
                  save_game(0,3,9999,0,5,-5, 5, 9000,0);
                  isrunning = true, screen = IN_GAME;
                  updatescreen();
                  initGame();
                  xposition = 0;
                  yposition = screen_height / 2 - ( screen_width / 20 );
            }
            if (mouseIsInside(&continueDim, mousex, mousey))
                  isrunning = true, screen = IN_GAME, updatescreen(),initGame();
            else if (mouseIsInside(&highScoreDim, mousex, mousey))
                  screen = HIGH_SCORES, highScore.updateUI();
            else if (mouseIsInside(&optionsDim, mousex, mousey))
                  screen=OPTIONS, options.updateUI();
            else if (mouseIsInside(&helpDim, mousex, mousey))
                  screen = HELP, help.updateUI();
            else if (mouseIsInside(&aboutDim, mousex, mousey))
                  screen=ABOUT, about.updateUI();      
            else if (mouseIsInside(&exitDim, mousex, mousey))
                  quit = true;
      }
      //records current mouse position for next frame
      prevMousex=mousex, prevMousey=mousey;
}
void MainMenue::run()
{
      //handle event
      handleEvent();
      //play music
      if(Mix_PlayingMusic()==0){
            Mix_PlayMusic(gBackgroundMusic,-1);
      }
      //clear renderer
      SDL_RenderClear(ren);
      //put elements one by one
      SDL_RenderCopy(ren, mainMenuBG, NULL, &bgdim);
      SDL_RenderCopy(ren, newGameB, NULL, &newGameDim);
      SDL_RenderCopy(ren, continueB, NULL, &continueDim);
      SDL_RenderCopy(ren, highScoreB, NULL, &highScoreDim);
      SDL_RenderCopy(ren, OptionsB, NULL, &optionsDim);
      SDL_RenderCopy(ren, helpB, NULL, &helpDim);
      SDL_RenderCopy(ren, aboutB, NULL, &aboutDim);
      SDL_RenderCopy(ren, exitB, NULL, &exitDim);
      SDL_RenderCopy(ren, cursor, NULL, &cursorDim);
      //present renderer
      SDL_RenderPresent(ren);
}

Pause::Pause()
{
      yVal = menumin = screen_height / 3; 
      step = screen_height / 10;
      buttonH = screen_height / 20;
      buttonW = screen_width / 6;
      xVal = (screen_width / 2) - buttonW / 2;
      menumax = screen_height / 3 + 2 * screen_height / 10;

      bgdim = {0, 0, screen_width, screen_height};
      cursorDim = {screen_width / 2 - screen_width / 12 - screen_width / 40, screen_height / 3, screen_width / 40, screen_height / 20};
      resumeDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      mainMenueDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      exitDim = {xVal, yVal, buttonW, buttonH};

      prevMousex = prevMousey = 0;
}
void Pause::updateUI()
{
      updatescreen();
      yVal = menumin = screen_height / 3; 
      step = screen_height / 10;
      buttonH = screen_height / 20;
      buttonW = screen_width / 6;
      xVal = (screen_width / 2) - buttonW / 2;
      menumax = screen_height / 3 + 2 * screen_height / 10;
      bgdim = {0, 0, screen_width, screen_height};
      cursorDim.w = screen_width / 40;
      cursorDim.h = screen_height / 20;
      cursorDim.x = xVal-cursorDim.w;
      cursorDim.y = yVal;
      resumeDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      mainMenueDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      exitDim = {xVal, yVal, buttonW, buttonH};
}
void Pause::cursorJump(SDL_Rect* r)
{
      cursorDim.y=r->y;
}
void Pause::cursorUpdate(int step)
{
       if (cursorDim.y + step < menumin) cursorJump(&exitDim);
             else if (cursorDim.y + step > menumax) cursorJump(&resumeDim);
             else cursorDim.y += step;     
}

void Pause::handleEvent()
{
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            if(win.handleEvent(e)) updateUI(), scaleGame(), walls.init();
            if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_BACKSPACE:
                              screen = IN_GAME, isrunning = true;
                              break;
                        case SDLK_m:
                              win.toggleFullscreen();
                              updateUI();
                              break;
                        case SDLK_UP:
                              cursorUpdate(-step);
                              break;
                        case SDLK_DOWN:
                              cursorUpdate(step); 
                              break;
                        case SDLK_o:
                              if(Mix_PausedMusic()==1){
                                    Mix_ResumeMusic();
                              }
                              else{
                                    Mix_PauseMusic();
                              }
                              break;
                        case SDLK_RETURN: {
                              if (cursorpoints(&resumeDim, &cursorDim))
                                    screen = IN_GAME, isrunning = true;
                              else if (cursorpoints(&mainMenueDim, &cursorDim))
                                    screen = MAIN_MENU, mainMenu.updateUI(), diffTimer.stop();
                              else if (cursorpoints(&exitDim, &cursorDim))
                                    quit = true;
                        }
                  }
            }
            
      }
 
      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (prevMousex != 0 && prevMousey != mousey) {
            if (mousey < mainMenueDim.y)
                  cursorJump(&resumeDim);
            else if (mousey >= mainMenueDim.y && mousey < mainMenueDim.y + mainMenueDim.h + 1)
                  cursorJump(&mainMenueDim);
            else if (mousey >= exitDim.y)
                  cursorJump(&exitDim);
      }
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {

            if (mouseIsInside(&resumeDim, mousex, mousey))
                  isrunning = true, screen = IN_GAME;
            else if (mouseIsInside(&mainMenueDim, mousex, mousey))
                  screen = MAIN_MENU, mainMenu.updateUI(), diffTimer.stop();
            else if (mouseIsInside(&exitDim, mousex, mousey))
                  quit = true;
      }
      prevMousex=mousex, prevMousey=mousey;
}

void Pause::run()
{
            handleEvent();
            SDL_RenderClear(ren);
            SDL_RenderCopy(ren, pauseBG, NULL, &bgdim);
            SDL_RenderCopy(ren, pausenewB, NULL, &mainMenueDim);
            SDL_RenderCopy(ren, resumeB, NULL, &resumeDim);
            SDL_RenderCopy(ren, pauseexitB, NULL, &exitDim);
            SDL_RenderCopy(ren, cursor, NULL, &cursorDim);
            SDL_RenderPresent(ren);
            SDL_Delay(1000/60);
}

Options::Options()
{
      yVal = menumin = screen_height / 10; 
      step = screen_height / 10;
      buttonH = screen_height / 10;
      buttonW = screen_width / 4;
      xVal = screen_width - 3 * buttonW / 2;
      menumax = menumin + buttonH;
      bgdim = {0, 0, screen_width, screen_height};
      cursorDim.w = screen_width / 40;
      cursorDim.h = screen_height / 20;
      cursorDim.x = xVal-cursorDim.w;
      cursorDim.y = yVal;

      fullScreenDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      mouseModeDim = {xVal, yVal, buttonW, buttonH};
      yVal += step;
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
      clearDim = {xVal, yVal, buttonW, buttonH};
}
void Options::updateUI()
{
      updatescreen();
      yVal = menumin = screen_height / 10; 
      step = screen_height / 10;
      buttonH = screen_height / 20;
      buttonW = screen_width / 6;
      xVal = screen_width - 3 * buttonW / 2;
      menumax = menumin + buttonH*6;
      bgdim = {0, 0, screen_width, screen_height};
      cursorDim.w = screen_width / 40;
      cursorDim.h = screen_height / 20;
      cursorDim.x = xVal-cursorDim.w;
      cursorDim.y = yVal;

      fullScreenDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      mouseModeDim = {xVal, yVal, buttonW, buttonH};
      yVal += step;
      clearDim = {xVal, yVal, buttonW, buttonH};
      yVal += step;
      musicDim = {xVal, yVal, buttonW, buttonH};
      
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
}
void Options::cursorJump(SDL_Rect* r)
{
      cursorDim.y=r->y;
      cursorDim.x=r->x-cursorDim.w;
}
void Options::cursorUpdate(int step)
{
       if (cursorDim.y + step < menumin) cursorJump(&backDim);
       else if (cursorDim.y >= backDim.y && step>0) cursorJump(&fullScreenDim);
       else if (cursorDim.y>=backDim.y && step<0) cursorJump(&musicDim);
       else if(cursorDim.y + step > menumax) cursorJump(&backDim);
       else cursorDim.y += step;
}

void Options::handleEvent()
{
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            if(win.handleEvent(e)) updateUI();
            if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_BACKSPACE:
                              screen = MAIN_MENU, isrunning = true, mainMenu.updateUI();
                              break;
                        case SDLK_UP:
                              cursorUpdate(-step);
                              break;
                        case SDLK_DOWN:
                              cursorUpdate(step); 
                              break;
                        case SDLK_o:
                              if(Mix_PausedMusic()==1){
                                    Mix_ResumeMusic();
                              }
                              else{
                                    Mix_PauseMusic();
                              }
                              break;
                        case SDLK_RETURN: {
                              if (cursorpoints(&fullScreenDim, &cursorDim))
                                    {
                                          win.toggleFullscreen();
                                          updateUI();
                                    }
                              else if (cursorpoints(&mouseModeDim, &cursorDim))
                                    mouseMode=!mouseMode;
                              else if (cursorpoints(&backDim, &cursorDim))
                                    screen=MAIN_MENU, mainMenu.updateUI();
                              else if (cursorpoints(&clearDim, &cursorDim))
                                    highscoreclear();
                              else if (cursorpoints(&musicDim, &cursorDim))
                                    {
                                          if(Mix_PausedMusic()==1)
                                                Mix_ResumeMusic();
                                          else
                                          Mix_PauseMusic();
                                    }     
                        }
                  }
            }
            
      }
 
      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (prevMousex != 0 && prevMousey != mousey) {
            if (mousey < mouseModeDim.y)
                  cursorJump(&fullScreenDim);
            else if (mousey >= mouseModeDim.y && mousey < mouseModeDim.y + mouseModeDim.h + 1)
                  cursorJump(&mouseModeDim);
            else if (mousey >= clearDim.y && mousey < clearDim.y + clearDim.h + 1)
                  cursorJump(&clearDim);
            else if (mousey >= musicDim.y && mousey < musicDim.y + musicDim.h + 1)
                  cursorJump(&musicDim);
            else if (mousey >= backDim.y)
                  cursorJump(&backDim);
      }
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {

            if (mouseIsInside(&fullScreenDim, mousex, mousey))
                        {
                              win.toggleFullscreen();
                              updateUI();
                        }
            else if (mouseIsInside(&mouseModeDim, mousex, mousey))
                  mouseMode=!mouseMode;
            else if (mouseIsInside(&clearDim, mousex, mousey))
                  highscoreclear();
            else if (mouseIsInside(&musicDim, mousex, mousey))
                  {
                        if(Mix_PausedMusic()==1)
                              Mix_ResumeMusic();
                        else
                        Mix_PauseMusic();
                  }      
            else if (mouseIsInside(&backDim, mousex, mousey))
                  screen = MAIN_MENU, mainMenu.updateUI();
      }
      prevMousex=mousex, prevMousey=mousey;
}
void Options::run()
{
      handleEvent();
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, pauseBG, NULL, &bgdim);
      SDL_RenderCopy(ren, optionsToggle[win.fullScreen], NULL, &fullScreenDim);
      SDL_RenderCopy(ren, optionsToggle[mouseMode], NULL, &mouseModeDim);
      SDL_RenderCopy(ren,cleartex,NULL, &clearDim);
      SDL_RenderCopy(ren, optionsToggle[!Mix_PausedMusic()], NULL, &musicDim);
      SDL_Rect area;
      printText(ren, screen_width/10, fullScreenDim.y,"Full Screen", &tscreentex, &area, White);
      SDL_RenderCopy(ren,tscreentex,NULL, &area);
      printText(ren, screen_width/10, mouseModeDim.y,"Mouse Mode", &tscreentex, &area, White);
      SDL_RenderCopy(ren,tscreentex,NULL, &area);
      printText(ren, screen_width/10, clearDim.y,"Highscore Reset", &tscreentex, &area, White);
      SDL_RenderCopy(ren,tscreentex,NULL, &area);
      printText(ren, screen_width/10, musicDim.y,"Music", &tscreentex, &area, White);
      SDL_RenderCopy(ren,tscreentex,NULL, &area);
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      SDL_RenderCopy(ren, cursor, NULL, &cursorDim);
      SDL_RenderPresent(ren);
}

HighScore::HighScore()
{
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
}
void HighScore::updateUI()
{
      updatescreen();
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};

}
void HighScore::handleEvents()
{
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_BACKSPACE:
                              screen = MAIN_MENU, mainMenu.updateUI();
                              break;
                        case SDLK_m:
                              win.toggleFullscreen();
                              updateUI();
                              break;
                        case SDLK_o:
                              if(Mix_PausedMusic()==1){
                                    Mix_ResumeMusic();
                              }
                              else{
                                    Mix_PauseMusic();
                              }
                              break;
                  }
            }
            if(win.handleEvent(e)) updateUI();
      }

      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (mouseIsInside(&backDim, mousex, mousey))
                  screen = MAIN_MENU, mainMenu.updateUI();
      }
}
void HighScore::run() {
      
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, highScoreBG, NULL, NULL);
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      TTF_Init();
      FILE *fptr = fopen("assets/highscore.txt", "r");
      // font = TTF_OpenFont("assets/Sans/Sans.ttf", 22);
      int num, x, y;
      x = screen_width/2-area.w/2;
      y = screen/20;

      while ((num = getw(fptr)) != EOF)
      {
            highscore_printing(num,x,y);
            y += 50;
      }
      fclose(fptr);
      SDL_RenderPresent(ren);
      handleEvents();
}



About::About()
{
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
}
void About::updateUI()
{
      updatescreen();
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};

}
void About::handleEvents()
{
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_BACKSPACE:
                              screen = MAIN_MENU, mainMenu.updateUI();
                              break;
                        case SDLK_m:
                              win.toggleFullscreen();
                              updateUI();
                              break;
                        case SDLK_o:
                              if(Mix_PausedMusic()==1){
                                    Mix_ResumeMusic();
                              }
                              else{
                                    Mix_PauseMusic();
                              }
                              break;
                  }
            }
            if(win.handleEvent(e)) updateUI();
            
      }

      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (mouseIsInside(&backDim, mousex, mousey))
                  screen = MAIN_MENU, mainMenu.updateUI();
      }
}
void About::run() {
      
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, aboutBG, NULL, NULL);
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      SDL_RenderPresent(ren);
      handleEvents();
}



Help::Help()
{
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
}
void Help::updateUI()
{
      updatescreen();
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};

}
void Help::handleEvents()
{
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_BACKSPACE:
                              screen = MAIN_MENU, mainMenu.updateUI();
                              break;
                        case SDLK_m:
                              win.toggleFullscreen();
                              updateUI();
                              break;
                        case SDLK_o:
                              if(Mix_PausedMusic()==1){
                                    Mix_ResumeMusic();
                              }
                              else{
                                    Mix_PauseMusic();
                              }
                              break;
                  }
            }
            if(win.handleEvent(e)) updateUI();
            
      }

      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (mouseIsInside(&backDim, mousex, mousey))
                  screen = MAIN_MENU, mainMenu.updateUI();
      }
}
void Help::run() {
      
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, inhelp, NULL, NULL);
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      SDL_RenderPresent(ren);
      handleEvents();
}
