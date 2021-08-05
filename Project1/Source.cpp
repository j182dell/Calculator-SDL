#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_mixer.h>

//prototypes and settings load before main
//if too much shit here, then move to header file later
bool InitialLoad();
SDL_Texture* createTexture(const char*);
SDL_Window* win;
SDL_Renderer* renderer;

int main(int argc, char* argv[])
{
    //Set up graphics, audio, inputs etc.
    if (!InitialLoad())
        printf("Failed loading 'InitialLoad()' function\n");

    //creates Texture from file
    SDL_Texture* tex = createTexture("resources/hello12.png");

    //Create Rectangular container 'h' (height) 'w' (width) you can resize picture by changing it just delete SDL_QueryTexture below which overriding these values,   'x' and 'y' represents upper left corner of rectangle and are used to position rectangle on screen ( example 0,0 very top left of application window )
    SDL_Rect dest;
    dest.h = 30;
    dest.w = 30;
    dest.x = 0;
    dest.y = 0;

	//get original picture height and width and save it
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

	// controls annimation loop
	int close = 0;

	// annimation loop
	while (!close) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				// handling of close button
				close = 1;
				break;

			case SDL_KEYDOWN:
				// keyboard API for key pressed
				switch (event.key.keysym.scancode)
				{
                //Hit Esc for quit application
                case SDL_SCANCODE_ESCAPE:
					close = 1;
					break;
				default:
					break;
				}
			}
		}


		// clears the screen
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderCopy(renderer, tex, NULL, &dest);

		// triggers the double buffers
		// for multiple rendering
		SDL_RenderPresent(renderer);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}

	// destroy texture
	SDL_DestroyTexture(tex);

	// destroy renderer
	SDL_DestroyRenderer(renderer);

	// destroy window
	SDL_DestroyWindow(win);

	// close SDL
	SDL_Quit();

	return 0;
}

bool InitialLoad()
{
    	// retutns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
        win = SDL_CreateWindow("GAME", // creates a window
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		400, 200, 0);

	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	renderer = SDL_CreateRenderer(win, -1, render_flags);

	return true;
};

SDL_Texture* createTexture(const char* file)
{
    // creates a surface to load an image into the main memory
	SDL_Surface* surface;

	// please provide a path for your image
	surface = IMG_Load(file);
	// loads image to our graphics hardware memory.
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	// clears main-memory
	SDL_FreeSurface(surface);

	return texture;
};
