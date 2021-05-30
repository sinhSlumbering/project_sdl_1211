#include "header.hpp"



Player::Player()
{
      xPos = 0;
      yPos = SCREEN_HEIGHT/2-(width/2);
      angle = 0.0;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
      htbx = {SCREEN_WIDTH/60, SCREEN_HEIGHT/50, width/15, height/12};
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
      else if(xPos+width>SCREEN_WIDTH) xPos = SCREEN_WIDTH-width;
      if(yPos<0) yPos=0;
      else if(yPos+height>SCREEN_HEIGHT) yPos=SCREEN_HEIGHT-height;
      htbx.x = xPos + hbspX;
      htbx.y = yPos + hbspY;
}
void Player::handleEvent(SDL_Event* e)
{
      int x=0, y=0;

      if(e->type==SDL_KEYDOWN)
      {
            switch(e->key.keysym.sym)
            {
                  case SDLK_UP: y=-1, angle = 330.0; break; 
                  case SDLK_DOWN: y=1, angle = 30.0; break;
                  case SDLK_RIGHT: x=1, angle=0.0; break;
                  case SDLK_LEFT: x=-1, angle=0.0; break;
            }
            
      }
     if(e->type==SDL_KEYUP)
      {
            angle=0.0;
            /*switch (e->key.keysym.sym)
            {
                  case SDLK_UP: y=0; break;
                  case SDLK_DOWN: y=0; break;
                  case SDLK_RIGHT: x=0; break;
                  case SDLK_LEFT: x=0; break;
            }*/
      }
      move(x, y);

}

Boss::Boss()
{
      xPos = SCREEN_WIDTH-width;
      yPos = SCREEN_HEIGHT/3;
      htbx={xPos, yPos, width, height};
}
void Boss::move()
{
      if((yPos<0)||(yPos + height>SCREEN_HEIGHT))
            scrolldir*=-1;
      yPos+=scrolldir*yVel;
}
void Boss::render()
{
      SDL_Rect renderQuad = {xPos, yPos, width, height};
      SDL_RenderCopyEx(ren, bosstex, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

Boss plane;


int cursorHalfway = (SCREEN_WIDTH - (SCREEN_WIDTH / 20) - SCREEN_WIDTH / 6 - SCREEN_WIDTH / 40);
SDL_Rect cursorDim = {cursorHalfway, SCREEN_HEIGHT / 20, SCREEN_WIDTH / 40, SCREEN_HEIGHT / 20};
SDL_Rect pcursorDim = {SCREEN_WIDTH / 2 - SCREEN_WIDTH / 12 - SCREEN_WIDTH / 40, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 40, SCREEN_HEIGHT / 20};
int menumax = 4 * SCREEN_HEIGHT / 10, pmenumax = SCREEN_HEIGHT / 3 + 2 * SCREEN_HEIGHT / 10;
int prevMousex = 0, prevMousey = 0;

SDL_Window* win;
SDL_Renderer* ren;
SDL_Texture* titleBG;
SDL_Texture* mainMenuBG;
SDL_Texture* pauseBG;
SDL_Texture* aboutBG;
SDL_Texture* inGameBG;
SDL_Texture* backB;
SDL_Texture* highScoreB;
SDL_Texture* aboutB;
SDL_Texture* newGameB;
SDL_Texture* helpB;
SDL_Texture* resumeB;
SDL_Texture* exitB;
SDL_Texture* cursor;
SDL_Texture* playertex;
SDL_Texture* bosstex;


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

void Error(const std::string msg) {
      printf("%s Error: %s\n", msg, SDL_GetError());
}
 
void imgError(const std::string msg) {
      printf("%s IMG_Error: %s\n", msg, IMG_GetError());
}
 
void imgLoadError(const std::string path) {
      printf("failed to load %s IMGERROR: %s\n", path, IMG_GetError());
}
 
bool init() {
      bool success = true;
 
      if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            Error("Initialization");
            success = false;
      } else {
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                  printf("linear texture filtering disabled\n");
            }
 
            win = SDL_CreateWindow("gaem0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (win == NULL) {
                  Error("window creation");
                  success = false;
            } else {
                  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
 
                  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                  if (!(IMG_Init(imgFlags) & imgFlags)) {
                        imgError("Initialization");
                        success = false;
                  }
            }
      }
      return success;
}


