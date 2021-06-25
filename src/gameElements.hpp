#ifndef GAMEELEMENTS_H
#define GAMEELEMENTS_H
//the player character
struct Player
{
      //dimensions of the player character
      int width;
      int height;
      //movement of the player per frame in both directions
      int xStep;
      int yStep;
      //the spacing of the hitbox inside the player
      int hbspX, hbspY;
      //the current player texture number
      int tex;
      //velocity of of the player bullet and the number
      int bulletVel, bulletIndex;
      //bullet dimensions
      int bulletW, bulletH;
      //controlls bullet fire
      bool fire;

      //Hitbox, player and bullet dimensions and position 
      SDL_Rect htbx;
      SDL_Rect playerdim;
      SDL_Rect bulletdim[PLAYERBULLET_N];
      
      //player position
      int xPos;
      int yPos;
      //player angle
      double angle;
      //constructor
      Player();

      //initalizer
      void init();
      //scales to the current screen size
      void scale();
      //handles the keyboard inputs to move the player
      void handleEvent();
      //moves the player
      void move(int x, int y);
      //player bullet subroutine
      void bullet();
      //renders the player
      void render();
      //checks for collission with the player
      bool col(SDL_Rect*);
};
extern Player player;
/*
      ingame elements also follow a naming scheme
      width and height refers to that elements with and height
      xVel and yVel refers to velocities in the x and y direction
      xPos and yPos refers to positions along the axes
      htbx refers to hitboxes
      all have a Constructor function
      init initalizes the struct
      scale scales the struct to the current screen size
      render renders the elements
      and move moves the elements 

      any deviation or addition is explicitly stated
*/
struct Boss
{
      int width;
      int height;
      int xVel;
      int yVel;
      //determines the direction in which the boss will move
      int scrolldir;
      int xPos;
      int yPos;
      //hitbox itself is used for rendering
      SDL_Rect htbx;
      
      Boss();

      void init();
      void scale();
      void move();
      void render();
};

extern Boss plane;

struct Wall
{
      int width;
      int height;
      int xVel;
      int yVel;
      //used for regulation of difficulty
      int mod;
      //hitbox itself is used for rendering
      SDL_Rect htbx;

      int xPos;
      int yPos;

      Wall();

      void move();
      void render();
};


struct Walls 
{
      //padding between two walls
      int padding;
      //number of wall
      int wall_number;
      //an array of inidividual walls;
      Wall wallz[3];
      Walls();

      void init();
      void scale();
      void move();
      void render();
      //checks collision with walls
      void colls();
};

extern Walls walls;

struct Powerup
{
      //signals spawing 
      bool spawn;
      //signals if a powerup is on screen
      bool running;
      //dimension of a powerup midflight and initially
      SDL_Rect powerupdim, initdim;
      //velocity of the powerup
      int vel;
      //enumerated to help randomization
      enum pUP{
            LIFE,
            INVINCIBILE,
            WAIT
      };
      //current powerup
      int current;

      Powerup();
      
      void init();
      void scale();
      void move();
      //chooses which powerup is active
      void choose();
      //runs the powerup subroutine
      void run();
};

extern Powerup powerup;

//enemy attacks
struct Attack
{
      //controls the spawing of a new attack
      bool spawn;
      //dimension and position of attacks and their hitboxes
      SDL_Rect bouncedim, homedim;
      SDL_Rect bhtbx, hhtbx;
      //velocites in both axes of attacks
      int bXvel, bYvel, hXvel, hYvel;
      //angle of the attack texture
      double angle;
      //enumerated to help randomiztion
      enum att
      {
            BOUNCING,
            HOMING
      };
      //current attack
      int current;

      Attack();
      
      void init();
      void scale();
      void choose();
      //bouncing attack subroutine
      void bounce();
      //homing attack subroutine
      void home();
      //runs the attack subroutine
      void run();
};

extern Attack attack;


#endif