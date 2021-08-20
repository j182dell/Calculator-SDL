#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_mixer.h>
#include <stack>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>


//prototypes and settings load before main
//if too much shit here, then move to header file later
bool InitialLoad(int, int);
void infixToPostfix();
SDL_Texture* createTexture(const char*);
SDL_Window* win;
SDL_Renderer* renderer;
//SDL_Rect CreateContainerFromTexture(SDL_Texture*,int x=0,int y=0);

int main(int argc, char* argv[])
{

    //Set window dimensions
    int window_height = 690;
    int window_width = 552;

    //Set up graphics, audio, inputs etc.
    if (!InitialLoad(window_width, window_height))
        printf("Failed loading 'InitialLoad()' function\n");

    //creates Texture from file
    SDL_Texture* gtex_Background = createTexture("resources/calcimg.jpg");

    //creates texture rectangular containers
    SDL_Rect dest_Background;
    dest_Background.w = window_width;
    dest_Background.h = window_height;
    dest_Background.x = 0;
    dest_Background.y = 0;

    // controls annimation loop
    int close = false;

    std::string answer_output = ("");

    // annimation loop
    while (!close)
    {

        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event))
        {

            int mouse_x = event.button.x;
            int mouse_y = event.button.y;


            switch (event.type)
            {

            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            case SDL_MOUSEBUTTONDOWN:

                /*
                    x1 = 0
                    x2 = 138
                    Button C: y1 = 0, y2 = 138
                    Button 7: y1 = 138, y2 = 276
                    Button 4: y1 = 276, y2 = 414
                    Button 1: y1 = 414, y2 = 552
                    Button 0: y1 = 552, y2 = 690
                */
                if (mouse_x >= 0 && mouse_x <= 138) {
                    if (mouse_y >= 0 && mouse_y <= 138) {
                        answer_output = "";
                        std::cout << std::endl;
                    }
                    else if (mouse_y >= 138 && mouse_y <= 276) {
                        answer_output += '7';
                        std::cout << '7';
                    }
                    else if (mouse_y >= 276 && mouse_y <= 414) {
                        answer_output += '4';
                        std::cout << '4';
                    }
                    else if (mouse_y >= 414 && mouse_y <= 552) {
                        answer_output += '1';
                        std::cout << '1';
                    }
                    else if (mouse_y >= 552 && mouse_y <= 690) {
                        answer_output += '0';
                        std::cout << '0';
                    }
                }

                /*
                    x1 = 138
                    x2 = 276
                    Button 8: y1 = 138, y2 = 276
                    Button 5: y1 = 276, y2 = 414
                    Button 2: y1 = 414, y2 = 552
                */
                else if (mouse_x >= 138 && mouse_x <= 276) {
                    if (mouse_y >= 138 && mouse_y <= 276) {
                        answer_output += '8';
                        std::cout << '8';
                    }
                    else if (mouse_y >= 276 && mouse_y <= 414) {
                        answer_output += '5';
                        std::cout << '5';
                    }
                    else if (mouse_y >= 414 && mouse_y <= 552) {
                        answer_output += '2';
                        std::cout << '2';
                    }
                }

                /*
                    x1 = 276
                    x2 = 414
                    Button 9: y1 = 138, y2 = 276
                    Button 6: y1 = 276, y2 = 414
                    Button 3: y1 = 414, y2 = 552
                */
                else if (mouse_x >= 276 && mouse_x <= 414) {
                    if (mouse_y >= 138 && mouse_y <= 276) {
                        answer_output += '9';
                        std::cout << '9';
                    }
                    else if (mouse_y >= 276 && mouse_y <= 414) {
                        answer_output += '6';
                        std::cout << '6';
                    }
                    if (mouse_y >= 414 && mouse_y <= 552) {
                        answer_output += '3';
                        std::cout << '3';
                    }
                }

                /*
                   x1 = 414
                   x2 = 552
                   Button /: y1 = 0, y2 = 138
                   Button X: y1 = 138, y2 = 276
                   Button -: y1 = 276, y2 = 414
                   Button +: y1 = 414, y2 = 552
                   Button =: y1 = 552, y2 = 690
               */
                else if (mouse_x >= 414 && mouse_x <= 552) {
                    if (mouse_y >= 0 && mouse_y <= 138) {
                        answer_output += '/';
                        std::cout << " / ";
                    }
                    else if (mouse_y >= 138 && mouse_y <= 276) {
                        answer_output += 'x';
                        std::cout << " x ";
                    }
                    else if (mouse_y >= 276 && mouse_y <= 414) {
                        answer_output += '-';
                        std::cout << " - ";
                    }
                    else if (mouse_y >= 414 && mouse_y <= 552) {
                        answer_output += '+';
                        std::cout << " + ";
                    }

                }

                if (mouse_x >= 414 && mouse_x <= 552 && mouse_y >= 552 && mouse_y <= 690) {
                    std::cout << std::endl << answer_output << std::endl;
                    answer_output = "";
                }


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


        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(renderer);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // destroy texture
    SDL_DestroyTexture(gtex_Background);

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

int button_press_event()
{
    return 0;
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
        // (, push it to the stack.
        else if (c == '(')
            st.push('(');

        // If the scanned character is an ),
        // pop and to output string from the stack
        // until an ( is encountered.
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
