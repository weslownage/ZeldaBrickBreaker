/************************************
* Name:		   John Wesolowski
* Assignment:  Project 2
* Class:	   CST 306
* Teacher:	   Dr. Byun
* Date:		   12/12/12
* Abstract:	  A legend of Zelda themed brick breaker. This game features 3 power ups, large paddle, speed up, and shooting.
			  The player starts off with 3 lives and must break all the block to continue. Breaking 100 blocks gratns a new life, and if player
			  loses all lives, the game is over. 
**************************************/



#include "zelda.h"
//int speed;
//int dir;

/* timer interrupt handler */
void inc_sec(void)
{
   sec++;
   
   if(sec > 59)
   {
	   min++;
	   sec=0;
   }
   if(playerlargetimer > 0)
	   playerlargetimer--;

   if(playershoottimer > 0)
   {
	   playershoottimer--;
   }else
	   canshoot = 0;
}
END_OF_FUNCTION(inc_sec)

//Centi-Second function
void inc_centiSec(void)
{
   centiSec++;
   if(centiSec > 99 )
       centiSec =0;
}
END_OF_FUNCTION(inc_centiSec)


/* //////////////////////////////////////  */

////////////////////////////////////////////////////////
/////             Colision detection			   /////
////////////////////////////////////////////////////////
int inside(int x,int y,int left,int top,int right,int bottom)
{
    if (x > left && x < right && y > top && y < bottom)
        return 1;
    else
        return 0;
}
int playercollidedright(SPRITE *ball, SPRITE *block)
{
    int wa = ball->x + ball->width;
    int ha =ball->y + ball->height;
    int wb = block->x + block->width;
    int hb = block->y + block->height;
	int bx;
	int by = 0;
	if(playerpaddle == 0 || playerpaddle == 2)
	{
		bx = 85;
	}
    if(playerpaddle == 1)
	{
		bx = 170;
	}
    

    if (inside(ball->x, ball->y, block->x+bx, block->y+by, wb, hb-by) ||//
		inside(ball->x+12, ball->y, block->x+bx, block->y+by, wb, hb-by) ||
		inside(ball->x, ball->y+25, block->x+bx, block->y+by, wb, hb-by) ||
		inside(ball->x+12, ball->y+25, block->x+bx, block->y+by, wb, hb-by) ||
		inside(ball->x+24, ball->y+25, block->x+bx, block->y+by, wb, hb-by) ||
        inside(ball->x, ha, block->x+bx, block->y+by, wb, hb-by) ||
        inside(wa, ball->y, block->x+bx, block->y+by, wb, hb-by) ||
        inside(wa, ha, block->x+bx, block->y+by, wb, hb-by))
        return 1;
    else
        return 0;
}
int playercollidedleft(SPRITE *ball, SPRITE *block)
{
    int wa = ball->x + ball->width;
    int ha =ball->y + ball->height;
    int wb = block->x + block->width;
    int hb = block->y + block->height;
    int bx; 
	int by = 0;
	if(playerpaddle == 0 || playerpaddle == 2)
	{
		bx = 85;
	}
    if(playerpaddle == 1)
	{
		bx = 170;
	}
   

    if (inside(ball->x, ball->y, block->x, block->y+by, wb-bx, hb-by) ||//
		inside(ball->x+12, ball->y, block->x, block->y+by, wb-bx, hb-by) ||
		inside(ball->x, ball->y+25, block->x, block->y+by, wb-bx, hb-by) ||
		inside(ball->x+12, ball->y+25, block->x, block->y+by, wb-bx, hb-by) ||
		inside(ball->x+24, ball->y+25, block->x, block->y+by, wb-bx, hb-by) ||
        inside(ball->x, ha, block->x, block->y+by, wb-bx, hb-by) ||
        inside(wa, ball->y, block->x, block->y+by, wb-bx, hb-by) ||
        inside(wa, ha, block->x, block->y+by, wb-bx, hb-by))
        return 1;
    else
        return 0;
}
int playercollidedmiddle(SPRITE *ball, SPRITE *block)
{
    int wa = ball->x + ball->width;
    int ha =ball->y + ball->height;
    int wb = block->x + block->width;
    int hb = block->y + block->height;
    int bx; 
	int by = 0;

	if(playerpaddle == 0 || playerpaddle == 2)
	{
		bx = 10;
	}
    if(playerpaddle == 1)
	{
		bx = 20;
	}
 

    if (inside(ball->x, ball->y, block->x+bx, block->y+by, wb-bx, hb-by) ||//
		inside(ball->x+12, ball->y, block->x+bx, block->y+by, wb-bx, hb-by) ||
		inside(ball->x, ball->y+25, block->x+bx, block->y+by, wb-bx, hb-by) ||
		inside(ball->x+12, ball->y+25, block->x+bx, block->y+by, wb-bx, hb-by) ||
		inside(ball->x+24, ball->y+25, block->x+bx, block->y+by, wb-bx, hb-by) ||
        inside(ball->x, ha, block->x+bx, block->y+by, wb-bx, hb-by) ||
        inside(wa, ball->y, block->x+bx, block->y+by, wb-bx, hb-by) ||
        inside(wa, ha, block->x+bx, block->y+by, wb-bx, hb-by))
        return 1;
    else
        return 0;
}
int ballcollidedtop(SPRITE *a, SPRITE *b)
{
    int wa = a->x + a->width;
    int ha =a->y + a->height;
    int wb = b->x + b->width;
    int hb = b->y + b->height;
    int bx = 0;
    int by = 0;

    if (inside(a->x, a->y, b->x+bx, b->y+by, wb-bx, hb-by) ||//top left		
		inside(a->x+12, a->y, b->x+bx, b->y+by, wb-bx, hb-by) ||//top middle
		inside(a->x+24, a->y, b->x+bx, b->y+by, wb-bx, hb-by))//top right
        return 1;
    else
        return 0;

	//inside(a->x, a->y+20, b->x+bx, b->y+by, wb-bx, hb-by) ||//bottom left
		//inside(a->x+10, a->y+20, b->x+bx, b->y+by, wb-bx, hb-by) ||//bottom middle
		//inside(a->x+20, a->y+20, b->x+bx, b->y+by, wb-bx, hb-by) ||//bottom right
  //      inside(wa, a->y, b->x+bx, b->y+by, wb-bx, hb-by) ||
  //      inside(wa, ha, b->x+bx, b->y+by, wb-bx, hb-by))
}
int ballcollidedbottom(SPRITE *a, SPRITE *b)
{
    int wa = a->x + a->width;
    int ha =a->y + a->height;
    int wb = b->x + b->width;
    int hb = b->y + b->height;
    int bx = 0;
    int by = 0;

    if (inside(a->x, a->y+20, b->x+bx, b->y+by, wb-bx, hb-by) ||//top left		
		inside(a->x+10, a->y+20, b->x+bx, b->y+by, wb-bx, hb-by) ||//top middle
		inside(a->x+20, a->y+20, b->x+bx, b->y+by, wb-bx, hb-by))//top right
        return 1;
    else
        return 0;

	//inside(a->x, a->y+20, b->x+bx, b->y+by, wb-bx, hb-by) ||//bottom left
		//inside(a->x+10, a->y+20, b->x+bx, b->y+by, wb-bx, hb-by) ||//bottom middle
		//inside(a->x+20, a->y+20, b->x+bx, b->y+by, wb-bx, hb-by) ||//bottom right
  //      inside(wa, a->y, b->x+bx, b->y+by, wb-bx, hb-by) ||
  //      inside(wa, ha, b->x+bx, b->y+by, wb-bx, hb-by))
}
int powerupcollided(SPRITE *a, SPRITE *b)
{
	int wa = a->x + a->width;
    int ha =a->y + a->height;
    int wb = b->x + b->width;
    int hb = b->y + b->height;
    int bx = 0;
    int by = 0;

    if (inside(a->x, a->y+16, b->x+bx, b->y+by, wb-bx, hb-by) ||//bottom left		
		inside(a->x+8, a->y+16, b->x+bx, b->y+by, wb-bx, hb-by) ||//bottom middle
		inside(a->x+16, a->y+16, b->x+bx, b->y+by, wb-bx, hb-by))//bottom right
        return 1;
    else
        return 0;
}
int swordcollided(SPRITE *a, SPRITE *b)
{
	int wa = a->x + a->width;
    int ha =a->y + a->height;
    int wb = b->x + b->width;
    int hb = b->y + b->height;
    int bx = 0;
    int by = 0;

    if (inside(a->x, a->y, b->x+bx, b->y+by, wb-bx, hb-by) ||//top left		
		inside(a->x+7, a->y, b->x+bx, b->y+by, wb-bx, hb-by) ||//top middle
		inside(a->x+14, a->y, b->x+bx, b->y+by, wb-bx, hb-by))//top right
        return 1;
    else
        return 0;
}

