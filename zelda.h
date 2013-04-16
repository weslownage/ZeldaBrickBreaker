/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 9 - Tank War Header (Enhancement 4)
/////////////////////////////////////////////////////////////////////////

#ifndef _TANKWAR_H
#define _TANKWAR_H

#include "allegro.h"

//define some game constants
#define MODE GFX_SAFE
#define WIDTH 740
#define HEIGHT 580
#define MAXSPEED 2
#define BULLETSPEED 6

//define some colors
#define TAN makecol(255,242,169)
#define BURST makecol(255,189,73)
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
#define GREEN makecol(20,160,20)
#define DGREEN makecol(20,90,20)
#define PURPLE makecol(174,74,174)
#define BLUE makecol(40,5,210)
#define RED makecol(200,0,0)


//music stuff
SAMPLE *dying;
SAMPLE *hurt;
SAMPLE *hit;
SAMPLE *shoot;
SAMPLE *explosion;
SAMPLE *lostwoods;
SAMPLE *lostwoodsdubstep;
SAMPLE *navi[5];
SAMPLE *nhello;
SAMPLE *nhey;
SAMPLE *nlisten;
SAMPLE *nlook;
SAMPLE *nwatchout;
SAMPLE *secret;
SAMPLE *songofstorms;
SAMPLE *maintheme;
SAMPLE *winning;

int panning =128;
int pitch = 1000;
int volume = 128;

//define the sprite structure
typedef struct SPRITE
{
//new elements
    int dir, alive;

    int x,y,r;
    int width,height;
	int ydir, xdir;
    int xspeed,yspeed;
    int xdelay,ydelay;
    int xcount,ycount;
    int curframe,maxframe,animdir;
    int framecount,framedelay;
}SPRITE;

//player, ball, block, paddle SPRITES
SPRITE myplayer[2];
SPRITE *player[2];
SPRITE mybullets[5];
SPRITE *bullet[5];
SPRITE myballs[9];
SPRITE *balls[9];
SPRITE myblock[450];
SPRITE *block[450];
SPRITE powerups[3];
SPRITE *powerup[3];

//replacement for the "score" variable in tank struct
int scores[2];

//declare some variables
int gameover = 0;
int boarder = 0;
int lives = 3;
int numofballs = 1;
int level = 1;
int point = 0;
int bcounter = 0;
int navimusic;
int playsong = 0;
int makepowerup = 0;

//player stuff
int playerpaddle = 0;
int playerlargetimer = 0;
int playershoottimer = 0;
int canshoot = 0;
int numofswords = 0;
int bonus = 0;


//power up vairable


//sprite bitmaps
BITMAP *player_bmp[3];
BITMAP *ball_bmp;
BITMAP *tank_bmp[2];
BITMAP *sword_bmp;
BITMAP *explode_bmp;
BITMAP *buffer;
BITMAP *block_bmp;
BITMAP *powerup_bmp[3];


//background bitmaps
BITMAP *bg[3];

//timer variables
volatile int counter;
volatile int ticks;
volatile int framerate;

volatile int sec = 0;
volatile int centiSec = 0;
volatile int min = 0;



//function prototypes
int drawlvl1();
void drawlvl2();
void updateplayer();
void updateball(int num);
void setupplayer();
void setupball();
void setupblocks();
int setupsound();
void setupshoot();
void drawgamestats();
int checkballsalive();
void playnavisound();
int checkloss();




//void drawtank(int num);
//void erasetank(int num);
//void movetank(int num);
void explode(int num, int x, int y);
void updatebullet(int num);
void fireweapon(int num);
void getinput();
void score(int);
void setupscreen();


#endif

