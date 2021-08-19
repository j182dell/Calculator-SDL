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
bool InitialLoad(int,int);
void infixToPostfix();
SDL_Texture* createTexture(const char*);
SDL_Window* win;
SDL_Renderer* renderer;
SDL_Rect CreateContainerFromTexture(SDL_Texture*,int x=0,int y=0);

int main(int argc, char* argv[])
{
    //Set window dimensions
    int window_height = 400;
    int window_width = 300;

    //Set up graphics, audio, inputs etc.
    if (!InitialLoad(window_width, window_height))
        printf("Failed loading 'InitialLoad()' function\n");

    //creates Texture from file
    SDL_Texture* gtex_Background = createTexture("resources/brushedmetal.jpg");
    SDL_Texture* gtex_0_button = createTexture("resources/0.jpg");
    SDL_Texture* gtex_1_button = createTexture("resources/1.jpg");
    SDL_Texture* gtex_2_button = createTexture("resources/2.jpg");
    SDL_Texture* gtex_3_button = createTexture("resources/3.jpg");
    SDL_Texture* gtex_4_button = createTexture("resources/4.jpg");
    SDL_Texture* gtex_5_button = createTexture("resources/5.jpg");
    SDL_Texture* gtex_6_button = createTexture("resources/6.jpg");
    SDL_Texture* gtex_7_button = createTexture("resources/7.jpg");
    SDL_Texture* gtex_8_button = createTexture("resources/8.jpg");
    SDL_Texture* gtex_9_button = createTexture("resources/9.jpg");

    //creates texture rectangular containers
    SDL_Rect dest_Background;
    dest_Background.w = window_width;
    dest_Background.h = window_height;
    dest_Background.x = 0;
    dest_Background.y = 0;


    int all_buttons_width = 60;
    int all_buttons_height = 60;
    int spacingbetweencells = 30;

    SDL_Rect dest_1_button;
    dest_1_button.w = all_buttons_width;
    dest_1_button.h = all_buttons_height;
    dest_1_button.x = 0;
    dest_1_button.y = 0;

    SDL_Rect dest_2_button;
    dest_2_button.w = all_buttons_width;
    dest_2_button.h = all_buttons_height;
    dest_2_button.x = dest_1_button.w+spacingbetweencells;
    dest_2_button.y = 0;

    SDL_Rect dest_3_button;
    dest_3_button.w = all_buttons_width;
    dest_3_button.h = all_buttons_height;
    dest_3_button.x = dest_2_button.x+dest_1_button.w+spacingbetweencells;
    dest_3_button.y = 0;

    SDL_Rect dest_4_button;
    dest_4_button.w = all_buttons_width;
    dest_4_button.h = all_buttons_height;
    dest_4_button.x = 0;
    dest_4_button.y = dest_1_button.h+spacingbetweencells;

    SDL_Rect dest_5_button;
    dest_5_button.w = all_buttons_width;
    dest_5_button.h = all_buttons_height;
    dest_5_button.x = dest_1_button.w+spacingbetweencells;
    dest_5_button.y = dest_1_button.h+spacingbetweencells;

    SDL_Rect dest_6_button;
    dest_6_button.w = all_buttons_width;
    dest_6_button.h = all_buttons_height;
    dest_6_button.x = dest_5_button.x+dest_1_button.w+spacingbetweencells;
    dest_6_button.y = dest_1_button.h+spacingbetweencells;

    SDL_Rect dest_7_button;
    dest_7_button.w = all_buttons_width;
    dest_7_button.h = all_buttons_height;
    dest_7_button.x = 0;
    dest_7_button.y = dest_4_button.y+dest_1_button.h+spacingbetweencells;

    SDL_Rect dest_8_button;
    dest_8_button.w = all_buttons_width;
    dest_8_button.h = all_buttons_height;
    dest_8_button.x = dest_1_button.w+spacingbetweencells;
    dest_8_button.y = dest_4_button.y+dest_1_button.h+spacingbetweencells;

    SDL_Rect dest_9_button;
    dest_9_button.w = all_buttons_width;
    dest_9_button.h = all_buttons_height;
    dest_9_button.x = dest_2_button.x+dest_1_button.w+spacingbetweencells;
    dest_9_button.y = dest_4_button.y+dest_1_button.h+spacingbetweencells;

    SDL_Rect dest_0_button;
    dest_0_button.w = all_buttons_width;
    dest_0_button.h = all_buttons_height;
    dest_0_button.x = dest_1_button.w+spacingbetweencells;
    dest_0_button.y = dest_7_button.y+dest_1_button.h+spacingbetweencells;

    //Move all butoons in window - this is used to align
    SDL_Rect all_buttons_anchor;
    all_buttons_anchor.x = 30;
    all_buttons_anchor.y = 20;

    dest_1_button.x += all_buttons_anchor.x;
    dest_2_button.x += all_buttons_anchor.x;
    dest_3_button.x += all_buttons_anchor.x;
    dest_4_button.x += all_buttons_anchor.x;
    dest_5_button.x += all_buttons_anchor.x;
    dest_6_button.x += all_buttons_anchor.x;
    dest_7_button.x += all_buttons_anchor.x;
    dest_8_button.x += all_buttons_anchor.x;
    dest_9_button.x += all_buttons_anchor.x;
    dest_0_button.x += all_buttons_anchor.x;

    dest_1_button.y += all_buttons_anchor.y;
    dest_2_button.y += all_buttons_anchor.y;
    dest_3_button.y += all_buttons_anchor.y;
    dest_4_button.y += all_buttons_anchor.y;
    dest_5_button.y += all_buttons_anchor.y;
    dest_6_button.y += all_buttons_anchor.y;
    dest_7_button.y += all_buttons_anchor.y;
    dest_8_button.y += all_buttons_anchor.y;
    dest_9_button.y += all_buttons_anchor.y;
    dest_0_button.y += all_buttons_anchor.y;



    // controls annimation loop
    int close = false;

    // annimation loop
    while (!close)
    {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

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
                //My own convinience for testing
                case SDL_SCANCODE_F10:
                    close = 1;
                    break;

                default:
                    break;
                }
            }
        }


        // clears the screen from previous pictures
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        //Copy new or updated pictures into screen
        SDL_RenderCopy(renderer, gtex_Background, NULL, &dest_Background);
        SDL_RenderCopy(renderer, gtex_0_button, NULL, &dest_0_button);
        SDL_RenderCopy(renderer, gtex_1_button, NULL, &dest_1_button);
        SDL_RenderCopy(renderer, gtex_2_button, NULL, &dest_2_button);
        SDL_RenderCopy(renderer, gtex_3_button, NULL, &dest_3_button);
        SDL_RenderCopy(renderer, gtex_4_button, NULL, &dest_4_button);
        SDL_RenderCopy(renderer, gtex_5_button, NULL, &dest_5_button);
        SDL_RenderCopy(renderer, gtex_6_button, NULL, &dest_6_button);
        SDL_RenderCopy(renderer, gtex_7_button, NULL, &dest_7_button);
        SDL_RenderCopy(renderer, gtex_8_button, NULL, &dest_8_button);
        SDL_RenderCopy(renderer, gtex_9_button, NULL, &dest_9_button);


        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(renderer);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // destroy texture
    SDL_DestroyTexture(gtex_Background);
    SDL_DestroyTexture(gtex_0_button);
    SDL_DestroyTexture(gtex_1_button);
    SDL_DestroyTexture(gtex_2_button);
    SDL_DestroyTexture(gtex_3_button);
    SDL_DestroyTexture(gtex_4_button);
    SDL_DestroyTexture(gtex_5_button);
    SDL_DestroyTexture(gtex_6_button);
    SDL_DestroyTexture(gtex_7_button);
    SDL_DestroyTexture(gtex_8_button);
    SDL_DestroyTexture(gtex_9_button);

    // destroy renderer
    SDL_DestroyRenderer(renderer);

    // destroy window
    SDL_DestroyWindow(win);

    // close SDL
    SDL_Quit();

    return 0;
}