////////////////////////////////////////////////////////
/////             Drawing Levels				   /////
////////////////////////////////////////////////////////
int drawlvl1()
{
	int n, k;
	int temp = 0;


	//draw top triangle of triforce
	//loop for the height
	for(n=0; n<8; n++)
	{
		//loop for the length
		for(k=0; k<=n; k++)
		{			
				if(block[bcounter]->alive)
				{
					block[bcounter]->x = (350 - (k*20));
					block[bcounter]->y = (40 + (13*n));
					draw_sprite(buffer, block_bmp, block[bcounter]->x, block[bcounter]->y);
					//draw_sprite(buffer, block_bmp, block[counter]->x+(40*k), block[counter]->y);
					temp++;
					bcounter++;
				}
				else
					bcounter++;
				if(block[bcounter]->alive)
				{
					block[bcounter]->x = (370 + (k*20));
					block[bcounter]->y = (40 + (13*n));
					draw_sprite(buffer, block_bmp, block[bcounter]->x, block[bcounter]->y);
					temp++;
					bcounter++;
				}
				else
					bcounter++;



		}
		 
	}

	//draw bottom left triangle of triforce
	//loop for the height
	for(n=0; n<8; n++)
	{
		//loop for the length
		for(k=0; k<=n; k++)
		{			
				if(block[bcounter]->alive)
				{
					block[bcounter]->x = (190 - (k*20));
					block[bcounter]->y = (140 + (13*n));
					draw_sprite(buffer, block_bmp, block[bcounter]->x, block[bcounter]->y);
					temp++;
					bcounter++;
				}
				else
					bcounter++;
				if(block[bcounter]->alive)
				{
					block[bcounter]->x = (210 + (k*20));
					block[bcounter]->y = (140 + (13*n));
					draw_sprite(buffer, block_bmp, block[bcounter]->x, block[bcounter]->y);
					temp++;
					bcounter++;
					
				}else
					bcounter++;
		}
	}

	//draw bottom right triangle of triforce
	//loop for the height
	for(n=0; n<8; n++)
	{
		//loop for the length
		for(k=0; k<=n; k++)
		{			
				if(block[bcounter]->alive)
				{
					block[bcounter]->x = (510 - (k*20));
					block[bcounter]->y = (140 + (13*n));
					draw_sprite(buffer, block_bmp, block[bcounter]->x, block[bcounter]->y);	
					temp++;
					bcounter++;
				}else
					bcounter++;
				if(block[bcounter]->alive)
				{
					block[bcounter]->x = (530 + (k*20));
					block[bcounter]->y = (140 + (13*n));
					draw_sprite(buffer, block_bmp, block[bcounter]->x, block[bcounter]->y);
					temp++;
					bcounter++;
				}else
					bcounter++;
		}
	}

	textprintf_ex(buffer,font,380,1,WHITE,PURPLE,"Blocks to destroy: %d ",temp);
	bcounter=0;
	return temp;
}
void drawlvl2()
{

}


