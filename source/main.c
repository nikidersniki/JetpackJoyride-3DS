// Simple citro2d untextured shape example
#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include <time.h>
#include "variables.h"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240
C2D_SpriteSheet spriteSheet;
C2D_SpriteSheet playerSprite;
C2D_Sprite caractersprite;
C2D_SpriteSheet backgroundSprite;
C2D_Sprite bg1, bg2, bg3, bg4;
C2D_SpriteSheet menu_bg;
C2D_SpriteSheet startBackground_sprite;

C2D_Sprite jetp1;
C2D_Sprite jetp2;
C2D_Sprite jetp3;
C2D_Sprite jetp4;
C2D_Sprite jetp5;
C2D_Sprite jetp6;
C2D_Sprite jetp7;
C2D_Sprite jetp8;
C2D_Sprite jetp9;
C2D_Sprite jetp10;
C2D_Sprite jetp11;
C2D_Sprite jetp12;
C2D_Sprite jetp13;
C2D_Sprite jetp14;
C2D_Sprite jetp15;
C2D_Sprite jetp16;
C2D_Sprite boom;
C2D_Sprite bullet;
C2D_Sprite fire;
C2D_Sprite flash;


int men = 0;
bool inGame = false;
void drawGame(float);
void caracterSprite();
void initplayerstripe(int);
void switch_backgrounds();
void jetpack();
void initialize_jet();
void bullets_jet();
void trigger_jetpack();
void level_generator();
float size = 0.5f;
bool up = false;
int caracter_animation_counter;
int bullets[100] = {};

//menu position
void menue(bool num){
	if(num==true){
		if(men<2){
			men++;
		}
		else{

		}
	}
	else{
		if(men>0){
			men--;
		}
		else{

		}
	}
	
}
//text for main menu
C2D_TextBuf g_staticBuf;
C2D_Text g_staticText[4];

//initialize main menu text/font 
static void sceneInit(void)
{
	// Create static text buffer
	g_staticBuf  = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
	C2D_Font textfont = C2D_FontLoad("romfs:/Menu.bcfnt");
	// Parse the static text strings
	C2D_TextFontParse(&g_staticText[0], textfont, g_staticBuf, "V1.0");
	C2D_TextFontParse(&g_staticText[1], textfont, g_staticBuf, "Start");
	C2D_TextFontParse(&g_staticText[2], textfont, g_staticBuf, "Settings");
	C2D_TextFontParse(&g_staticText[3], textfont, g_staticBuf, "Exit");
	// Optimize the static text strings
	C2D_TextOptimize(&g_staticText[0]);
	C2D_TextOptimize(&g_staticText[1]);
	C2D_TextOptimize(&g_staticText[2]);
	C2D_TextOptimize(&g_staticText[3]);
}
//draw static strings to positions
static void textRender(float size)
{
	// Draw static text strings
	C2D_DrawText(&g_staticText[0], C2D_WithColor, 5.0f, 215.0f, 0.5f, 0.5f, 0.75f, C2D_Color32f(0.0f,0.0f,0.0f,1.0f));
	C2D_DrawText(&g_staticText[1], C2D_WithColor, 185.0f, 100.0f, 0.5f, 0.5f, 0.75f, C2D_Color32f(1.0f,0.0f,0.0f,1.0f));
	C2D_DrawText(&g_staticText[2], C2D_WithColor, 175.0f, 140.0f, 0.5f, 0.5f, 0.75f, C2D_Color32f(1.0f,0.0f,0.0f,1.0f));
	C2D_DrawText(&g_staticText[3], C2D_WithColor, 187.0f, 180.0f, 0.5f, 0.5f, 0.75f, C2D_Color32f(1.0f,0.0f,0.0f,1.0f));
}

