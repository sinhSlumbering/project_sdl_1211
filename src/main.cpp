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
                                    mainMenu.run();
                                    break;
 
                              case IN_GAME:
                                    gamestart();
                                    break;
 
                              case HIGH_SCORES:
                                    highScore.run();
                                    break;
 
                              case HELP:
                                    help.run();
                                    break;
 
                              case ABOUT:
                                    about.run();
                                    break;
 
                              case PAUSE:
                                    pause.run();
                                    break;
                        }
                  }
 
                  SDL_Delay(1000 / 60);
            }
            close();
      }
      return 0;
}