bool InitialLoad(int window_width, int window_height)
{
    // retutns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    win = SDL_CreateWindow("GAME", // creates a window
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           window_width, window_height, 0);

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
int prec(char c)
{
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
void infixToPostfix(std::string s)
{

    std::stack<char> st; //For stack operations, we are using C++ built in stack
    std::string result;


    for (int i = 0; i < s.length(); i++)
    {
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
        else if (c == ')')
        {
            while (st.top() != '(')
            {

                result += st.top();
                result += '%';

                st.pop();
            }
            st.pop();
        }

        //If an operator is scanned
        else
        {
            while (!st.empty() && prec(s[i]) <= prec(st.top()))
            {

                result += st.top();
                result += '%';

                st.pop();
            }
            st.push(c);
        }
    }

    // Pop all the remaining elements from the stack
    while (!st.empty())
    {

        result += '%';
        result += st.top();
        result += '%';

        st.pop();
    }

    std::cout << result;
}

SDL_Rect CreateContainerFromTexture(SDL_Texture* texture, int x, int y)
{
    //Create Rectangular container
    SDL_Rect rectangle;
    rectangle.w = 0;
    rectangle.h = 0;
    rectangle.x = x;
    rectangle.y = y;

    //get texture height and width and save it
    SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h);

    return rectangle;
}