////////////////////////////////////////////////////////
/////             Setup Sprites      			   /////
////////////////////////////////////////////////////////
void setupplayer()
{
   
    
    //configure player 1's paddle
    player[0] = &myplayer[0];
    player[0]->x = SCREEN_W/2;
    player[0]->y = 540;
    player[0]->xspeed = 8;
    player[0]->dir = 0;
	player[0]->width = 100;
	player[0]->height = 10;
	player[0]->alive = 1;
    //load first player bitmap
    player_bmp[0] = load_bitmap("player.bmp", NULL);

	//configure large paddle
	
	//load large paddle bmp
	player_bmp[1] = load_bitmap("playerlarge.bmp",NULL);

	//load shooting paddle bmp
	player_bmp[2] = load_bitmap("playershoot.bmp",NULL);
    
  
}
void setupball()
{
	int i;
	//configure ball information
	for(i=0;i<1;i++)
	{
		balls[i] = &myballs[i];
		balls[i]->x = 300 + rand()%15;
		balls[i]->y = 300 +rand()%15;
		balls[i]->r;
		balls[i]->xdir = 0;
		balls[i]->ydir = 0;
		balls[i]->xspeed = 5;
		balls[i]->yspeed = 6;
		balls[i]->width = 24;
		balls[i]->height = 24;
		balls[i]->alive = 0;

		//load the ball image
		ball_bmp = load_bitmap("ball.bmp", NULL);
	}
	balls[0]->alive=1;
}
void setupblocks()
{
	int n;
	//create my blocks and give them some information 
	for(n=0; n<216; n++)
	{
		block[n] = &myblock[n];
		block[n]->alive = 1;
		block[n]->width = 20;
		block[n]->height = 13;
		block[n]->x = 0;
		block[n]->y = 0;
	}
	//load block bmp
	block_bmp = load_bitmap("block.bmp",NULL);
}
void setupscreen()
{
    int ret;

    //set video mode    
    set_color_depth(16);
    ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
    if (ret != 0) {
        allegro_message(allegro_error);
        return;
    }

	//create double buffer
    buffer = create_bitmap(740,580);

  
    //draw screen border        
    rect(buffer, 0, 12, SCREEN_W-1, SCREEN_H-1, GREEN);
    rect(buffer, 1, 13, SCREEN_W-2, SCREEN_H-2, GREEN);
   
}
void setuppowerups()
{
	int n;
	for(n=0;n<3; n++)
	{
		powerup[n] = &powerups[n];
		powerup[n]->x = 16;
		powerup[n]->y = 16;
		powerup[n]->yspeed = 4;
		powerup[n]->alive = 0;
		powerup[n]->ydir = 0;
	}
	powerup_bmp[0] = load_bitmap("powerup1.bmp",NULL);
	powerup_bmp[1] = load_bitmap("powerup2.bmp",NULL);
	powerup_bmp[2] = load_bitmap("powerupspeed.bmp",NULL);
}
int setupsound()
{
	
	//install a digital sound driver
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "") != 0) 
    {
        allegro_message("Error initializing sound system");
        return 1;
    }

	//load .wav files into variables
	dying = load_sample("dying.wav");
    if (!dying) 
    {
        allegro_message("Error reading wave file");
        return 1;
    }
	hurt = load_sample("hurt.wav");
    if (!hurt) 
    {
        allegro_message("Error reading wave file");
        return 1;
    }
	hit = load_sample("hit.wav");
    if (!hit) 
    {
        allegro_message("Error reading wave file");
        return 1;
    }
	shoot = load_sample("shoot.wav");
    if (!shoot) 
    {
        allegro_message("Error reading wave file");
        return 1;
    }
	//game music lvl1
	lostwoods = load_sample("lostwoods.wav");
    if (!lostwoods) 
    {
        allegro_message("Error reading wave file");
        return 1;
    }
	maintheme = load_sample("maintheme.wav");
    if (!maintheme) 
    {
        allegro_message("Error reading wave file");
        return 1;
    }
	//lostwoodsdubstep = load_sample("lostwoodsdubstep.wav");
 //   if (!lostwoodsdubstep) 
 //   {
 //       allegro_message("Error reading wave file");
 //       return 1;
 //   }
	winning = load_sample("winning.wav");
	if(!winning)
	{
		allegro_message("errore reading wave file");
		return 1;
	}
	songofstorms = load_sample("songofstorms.wav");
    if (!songofstorms) 
    {
        allegro_message("Error reading wave file");
        return 1;
    }
	

		nhello = load_sample("OOT_Navi_Hello1.wav");
		if (!nhello) 
		{
			allegro_message("Error reading wave file");
			return 1;
		}
		nhey = load_sample("OOT_Navi_Hey1.wav");
		if (!nhey) 
		{
			allegro_message("Error reading wave file");
			return 1;
		}
		nlisten = load_sample("OOT_Navi_Listen1.wav");
		if (!nlisten) 
		{
			allegro_message("Error reading wave file");
			return 1;
		}
		nlook = load_sample("OOT_Navi_Look1.wav");
		if (!nlook) 
		{
			allegro_message("Error reading wave file");
			return 1;
		}
		nwatchout = load_sample("OOT_Navi_WatchOut1.wav");
		if (!nwatchout) 
		{
			allegro_message("Error reading wave file");
			return 1;
		}
	
	secret = load_sample("OOT_Secret.wav");
    if (!secret) 
    {
        allegro_message("Error reading wave file");
        return 1;
    }
	
	return 0;
}
void setupshoot()
{
	int i;

	for(i=0;i<5;i++)
	{
		bullet[i] = &mybullets[i];
		bullet[i]->x = 0;
		bullet[i]->y = 0;
		bullet[i]->alive = 0;
		bullet[i]->yspeed = 7;
		bullet[i]->width = 14;
		bullet[i]->height = 42; 
	}

	sword_bmp = load_bitmap("sword.bmp",NULL);
}

