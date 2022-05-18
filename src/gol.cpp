#pragma once
#include "gol.h"

using namespace std;
bool load_music()
{   
	bool setup = true;
	// init SDL music
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		Mix_GetError();
	}
	bg = Mix_LoadMUS("./data/bg.mp3"); // Load background music
	if (bg == NULL)
	{
		cout << Mix_GetError();
		setup = false;
	}
	return setup;
}

bool init()
{
	bool setup = true;

	if (TTF_Init() < 0)
	{
		printf("TTF_Init error: %s\n", TTF_GetError());
		setup = false;
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		setup = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: Linear texture filtering not enabled!");
		window = SDL_CreateWindow("Conway game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			setup = false;
		}
		else
		{ 
			screen = SDL_GetWindowSurface(window);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				setup = false;
			}
			else
			{ 
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				gFont = TTF_OpenFont("./data/font.ttf", 72);
				if (!gFont)
				{
					printf("TTF_OpenFont: %s\n", TTF_GetError());
					setup = false;
				}
			}
		}
	}
	return setup;
}

bool loadMedia()
{
	// Loading setup flag
	bool setup = true;

	// Load splash image
	title = SDL_LoadBMP("./data/pixel-title.bmp");
	endgame = SDL_LoadBMP("./data/last-gameover.bmp");
	if (title == NULL)
	{
		printf("Failed to load image %s! SDL Error: %s\n", SDL_GetError());
		setup = false;
	}

	return setup;
}

void print_title()
{
	if (!loadMedia())
		printf("Failed to load media!\n");
	else
	{
		SDL_Rect src;
		SDL_Rect dest;
		src.x = 0;
		src.y = 0;
		src.w = title->w;
		src.h = title->h;

		dest.x = (screen->w / 2) - (src.w / 2);
		dest.y = (screen->h / 2) - (src.h / 2);
		dest.w = title->w;
		dest.h = title->h;

		SDL_BlitSurface(title, &src, screen, &dest); // display the title 
	}
	SDL_UpdateWindowSurface(window);
}

void print_gameover()
{
	if (!loadMedia())
		printf("Failed to load media!\n");
	else
	{
		SDL_Rect src;
		SDL_Rect dest;
		src.x = 0;
		src.y = 0;
		src.w = endgame->w - 20;
		src.h = title->h - 20;

		dest.x = (screen->w / 2) - (src.w / 2);
		dest.y = (screen->h / 2) - (src.h / 2);
		dest.w = endgame->w;
		dest.h = endgame->h;

		SDL_BlitSurface(endgame, &src, screen, &dest);
	}
	SDL_UpdateWindowSurface(window);
}
void close()
{   
	SDL_FreeSurface(screen);
	SDL_FreeSurface(title);
	SDL_DestroyTexture(Message);
	// Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	title = NULL;
	window = NULL;
	TTF_CloseFont(gFont);
	// Quit SDL subsystems
	SDL_Quit();
	TTF_Quit();
}

void _drawFillRect(SDL_Color &col, int x, int y, int width, int height)
{
	SDL_Rect fillRect = {x, y, width, height};
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	SDL_RenderFillRect(renderer, &fillRect);
}

void _drawOutlineRect(SDL_Color &col, int x, int y, int width, int height)
{
	SDL_Rect outlineRect = {x, y, width, height};
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	SDL_RenderDrawRect(renderer, &outlineRect);
}
