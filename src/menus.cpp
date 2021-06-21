#include "header.hpp"

SDL_Rect tscreentextdim={screen_width/3, screen_height-(screen_height/8)*2, screen_width/2, screen_height/8};

void titlescreen() {
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, titleBG, NULL, NULL);
      font = TTF_OpenFont("assets/Sans/Sans.ttf", 24);
      printText(ren, screen_width/4, screen_height-screen_height/4, "Press any key to continue", &tscreentex, &tscreentextdim, White); 
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

MainMenue::MainMenue()
{
      yVal = menumin = screen_height / 20; 
      step = screen_height / 10;
      buttonH = screen_height / 20;
      buttonW = screen_width / 6;
      xVal=screen_width-buttonW-buttonW/3;
      menumax = 6 * screen_height / 10;
      bgdim = {0, 0, screen_width, screen_height};
      cursorDim.w = screen_width / 40;
      cursorDim.h = screen_height / 20;
      cursorDim.x = xVal-cursorDim.w;
      cursorDim.y = yVal;
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
       if (cursorDim.y + step < menumin) cursorJump(&exitDim);
             else if (cursorDim.y + step > menumax) cursorJump(&newGameDim);
             else cursorDim.y += step;
}
void MainMenue::handleEvent()
{
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            if(win.handleEvent(e)) updateUI();
            if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
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
                        case SDLK_RETURN: {
                              if (cursorpoints(&newGameDim, &cursorDim)){
                                    screen = IN_GAME, isrunning = true;
                                    save_game(0,3,9999,0,5,-5, 5);
                                    updatescreen();
                              }
                              if(cursorpoints(&continueDim, &cursorDim)){
                                    screen = IN_GAME;
                                    isrunning = true;
                                    updatescreen();
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
      if (prevMousex != 0 && prevMousey != mousey) {
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

            if (mouseIsInside(&newGameDim, mousex, mousey)){
                  save_game(0,3,9999,0,5,-5, 5);
                  isrunning = true, screen = IN_GAME;
                  updatescreen();
            }
            if (mouseIsInside(&continueDim, mousex, mousey))
                  isrunning = true, screen = IN_GAME, updatescreen();
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
      prevMousex=mousex, prevMousey=mousey;
}
void MainMenue::run()
{
      handleEvent();
      if(Mix_PlayingMusic()==0){
            Mix_PlayMusic(gBackgroundMusic,-1);
      }
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, mainMenuBG, NULL, &bgdim);
      SDL_RenderCopy(ren, newGameB, NULL, &newGameDim);
      SDL_RenderCopy(ren, newGameB, NULL, &continueDim);
      SDL_RenderCopy(ren, highScoreB, NULL, &highScoreDim);
      SDL_RenderCopy(ren, OptionsB, NULL, &optionsDim);
      SDL_RenderCopy(ren, helpB, NULL, &helpDim);
      SDL_RenderCopy(ren, aboutB, NULL, &aboutDim);
      SDL_RenderCopy(ren, exitB, NULL, &exitDim);
      SDL_RenderCopy(ren, cursor, NULL, &cursorDim);
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
            if(win.handleEvent(e)) updateUI();
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
      //fullScreenTextDim = {screen_width/8, yVal, buttonW*2, buttonH};
      yVal+=step;
      mouseModeDim = {xVal, yVal, buttonW, buttonH};
      //mouseModeTextDim = {screen_width/8, yVal, buttonW*2, buttonH};
      
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
      // font = TTF_OpenFont("assets/Sans/Sans.ttf", 22);
      // printText(ren, screen_width/8, fullScreenDim.y, "Fullscreen", font, &fullScreenText, &fullScreenTextDim);
      // printText(ren, screen_width/8, mouseModeDim.y, "Mouse Mode", font, &mouseModeText, &mouseModeTextDim);
}
void Options::updateUI()
{
      updatescreen();
      yVal = menumin = screen_height / 10; 
      step = screen_height / 10;
      buttonH = screen_height / 20;
      buttonW = screen_width / 6;
      xVal = screen_width - 3 * buttonW / 2;
      menumax = menumin + buttonH*2;
      bgdim = {0, 0, screen_width, screen_height};
      cursorDim.w = screen_width / 40;
      cursorDim.h = screen_height / 20;
      cursorDim.x = xVal-cursorDim.w;
      cursorDim.y = yVal;

      fullScreenDim = {xVal, yVal, buttonW, buttonH};
      //fullScreenTextDim = {screen_width/8, yVal, buttonW*2, buttonH};
      yVal+=step;
      mouseModeDim = {xVal, yVal, buttonW, buttonH};
      //mouseModeTextDim = {screen_width/8, yVal, buttonW*2, buttonH};
      
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
      else if (cursorDim.y> menumax && step<0) cursorJump(&mouseModeDim);
      else if (cursorDim.y> menumax && step>0) cursorJump(&fullScreenDim);
      else if (cursorDim.y + step > menumax) cursorJump(&backDim);
      else cursorDim.y +=step;
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
      SDL_Rect area;
      printText(ren, screen_width/10, fullScreenDim.y,"Full Screen", &tscreentex, &area, White);
      SDL_RenderCopy(ren,tscreentex,NULL, &area);
      printText(ren, screen_width/10, mouseModeDim.y,"Mouse Mode", &tscreentex, &area, White);
      SDL_RenderCopy(ren,tscreentex,NULL, &area);
      // SDL_RenderCopy(ren, fullScreenText, NULL, &fullScreenTextDim);
      // SDL_RenderCopy(ren, mouseModeText, NULL, &mouseModeTextDim);
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
      SDL_RenderCopy(ren, pauseBG, NULL, NULL);
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      SDL_RenderPresent(ren);
      handleEvents();
}