////////////////////////////////////////////////////////
/////             Update Sprites      			   /////
////////////////////////////////////////////////////////
void updateplayer()
{
	//erase the palyer
	int x = player[0]->x;
    int y = player[0]->y;
	int dir = player[0]->dir;

	
	if(playerpaddle == 0 || playerpaddle == 2)//erase small paddle
	{
		rectfill(buffer, x, y, x+100, y+10, BLACK);
	}
	if(playerpaddle == 1)//erase large paddle
	{
		rectfill(buffer, x, y, x+200, y+10, BLACK);
	}

	//do we have paddle bonus, is it over?
	if(playerlargetimer == 0 && playershoottimer == 0)
	{
		player[0]->width = 100;
		playerpaddle = 0;
	}
	

    //update paddle position based on direction
    switch(dir)
    {
		
        case 0://left
			player[0]->x -= player[0]->xspeed;
			player[0]->xspeed=0;
            break;
        case 1://right
            player[0]->x += player[0]->xspeed;
			player[0]->xspeed = 0;
            break;
       
      }
	if((playerpaddle == 0) || (playerpaddle == 2))//small paddle
	{
		//keep palyer inside the screen
		//use xspeed as a generic "speed" variable
		if (player[0]->x > SCREEN_W-105)
		{
			player[0]->x = SCREEN_W-105;
			player[0]->xspeed = 0;
		}
		if (player[0]->x < 4)
		{
			player[0]->x = 4;
			player[0]->xspeed = 0;
		}
  
	}
	if(playerpaddle == 1)//large paddle
	{
		//keep palyer inside the screen
		//use xspeed as a generic "speed" variable
		if (player[0]->x > SCREEN_W-205)
		{
			player[0]->x = SCREEN_W-205;
			player[0]->xspeed = 0;
		}
		if (player[0]->x < 4)
		{
			player[0]->x = 4;
			player[0]->xspeed = 0;
		}
  
	}
		
    
	//draw the players paddle
	
	 draw_sprite(buffer, player_bmp[playerpaddle], player[0]->x,player[0]->y);
	
}
void updateball(int num)
{ 
	int i,j;
	int x = balls[num]->x;
	int y = balls[num]->y;
	//int dir = balls[num]->dir;

	

	//loop thru all the balls
	for(i=0;i<1;i++)
	{
		///erase the ball
		circlefill(buffer,balls[i]->x+12,balls[i]->y+12,11,BLACK);

		//make sure ball is alive
		if(balls[i]->alive)
		{
			//update direction
			if(balls[i]->x > 710-balls[i]->r) 
				balls[i]->xdir = 1;
			if(balls[i]->y > 550-balls[i]->r)
				balls[i]->ydir = 1;
			if(balls[i]->x < balls[i]->r+6)
				balls[i]->xdir = 0;
			if(balls[i]->y < balls[i]->r+25)
				balls[i]->ydir = 0;

			//updating position bassed on direction
			if(balls[i]->xdir == 0)
				balls[i]->x +=balls[i]->xspeed;
			if(balls[i]->ydir == 0)
				balls[i]->y +=balls[i]->yspeed;
			if(balls[i]->xdir == 1)
				balls[i]->x -=balls[i]->xspeed;
			if(balls[i]->ydir == 1)
				balls[i]->y -=balls[i]->yspeed;

			//check if ball went bellow paddle
			if(balls[i]->y > player[0]->y)
			{
				//destroy ball
				balls[i]->alive = 0;

				//play hit sound
				play_sample(hurt,volume,panning,pitch, FALSE);
				rest(1000);

				///erase the ball
				circlefill(buffer,balls[i]->x+12,balls[i]->y+12,11,BLACK);
				if(!checkballsalive())
				{
					lives--;
					if(lives==0)
					{
						break;
					}
					else//make new ball and continue game
						balls[0]->alive = 1;
						balls[0]->x = 250 + rand()%50;
						balls[0]->y = 250 + rand()%50;
						balls[0]->xspeed = 5;
						balls[0]->yspeed = 6;
						//draw the ball
						draw_sprite(buffer,ball_bmp,balls[i]->x,balls[i]->y);
						rest(100);
				}

			}

			
			//check collision with blocks
			for(j=0;j<216;j++)
			{
				if(block[j]->alive)
				{
					if(ballcollidedtop(balls[i],block[j]))//check hit from top of ball, bounce ball down
					{
						block[j]->alive = 0;
						rectfill(buffer,block[j]->x,block[j]->y,block[j]->x+block[j]->width,block[j]->y+block[j]->height,BLACK);
						balls[i]->ydir =0;
						score(0);

						//do we make a powerup?
						makepowerup = rand()%9;
						if(makepowerup == 1 && !powerup[0]->alive && playerpaddle != 1 && playerpaddle !=2)//make large paddle
						{
							powerup[0]->alive = 1;
							powerup[0]->x = block[j]->x+10;
							powerup[0]->y = block[j]->y;
							play_sample(secret,volume,panning,pitch,FALSE);
						}
						if(makepowerup == 2 && !powerup[1]->alive && playerpaddle != 2 && playerpaddle != 1 )//shoot master swords
						{
							powerup[1]->alive = 1;
							powerup[1]->x = balls[i]->x;
							powerup[1]->y = balls[i]->y;
							play_sample(secret,volume,panning,pitch,FALSE);
						}
						if(makepowerup == 3 && !powerup[2]->alive && balls[0]->xspeed < 13)//speed up game
						{
							powerup[2]->alive = 1;
							powerup[2]->x = balls[i]->x;
							powerup[2]->y = balls[i]->y;
							play_sample(secret,volume,panning,pitch,FALSE);
						}

					}
					if(ballcollidedbottom(balls[i],block[j]))//check hit from bottom of ball, bounce ball up
					{
						block[j]->alive = 0;
						rectfill(buffer,block[j]->x,block[j]->y,block[j]->x+block[j]->width,block[j]->y+block[j]->height,BLACK);
						balls[i]->ydir =1;

						//do we make a powerup?
						makepowerup = rand()%9;
						if(makepowerup == 1 && !powerup[0]->alive && playerpaddle != 1 && playerpaddle != 2)//make large paddle
						{
							powerup[0]->alive = 1;
							powerup[0]->x = block[j]->x;
							powerup[0]->y = block[j]->y;
							play_sample(secret,volume,panning,pitch,FALSE);
						}
						if(makepowerup == 22 && !powerup[1]->alive && playerpaddle != 2 && playerpaddle != 1 )//shoot master swords
						{
							powerup[1]->alive = 1;
							powerup[1]->x = balls[i]->x;
							powerup[1]->y = balls[i]->y;
							play_sample(secret,volume,panning,pitch,FALSE);
						}
						if(makepowerup == 3 && !powerup[2]->alive && balls[0]->xspeed < 13)//speed up game
						{
							powerup[2]->alive = 1;
							powerup[2]->x = balls[i]->x;
							powerup[2]->y = balls[i]->y;
							play_sample(secret,volume,panning,pitch,FALSE);
						}

						/*textprintf(buffer,font,2,48,WHITE,"number block destroyed: %d", j);
						textprintf(buffer,font,2,58,WHITE,"block x: %d block y: %d", block[j]->x, block[j]->y);
						textprintf(buffer,font,2,68,WHITE,"block alive: %d", block[j]->alive);*/
						score(0);
						//rest(1000);
						//break;
					}
				}
			}

			//check collision with paddle
			if(playercollidedright(balls[i],player[0]))
			{
				//play hit sound
				play_sample(hit,volume,panning,pitch, FALSE);
				balls[i]->ydir =1;
				if(balls[i]->xdir ==0)
				{
				
					balls[i]->xspeed++;
				}
				else if(balls[i]->xdir ==1)
				{
					balls[i]->xdir=0;
					
				}
			}
			else if(playercollidedleft(balls[i],player[0]))
			{
				//play hit sound
				play_sample(hit,volume,panning,pitch, FALSE);
				balls[i]->ydir =1;
				if(balls[i]->xdir ==1)
				{
					balls[i]->xspeed++;
				}
				else if(balls[i]->xdir ==0)
				{
					balls[i]->xdir=1;
				}

			}
			 else if(playercollidedmiddle(balls[i],player[0]))
			{
				//play hit sound
				play_sample(hit,volume,panning,pitch, FALSE);
				balls[i]->ydir =1;
				balls[i]->xspeed--;
				if(balls[i]->xspeed <2)
					balls[i]->xspeed = 2;
				
			}

			//draw the ball
			draw_sprite(buffer,ball_bmp,balls[i]->x,balls[i]->y);
			

		}
	}

}
void updatepowerup(int num)
{
	int x = powerup[num]->x;
	int y  = powerup[num]->y;

	//check if power up is alive 
	if(powerup[num]->alive)
	{
		//erase powerup
		circlefill(buffer,powerup[num]->x+8,powerup[num]->y+8,13,BLACK);

		//move the powerup down
		powerup[num]->y += powerup[num]->yspeed;

		//check collision with player
		if(powerupcollided(powerup[num],player[0]))
		{
			//give player large paddle
			if(num==0)
			{
				powerup[num]->alive = 0;
				circlefill(buffer,powerup[num]->x+8,powerup[num]->y+8,13,BLACK);
				playerpaddle = 1;
				player[0]->width = 200;
				playerlargetimer = 30;
				bonus = 1;
				return;
			}
			if(num==1)
			{
				powerup[num]->alive = 0;
				circlefill(buffer,powerup[num]->x+8,powerup[num]->y+8,13,BLACK);
				playerpaddle = 2;
				playershoottimer = 30;
				canshoot = 1;
				bonus = 1;
				return;

			}
			if(num==2)
			{
				powerup[num]->alive = 0;
				circlefill(buffer,powerup[num]->x+8,powerup[num]->y+8,13,BLACK);
				player[0]->xspeed++;
				balls[0]->xspeed++;
				balls[0]->yspeed++;
				return;

			}
		}

		//check if went below paddle
		if(powerup[num]->y > player[0]->y + 4)
		{
			powerup[num]->alive = 0;
			circlefill(buffer,powerup[num]->x+8,powerup[num]->y+8,13,BLACK);
			return;
		}


		//draw the powerup
		draw_sprite(buffer,powerup_bmp[num],x,y);
	}



}
void updatebullet(int num)
{
    int x = bullet[num]->x;
	int y = bullet[num]->y;
	int n;

	//is sword alive?
	if(bullet[num]->alive)
	{
		//erase sword
		rectfill(buffer,x,y,x+19,y+49,BLACK);

		//move the sword
		bullet[num]->y -= bullet[num]->yspeed;

		//check collisoin with block
		for(n=0; n<216; n++)
		{
			if(block[n]->alive)
			{
				if(swordcollided(bullet[num],block[n]) && bullet[num]->alive)
				{
					//destroy block
					block[n]->alive = 0;
					rectfill(buffer,block[n]->x,block[n]->y,block[n]->x+block[n]->width,block[n]->y+block[n]->height,BLACK);
					rectfill(buffer,bullet[0]->x,bullet[0]->y,x+14,y+47,BLACK);
					//destroy sword
					bullet[num]->alive = 0;
					score(0);
					return;
				}
			}
		}

		//check if above screen
		if(bullet[num]->y < 25)
		{
			//destroy sword
			bullet[num]->alive = 0;
			rectfill(buffer,x,y,x+14,y+47,BLACK);
		}

		//draw the sword
		if(bullet[0]->alive)
		draw_sprite(buffer,sword_bmp,x,y);
	}

}

