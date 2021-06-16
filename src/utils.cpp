#include "header.hpp"


gWindow win;

void updatescreen()
{
      SDL_GetWindowSize(win.window, &screen_width, &screen_height);
}

int screen_width=SCREEN_WIDTH;
int screen_height=SCREEN_HEIGHT;

About about;
Help help;
HighScore highScore;
Pause pause;
MainMenue mainMenu;
Options options;
upTimer iFrame, cFrame;

bool mouseMode=false;


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
SDL_Texture* optionsToggle[2];


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

upTimer::upTimer()
{
      running=false;
}
void upTimer::start()
{
      running = true;
      startTicks=SDL_GetTicks();
}
Uint32 upTimer::getTicks()
{
      return SDL_GetTicks() - startTicks;
}
void upTimer::stop()
{
      running=false;
      startTicks=0;
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
      playertex = loadTex("assets/player1.png");
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
      //rework dis later
      //DANGEROUS_STUFF_PLEASE CHANGE_FOR_THE_LOVE_OF_ALL_THATS_HOLY
      optionsToggle[0]=exitB;
      optionsToggle[1]=bosstex;

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
      SDL_DestroyTexture(optionsToggle[0]);
      optionsToggle[0]=NULL;
      SDL_DestroyTexture(optionsToggle[0]);
      optionsToggle[0]=NULL;
      
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
  

 

