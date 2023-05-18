//this file has the most functions to draw the game
#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
//sincronize variables
#include "variables.h"

//screen width in pixels
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

float scroll = 0;
float viewX = 0;
float x = 100.0f;
float y = 220.0f;
float speed = 2.5;
float ygoal = 0;
int caracter_sprite = 3;
int jetpack_sprite = 1;
int bullet_count = 0;
//jetpack animation each
void initialize_jet(){
	C2D_SpriteSheet jetpacksheet;
	jetpacksheet = C2D_SpriteSheetLoad("romfs:/gfx/JetpackAnimation.t3x");
	if (!jetpacksheet) svcBreak(USERBREAK_PANIC);//stop application if load of sprite fails
	C2D_SpriteFromSheet(&jetp1, jetpacksheet, 0);
	C2D_SpriteSetDepth(&jetp1, 0.0f);
	C2D_SpriteFromSheet(&jetp2, jetpacksheet, 1);
	C2D_SpriteSetDepth(&jetp2, 0.0f);
	C2D_SpriteSetPos(&jetp2, x, y);
	C2D_SpriteFromSheet(&jetp3, jetpacksheet, 2);
	C2D_SpriteSetDepth(&jetp3, 0.0f);
	C2D_SpriteSetPos(&jetp3, x, y);
	C2D_SpriteFromSheet(&jetp4, jetpacksheet, 3);
	C2D_SpriteSetDepth(&jetp4, 0.0f);
	C2D_SpriteSetPos(&jetp4, x, y);
	C2D_SpriteFromSheet(&jetp5, jetpacksheet, 4);
	C2D_SpriteSetDepth(&jetp5, 0.0f);
	C2D_SpriteSetPos(&jetp5, x, y);
	C2D_SpriteFromSheet(&jetp6, jetpacksheet, 5);
	C2D_SpriteSetDepth(&jetp6, 0.0f);
	C2D_SpriteSetPos(&jetp6, x, y);
	C2D_SpriteFromSheet(&jetp7, jetpacksheet, 6);
	C2D_SpriteSetDepth(&jetp7, 0.0f);
	C2D_SpriteSetPos(&jetp7, x, y);
	C2D_SpriteFromSheet(&jetp8, jetpacksheet, 7);
	C2D_SpriteSetDepth(&jetp8, 0.0f);
	C2D_SpriteSetPos(&jetp8, x, y);
	C2D_SpriteFromSheet(&jetp9, jetpacksheet, 8);
	C2D_SpriteSetDepth(&jetp9, 0.0f);
	C2D_SpriteSetPos(&jetp9, x, y);
	C2D_SpriteFromSheet(&jetp10, jetpacksheet, 9);
	C2D_SpriteSetDepth(&jetp10, 0.0f);
	C2D_SpriteSetPos(&jetp10, x, y);
	C2D_SpriteFromSheet(&jetp11, jetpacksheet, 10);
	C2D_SpriteSetDepth(&jetp11, 0.0f);
	C2D_SpriteSetPos(&jetp11, x, y);
	C2D_SpriteFromSheet(&jetp12, jetpacksheet, 11);
	C2D_SpriteSetDepth(&jetp12, 0.0f);
	C2D_SpriteSetPos(&jetp12, x, y);
	C2D_SpriteFromSheet(&jetp13, jetpacksheet, 12);
	C2D_SpriteSetDepth(&jetp13, 0.0f);
	C2D_SpriteSetPos(&jetp13, x, y);
	C2D_SpriteFromSheet(&jetp14, jetpacksheet, 13);
	C2D_SpriteSetDepth(&jetp14, 0.0f);
	C2D_SpriteSetPos(&jetp14, x, y);
	C2D_SpriteFromSheet(&jetp15, jetpacksheet, 14);
	C2D_SpriteSetDepth(&jetp15, 0.0f);
	C2D_SpriteSetPos(&jetp15, x, y);
	C2D_SpriteFromSheet(&jetp16, jetpacksheet, 15);
	C2D_SpriteSetDepth(&jetp16, 0.0f);
	C2D_SpriteSetPos(&jetp16, x, y);
}
void bullets_jet(){
	C2D_SpriteSheet jetpack_bangsheet;
	jetpack_bangsheet = C2D_SpriteSheetLoad("romfs:/gfx/jetpack_bang.t3x");
	if (!jetpack_bangsheet) svcBreak(USERBREAK_PANIC);//stop application if load of sprite fails
	C2D_SpriteFromSheet(&boom, jetpack_bangsheet, 0);
	C2D_SpriteSetDepth(&boom, 1.0f);
	C2D_SpriteScale(&boom, 0.2f, 0.2f);
	C2D_SpriteFromSheet(&bullet, jetpack_bangsheet, 2);
	C2D_SpriteSetDepth(&bullet, 0.0f);
	C2D_SpriteScale(&bullet, 0.15f, 0.15f);
	C2D_SpriteFromSheet(&fire, jetpack_bangsheet, 1);
	C2D_SpriteSetDepth(&fire, -1.0f);
	C2D_SpriteSetPos(&fire, x, y);
	C2D_SpriteFromSheet(&flash, jetpack_bangsheet, 3);
	C2D_SpriteScale(&flash, 0.3f, 0.3f);
	C2D_SpriteSetDepth(&flash, 1.0f);
}
static void player(){
	u32 yellow = C2D_Color32(0xff, 0xf7, 0x00, 0xFF);
}