int checkballsalive()
{
	int n;
	int dead=numofballs;
	for(n=0; n<numofballs; n++)
		if(!balls[n]->alive)
			dead--;
	return dead;
}
int checkloss()
{

	if(lives==0)
		{
			
			rest(777);
			//draw box over screen
			rectfill(screen,1,1,SCREEN_W,SCREEN_H,0);
			//display losing message
			textprintf_ex(screen, font, SCREEN_W/2, SCREEN_H/2, WHITE, BLACK, "You ran out of lives!");
			play_sample(dying,volume, panning, pitch, FALSE);
			rest(3500);
			return 1;
		}else
			return 0;
}
void score(int player)
{
    //update score
	 ++scores[player];
	 point++;
	if(point > 100)
	{
		lives++;
		point=0;
	}
}
void playnavisound()
{
	//play navi sound?
	navimusic = rand()%3000;
	if(navimusic==0)
	{
		//play navi sound 0
		play_sample(nhello,volume,panning,pitch, FALSE);
		//balls[0]->xspeed++;
	}
	if(navimusic==1)
	{
		//play navi sound 1
		play_sample(nhey,volume,panning,pitch, FALSE);
		//balls[0]->xspeed--;
	}
	if(navimusic==2)
	{
		//play navi sound 2
		play_sample(nlisten,volume,panning,pitch, FALSE);
		balls[0]->yspeed++;
	}
	if(navimusic==3)
	{
		//play navi sound 3
		play_sample(nlook,volume,panning,pitch, FALSE);
		balls[0]->yspeed--;
	}
	if(navimusic==4)
	{
		//play navi sound 4
		play_sample(nwatchout,volume,panning,pitch, FALSE);
		balls[0]->xspeed++;
		balls[0]->yspeed++;
	}

	//speed control of ball
	if(balls[0]->yspeed > 10)
	{ 
		balls[0]->yspeed = 5;
	}
	if(balls[0]->xspeed > 10)
	{
		balls[0]->xspeed = 5;
	}
}
void drawgamestats()
{
	int n;
	//draw box to erase old stats
	rectfill(buffer,1,1,750,10,0);
			
	//draw number of lives and balls
	textprintf_ex(buffer, font, 1, 1, WHITE, DGREEN, "Number of Lives: %d", lives);
	for(n=0; n<lives; n++)
	{
		circlefill(buffer, 155+(10*n),5,3,WHITE);
	}
	//display score
	textprintf_ex(buffer, font, 660, 1, WHITE,DGREEN, "Score: %d ", scores[0]);

	//show game time
	textprintf_ex(buffer,font,240,1,WHITE,BLUE,"Time:%.2d:%.2d:%.2d",min, sec, centiSec);

	//show time left with large paddle
	if(playerlargetimer > 0 )
	{
		textprintf_ex(buffer,font,4,16,WHITE,RED,"Time Remaining with bonus: %d ",playerlargetimer);
	}
	else
		rectfill(buffer,4,16,324,25,0);
	//show time left with shooting
	if(playershoottimer > 0 )
	{
		textprintf_ex(buffer,font, 4, 26, WHITE, DGREEN,"Time with shooting: %d ",playershoottimer);
	}
	else
		rectfill(buffer,4,26,344,36,0);

}

