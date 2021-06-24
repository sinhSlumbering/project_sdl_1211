#include "header.hpp"

gWindow win;

void updatescreen()
{
      screen_x_frac=(float)screen_width;
      screen_y_frac=(float)screen_height;
      SDL_GetWindowSize(win.window, &screen_width, &screen_height);
      screen_x_frac=screen_width/screen_x_frac;
      screen_y_frac=screen_height/screen_y_frac;
}

int screen_width=SCREEN_WIDTH;
int screen_height=SCREEN_HEIGHT;
float screen_x_frac=1;
float screen_y_frac=1;
int phase = 0;

About about;
Help help;
HighScore highScore;
Pause pause;
MainMenue mainMenu;
Options options;
upTimer iFrame, cFrame, ptimer, btimer, diffTimer;

bool mouseMode=false;
extern long prevtime=0;
extern float remaintime=0;

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
SDL_Texture* continueB;
SDL_Texture* helpB;
SDL_Texture* inhelp;
SDL_Texture* resumeB;
SDL_Texture* exitB;
SDL_Texture* cursor;
SDL_Texture* playertex[3];
SDL_Texture* playerbullet;
SDL_Texture* bosstex[2];
SDL_Texture* optionsToggle[2];
SDL_Texture* cleartex;
SDL_Texture* towertex;
SDL_Texture* dashtex;
SDL_Texture* poweruptex[POWERUP_N];
SDL_Texture* fireballtex;
SDL_Texture* homingtex;
SDL_Texture* tscreentex;
SDL_Texture* fullScreenText;
SDL_Texture* mouseModeText;

TTF_Font *font= TTF_OpenFont("assets/Sans/Sans.ttf",24);

SDL_Color White = {255,255,255,0};
SDL_Color Megenta = {236, 134, 134, 0};

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

// SDL initialisation
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

//Loads necessary textures and musics
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
 
      inGameBG = loadTex("assets/newbg.png");
      if (inGameBG == NULL) {
            printf("failed to load game screen\n");
            success = false;
      }
 
      backB = loadTex("assets/Back.jpg");
      if (backB == NULL) {
            printf("failed to load back button\n");
            success = false;
      }
 
      aboutB = loadTex("assets/mainMenu/about.png");
      if (aboutB == NULL) {
            printf("failed to load about button\n");
            success = false;
      }
      highScoreB = loadTex("assets/mainMenu/highscore.png");
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
      newGameB = loadTex("assets/mainMenu/new game.png");
      if (newGameB == NULL) {
            printf("failed to load newgame button\n");
            success = false;
      }
      continueB = loadTex("assets/mainMenu/continue.png");
      if (continueB == NULL) {
            printf("failed to load continue button\n");
            success = false;
      }
      helpB = loadTex("assets/mainMenu/help.png");
      if (helpB == NULL) {
            printf("failed to load help button\n");
            success = false;
      }
      inhelp = loadTex("assets/Help.png");
      if (inhelp == NULL) {
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
      OptionsB = loadTex("assets/mainMenu/options.png");
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
            printf("failed to load playerdash\n");
            success = false;
      }
      playerbullet= loadTex("assets/playerbullet.png");
      if (playerbullet == NULL)
      {
            printf("failed to load playerbullet\n");
            success = false;
      }
      bosstex[0] = loadTex("assets/Hilda_Berg_Intro_Sprite.png");
      if(bosstex[0]==NULL)
      {
            success = false;
      }
      bosstex[1] = loadTex("assets/hilda breg phase 2.png");
      if(bosstex[1]==NULL)
      {
            success = false;
      }
      towertex = loadTex("assets/log.png");
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
      optionsToggle[0] = loadTex("assets/off.png");
      if (optionsToggle[0] == NULL)
      {
            printf("failed to load optionstoggle\n");
            success = false;
      }
      optionsToggle[1] = loadTex("assets/on.png");
      if (optionsToggle[1] == NULL)
      {
            printf("failed to load optionstoggle\n");
            success = false;
      }
      cleartex = loadTex("assets/clear.png");
      if(cleartex == NULL){
            printf("failed to load clear button\n");
            success = false;
      }
      return success;
}
//takes the path and makes a texture
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