static void move(){
	if (y < 30){
		speed = 1;
		ygoal = 0;
		y = 30;
	}
	else if (ygoal > 0.0f){
		ygoal = ygoal - speed;
		y = y - speed;
		if (speed>1){
				speed = speed * 0.97;
		}
	}
	else if (ygoal <= 0.0 && y < 220.0){
		y = y + speed;
		if(speed<4.6){
			speed = speed * 1.1;
		}
	}
	else{
		speed = 3.5;
		ygoal = 0;
		y = 220.0;
	}
	printf("\x1b[5;1HValocityY%f", speed);
	printf("\x1b[7;1HX%f", x);
	printf("\x1b[8;1HY%f", y);
	printf("\x1b[9;1HGoal%f", ygoal);
}

void drawGame(float moveY) {
	if (ygoal <= 0){
		ygoal = ygoal + moveY;
	}
	u32 grey = C2D_Color32(0x70, 0x70, 0x70, 0xFF);
	move();
	player();
}
void caracterSprite(){
	int i;
	if (y == 220){
		if (caracter_sprite == 3){
			i = 1;
		}
		else if (caracter_sprite == 2){
			i = 0;
		}
		else if (caracter_sprite == 1){
			i = 2;
		}
		else if (caracter_sprite == 0){
			i = 1;
		}
	caracter_sprite = i;
	}
	else{
		i = 3;
		caracter_sprite = i;
	}
}
void initplayerstripe(int sheet)
{
	if(sheet==0){
		playerSprite = C2D_SpriteSheetLoad("romfs:/gfx/caracter.t3x");	
	}
	if(sheet==1){
		playerSprite = C2D_SpriteSheetLoad("romfs:/gfx/caracter.t3x");	
	}
	if (!playerSprite) svcBreak(USERBREAK_PANIC);//stop application if load of sprite fails
	C2D_SpriteSetDepth(&caractersprite, 1.0f);
	C2D_SpriteScale	(&caractersprite, 1.f, 1.f);
}

void switch_backgrounds(){
	backgroundSprite = C2D_SpriteSheetLoad("romfs:/gfx/background.t3x");
	if (!backgroundSprite) svcBreak(USERBREAK_PANIC);//stop application if load of sprite fails
	C2D_SpriteFromSheet(&bg1, backgroundSprite, 0);
	C2D_SpriteSetDepth(&bg1, 0.0f);
	C2D_SpriteScale	(&bg1, 0.725, 0.76);
	C2D_SpriteFromSheet(&bg2, backgroundSprite, 0);
	C2D_SpriteSetDepth(&bg2, 0.0f);
	C2D_SpriteScale	(&bg2, 0.725, 0.76);
	C2D_SpriteFromSheet(&bg3, backgroundSprite, 0);
	C2D_SpriteSetDepth(&bg3, 0.0f);
	C2D_SpriteScale	(&bg3, 0.725, 0.76);
	C2D_SpriteFromSheet(&bg4, backgroundSprite, 0);
	C2D_SpriteSetDepth(&bg4, 0.0f);
	C2D_SpriteScale	(&bg4, 0.725, 0.76);
	C2D_SpriteSetPos(&bg1, 0, 0);
	C2D_SpriteSetPos(&bg2, 175, 0);
	C2D_SpriteSetPos(&bg3, 350, 0);
	C2D_SpriteSetPos(&bg4, 525, 0);
}
void jetpack(){
	if (y==220){
		if(jetpack_sprite<=30){
			if(jetpack_sprite < 10){
				C2D_SpriteSetPos(&jetp11, x-10, y-17);
				C2D_DrawSprite(&jetp11);
			}
			else if(jetpack_sprite < 20){
				C2D_SpriteSetPos(&jetp12, x-10, y-17);
				C2D_DrawSprite(&jetp12);
			}
			else if(jetpack_sprite < 30){
				C2D_SpriteSetPos(&jetp13, x-10, y-17);
				C2D_DrawSprite(&jetp13);
			}
			jetpack_sprite++;
			}
			else{
				jetpack_sprite = 1;
				C2D_SpriteSetPos(&jetp12, x-10, y-17);
				C2D_DrawSprite(&jetp12);
			}
	}
	else{
		if(jetpack_sprite<=30){
			if(jetpack_sprite < 10){
				C2D_SpriteSetPos(&jetp5, x-10, y-17);
				C2D_DrawSprite(&jetp5);
			}
			else if(jetpack_sprite < 20){
				C2D_SpriteSetPos(&jetp6, x-10, y-17);
				C2D_DrawSprite(&jetp6);
			}
			else if(jetpack_sprite < 30){
				C2D_SpriteSetPos(&jetp7, x-10, y-17);
				C2D_DrawSprite(&jetp7);
			}
			jetpack_sprite++;
			}
			else{
				jetpack_sprite = 1;
				C2D_SpriteSetPos(&jetp8, x-10, y-17);
				C2D_DrawSprite(&jetp8);
			}
	}
	
}
void trigger_jetpack(){
	if (bullet_count >= 20){
		bullet_count = 0;
	}
	C2D_SpriteSetPos(&flash, x-8, y+10);
	C2D_SpriteSetPos(&bullet, x-8, y+15);
	if(jetpack_sprite > 1 && jetpack_sprite < 4){
		C2D_DrawSprite(&flash);
		bullet_count++;
		bullets[bullet_count] = y;
	}
	else if(jetpack_sprite > 7 && jetpack_sprite < 11){
		C2D_DrawSprite(&flash);
		C2D_DrawSprite(&flash);
		bullet_count++;
		bullets[bullet_count] = y;
	}
	else if(jetpack_sprite > 15 && jetpack_sprite < 18){
		C2D_DrawSprite(&flash);
		C2D_DrawSprite(&flash);
		bullet_count++;
		bullets[bullet_count] = y;
	}
	else if(jetpack_sprite > 25 && jetpack_sprite < 28){
		C2D_DrawSprite(&flash);
		C2D_DrawSprite(&flash);
		bullet_count++;
		bullets[bullet_count] = y;
	}
}