void getinput()
{
    //hit ESC to quit
    if (key[KEY_ESC])   gameover = 1;
    
    //WASD - SPACE keys control tank 1
   
    if (key[KEY_RIGHT])
	{
		player[0]->xspeed = 15;
		player[0]->dir=1;
	}
    if (key[KEY_LEFT])
	{
		player[0]->xspeed = 15;
		player[0]->dir=0;
	}
	if(canshoot)
	{
		if(key[KEY_SPACE])
		{
			if(!bullet[0]->alive)
			{
				play_sample(shoot,volume,panning,pitch,FALSE);
				bullet[0]->alive = 1;
				bullet[0]->x = player[0]->x + (player[0]->width/2);
				bullet[0]->y = player[0]->y - 40;
			}
			
		}
	}
   
    //short delay after keypress        
    rest(10);
}

int main(void)
{
	int j,over;

    //initialize the game
    allegro_init(); 
    install_keyboard(); 
    install_timer();
    srand(time(NULL));
    setupscreen();
    setupplayer();
	setupball();
	setupblocks();
	setupsound();
	setuppowerups();
	setupshoot();

	 /* all variables and code used inside the interrupt handler must be locked */
   LOCK_VARIABLE(min);	
   LOCK_VARIABLE(sec);
   LOCK_FUNCTION(inc_sec);

   LOCK_VARIABLE(centiSec);
   LOCK_FUNCTION(inc_centiSec);

   /* the speed can be specified in milliseconds (this is once a second) */
   install_int(inc_sec, 1000);
   install_int(inc_centiSec, 10);

    //game loop
    while(!gameover)
    {
		////play some game music
		if(min >= 1 && sec >= 10 && playsong==1)
		{
			play_sample(songofstorms,volume+20,panning,pitch,FALSE);
			playsong++;
		}else if(min <= 1 && sec <= 10 && playsong==0)
		{
			play_sample(lostwoods,volume+250,panning,pitch, FALSE);
			playsong++;
		}
		//stuff for debugging
	

		
		//draw time, score and lives at top of screen
		drawgamestats();


       //check for keypresses
        if (keypressed())
            getinput();

		//move the players paddle
		updateplayer();    
		updateball(0);

		//update power ups
		for(j=0;j<3;j++)
			updatepowerup(j);
		
		//update bullets
		for(j=0;j<5;j++)
			updatebullet(j);

		//draw the level
		switch(level)
		{
			case 1://level 1
				over = drawlvl1();
			case 2://level 2
				drawlvl2();
		}
		
		//play navi sound?
		playnavisound();

		//check for loss condition
		if(checkloss())
			break;
		//check win
		if(over == 0)
		{
			while(!gameover)
			{
				//draw box over screen
				rectfill(screen,1,1,SCREEN_W,SCREEN_H,0);
				//display winning message
				textprintf_ex(screen, font, SCREEN_W/2, SCREEN_H/2, WHITE, BLACK, "You WON!");
				play_sample(winning,volume, panning, pitch, FALSE);
				rest(3500);
				break;
			}
			return 0;
		}

        //update the screen
        acquire_screen();
        blit(buffer,screen,0,0,0,0,SCREEN_W-1,SCREEN_H-1);
        release_screen();
	

		////check if game time is up
		//if((min==0)&&(sec==0))
		//{
		//	 ////print title
		//	textprintf_ex(buffer, font, 1, 1, -1,
  //             BURST, "Time Remaining:%.2d:%.2d:%.2d",min, sec, centiSec);
		//	 //display gameover
		//	 textprintf_ex(screen, font, SCREEN_W/2, SCREEN_H/2,-1,
		//	 BURST, "Score: %d", scores[0]);
		//	 rest(3000);
		//	 break;
		//}

        //slow the game down
        rest(10);
    }


    //end program
    allegro_exit();
    return 0;
}
END_OF_MAIN()
