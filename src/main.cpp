#include "header.hpp"
 
bool quit = false;
screens screen = TITLE_SCREEN;
bool isrunning = true;
//bool Fullscreen=false; 
int main(int argc, char const *argv[]) {
      if (!init()) {
            printf("initialization failed\n");
      } else {
            if (!loadMedia()) {
                  printf("failed to load media\n");
            } else {
                  while (!quit) {
                        switch (screen) {
                              case TITLE_SCREEN:
                                    titlescreen();
                                    break;
 
                              case MAIN_MENU:
                                    main_menue();
                                    break;
 
                              case IN_GAME:
                                    gamestart();
                                    break;
 
                              case HIGH_SCORES:
                                    high_score();
                                    break;
 
                              case HELP:
                                    help();
                                    break;
 
                              case ABOUT:
                                    about();
                                    break;
 
                              case PAUSE:
                                    pauseM();
                                    break;
                        }
                  }
 
                  SDL_Delay(1000 / 60);
            }
            close();
      }
      return 0;
}