//rework dis?
bool loadMedia() {
      bool success = true;
 
      titleBG = loadTex("assets/titlescreen.jpg");
      if (titleBG == NULL) {
            printf("failed to load title screen\n");
            success = false;
      }
 
      mainMenuBG = loadTex("assets/mainMenu/mainmenu.jpg");
      if (mainMenuBG == NULL) {
            printf("failed to load menu screen\n");
            success = false;
      }
 
      pauseBG = loadTex("assets/pause.png");
      if (pauseBG == NULL) {
            printf("failed to load pause screen\n");
            success = false;
      }
 
      aboutBG = loadTex("assets/About.jpg");
      if (aboutBG == NULL) {
            printf("failed to load about screen\n");
            success = false;
      }
 
      inGameBG = loadTex("assets/ingame.png");
      if (inGameBG == NULL) {
            printf("failed to load game screen\n");
            success = false;
      }
 
      backB = loadTex("assets/Back.jpg");
      if (backB == NULL) {
            printf("failed to load back button\n");
            success = false;
      }
 
      aboutB = loadTex("assets/mainMenu/about.jpg");
      if (aboutB == NULL) {
            printf("failed to load about button\n");
            success = false;
      }
      highScoreB = loadTex("assets/mainMenu/highscore.jpg");
      if (highScoreB == NULL) {
            printf("failed to load highscore button\n");
            success = false;
      }
      newGameB = loadTex("assets/mainMenu/newgame.jpg");
      if (newGameB == NULL) {
            printf("failed to load newgame button\n");
            success = false;
      }
 
      helpB = loadTex("assets/mainMenu/help.jpg");
      if (helpB == NULL) {
            printf("failed to load help button\n");
            success = false;
      }
 
      resumeB = loadTex("assets/resume.png");
      if (resumeB == NULL) {
            printf("failed to load resume button\n");
            success = false;
      }
 
      exitB = loadTex("assets/exit.png");
      if (exitB == NULL) {
            printf("failed to load exit button\n");
            success = false;
      }
      cursor = loadTex("assets/point.png");
      if (cursor == NULL) {
            printf("failed to load cursor\n");
            success = false;
      }
      playertex = loadTex("assets/player.png");
      if (playertex == NULL)
      {
            printf("failed to load player\n");
            success = false;
      }
      bosstex = loadTex("assets/boss.png");
      if(bosstex==NULL)
      {
            success = false;
      }
      return success;
}
 
SDL_Texture* loadTex(std::string path) {
      SDL_Texture* newTexture = NULL;
 
      SDL_Surface* loadedSurface = IMG_Load(path.c_str());
      if (loadedSurface == NULL) {
            imgLoadError(path.c_str());
      } else {
            newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
            if (newTexture == NULL) {
                  printf("texture creation from %s failed", path.c_str());
                  Error("");
            }
      }
      return newTexture;
}
 
void close() {
      SDL_DestroyTexture(titleBG);
      titleBG = NULL;
      SDL_DestroyTexture(mainMenuBG);
      mainMenuBG = NULL;
      SDL_DestroyTexture(pauseBG);
      pauseBG = NULL;
      SDL_DestroyTexture(aboutBG);
      aboutB = NULL;
      SDL_DestroyTexture(inGameBG);
      inGameBG = NULL;
      SDL_DestroyTexture(backB);
      backB = NULL;
      SDL_DestroyTexture(aboutB);
      aboutB = NULL;
      SDL_DestroyTexture(highScoreB);
      highScoreB = NULL;
      SDL_DestroyTexture(newGameB);
      newGameB = NULL;
      SDL_DestroyTexture(helpB);
      helpB = NULL;
      SDL_DestroyTexture(resumeB);
      resumeB = NULL;
      SDL_DestroyTexture(exitB);
      exitB = NULL;
      SDL_DestroyTexture(playertex);
      playertex=NULL:
      SDL_DestroyTexture(bosstex);
      bosstex=NULL;
      SDL_DestroyRenderer(ren);
      ren = NULL;
      SDL_DestroyWindow(win);
      win = NULL;
 
      IMG_Quit();
      SDL_Quit();
}
 
bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey) {
      return (mousex >= rect->x && mousex <= rect->x + rect->w) && (mousey >= rect->y && mousey <= rect->y + rect->h);
}
 
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim) {
      return (cursorDim->y >= rect->y) && ((cursorDim->h + cursorDim->y) <= (rect->y + rect->h));
}
 
