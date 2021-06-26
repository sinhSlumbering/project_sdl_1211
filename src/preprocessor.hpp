#ifndef PREPROCESSOR
#define PREPROCESSOR
//Using sdl, sdl image, sdl true type fonts, sdl mixer
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>
#include <time.h>

//preprocessors

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define POWERUP_N 3
#define LIVES_ON_START 3
#define DIFFICULTY_STEP_HP 1000
#define STARTING_DIFFICULTY_THRESHOLD 9000
#define BOSSHEALTH_MAX 9999 
#define POWERUP_INTERVAL 15000
#define PLAYERBULLET_N 5
#define PLAYERBULLET_RATE 300
#define PLAYERBULLET_DAMMAGE 50
#define IFRAME_TIME 1500
#define DASH_INTERVAL 500
#define DASH_IFRAME_STOP 300
#define WALL_START_TIME 5000
#define WALL_SCROLL_SPEED 5
#define ATTACK_START_TIME 10000
#define POWERUP_START_TIME 3000
#define POWERUP_VELOCITY 5

#endif