int main(int argc, char* argv[]) {
	// Init libs
	romfsInit();
	cfguInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);


	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	//define colors in hex  r     g      b    a
	u32 grey = C2D_Color32(0x70, 0x70, 0x70, 0xFF);
	u32 yellow = C2D_Color32(0xff, 0xf7, 0x00, 0xFF);
	u32 clrClear = C2D_Color32(0x10, 0x10, 0x10, 0xFF);


	//initalite the main menue png
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/logo_big.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);//stop application if load of sprite fails
	C2D_Sprite sprite;
    C2D_SpriteFromSheet(&sprite, spriteSheet, 0);
	C2D_SpriteSetDepth(&sprite, 1.0f);
	C2D_SpriteScale	(&sprite, 0.5f, 0.5f);
	C2D_SpriteSetPos (&sprite, SCREEN_WIDTH / 2 - 84 , 10);
	menu_bg = C2D_SpriteSheetLoad("romfs:/gfx/main_bg.t3x");
	C2D_Sprite bgsprite;
    C2D_SpriteFromSheet(&bgsprite, menu_bg, 0);
	C2D_SpriteSetDepth(&bgsprite, 0.0f);
	C2D_SpriteScale	(&bgsprite, 1.0f, 1.0f);
	C2D_SpriteSetPos(&bgsprite, 0, 0);


	//Player Sprite
	initplayerstripe(0);
	
	//Initialize Backgrount
	switch_backgrounds();

	//initialize map
	level_generator();
	//initialize font
	sceneInit();

	//initialize jetpack
	initialize_jet();

	//initialize bullets
	bullets_jet();
	// Main loop
	while (aptMainLoop())
	{

		//time for caracter animation
		caracter_animation_counter++;
		if (caracter_animation_counter == 4){
			caracterSprite();
			caracter_animation_counter = 0;
		}
		//switch between jetpack and running sprite sheet
		if(scroll == -200){
			initplayerstripe(1);
		}
		//read all inputs
		hidScanInput();
		// Respond to user input
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();		
		if(inGame == false){
			if (kDown & KEY_START)
				break; // break in order to return to hbmenu	
			if (kDown & KEY_DOWN){
				menue(true);
			}
			if (kDown & KEY_UP){
				menue(false);
			}
			if (kDown & KEY_A){
				if(men==0){
					inGame = true;
					C2D_Flush();
					drawGame(0.0);
				}
				if(men==1){
					
				}
				if(men==2){
					break; // break in order to return to hbmenu
				}
			}
		}
		else{
			if (kDown & KEY_START){
				inGame = false;
			}
			up = false;
			if (kHeld & KEY_A){
				up = true;
				drawGame(25.0);
			}

				


		}
		printf("\x1b[1;1HUsage Monitor");
		printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);//cpu usage
		printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);//gpu usage if over 100% game beginns to lag
		printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);//cmd buffer

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);
		//main menu options
		if(inGame == false){
			C2D_DrawSprite(&bg1);
    		C2D_DrawSprite(&bg2);
    		C2D_DrawSprite(&bg3);
    		C2D_DrawSprite(&bg4);
			C2D_DrawSprite(&bgsprite);
			C2D_DrawSprite(&sprite);
			C2D_DrawRectangle (100, 100, 0, 200, 25, grey, grey, grey, grey);//Start
			C2D_DrawRectangle (100, 140, 0, 200, 25, grey, grey, grey, grey);//Settings
			C2D_DrawRectangle (100, 180, 0, 200, 25, grey, grey, grey, grey);//Exit
			if(men==0){
				C2D_DrawRectangle (100, 100, 0, 200, 25, yellow, yellow, yellow, yellow);//option1
			}
			else if (men==1){
				C2D_DrawRectangle (100, 140, 0, 200, 25, yellow, yellow, yellow, yellow);//option2
			}
			else if (men==2){
				C2D_DrawRectangle (100, 180, 0, 200, 25, yellow, yellow, yellow, yellow);//option3
			}
			textRender(size);
		}
		else{
			drawGame(0.0);
			//draw background
			C2D_SpriteSetPos(&bg1, fmodf(scroll, 700) + 525, 0);
    		C2D_SpriteSetPos(&bg2, fmodf(scroll + 175, 700) + 525, 0);
    		C2D_SpriteSetPos(&bg3, fmodf(scroll + 350, 700) + 525, 0);
    		C2D_SpriteSetPos(&bg4, fmodf(scroll + 525, 700) + 525, 0);
			C2D_SpriteSetPos(&bgsprite, scroll, 0);
			C2D_DrawSprite(&bgsprite);
			//draw walways repeating backgrounds
			C2D_DrawSprite(&bg1);
    		C2D_DrawSprite(&bg2);
    		C2D_DrawSprite(&bg3);
    		C2D_DrawSprite(&bg4);
			scroll -= 2.0f;
			printf("\x1b[10;1Hscroll%f", scroll);
			//draw caracter
			C2D_SpriteFromSheet(&caractersprite, playerSprite, caracter_sprite);
			C2D_SpriteSetPos (&caractersprite, x , y - 20);
			C2D_DrawSprite(&caractersprite);
			//draw jetpack
			jetpack();
			if (up==true){
				trigger_jetpack();
			}
			//loop threw each Bullet
			int loop;
			for(loop = 0; loop < 20; loop++){
				//if bullet is to low to the ground reset the value to -40 to be out of view
				if (bullets[loop] >= 200){
					C2D_SpriteSetPos(&boom, x -7, 210);
					C2D_DrawSprite(&boom);
					bullets[loop] = -40;
				}
				//if bullet out of view do....
				else if(bullets[loop]==-40){
				}
				//if bullet is currently flying add +10 to the y pos of it
				else{
					bullets[loop] = bullets[loop] + 10;
				}
				//print all y positions of bullets in console
      			//printf("   %d", bullets[loop]);
				//set modified y pos 
				C2D_SpriteSetPos (&bullet, x , bullets[loop]);
				C2D_DrawSprite(&bullet);
			}
		}
		C3D_FrameEnd(0);
	}
	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	romfsExit();
	cfguExit();
	gfxExit();
	return 0;
}