void cursorupdate(int step) {
      if (screen == MAIN_MENU) {
            if (cursorDim.y + step < SCREEN_HEIGHT / 20) cursorDim.y = SCREEN_HEIGHT / 20;
            else if (cursorDim.y + step > menumax);
            else cursorDim.y += step;
      } else if (screen == PAUSE) {
            if (pcursorDim.y + step < SCREEN_HEIGHT / 3) pcursorDim.y = SCREEN_HEIGHT / 3;
            else if (pcursorDim.y + step > pmenumax);
            else pcursorDim.y += step;
      }
}
 
void cursorjump(SDL_Rect* rect) {
      if (screen == MAIN_MENU)
            cursorDim.y = rect->y;
      else if (screen == PAUSE)
            pcursorDim.y = rect->y;
}
 
void titlescreen() {
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, titleBG, NULL, NULL);
      SDL_RenderPresent(ren);
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN)
                  screen = MAIN_MENU;
            else if (e.type == SDL_MOUSEBUTTONDOWN)
                  screen = MAIN_MENU;
      }
}
 
void main_menue() {
      /****position variables should be global, don't need to do maths this much?****/
      int yval = SCREEN_HEIGHT / 20, step = SCREEN_HEIGHT / 10, buttonH = SCREEN_HEIGHT / 20, buttonW = SCREEN_WIDTH / 6, xval = SCREEN_WIDTH - (SCREEN_WIDTH / 20) - buttonW;
 
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, mainMenuBG, NULL, NULL);
      SDL_Rect newGameDim = {xval, yval, buttonW, buttonH};
      SDL_RenderCopy(ren, newGameB, NULL, &newGameDim);
      yval += step;
      SDL_Rect helpDim = {xval, yval, buttonW, buttonH};
      SDL_RenderCopy(ren, helpB, NULL, &helpDim);
      //yval=SCREEN_HEIGHT/2;
      //xval=SCREEN_WIDTH-(SCREEN_WIDTH/20)-buttonW;
      SDL_Rect highScoreDim = {xval, yval, buttonW, buttonH};
      SDL_RenderCopy(ren, highScoreB, NULL, &highScoreDim);
      yval += step;
      SDL_Rect aboutDim = {xval, yval, buttonW, buttonH};
      SDL_RenderCopy(ren, aboutB, NULL, &aboutDim);
      yval += step;
      SDL_Rect exitDim = {xval, yval, buttonW, buttonH};
      SDL_RenderCopy(ren, exitB, NULL, &exitDim);
      SDL_RenderCopy(ren, cursor, NULL, &cursorDim);
 
      SDL_RenderPresent(ren);
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_DOWN:
                              cursorupdate(step);
                              break;
 
                        case SDLK_UP:
                              cursorupdate(-step);
                              break;
 
                        case SDLK_RETURN: {
                              if (cursorpoints(&newGameDim, &cursorDim))
                                    screen = IN_GAME, isrunning = true;
                              else if (cursorpoints(&highScoreDim, &cursorDim))
                                    screen = HIGH_SCORES;
                              else if (cursorpoints(&aboutDim, &cursorDim))
                                    screen = ABOUT;
                              else if (cursorpoints(&exitDim, &cursorDim))
                                    quit = true;
                        } break;
                  }
            }
      }
 
      /***what about a mouse handler?***/
      int mousex, mousey;
      int mButton = SDL_GetMouseState(&mousex, &mousey);
      //very jank mouse nav handler
      if (prevMousex != 0 && prevMousey != mousey) {
            if (mousey < highScoreDim.y)
                  cursorjump(&newGameDim);
            else if (mousey >= highScoreDim.y && mousey < highScoreDim.y + highScoreDim.h + 1)
                  cursorjump(&highScoreDim);
            else if (mousey >= aboutDim.y && mousey < aboutDim.h + aboutDim.y + 1)
                  cursorjump(&aboutDim);
            else if (mousey >= exitDim.y)
                  cursorjump(&exitDim);
      }
      prevMousex = mousex, prevMousey = mousey;
 
      if (mButton & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (mouseIsInside(&newGameDim, mousex, mousey))
                  screen = IN_GAME, isrunning = true;
            else if (mouseIsInside(&highScoreDim, mousex, mousey))
                  screen = HIGH_SCORES;
            else if (mouseIsInside(&helpDim, mousex, mousey))
                  screen = HELP;
            else if (mouseIsInside(&aboutDim, mousex, mousey))
                  screen = ABOUT;
            else if (mouseIsInside(&exitDim, mousex, mousey))
                  quit = true;
      }
}
 
