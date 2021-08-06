#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_mixer.h>
#include <stack>
#include <iostream>
#include <string>

//prototypes and settings load before main
//if too much shit here, then move to header file later
bool InitialLoad();
void infixToPostfix();
SDL_Texture* createTexture(const char*);
SDL_Window* win;
SDL_Renderer* renderer;
SDL_Rect CreateTextureContainer(SDL_Texture*);

int main(int argc, char* argv[])
{
    //Set up graphics, audio, inputs etc.
    if (!InitialLoad())
        printf("Failed loading 'InitialLoad()' function\n");

    //creates Texture from file
    SDL_Texture* tex = createTexture("resources/hello12.png");
    //creates texture rectangular container from original picture
    SDL_Rect dest = CreateTextureContainer(tex);

	// controls annimation loop
	int close = false;

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

	int window_height = 400;
	int window_width = 200;


    	// retutns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
        win = SDL_CreateWindow("GAME", // creates a window
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_height, window_width, 0);

	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	renderer = SDL_CreateRenderer(win, -1, render_flags);

	return true;
}

void infixToPostfix()
{
}

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
}


//Function to return precedence of operators
int prec(char c) {
	if (c == '^')
		return 3;
	else if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

// The main function to convert infix expression
//to postfix expression
 void infixToPostfix(std::string s) {

	std::stack<char> st; //For stack operations, we are using C++ built in stack
	std::string result;


	for (int i = 0; i < s.length(); i++) {
		char c = s[i];


		// If the scanned character is
		// an operand, add it to output string.
		if ((c >= '0' && c <= '9'))
			result += c;


		else if (c == '%')
			result += '%';

		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if (c == '(')
			st.push('(');

		// If the scanned character is an ‘)’,
		// pop and to output string from the stack
		// until an ‘(‘ is encountered.
		else if (c == ')') {
			while (st.top() != '(')
			{

				result += st.top();
				result += '%';

				st.pop();
			}
			st.pop();
		}

		//If an operator is scanned
		else {
			while (!st.empty() && prec(s[i]) <= prec(st.top())) {

				result += st.top();
				result += '%';

				st.pop();
			}
			st.push(c);
		}
	}

	// Pop all the remaining elements from the stack
	while (!st.empty()) {

		result += '%';
		result += st.top();
		result += '%';

		st.pop();
	}

	std::cout << result;
 }

 SDL_Rect CreateTextureContainer(SDL_Texture* texture)
 {
    //Create Rectangular container
    SDL_Rect rectangle;
    rectangle.h = 0;
    rectangle.w = 0;
    rectangle.x = 0;
    rectangle.y = 0;

	//get texture height and width and save it
    SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h);

    return rectangle;
 }
