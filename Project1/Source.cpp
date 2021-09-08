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
int prec(char);

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
        background2,
        /*button_1,
        button_2,
        button_3,
        button_4,
        button_5,
        button_6,
        button_7,
        button_8,
        button_9,*/
        texturesTotal
    };

    SDL_Texture* graphicTexture[texturesTotal];

    for(int i=0; i<texturesTotal; i++)
        graphicTexture[i] = nullptr;


    //creates Texture from file
    graphicTexture[background] = createTexture("resources/calcimg.jpg");
    graphicTexture[background2] = createTexture("resources/calcimg-highlight.jpg");
    /*graphicTexture[button_1] = createTexture("");
    graphicTexture[button_2] = createTexture("");
    graphicTexture[button_3] = createTexture("");
    graphicTexture[button_4] = createTexture("");
    graphicTexture[button_5] = createTexture("");
    graphicTexture[button_6] = createTexture("");
    graphicTexture[button_7] = createTexture("");
    graphicTexture[button_8] = createTexture("");
    graphicTexture[button_9] = createTexture("");*/

    //check if all textures loaded
    //Currently not working need to assign NULL for every element in graphic textures
    for(int i=0; i<texturesTotal; i++)
    {
        if (graphicTexture[i]==NULL)
            cout<<"File #"<<i<<" did not load correctly"<<endl;
    }

    //creates texture rectangular containers -- destination copy entire texture into this container
    SDL_Rect dest_Background = CreateContainerFromTexture(graphicTexture[background]);
    dest_Background.w = window_width;
    dest_Background.h = window_height;

    //creates texture rectangular containers -- source copy part of texture into this container
    SDL_Rect src_Background = CreateContainerFromTexture(graphicTexture[background]);


    int buttons_total = 20;
    SDL_Rect src[buttons_total];
    SDL_Rect dst[buttons_total];
    int src_button_width = src_Background.w / 4;
    int src_button_height = src_Background.h / 5;
    int dst_button_width = window_width / 4;
    int dst_button_height = window_height / 5;


    //set button dimensions and default coordinate
    for (int i=0; i<buttons_total; i++)
    {
        src[i].w = src_button_width;
        src[i].h = src_button_height;
        dst[i].w = dst_button_width;
        dst[i].h = dst_button_height;

        src[i].x = 0;
        src[i].y = 0;
        dst[i].x = 0;
        dst[i].y = 0;
    }

    //set button coordinates
    for(int i=0, r=0, c=0; i<buttons_total; i++ )
    {
        if (r>3)
        {
            r=0;
            c++;
        }

        src[i].x = src_button_width*r;
        src[i].y = src_button_height*c;
        dst[i].x = dst_button_width*r;
        dst[i].y = dst_button_height*c;

        r++;
    }

    // controls annimation loop
    int close = false;

    cout<<"Calcoolator 3000 ver.2.15896 beta assembly, copyrighted, all rights reserved"<<endl<<endl<<"\t>\r\t";
    std::string answer_output = ("");

    // annimation loop
    while (!close)
    {

        SDL_Event event;
        int display_highl_pict;

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


                if (mouse_x >= 0 && mouse_x <= dst_button_width) {
                    if (mouse_y >= 0 && mouse_y <= dst_button_height) {
                        //flush screen and clear answer_output
                        display_highl_pict = 0;
                        answer_output += "";
                        system ("CLS");
                        cout<<"Calcoolator 3000 ver.2.15896 beta assembly, copyrighted, all rights reserved"<<endl<<endl<<"\t>\r\t";

                    }
                    else if (mouse_y >= dst_button_height && mouse_y <= dst_button_height*2) {
                        answer_output += '7';
                        display_highl_pict = 4;
                        std::cout <<""<<'7';
                    }
                    else if (mouse_y >= dst_button_height*2 && mouse_y <= dst_button_height*3) {
                        answer_output += '4';
                        display_highl_pict = 8;
                        std::cout << '4';
                    }
                    else if (mouse_y >= dst_button_height*3 && mouse_y <= dst_button_height*4) {
                        answer_output += '1';
                        display_highl_pict = 12;
                        std::cout << '1';
                    }
                    else if (mouse_y >= dst_button_height*4 && mouse_y <= window_height) {
                        answer_output += '0';
                        display_highl_pict = 16;
                        std::cout << '0';
                    }
                }

                else if (mouse_x >= dst_button_width && mouse_x <= dst_button_width*2) {
                    if (mouse_y >= 0 && mouse_y <= dst_button_height) {
                        answer_output += "";
                        display_highl_pict = 1;
                        std::cout << " +/- ";
                    }

                    if (mouse_y >= dst_button_height && mouse_y <= dst_button_height*2) {
                        answer_output += '8';
                        display_highl_pict = 5;
                        std::cout << '8';
                    }
                    else if (mouse_y >= dst_button_height*2 && mouse_y <= dst_button_height*3) {
                        answer_output += '5';
                        display_highl_pict = 9;
                        std::cout << '5';
                    }
                    else if (mouse_y >= dst_button_height*3 && mouse_y <= dst_button_height*4) {
                        answer_output += '2';
                        display_highl_pict = 13;
                        std::cout << '2';
                    }
                }

                else if (mouse_x >= dst_button_width*2 && mouse_x <= dst_button_width*3) {
                    if (mouse_y >= 0 && mouse_y <= dst_button_height) {
                        answer_output += "";
                        display_highl_pict = 2;
                        std::cout << " % ";
                    }
                    else if (mouse_y >= dst_button_height && mouse_y <= dst_button_height*2) {
                        answer_output += '9';
                        display_highl_pict = 6;
                        std::cout << '9';
                    }
                    else if (mouse_y >= dst_button_height*2 && mouse_y <= dst_button_height*3) {
                        answer_output += '6';
                        display_highl_pict = 10;
                        std::cout << '6';
                    }
                    else if (mouse_y >= dst_button_height*3 && mouse_y <= dst_button_height*4) {
                        answer_output += '3';
                        display_highl_pict = 14;
                        std::cout << '3';
                    }
                    else if (mouse_y >= dst_button_height*4 && mouse_y <= window_height) {
                        answer_output += "";
                        display_highl_pict = 18;
                        std::cout << ",";
                    }
                }

                else if (mouse_x >= dst_button_width*3 && mouse_x <= dst_button_width*4) {
                    if (mouse_y >= 0 && mouse_y <= dst_button_height) {
                        answer_output += '/';
                        display_highl_pict = 3;
                        std::cout << " / ";
                    }
                    else if (mouse_y >= dst_button_height && mouse_y <= dst_button_height*2) {
                        answer_output += 'x';
                        display_highl_pict = 7;
                        std::cout << " x ";
                    }
                    else if (mouse_y >= dst_button_height*2 && mouse_y <= dst_button_height*3) {
                        answer_output += '-';
                        display_highl_pict = 11;
                        std::cout << " - ";
                    }
                    else if (mouse_y >= dst_button_height*3 && mouse_y <= dst_button_height*4) {
                        answer_output += '+';
                        display_highl_pict = 15;
                        std::cout << " + ";
                    }
                    else if (mouse_y >= dst_button_height*4 && mouse_y <= window_height) {
                        answer_output += "";
                        display_highl_pict = 19;
                        std::cout << " = ";
                    }

                }

                // Jonas what is this one for???
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

        //-------------Copy new or updated pictures into screen---------------------------------

        for(int i=0; i<buttons_total; i++ )
        {
            SDL_RenderCopy(renderer, graphicTexture[background], &src[i], &dst[i]);

        }

        if (event.type == SDL_MOUSEBUTTONDOWN && display_highl_pict>=0)
        {

            SDL_RenderCopy(renderer, graphicTexture[background2], &src[display_highl_pict], &dst[display_highl_pict]);
        }


        //--------------------------------------------------------------------------------------


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
    win = SDL_CreateWindow("CalCoolator 3000", // creates a window
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

