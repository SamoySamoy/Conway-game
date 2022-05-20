#pragma once
#include "conway.h"


void run()
{   
    if (!load_music()) 
	{
		cout << "Failed to load music";
		return;
	}
	// apply background music for the game with infinite loop
	Mix_PlayMusic(bg, -1);
	if (!sdl_init())
	{
		cout << "Failed to initialize";
		return;
	}
	while (quit == false)
	{	 									
		const Uint8 *keystate = SDL_GetKeyboardState(NULL); // init keystate events
		if (keystate[SDL_SCANCODE_ESCAPE]) quit = true; // press ESC to exit the game 
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
			{
				quit = true;
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{ // mouse events
				SDL_MouseButtonEvent *temp = (SDL_MouseButtonEvent *)&e;
				if (temp->windowID == SDL_GetWindowID(window))
				{
					int x = int(temp->x / 10);
					int y = int(temp->y / 10);
					if (x >= 0 && x < BOARD_SIZE_X && y >= 0 && y < BOARD_SIZE_Y)
					{
						// left click to generate "resident square"
						if (temp->button == SDL_BUTTON_LEFT)
						{
							if (board[x][y] == 0)
							{
								board[x][y] = 1;
								population_count++;
							}
						}
						// right click to delete "resident square" before apply logic
						else if (temp->button == SDL_BUTTON_RIGHT)
						{
							if (board[x][y] == 1)
							{
								board[x][y] = 0;
								population_count--;
							}
						}
					}
				}
				break;
			}
			case SDL_KEYDOWN:
			{
				if (e.key.keysym.sym == SDLK_s && state == 1)  // press S to start generating
				{
					gene = true;
				}
				break;
			}
			}
		}
		SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
		SDL_RenderClear(renderer);
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 185, 65, 16)); // menu background color
		if (state == 0) // menu state
		{
			print_title();
			if (keystate[SDL_SCANCODE_SPACE])  // press space to begin / unpaused
			{
				state = 1; 
				paused = false;
				previous = 0;
			}
			SDL_Delay(100);
		}
		else if (state == 2) {
			print_gameover();
			if (keystate[SDL_SCANCODE_R]) { // refresh game data
				for (int i = 0; i < BOARD_SIZE_X; i++)
				{
					for (int j = 0; j < BOARD_SIZE_Y; j++)
					{
						board[i][j] = 0;
					}
				}
				population_count = 0;
				previous = 0;
				high = 0;
				low = 1000;
				gene = false;
				state = 0;
				speed = 300;
			}
		}
		else if (state == 1) // main state
		{   
			
			if (keystate[SDL_SCANCODE_R]) // restart the game
		    {   
				for (int i = 0; i < BOARD_SIZE_X; i++)
				{
					for (int j = 0; j < BOARD_SIZE_Y; j++)
					{
						board[i][j] = 0;
					}
				}
				population_count = 0;
				previous = 0;
				high = 0;
				low = 1000;
				gene = false;
				state = 0;
				speed = 300;
			}
			if (SDL_GetTicks64() - previous >= speed) // Get the number of milliseconds since SDL library initialization.
			{ 
				previous = SDL_GetTicks64();
				if (keystate[SDL_SCANCODE_UP]) 
					speed -= 40;
				if (keystate[SDL_SCANCODE_DOWN])
					speed += 40;
				if (keystate[SDL_SCANCODE_P] && state == 1)
				{
					if (!paused) paused = true;
					state = 0;
					SDL_Delay(50);
				}
				if (gene == true && paused == false) // apply the game logic
				{   
					bool stop = true; // check for endgame
					int newboard[BOARD_SIZE_X][BOARD_SIZE_Y];
					// create a newboard for checking game gene
					std::copy(&board[0][0], &board[0][0] + BOARD_SIZE_X * BOARD_SIZE_Y, &newboard[0][0]);
					for (int i = 0; i < BOARD_SIZE_X; i++)
					{
						for (int j = 0; j < BOARD_SIZE_Y; j++)
						{   
							int alive = 0;
							int dead = 0;
							for (int k = 0; k < 8; k++)
							{
								int newx = i - nx[k];
								int newy = j - ny[k];
								// Check validations
								if (newx >= 0 && newx < BOARD_SIZE_X && newy >= 0 && newy < BOARD_SIZE_Y)
								{
									if (board[newx][newy] == 0)
										dead++;
									else
										alive++;
								}
							}
							if (board[i][j] == 1 && (alive == 2 || alive == 3)) continue;
							else if (board[i][j] == 1)
							{
								newboard[i][j] = 0;
								population_count--;
								stop = false;
							}	
							else if (board[i][j] == 0 && alive == 3)
							{
								newboard[i][j] = 1;
								population_count++;
								stop = false;
							}	
						}
					}
					// update the lowest and highest population
					if (high < population_count)
						high = population_count;
					if (low > population_count)
						low = population_count;
					// update the board
					std::copy(&newboard[0][0], &newboard[0][0] + BOARD_SIZE_X * BOARD_SIZE_Y, &board[0][0]);
					char paneltext[64];
					// dipslay the text
					snprintf(paneltext, 64, "Population: %i Lowest: %i Crowdest: %i", population_count, low, high);
					surfaceMessage = TTF_RenderText_Shaded(gFont, paneltext, panel_outline, bg_color);
					Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
					SDL_FreeSurface(surfaceMessage);		
					if (SDL_GetTicks64() >= 300 && state == 1) {
						if (stop) {
							SDL_Delay(1234); // Delay before moving to endgame state
							state = 2;
						}	
					}
				}
			}
			SDL_Rect Message_rect = {20, SCREEN_HEIGHT - PANEL + 20, 450, 75}; // Text position
			SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
			// fill color
			for (int i = 0; i < BOARD_SIZE_X; i++)
			{
				for (int j = 0; j < BOARD_SIZE_Y; j++)
				{
					if (board[i][j] == 1)
						draw_square(filled, i * 10, j * 10, 10, 10); 
				}
			}
            
			SDL_SetRenderDrawColor(renderer, panel_outline.r, panel_outline.g, panel_outline.b, panel_outline.a);
			for (int t = 0; t < THICKNESS; t++)
			{
				SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT - PANEL + t, SCREEN_WIDTH, SCREEN_HEIGHT - PANEL + t);
			}
			SDL_RenderPresent(renderer); // Update screen
		}
	}
	// close SDL
	close();
}
