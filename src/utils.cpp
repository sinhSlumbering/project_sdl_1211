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
upTimer iFrame, cFrame, ptimer;

bool mouseMode=false;


SDL_Renderer* ren;
SDL_Texture* titleBG;
SDL_Texture* mainMenuBG;
SDL_Texture* pauseBG;
SDL_Texture* aboutBG;
SDL_Texture* inGameBG;
SDL_Texture* backB;
SDL_Texture* highScoreB;
SDL_Texture* highScoreBG;
SDL_Texture* OptionsB;
SDL_Texture* FullScreenB;
SDL_Texture* MouseModeB;
SDL_Texture* pausenewB;
SDL_Texture* pauseexitB;
SDL_Texture* aboutB;
SDL_Texture* newGameB;
SDL_Texture* helpB;
SDL_Texture* resumeB;
SDL_Texture* exitB;
SDL_Texture* cursor;
SDL_Texture* playertex[3];
SDL_Texture* bosstex;
SDL_Texture* optionsToggle[2];
SDL_Texture* towertex;
SDL_Texture* dashtex;
SDL_Texture* poweruptex[POWERUP_N];
SDL_Texture* fireballtex;
SDL_Texture* homingtex;


Mix_Music *gBackgroundMusic;
Mix_Chunk *gScratch; 
Mix_Chunk *gForward;
Mix_Chunk *gBackword;
Mix_Chunk *ghit;
Mix_Chunk *gdie;
Mix_Chunk *gpoint;

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
 
      if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
      {
            Error("Initialization");
            success = false;
      } else {
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                  printf("linear texture filtering disabled\n");
            }
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                  printf("SDL_mixer Error: %s\n", Mix_GetError());
                  success = false;
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
                  TTF_Init();
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
 
      inGameBG = loadTex("assets/background3.png");
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
      highScoreBG = loadTex("assets/highscore.png");
      if (highScoreBG == NULL)
      {
            printf("failed to load highscore background\n");
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
      pausenewB = loadTex("assets/newgame.png");
      if (pausenewB == NULL) {
            printf("failed to load resume button\n");
            success = false;
      }
      pauseexitB = loadTex("assets/exitpause.png");
      if (pauseexitB == NULL) {
            printf("failed to load resume button\n");
            success = false;
      }
      OptionsB = loadTex("assets/mainMenu/Options.png");
      if (OptionsB == NULL) {
            printf("failed to load option button\n");
            success = false;
      }
      FullScreenB = loadTex("assets/Full Screen 0ption.png");
      if (FullScreenB == NULL) {
            printf("failed to load fullscreen button button\n");
            success = false;
      }
      MouseModeB = loadTex("assets/Mouse Mode.png");
      if (MouseModeB == NULL) {
            printf("failed to load Mouse Mode button\n");
            success = false;
      }
      exitB = loadTex("assets/mainMenu/exit.png");
      if (exitB == NULL) {
            printf("failed to load exit button\n");
            success = false;
      }
      cursor = loadTex("assets/point.png");
      if (cursor == NULL) {
            printf("failed to load cursor\n");
            success = false;
      }
      playertex[0] = loadTex("assets/player1_new.png");
      if (playertex[0] == NULL)
      {
            printf("failed to load player\n");
            success = false;
      }
      playertex[1] = loadTex("assets/player2.png");
      if (playertex[1] == NULL)
      {
            printf("failed to load player\n");
            success = false;
      }
      playertex[2] = loadTex("assets/playerwithdash.png");
      if (playertex[2] == NULL)
      {
            printf("failed to load player\n");
            success = false;
      }
      bosstex = loadTex("assets/Hilda_Berg_Intro_Sprite.png");
      if(bosstex==NULL)
      {
            success = false;
      }
      towertex = loadTex("assets/tower.png");
      if(towertex==NULL)
      {
            success = false;
      }
      dashtex = loadTex("assets/dash.png");
      if(dashtex==NULL)
      {
            success = false;
      }
      poweruptex[0] = loadTex("assets/heart.png");
      if(poweruptex[0]==NULL)
      {
            success = false;
      }
      poweruptex[1] = loadTex("assets/omniman.png");
      if(poweruptex[1]==NULL)
      {
            success = false;
      }
      fireballtex = loadTex("assets/fireball.png");
      if(fireballtex==NULL)
      {
            success = false;
      }
      homingtex = loadTex("assets/homing.png");
      if(homingtex==NULL)
      {
            success = false;
      }
      gBackgroundMusic = Mix_LoadMUS("assets/Fluffing-a-Duck.mp3");
      if (gBackgroundMusic == NULL)
      {
            printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
      }
      ghit = Mix_LoadWAV("assets/hit.wav");
      if (ghit == NULL)
      {
            printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
      }
      gpoint = Mix_LoadWAV("assets/point.wav");
      if (gpoint == NULL)
      {
            printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
      }
      gForward = Mix_LoadWAV("assets/a.wav");
      if (gForward == NULL)
      {
            printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
      }
      gBackword = Mix_LoadWAV("assets/sfx_swooshing.wav");
      if (gBackword == NULL)
      {
            printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
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

void Cal_highscore(int a)
{
      FILE *fptr;
      int num[11];

      num[10] = a;
      int b;
      fptr = fopen("assets/highscore.txt", "r");
      int i = 0;
      while ((b = getw(fptr)) != EOF)
      {
            num[i] = b;
            // printf("%d ",num[i]);
            i++;
      }
      int num2[10];
      for (int i = 0; i < 10; i++)
      {
            for (int j = 0; j < 10 - i; j++)
            {
                  if (num[j] > num[j + 1])
                  {
                        int swap = num[j];
                        num[j] = num[j + 1];
                        num[j + 1] = swap;
                  }
            }
      }
      for (i = 0; i < 10; i++)
      {
            num2[i] = num[10 - i];
      }
      fclose(fptr);
      remove("assets/highscore.txt");
      fptr = fopen("assets/highscore.txt", "w");
      for (int i = 0; i < 10; i++)
      {
            putw(num2[i], fptr);
      }
      fclose(fptr);
}
 
void printText(SDL_Renderer *renderer, int x, int y, std::string point,
             TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect)
{
      int text_width;
      int text_height;
      SDL_Surface *surface;
      SDL_Color white = {255, 255, 255, 0};

      surface = TTF_RenderText_Solid(font, point.c_str(), white);
      *texture = SDL_CreateTextureFromSurface(renderer, surface);
      text_width = surface->w;
      text_height = surface->h;
      SDL_FreeSurface(surface);
      rect->x = x;
      rect->y = y;
      rect->w = text_width;
      rect->h = text_height;
}

void highscore_printing(int a, int x, int y)
{

      std::string show = std::to_string(a);
      printText(ren, x, y, show, font, &scoretex, &area);
      SDL_RenderCopy(ren, scoretex, NULL, &area);
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
      SDL_DestroyTexture(playertex[0]);
      playertex[0]=NULL;
      SDL_DestroyTexture(playertex[2]);
      playertex[2]=NULL;
      SDL_DestroyTexture(playertex[2]);
      playertex[2]=NULL;
      SDL_DestroyTexture(bosstex);
      bosstex=NULL;
      SDL_DestroyTexture(optionsToggle[0]);
      optionsToggle[0]=NULL;
      SDL_DestroyTexture(optionsToggle[0]);
      SDL_DestroyTexture(FullScreenB);
      SDL_DestroyTexture(MouseModeB);
      optionsToggle[0]=NULL;
      SDL_DestroyTexture(scoretex);
      scoretex=NULL;
      SDL_DestroyTexture(towertex);
      towertex=NULL;
      SDL_DestroyTexture(dashtex);
      dashtex=NULL;
      SDL_DestroyTexture(poweruptex[0]);
      poweruptex[0]=NULL;
      SDL_DestroyTexture(poweruptex[1]);
      poweruptex[1]=NULL;
      SDL_DestroyTexture(fireballtex);
      fireballtex=NULL;
      SDL_DestroyTexture(homingtex);
      homingtex=NULL;
      
      SDL_DestroyRenderer(ren);
      ren = NULL;
      win.free();
      TTF_CloseFont(font);
      Mix_FreeMusic(gBackgroundMusic);
      Mix_FreeChunk(ghit);
      Mix_FreeChunk(gForward);
      Mix_FreeChunk(gBackword);
      Mix_FreeChunk(gpoint);
      Mix_Quit();
      TTF_Quit();
      IMG_Quit();
      SDL_Quit();
}
 
bool mouseIsInside(SDL_Rect* rect, int mousex, int mousey) {
      return (mousex >= rect->x && mousex <= rect->x + rect->w) && (mousey >= rect->y && mousey <= rect->y + rect->h);
}
 
bool cursorpoints(SDL_Rect* rect, SDL_Rect* cursorDim) {
      return (cursorDim->y >= rect->y) && ((cursorDim->h + cursorDim->y) <= (rect->y + rect->h));
}
  

 

