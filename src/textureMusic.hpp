#ifndef TEXTURES_MUSIC_H
#define TEXTURE_MUSIC_H
#include "preprocessor.hpp"
/*
textures used in the game follow a naming scheme
BG refers to background texture
B refers to button textures
tex is the suffix of game objects
text is the suffix of text rendered on menus
the notable exception being the options toggle and cursor which are self explanatory
and tscreentex used for displaying text on screen
*/
extern SDL_Texture* titleBG;
extern SDL_Texture* gameoverBG;
extern SDL_Texture* mainMenuBG;
extern SDL_Texture* pauseBG;
extern SDL_Texture* aboutBG;
extern SDL_Texture* inGameBG;
extern SDL_Texture* backB;
extern SDL_Texture* highScoreB;
extern SDL_Texture* highScoreBG;
extern SDL_Texture* OptionsB;
extern SDL_Texture* FullScreenB;
extern SDL_Texture* MouseModeB;
extern SDL_Texture* pausenewB;
extern SDL_Texture* pauseexitB;
extern SDL_Texture* aboutB;
extern SDL_Texture* newGameB;
extern SDL_Texture* continueB;
extern SDL_Texture* helpB;
extern SDL_Texture* inhelp;
extern SDL_Texture* resumeB;
extern SDL_Texture* exitB;
extern SDL_Texture* cursor;
extern SDL_Texture* playertex[3];
extern SDL_Texture* playerbullet;
extern SDL_Texture* bosstex[2];
extern SDL_Texture* optionsToggle[2];
extern SDL_Texture* cleartex;
extern SDL_Texture* scoretex;
extern SDL_Texture* lifetex;
extern SDL_Texture* dashtex;
extern SDL_Texture* hittex;
extern SDL_Texture* towertex;
extern SDL_Texture* poweruptex[POWERUP_N];
extern SDL_Texture* fireballtex;
extern SDL_Texture* homingtex;
extern SDL_Texture* Bombtex;
extern SDL_Texture* tscreentex;
extern SDL_Texture* fullScreenText;
extern SDL_Texture* mouseModeText;

extern Mix_Music *gBackgroundMusic;
extern Mix_Chunk *gpoint; 
extern Mix_Chunk *gForward;
extern Mix_Chunk *gBackword;
extern Mix_Chunk *ghit;
extern Mix_Chunk *gdie;

#endif