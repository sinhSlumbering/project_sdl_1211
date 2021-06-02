#include "header.hpp"


gWindow win;

void updatescreen()
{
      SDL_GetWindowSize(win.window, &screen_width, &screen_height);
}

int screen_width=SCREEN_WIDTH;
int screen_height=SCREEN_HEIGHT;

Boss plane;
About about;
Help help;
HighScore highScore;
Pause pause;
MainMenue mainMenu;


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


//SDL_Window* win;
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

gWindow::gWindow()
{
      window=NULL;
      mouseFocus=false;
      keyboardFocus=false;
      fullScreen=false;
      minimized=false;
      width=0;
      height=0;
}
void gWindow::toggleFullscreen()
{
      if( fullScreen )
		{
			SDL_SetWindowFullscreen( window, SDL_FALSE );
			fullScreen = false;
		}
		else
		{
			SDL_SetWindowFullscreen( window, SDL_TRUE );
			fullScreen = true;
			minimized = false;
		}
            
}
bool gWindow::init()
{
      window=SDL_CreateWindow("UtensilCranium", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
      if(window!=NULL)
      {
            mouseFocus=true;
            keyboardFocus=true;
            width=screen_width;
            height=screen_height;
      }
      return window!=NULL;
}
SDL_Renderer* gWindow::createRenderer()
{
	return SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}
bool gWindow::handleEvent( SDL_Event& e )
{
      bool update=false;
      //Window event occured
	if( e.type == SDL_WINDOWEVENT )
	{

		switch( e.window.event )
		{
			//Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			updatescreen();
			SDL_RenderPresent( ren );
                  update=true;
			break;

			//Repaint on exposure
			case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent( ren );
			break;

			//Mouse entered window
			case SDL_WINDOWEVENT_ENTER:
		      mouseFocus = true;
			//updateCaption = true;
			break;
			
			//Mouse left window
			case SDL_WINDOWEVENT_LEAVE:
			mouseFocus = false;
			//updateCaption = true;
			break;

			//Window has keyboard focus
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			keyboardFocus = true;
			//updateCaption = true;
			break;

			//Window lost keyboard focus
			case SDL_WINDOWEVENT_FOCUS_LOST:
			keyboardFocus = false;
			//updateCaption = true;
			break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
                  minimized = true;
                  break;

			//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
			minimized = false;
                  break;
			
			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
			minimized = false;
                  break;
		}

		//Update window caption with new data
		//if( updateCaption )
		//{
                  // std::stringstream caption;
			// caption << "SDL Tutorial - MouseFocus:" << ( ( mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( keyboardFocus ) ? "On" : "Off" );
			// SDL_SetWindowTitle( window, caption.str().c_str() );
                  //printf("%d, %d\n", screen_height, screen_width);
		//}
	}
      return update;
	
}
void gWindow::free()
{
      if(win.window!=NULL)
      {
            SDL_DestroyWindow(window);
      }
      mouseFocus=false;
      keyboardFocus=false;
      fullScreen=false;
      minimized=false;
      width=0;
      height=0;
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

            if(!win.init())
            {
                  Error("window creation");
                  success=false;
            }
            // win = SDL_CreateWindow("gaem0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
            // if (win == NULL) {
            //       Error("window creation");
            //       success = false;
            //} 
            else {
                  ren = win.createRenderer();
 
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
      playertex=NULL;
      SDL_DestroyTexture(bosstex);
      bosstex=NULL;
      SDL_DestroyRenderer(ren);
      ren = NULL;
      win.free();
 
      IMG_Quit();
      SDL_Quit();
}
 
bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey) {
      return (mousex >= rect->x && mousex <= rect->x + rect->w) && (mousey >= rect->y && mousey <= rect->y + rect->h);
}
 
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim) {
      return (cursorDim->y >= rect->y) && ((cursorDim->h + cursorDim->y) <= (rect->y + rect->h));
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
      yVal = menumin = screen_height / 20; 
      step = screen_height / 10;
      buttonH = screen_height / 20;
      buttonW = screen_width / 6;
      xVal=screen_width-buttonW-buttonW/3;
      cursorDim.w = screen_width / 40;
      cursorDim.h = screen_height / 20;
      cursorDim.x = xVal-cursorDim.w;
      cursorDim.y = yVal;
      //cursorDim = {screen_width / 2 - screen_width / 12 - screen_width / 40, screen_height / 3, screen_width / 40, screen_height / 20};
      bgdim = {0, 0, screen_width, screen_height};
      newGameDim = {xVal, yVal, buttonW, buttonH};
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
void MainMenue::cursorUpdate(int step)
{
      if (cursorDim.y + step < menumin) cursorDim.y = menumin;
             else if (cursorDim.y + step > menumax);
             else cursorDim.y += step;     
}
void MainMenue::cursorJump(SDL_Rect* r)
{
      cursorDim.y=r->y;
}
void MainMenue::handleEvent()
{
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true, runs=false;
            if(win.handleEvent(e)) updateUI();
            if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                              screen = IN_GAME, isrunning = true;
                              break;
                        case SDLK_m:
                              win.toggleFullscreen();
                              updatescreen();
                              updateUI();
                              break;
                        case SDLK_UP:
                              cursorUpdate(-step);
                              break;
                        case SDLK_DOWN:
                              cursorUpdate(step); 
                              break;
                        case SDLK_RETURN: {
                              runs = false;
                              if (cursorpoints(&newGameDim, &cursorDim))
                                    screen = IN_GAME, isrunning = true;
                              else if(cursorpoints(&highScoreDim, &cursorDim))
                                    screen=HIGH_SCORES;
                              else if (cursorpoints(&optionsDim, &cursorDim))
                                    printf("implement options ffs. ;-;\n");
                              else if (cursorpoints(&helpDim, &cursorDim))
                                    printf("implement help ffs. ;-;\n");
                              else if (cursorpoints(&optionsDim, &cursorDim))
                                    screen=ABOUT;      
                              else if (cursorpoints(&exitDim, &cursorDim))
                                    quit = true;
                        }
                  }
            }
            
      }
 
      int mousex, mousey;
      int mbutton = SDL_GetMouseState(&mousex, &mousey);
      if (prevMousex != 0 && prevMousey != mousey) {
            if (mousey < newGameDim.y)
                  cursorJump(&newGameDim);
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

            if (mouseIsInside(&newGameDim, mousex, mousey))
                  isrunning = true, screen = IN_GAME, runs=false;
            else if (mouseIsInside(&highScoreDim, mousex, mousey))
                  screen = HIGH_SCORES, runs=false;
            else if (mouseIsInside(&optionsDim, mousex, mousey))
                  ;
            else if (mouseIsInside(&helpDim, mousex, mousey))
                  ;
            else if (mouseIsInside(&aboutDim, mousex, mousey))
                  screen=ABOUT;      
            else if (mouseIsInside(&exitDim, mousex, mousey))
                  quit = true, runs=false;
      }
      prevMousex=mousex, prevMousey=mousey;
}
void MainMenue::run()
{
      //printf("%d %d", screen_width, screen_height);
      handleEvent();
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, mainMenuBG, NULL, &bgdim);
      SDL_RenderCopy(ren, newGameB, NULL, &newGameDim);
      SDL_RenderCopy(ren, highScoreB, NULL, &highScoreDim);
      SDL_RenderCopy(ren, exitB, NULL, &optionsDim);
      SDL_RenderCopy(ren, helpB, NULL, &helpDim);
      SDL_RenderCopy(ren, aboutB, NULL, &aboutDim);
      SDL_RenderCopy(ren, exitB, NULL, &exitDim);
      SDL_RenderCopy(ren, cursor, NULL, &cursorDim);
      SDL_RenderPresent(ren);
}

 
void gamestart() {
      Player player;
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
      yVal = menumin = screen_height / 3; 
      step = screen_height / 10;
      buttonH = screen_height / 20;
      buttonW = screen_width / 6;
      xVal = (screen_width / 2) - buttonW / 2;
      menumax = screen_height / 3 + 2 * screen_height / 10;

      bgdim = {0, 0, screen_width, screen_height};
      //cursorDim = {screen_width / 2 - screen_width / 12 - screen_width / 40, screen_height / 3, screen_width / 40, screen_height / 20};
      cursorDim.w = screen_width / 40;
      cursorDim.h = screen_height / 20;
      cursorDim.x = xVal-cursorDim.w;
      resumeDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      mainMenueDim = {xVal, yVal, buttonW, buttonH};
      yVal+=step;
      exitDim = {xVal, yVal, buttonW, buttonH};
}
void Pause::cursorUpdate(int step)
{
       if (cursorDim.y + step < menumin) cursorDim.y = menumin;
             else if (cursorDim.y + step > menumax);
             else cursorDim.y += step;     
}
void Pause::cursorJump(SDL_Rect* r)
{
      cursorDim.y=r->y;
}
void Pause::handleEvent()
{
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                  quit = true, runs=false;
            if(win.handleEvent(e)) updateUI();
            if (e.type == SDL_KEYDOWN) {
                  switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                              screen = IN_GAME, isrunning = true;
                              break;
                        case SDLK_m:
                              win.toggleFullscreen();
                              updatescreen();
                              updateUI();
                              break;
                        case SDLK_UP:
                              cursorUpdate(-step);
                              break;
                        case SDLK_DOWN:
                              cursorUpdate(step); 
                              break;
                        case SDLK_RETURN: {
                              runs = false;
                              if (cursorpoints(&resumeDim, &cursorDim))
                                    screen = IN_GAME, isrunning = true;
                              else if (cursorpoints(&mainMenueDim, &cursorDim))
                                    screen = MAIN_MENU;
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
                  isrunning = true, screen = IN_GAME, runs=false;
            else if (mouseIsInside(&mainMenueDim, mousex, mousey))
                  screen = MAIN_MENU, runs=false;
            else if (mouseIsInside(&exitDim, mousex, mousey))
                  quit = true, runs=false;
      }
      prevMousex=mousex, prevMousey=mousey;
}

void Pause::run()
{
      runs=true;
      while(runs)
      {
            handleEvent();
            SDL_RenderClear(ren);
            SDL_RenderCopy(ren, pauseBG, NULL, &bgdim);
            SDL_RenderCopy(ren, resumeB, NULL, &resumeDim);
            SDL_RenderCopy(ren, resumeB, NULL, &mainMenueDim);
            SDL_RenderCopy(ren, exitB, NULL, &exitDim);
            SDL_RenderCopy(ren, cursor, NULL, &cursorDim);
            SDL_RenderPresent(ren);
            SDL_Delay(1000/60);
      }
}

 

HighScore::HighScore()
{
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
}
void HighScore::updateUI()
{
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
                              screen = MAIN_MENU;
                              break;
                        case SDLK_m:
                              win.toggleFullscreen();
                              updatescreen();
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
                  screen = MAIN_MENU;
      }
}
void HighScore::run() {
      
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, pauseBG, NULL, NULL);
      //SDL_Rect backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      SDL_RenderPresent(ren);
      handleEvents();
}



About::About()
{
      backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
}
void About::updateUI()
{
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
                              screen = MAIN_MENU;
                              break;
                        case SDLK_m:
                              win.toggleFullscreen();
                              updatescreen();
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
                  screen = MAIN_MENU;
      }
}
void About::run() {
      
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, aboutBG, NULL, NULL);
      //SDL_Rect backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
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
                              screen = MAIN_MENU;
                              break;
                        case SDLK_m:
                              win.toggleFullscreen();
                              updatescreen();
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
                  screen = MAIN_MENU;
      }
}
void Help::run() {
      
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, pauseBG, NULL, NULL);
      //SDL_Rect backDim = {screen_width - screen_width / 10, screen_height - screen_height / 15, screen_width / 10, screen_height / 15};
      SDL_RenderCopy(ren, backB, NULL, &backDim);
      SDL_RenderPresent(ren);
      handleEvents();
}
