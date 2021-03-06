#include "loadOps.hpp"
#include "globalvars.hpp"


//This are the textures frequently used
//they are preprocessed and stored in global variables

SDL_Texture* titleBG;
SDL_Texture* gameoverBG;
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
SDL_Texture* hittex;
SDL_Texture* poweruptex[POWERUP_N];
SDL_Texture* fireballtex;
SDL_Texture* homingtex;
SDL_Texture* Bombtex;
SDL_Texture* tscreentex;
SDL_Texture* fullScreenText;
SDL_Texture* mouseModeText;

Mix_Music *gBackgroundMusic;
Mix_Chunk *gScratch; 
Mix_Chunk *gForward;
Mix_Chunk *gBackword;
Mix_Chunk *ghit;
Mix_Chunk *gdie;
Mix_Chunk *gpoint;




//Loads necessary textures and musics
bool loadMedia() {
      bool success = true;
 
      titleBG = loadTex("assets/titlescreen.jpg");
      if (titleBG == NULL) {
            printf("failed to load title screen\n");
            success = false;
      }
      gameoverBG = loadTex("assets/game over.jpg");
      if (gameoverBG == NULL) {
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
      pausenewB = loadTex("assets/new game.png");
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
      hittex = loadTex("assets/hit.png");
      if(hittex==NULL)
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
      poweruptex[2] = loadTex("assets/clock.png");
      if(poweruptex[2]==NULL)
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
      Bombtex = loadTex("assets/Bomb.png");
      if(Bombtex==NULL)
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
            printf("%s IMG_Error: %s\n", path.c_str(), IMG_GetError());
      } else {
            newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
            if (newTexture == NULL) {
                  printf("texture creation from %s failed. SDL_Error: %s\n", path.c_str(), SDL_GetError());
            }
      }
      return newTexture;
}

//frees ram
void close() {
      SDL_DestroyTexture(titleBG);
      titleBG = NULL;
      SDL_DestroyTexture(gameoverBG);
      gameoverBG = NULL;
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
      SDL_DestroyTexture(hittex);
      hittex=NULL;
      SDL_DestroyTexture(poweruptex[0]);
      poweruptex[0]=NULL;
      SDL_DestroyTexture(poweruptex[1]);
      poweruptex[1]=NULL;
      SDL_DestroyTexture(poweruptex[2]);
      poweruptex[2]=NULL;
      SDL_DestroyTexture(fireballtex);
      fireballtex=NULL;
      SDL_DestroyTexture(homingtex);
      homingtex=NULL;
      SDL_DestroyTexture(Bombtex);
      Bombtex=NULL;
      
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