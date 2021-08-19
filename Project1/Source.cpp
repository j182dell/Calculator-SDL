#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_mixer.h>
#include <stack>
#include <iostream>
#include <string>

using namespace std;

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


    enum  graphicTexture
    {
        background,
        button_0,
        button_1,
        button_2,
        button_3,
        button_4,
        button_5,
        button_6,
        button_7,
        button_8,
        button_9,
        texturesTotal
    };

    SDL_Texture* graphicTexture[texturesTotal];


    //creates Texture from file
    graphicTexture[background] = createTexture("resources/brushedmetal.jpg");
    graphicTexture[button_0] = createTexture("resources/0.jpg");
    graphicTexture[button_1] = createTexture("resources/1.jpg");
    graphicTexture[button_2] = createTexture("resources/2.jpg");
    graphicTexture[button_3] = createTexture("resources/3.jpg");
    graphicTexture[button_4] = createTexture("resources/4.jpg");
    graphicTexture[button_5] = createTexture("resources/5.jpg");
    graphicTexture[button_6] = createTexture("resources/6.jpg");
    graphicTexture[button_7] = createTexture("resources/7.jpg");
    graphicTexture[button_8] = createTexture("resources/8.jpg");
    graphicTexture[button_9] = createTexture("resources/9.jpg");

    //check if all textures loaded
    //Currently not working need to assign NULL for every element in graphic textures
    for(int i=0; i<texturesTotal; i++)
    {
        if (graphicTexture[i]==NULL)
            cout<<"File #"<<i<<" did not load correctly"<<endl;
    }

    //creates texture rectangular containers
    SDL_Rect dest_Background;
    dest_Background.w = window_width;
    dest_Background.h = window_height;
    dest_Background.x = 0;
    dest_Background.y = 0;


    int all_buttons_width = 80;
    int all_buttons_height = 80;
    int spacingbetweencells = 10;


    //create as many containers as textures
    SDL_Rect  dest_button[texturesTotal];

    for(int i=0;i<texturesTotal;i++)
    {
        //set all buttons dimensions
        dest_button[i].w = all_buttons_width;
        dest_button[i].h = all_buttons_height;
        //set default values just in case, change it in function below
        dest_button[i].x = 0;
        dest_button[i].y = 0;


        //NEED COMPLETE THIS:

        //pictures in rows 3
        for(int r=0; r<3;r++)
        {

        }

        //pictures in collumns 3
        for(int c=0; c<3;c++)
        {

        }


    }



    //Move all butoons in window - this is used to align
    SDL_Rect all_buttons_anchor;
    all_buttons_anchor.x = 20;
    all_buttons_anchor.y = 20;

    for(int i=0;i<texturesTotal;i++)
    {
        dest_button[i].x += all_buttons_anchor.x;
        dest_button[i].y += all_buttons_anchor.y;

    }



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
        SDL_RenderCopy(renderer, graphicTexture[background], NULL, &dest_Background);
        SDL_RenderCopy(renderer, graphicTexture[button_0], NULL, &dest_button[0]);
        SDL_RenderCopy(renderer, graphicTexture[button_1], NULL, &dest_button[1]);
        SDL_RenderCopy(renderer, graphicTexture[button_2], NULL, &dest_button[2]);
        SDL_RenderCopy(renderer, graphicTexture[button_3], NULL, &dest_button[3]);
        SDL_RenderCopy(renderer, graphicTexture[button_4], NULL, &dest_button[4]);
        SDL_RenderCopy(renderer, graphicTexture[button_5], NULL, &dest_button[5]);
        SDL_RenderCopy(renderer, graphicTexture[button_6], NULL, &dest_button[6]);
        SDL_RenderCopy(renderer, graphicTexture[button_7], NULL, &dest_button[7]);
        SDL_RenderCopy(renderer, graphicTexture[button_8], NULL, &dest_button[8]);
        SDL_RenderCopy(renderer, graphicTexture[button_9], NULL, &dest_button[9]);


        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(renderer);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // destroy textures
    for(int i=0; i<texturesTotal; i++)
        SDL_DestroyTexture(graphicTexture[i]);

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