void gamestart() {
      Player player;
      int lives = 3;
      while (isrunning) {
            SDL_RenderClear(ren);
            SDL_Rect bgdim = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_RenderCopy(ren, inGameBG, NULL, &bgdim);
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                  if (e.type == SDL_QUIT)
                        quit = true, isrunning = false;
                  player.handleEvent(&e);
                  if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                              case SDLK_ESCAPE:
                                    screen = PAUSE, isrunning = false;
                                    break;
                        }
                        
                  }
            }
            if(lives<1) screen=MAIN_MENU, isrunning=false;
            player.render();
            plane.render();
            plane.move();
            if(checkCol(&player.htbx, &plane.htbx)==true) printf("ouch\n"), lives--;
            SDL_RenderPresent(ren);
            SDL_Delay(1000 / 120);
      }
}
void pauseM() {
      int yval = SCREEN_HEIGHT / 3, step = SCREEN_HEIGHT / 10, buttonH = SCREEN_HEIGHT / 20, buttonW = SCREEN_WIDTH / 6, xval = (SCREEN_WIDTH / 2) - buttonW / 2;
 
      SDL_RenderClear(ren);
      SDL_Rect bgdim = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
      SDL_RenderCopy(ren, pauseBG, NULL, &bgdim);
      SDL_Rect resumeDim = {xval, yval, buttonW, buttonH};
      SDL_RenderCopy(ren, resumeB, NULL, &resumeDim);
      yval += step;
      SDL_Rect mainMenueDim = {xval, yval, buttonW, buttonH};
      SDL_RenderCopy(ren, resumeB, NULL, &mainMenueDim);
      yval += step;
      SDL_Rect exitDim = {xval, yval, buttonW, buttonH};
      SDL_RenderCopy(ren, exitB, NULL, &exitDim);
      SDL_RenderCopy(ren, cursor, NULL, &pcursorDim);
      SDL_RenderPresent(ren);
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                              screen = IN_GAME, isrunning = true;
                              break;
 
                        case SDLK_UP:
                              cursorupdate(-step);
                              break;
                        case SDLK_DOWN:
                              cursorupdate(step);
                              break;
                        case SDLK_RETURN: {
                              if (cursorpoints(&resumeDim, &pcursorDim))
                                    screen = IN_GAME, isrunning = true;
                              else if (cursorpoints(&mainMenueDim, &pcursorDim))
                                    screen = MAIN_MENU;
                              else if (cursorpoints(&exitDim, &pcursorDim))
                                    quit = true;
                        }
                  }
            }
      }
 
      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (prevMousex != 0 && prevMousey != mousey) {
            if (mousey < mainMenueDim.y)
                  cursorjump(&resumeDim);
            else if (mousey >= mainMenueDim.y && mousey < mainMenueDim.y + mainMenueDim.h + 1)
                  cursorjump(&mainMenueDim);
            else if (mousey >= exitDim.y)
                  cursorjump(&exitDim);
      }
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (mouseIsInside(&resumeDim, mousex, mousey))
                  isrunning = true, screen = IN_GAME;
            else if (mouseIsInside(&mainMenueDim, mousex, mousey))
                  screen = MAIN_MENU;
            else if (mouseIsInside(&exitDim, mousex, mousey))
                  quit = true;
      }
}
 
void high_score() {
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                              screen = MAIN_MENU;
                              break;
                  }
            }
      }
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, pauseBG, NULL, NULL);
      SDL_Rect backDim = {SCREEN_WIDTH - SCREEN_WIDTH / 10, SCREEN_HEIGHT - SCREEN_HEIGHT / 15, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 15};
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      SDL_RenderPresent(ren);
      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (mouseIsInside(&backDim, mousex, mousey))
                  screen = MAIN_MENU;
      }
}
 
void help() {
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                              screen = MAIN_MENU;
                              break;
                  }
            }
      }
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, pauseBG, NULL, NULL);
      SDL_Rect backDim = {SCREEN_WIDTH - SCREEN_WIDTH / 10, SCREEN_HEIGHT - SCREEN_HEIGHT / 15, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 15};
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      SDL_RenderPresent(ren);
      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (mouseIsInside(&backDim, mousex, mousey))
                  screen = MAIN_MENU;
      }
}
 
void about() {
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true;
            else if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                              screen = MAIN_MENU;
                              break;
                  }
            }
      }
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, aboutBG, NULL, NULL);
      SDL_Rect backDim = {SCREEN_WIDTH - SCREEN_WIDTH / 10, SCREEN_HEIGHT - SCREEN_HEIGHT / 15, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 15};
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      SDL_RenderPresent(ren);
      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (mbutton & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (mouseIsInside(&backDim, mousex, mousey))
                  screen = MAIN_MENU;
      }

}