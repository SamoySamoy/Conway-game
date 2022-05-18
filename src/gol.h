#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>

SDL_Window* window = NULL;
SDL_Renderer* renderer;
TTF_Font* gFont = NULL;
Mix_Music *bg = NULL;
SDL_Texture *screen_texture;
SDL_Surface* title = NULL;
SDL_Surface* endgame = NULL;
SDL_Surface* screen = NULL;

SDL_Color bg_color = {0x2C, 0x34, 0x48, 0xFF};		
SDL_Color filled = {0x9D, 0xA3, 0xB3, 0xFF};
SDL_Color panel_outline = {0x10, 0x19, 0x2E, 0xFF};
SDL_Event e;
SDL_Surface *surfaceMessage = TTF_RenderText_Solid(gFont, "", {0x10, 0x19, 0x2E, 0xFF});
SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 640;
const int PANEL = 100;
const int THICKNESS = 3; 
const int BOARD_SIZE_X = SCREEN_WIDTH/10;
const int BOARD_SIZE_Y = (SCREEN_HEIGHT-PANEL)/10;
int board[BOARD_SIZE_X][BOARD_SIZE_Y] = {0}; 
// n : neighbours (each square has 8 neighbour squares)
int nx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int ny[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int state = 0;
int previous = 0;
int population_count = 0;
int low = 1000;
int high = 0;
int speed = 150;
bool quit = false;
bool gene = false;
bool paused = false;
bool rText = false;

bool init();
bool loadMedia();
void print_title();
bool load_music();
void mouse_event();
void close();
void _drawFillRect(SDL_Color&, int, int, int, int);
void _drawOutlineRect(SDL_Color&, int, int, int, int);
void print_gameover();