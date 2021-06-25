#include "utills.hpp"
#include "globalvars.hpp"
#include "textureMusic.hpp"
#include "gameElements.hpp"

gWindow win;

//updates screen variables and the factors by which it has changed
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



bool mouseMode=false;
extern long prevtime=0;
extern float remaintime=0;

SDL_Renderer* ren;

TTF_Font *font= TTF_OpenFont("assets/Sans/Sans.ttf",24);

SDL_Color White = {255,255,255,0};
SDL_Color Megenta = {236, 134, 134, 0};

//the game window struct
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
      //toggles fullscreen and records the state in a variable
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
      //window creation with screen consts and undefined position
      window=SDL_CreateWindow("PlaneDude", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
      //renderer accelerated by the 1st available graphics hardware and with vsync
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
      //freeing memory
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

//logs error.
void Error(const std::string msg) {
      printf("%s Error: %s\n", msg, SDL_GetError());
}
 


 
// void imgLoadError(const std::string path) {
//       printf("failed to load %s IMGERROR: %s\n", path, IMG_GetError());
// }

// SDL initialisation
bool init() {
      //success flag
      bool success = true;
      //initializes SDL
      if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
      {
            Error("Initialization");
            success = false;
      } else {
            //linear filtering
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                  printf("linear texture filtering disabled\n");
            }
            //initializing SDL_mixer
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                  printf("SDL_mixer Error: %s\n", Mix_GetError());
                  success = false;
            }
            //initializing window
            if(!win.init())
            {
                  Error("window creation");
                  success=false;
            } 
            else {
                  //create renderer
                  ren = win.createRenderer();
                  //initialize sdl image
                  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                  if (!(IMG_Init(imgFlags) & imgFlags)) {
                        printf("Initialization Error IMG_Error: %s\n", IMG_GetError());
                        success = false;
                  }
                  //fonts
                  TTF_Init();
            }
      }
      return success;
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

//clears highscore in options
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

void optimizeFPS(long *prevtime, float *remainder)
{
      long wait, frameTime;
      //Ideally wait 16.667ms
      wait = 16 + *remainder;
      //record fraction of ms for next pass
      *remainder -= (int)*remainder;
      //the current frametime by subtracting previous
      frameTime = SDL_GetTicks() - *prevtime;
      //delay between frametimes
      wait -= frameTime;
      //incase of a larger delay default to 1ms
	if (wait < 1)	wait = 1;
      //wait before next frame
	SDL_Delay(wait);
	*remainder += 0.667;
      //record frametime for this frame
	*prevtime = SDL_GetTicks();
}