void scaleIntX(int *x){
      double y = (double)(*x);
      *x=(int)( y * screen_x_frac);
}
void scaleIntY(int *y){
      int c=*y;
      double x = (double)(*y);
      *y=(int)(x * screen_y_frac);
      if(*y==0) *y=c;
}
void scaleRect(SDL_Rect* r)
{
      scaleIntX(&r->x);
      scaleIntY(&r->y);
      scaleIntX(&r->w);
      scaleIntY(&r->h);
      if(r->h<=10) r->h=1;
      if(r->w<=10) r->w=1;
}
void scaleSqr(SDL_Rect* r)
{
      printf("before %d %d\n", r->w, r->h);
      scaleIntX(&r->x);
      scaleIntY(&r->y);
      scaleIntY(&r->w);
      if(r->w<=10) r->w=10;
      else r->h=r->w;
      printf("after %d %d\n", r->w, r->h);
}
// Stores top 10 scores in a file
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
// Clears pre existing high scores
void highscoreclear(){
      FILE* fptr;
      remove("assets/highscore.txt");
      fptr = fopen("assets/highscore.txt", "w");
      for (int i = 0; i < 10; i++)
      {
            putw(0, fptr);
      }
      fclose(fptr);
}
//makes a texture of a string to present in the renderer
void printText(SDL_Renderer *renderer, int x, int y, std::string point,
              SDL_Texture **texture, SDL_Rect *rect, SDL_Color white)
{
      int text_width;
      int text_height;
      SDL_Surface *surface;
      // SDL_Color white = {236, 134, 134, 0};

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
//Prints highscores using printtext
void highscore_printing(int a, int x, int y)
{

      std::string show = std::to_string(a);
      printText(ren, x, y, show, &scoretex, &area, White);
      SDL_RenderCopy(ren, scoretex, NULL, &area);
}
//Gets the current playing environment from a text file in the following variables
//score,lives,bosshealth,wall number, attack speed in x direction, attack speed in y direction,
//wall speed, difficulty, boss phase
void play(int *a, int *b, int *c, int *d, int *e, int *f, int *g, int *h,int *i){
      FILE* fptr = fopen("assets/save game.txt","r");
      *a = getw(fptr);
      *b = getw(fptr);
      *c = getw(fptr);
      *d = getw(fptr);
      *e = getw(fptr);
      *f = getw(fptr);
      *g = getw(fptr);
      *h = getw(fptr);
      *i = getw(fptr);
      fclose(fptr);
}
//Saves the current playing environment to a text file in the following variables
//score,lives,bosshealth,wall number, attack speed in x direction, attack speed in y direction,
//wall speed, difficulty, boss phase
void save_game(int playerscore, int lifeleft, int boss_health, int a, int b, int c, int d, int e, int f){
      remove("assets/save game.txt");
      FILE* fptr = fopen("assets/save game.txt","w");
      putw(playerscore,fptr);
      putw(lifeleft,fptr);
      putw(boss_health,fptr);
      putw(a, fptr);
      putw(b, fptr);
      putw(c, fptr);
      putw(d, fptr);
      putw(e,fptr);
      putw(f,fptr);
      fclose(fptr);
}
//increases difficulty as boss health decreases
void difficulty(){
      if(walls.wall_number >= 3)
      {
            wallspeed += 5;
      }
      else walls.wall_number++, walls.wallz[walls.wall_number-1].xPos=walls.wallz[walls.wall_number-2].xPos+walls.padding;
      if(attack.bXvel < 0){
            attack.bXvel -= 2;
      }
      else{
            attack.bXvel += 2;
      }
      if(attack.bYvel < 0){
            attack.bYvel -= 2;
      }
      else{
            attack.bYvel += 2;
      } 
      //printf("\nwall %d\n", walls.wall_number);
}
void boss_change_phase(SDL_Rect r, SDL_Rect background){
      SDL_Rect source = {0,0,441, 689};
      int speed = screen_width/160;
      int step = (133+speed-1)/speed;
      int speed2 = 441/step;
      while (r.x < 800)
      {
            SDL_RenderClear(ren);
            SDL_RenderCopy(ren, inGameBG, &background, NULL);
            SDL_RenderCopy(ren,bosstex[phase],&source,&r);
            SDL_RenderPresent(ren);
            r.x+=speed;
            r.w-=speed;
            source.w-=speed2;
            if(r.x >= 800){
                  r.x = 800;
                  r.w = 0;
            }
            if(source.w <= 0){
                  source.w = 0;
            }
            SDL_Delay(60);
      }
      phase = 1;
      while (r.x > 667)
      {
            SDL_RenderClear(ren);
            player.render();
            SDL_RenderCopy(ren, inGameBG, &background, NULL);
            walls.render();
            SDL_RenderCopy(ren,bosstex[phase],&source,&r);
            SDL_RenderPresent(ren);
            r.x-=speed;
            r.w+=speed;
            source.w+=speed2;
            if(r.x <= 667){
                  r.x = 667;
                  r.w = 133;
            }
            if(source.w >= 441){
                  source.w = 441;
            }
            SDL_Delay(60);
      }
}
void optimizeFPS(long *prevtime, float *remainder)
{
      long wait, frameTime;
      wait = 16 + *remainder;
      *remainder -= (int)*remainder;

      frameTime = SDL_GetTicks() - *prevtime;
      wait -= frameTime;

	if (wait < 1)	wait = 1;

	SDL_Delay(wait);

	*remainder += 0.667;
	*prevtime = SDL_GetTicks();
}

//frees ram
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
      SDL_DestroyTexture(bosstex[0]);
      bosstex[0]=NULL;
      SDL_DestroyTexture(bosstex[1]);
      bosstex[1]=NULL;
      SDL_DestroyTexture(optionsToggle[0]);
      optionsToggle[0]=NULL;
      SDL_DestroyTexture(optionsToggle[1]);
      optionsToggle[1]=NULL;
      SDL_DestroyTexture(cleartex);
      cleartex=NULL;
      SDL_DestroyTexture(FullScreenB);
      SDL_DestroyTexture(MouseModeB);
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
  

 

