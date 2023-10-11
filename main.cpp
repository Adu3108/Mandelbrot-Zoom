/* * * * * * * MANDELBROT ZOOM PROJECT FOR CS 293 * * * * * *
    I have tested this code on MacOS Catalina
    For graphics, I have used SDL graphics library
    All the header files required for using SDL graphics library have been included in the project folder
    For executing the program, I have a Makefile of name 'rawmake'
    In order to generate the executable (which in this case is named 'play'), enter the following command
    $ make -f rawmake game
    This generates the executable which can be run using the following command
    $ ./play
*/

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <string.h> 
#include <time.h> 
using namespace std;

// Defining Window Dimensions 
int WIDTH = 800;
int HEIGHT = 800;
int MAX_ITERATIONS = 200;
long double factor = 1.0;

// Setting the constants for Mandelbrot Set Analysis
long double minimum_x = -2;
long double maximum_x = 2;
long double minimum_y = -2;
long double maximum_y = 2;

// Used to bring the pixel co-ordinates in range 
long double map(long double value, long double input_min, long double input_max, long double output_min, long double output_max){
    return (value - input_min)*(output_max - output_min)/(input_max - input_min) + output_min;
}

// Moves the picture to right
void right(){
    maximum_x = maximum_x - 0.1*factor;
    minimum_x = minimum_x - 0.1*factor;
}

// Moves the picture to left
void left(){
    maximum_x = maximum_x + 0.1*factor;
    minimum_x = minimum_x + 0.1*factor;
}

// Moves the picture up
void up(){
    maximum_y = maximum_y + 0.1*factor;
    minimum_y = minimum_y + 0.1*factor;
}

// Moves the picture down
void down(){
    maximum_y = maximum_y - 0.1*factor;
    minimum_y = minimum_y - 0.1*factor;
}

// Zoom into the picture
void zoom_in(){
    MAX_ITERATIONS = MAX_ITERATIONS + 16;
    maximum_y = maximum_y - 0.1*factor;
    minimum_y = minimum_y + 0.06*factor;
    maximum_x = maximum_x - 0.1*factor;
    minimum_x = minimum_x + 0.06*factor;
    factor = factor*0.96;
}

// Zoom out of the picture
void zoom_out(){
    MAX_ITERATIONS = MAX_ITERATIONS - 16;
    maximum_y = maximum_y + 0.1*factor;
    minimum_y = minimum_y - 0.06*factor;
    maximum_x = maximum_x + 0.1*factor;
    minimum_x = minimum_x - 0.06*factor;
    factor = factor/0.96;
}

// Restart the Mandelbrot Zoom
void restart(){
    maximum_x = 2;
    maximum_y = 2;
    minimum_x = -2;
    minimum_y = -2;
    factor = 1;
    MAX_ITERATIONS = 200;
}

// Calculate distance of given complex number from origin
long double magnitude(long double x, long double y){
    return x*x + y*y;
}

// Compute the x-coordinate of next iterate
long double new_x(long double x, long double y){
    return x*x - y*y;
}

// Compute y-coordinate of next iterate
long double new_y(long double x, long double y){
    return 2*x*y;
}

int main(){
    // Modern Color Palette for Mandelbrot Set
    int color[16][3];
    color[0][0] = 66;
    color[0][1] = 30;
    color[0][2] = 15;
    color[1][0] = 25;
    color[1][1] = 7;
    color[1][2] = 26;
    color[2][0] = 9;
    color[2][1] = 1;
    color[2][2] = 47;
    color[3][0] = 4;
    color[3][1] = 4;
    color[3][2] = 73;
    color[4][0] = 0;
    color[4][1] = 7;
    color[4][2] = 100;
    color[5][0] = 12;
    color[5][1] = 44;
    color[5][2] = 138;
    color[6][0] = 24;
    color[6][1] = 82;
    color[6][2] = 177;
    color[7][0] = 57;
    color[7][1] = 125;
    color[7][2] = 209;
    color[8][0] = 134;
    color[8][1] = 181;
    color[8][2] = 229;
    color[9][0] = 211;
    color[9][1] = 236;
    color[9][2] = 248;
    color[10][0] = 241;
    color[10][1] = 233;
    color[10][2] = 191;
    color[11][0] = 248;
    color[11][1] = 201;
    color[11][2] = 95;
    color[12][0] = 255;
    color[12][1] = 170;
    color[12][2] = 0;
    color[13][0] = 204;
    color[13][1] = 128;
    color[13][2] = 0;
    color[14][0] = 153;
    color[14][1] = 87;
    color[14][2] = 0;
    color[15][0] = 106;
    color[15][1] = 52;
    color[15][2] = 3;

    // Creating the Window for Mandelbrot Zoom
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window; 
    SDL_Renderer* renderer;
    SDL_Event event;
    
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

    // RGB values for each pixel
    int red = 255; 
    int green = 255;
    int blue = 255;

    // Selecting the Mode for Mandelbrot Zoom
    cout << "Select a Mode : Automatic or Manual" << endl;
    cout << "Press a for Automatic Mode" << endl;
    cout << "Press m for Manual Mode" << endl;

    bool done = true;
    string automatic("a");
    string manual("m");
    string q; 

    // Taking User input from command line 
    while(done){
        getline(cin,q);
        if((q.compare(manual)==0) || (q.compare(automatic)==0)){
            done = false;
        }
        else{
            cout << "Incorrect Input. Try again" << endl;
        }
    }

    // Manual Mode has been selected
    if(q.compare(manual)==0){
        cout << endl;
        cout << "Manual mode activated" << endl;
        cout << endl;
    }
    // Automatic Mode has been selected
    else{
        cout << endl;
        cout << "Automatic Mode activated" << endl;
        cout << endl;
    }

    // Selecting a color scheme for Mandelbrot Zoom
    cout << "Please select a color scheme for the Mandelbrot Set" << endl;
    cout << "Press t for Traditional Color Scheme" << endl;
    cout << "Press m for Modern Color Scheme" << endl;

    bool done2 = true;
    bool done3 = true;
    string traditional("t");
    string modern("m");
    string Blue("1");
    string Purple("2");
    string Pink("3");
    string Orange("4");
    string Green("5");
    string colour; 
    string color_type;

    // Taking User Input from command line 
    while(done2){
        getline(cin,colour);
        if((colour.compare(modern)==0) || (colour.compare(traditional)==0)){
            done2 = false;
        }
        else{
            cout << "Incorrect Input. Try again" << endl;
        }
    }

    if(colour.compare(modern)==0){
        cout << endl;
        cout << "You have selected Modern Color Scheme" << endl;
        cout << endl;
    }
    else{
        // Selecting the primary color for the traditional color scheme
        cout << endl;
        cout << "You have selected Traditional Color Scheme" << endl;
        cout << "Please select your favourite color" << endl;
        cout << endl;
        cout << "Press 1 for Blue" << endl;
        cout << "Press 2 for Purple" << endl;
        cout << "Press 3 for Pink" << endl;
        cout << "Press 4 for Orange" << endl;
        cout << "Press 5 for Green" << endl;

        // Taking User Input from command line
        while (done3){
            getline(cin,color_type);
            if((color_type.compare(Blue)==0) || (color_type.compare(Pink)==0) || (color_type.compare(Orange)==0) || (color_type.compare(Green)==0) || (color_type.compare(Purple)==0)){
                done3 = false;
            }
            else{
                cout << "Incorrect Input. Try again" << endl;
            }
        }

        // Blue color has been selected
        if(color_type.compare(Blue)==0){
            cout << endl;
            cout << "You have selected Blue color for the Mandelbrot Set" << endl;
            cout << endl;
        }
        // Purple color has been selected
        else if(color_type.compare(Purple)==0){
            cout << endl;
            cout << "You have selected Purple color for the Mandelbrot Set" << endl;
            cout << endl;
        }
        // Orange color has been selected
        else if(color_type.compare(Orange)==0){
            cout << endl;
            cout << "You have selected Orange color for the Mandelbrot Set" << endl;
            cout << endl;
        }
        // Green color has been selected
        else if(color_type.compare(Green)==0){
            cout << endl;
            cout << "You have selected Green color for the Mandelbrot Set" << endl;
            cout << endl;
        }
        // Pink color has been selected
        else{
            cout << endl;
            cout << "You have selected Pink color for the Mandelbrot Set" << endl;
            cout << endl;
        }
    }

    int count = 1; // Keeps track of number of commands entered
    int print_count = 0;
    int restart_count = 0;
    bool pause = true;
    if(q.compare(manual) == 0){
        cout << "This is your Command History :-" << endl;
    }
    else{
        cout << "The status of program :-" << endl;
        cout << "The program is running" << endl;
    }

    /* * * * * * MANUAL MODE * * * * * *
    In Manual Mode, you navigate across the Mandelbrot set using button presses
    Acceptable Commands :-
    Q                   : Quit the Program
    R                   : Restart the Program
    Z                   : Zoom in 
    Spacebar            : Zoom out
    Left Arrow Key      : Move the picture to left
    Right Arrow key     : Move the picture to right
    Up Arrow Key        : Move the picture up
    Down Arrow Key      : Move the picture down 
    */

   // Program takes some time to display the Mandelbrot Set
   // It has been observed that at around 20-30 iterations, the program becomes a little bit slow
   // However after say 50 iterations, the program again becomes fast
   
    while(true){
        if(q.compare(manual)==0){  
            while(SDL_WaitEvent(&event)){ 
                if(count >= 1 && count < 3){
                    break;
                }  
                else if(event.type == SDL_KEYDOWN){
                    if(event.key.keysym.sym == SDLK_RIGHT){
                        cout << "You pressed Right arrow key" << endl;
                        right();
                        break;
                    }
                    else if(event.key.keysym.sym == SDLK_LEFT){
                        cout << "You pressed Left arrow key" << endl;
                        left();
                        break;
                    }
                    else if(event.key.keysym.sym == SDLK_DOWN){
                        cout << "You pressed Down arrow key" << endl;
                        down();
                        break;
                    }
                    else if(event.key.keysym.sym == SDLK_UP){
                        cout << "You pressed Up arrow key" << endl;
                        up();
                        break;
                    }
                    else if(event.key.keysym.sym == SDLK_q){
                        cout << "You pressed Q" << endl;
                        return 0;
                    }
                    else if(event.key.keysym.sym == SDLK_z){
                        cout << "You pressed Z" << endl;
                        zoom_in();
                        break;
                    }
                    else if(event.key.keysym.sym == SDLK_SPACE){
                        cout << "You pressed Space bar" << endl;
                        zoom_out();
                        break;
                    }
                    else if(event.key.keysym.sym == SDLK_r){
                        cout << "You pressed R" << endl;
                        restart();
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    continue;
                }
            }
        }

        /* * * * * AUTOMATIC MODE * * * * *
        In Automatic Mode, I have already fed in a set of commands which will execute automatically
        No input needed from the user end
        I have provided a minute long video demonstrating the automatic mode named 'demo.mp4'
        The original video is longer than this and have provided the fast forwarded version
        Acceptable commands :-
        Q                   : Quit the program
        K                   : Pause the program
        R                   : Resume the program
        Spacebar            : Restart the program
        */

        else{
            SDL_PollEvent(&event);
            // Quit the program
            if(event.key.keysym.sym == SDLK_q){
                cout << "You exited the program" << endl;
                return 0;
            }
            // Pause the program
            else if(event.key.keysym.sym == SDLK_k){
                if(print_count == 0){
                    cout << "The program has been paused" << endl;
                    print_count++;
                }
                pause = false;
                continue;
            }
            // Resume the program
            else if(event.key.keysym.sym == SDLK_r){
                if(print_count == 1){
                    cout << "The program has resumed" << endl;
                    cout << "The program is running" << endl;
                    print_count = 0;
                }
                pause = true;
            }
            // Restart the program
            // After restarting, press r key once
            else if(event.key.keysym.sym == SDLK_SPACE){
                restart();
                count = 1;
                pause = true;
                print_count = 0;
            }
            //cout << count << " " << restart_count << endl;
            if(pause){
            if(count >= 1 && count < 5){
                right();
            }
            else if(count >= 5 && count < 16){
                zoom_in();
            }
            else if(count >= 16 && count < 18){
                left();
            }
            else if(count >= 18 && count < 23){
                zoom_in();
            }
            else if(count >= 23 && count < 27){
                left();
            }
            else if(count >= 27 && count < 61){
                zoom_in();
            }
            else if(count >= 61 && count < 66){
                right();
            }
            else if(count >= 66 && count < 69){
                up();
            }
            else if(count >= 69 && count < 207){
                zoom_in();
            }
            else if(count >= 207 && count < 217){
                up();
            }
            else if(count >= 217 && count < 222){
                zoom_in();
            }
            else if(count >= 222 && count < 228){
                left();
            }
            else if(count >= 228 && count < 267){
                zoom_in();
            }
            else if(count >= 267 && count < 270){
                up();
            }
            else if(count >= 270 && count < 301){
                zoom_in();
            }
            else if(count >= 301 && count < 323){
                up();
            }
            else if(count >= 323 && count < 367){
                zoom_in();
            }
            else if(count >= 367 && count < 373){
                up();
            }
            else if(count >= 373 && count < 377){
                left();
            }
            else if(count >= 377 && count < 430){
                zoom_in();
            }
            else if(count >= 430 && count < 449){
                up();
            }
            else if(count >= 449 && count < 453){
                zoom_in();
            }
            else if(count >= 453 && count < 460){
                down();
            }
            else if(count >= 460 && count < 503){
                zoom_in();
            }
            else if(count >= 503 && count < 505){
                left();
            }
            else if(count >= 505 && count < 510){
                up();
            }
            else if(count == 510){
                right();
            }
            else if(count == 511){
                up();
            }
            else if(count >= 512 && count < 514){
                right();
            }
            else if(count >= 514 && count < 525){
                left();
            }
            else if(count >= 525 && count < 545){
                zoom_in();
            }
            else if(count >= 545 && count < 551){
                up();
            }
            else if(count >= 551 && count < 618){
                zoom_in();
            }
            else if(count >= 618 && count < 622){
                up();
            }
            else if(count >= 622 && count < 641){
                zoom_in();
            }
            else if(count >= 641){
                q = manual;
            }
            }
        }

        // clock_t t;
        // t = clock();

        // Draw the Mandelbrot Set
        SDL_RenderPresent(renderer);   
        // Iterate over all the pixels
        for(int x=0; x<WIDTH; x++){
            for(int y=0; y<HEIGHT; y++){
                // a tracks the x-coordinate of pixel
                // b tracks the y-coordinate of pixel
                long double a = map(x, 0, WIDTH, minimum_x, maximum_x); // Bring the x-coordinate of pixel into the range (-2,2)
                long double b = map(y, 0, HEIGHT, minimum_y, maximum_y); // Bring the y-coordinate of pixel into the range (-2,2)
                long double ai = a; // Initial real part of C
                long double bi = b; // Initial complex part of C

                int n=0; // Counts no. of iterations before Z blows up
                // Checking the iteration at which Z blows up i.e Mandelbrot sequence diverges to infinity
                // We will check only 200 iterations for computational purposes
                for(int i=0; i<MAX_ITERATIONS; i++){
                    long double a1 = a*a - b*b; // X-coordinate of Z^2
                    long double b1 = 2*a*b; // Y-coordinate of Z^2
                    a = a1 + ai; // New X-coordinate
                    b = b1 + bi; // New Y-coordinate
                    // Check whether the given pixel value blows up or not
                    if(a*a+b*b>4.0){ 
                        break;
                    }
                    n++;
                }
                
                // Setting color of the pixel using the given color palette
                // Option 1 : Modern Color Scheme
                // More favourable for Mandelbrot Zoom
                if(colour.compare(modern)==0){
                    int it = n % 16;
                    red = color[it][0];
                    green = color[it][1];
                    blue = color[it][2];
                }
                // Option 2 : Traditional Color Scheme
                // More favourable for visualising Mandelbrot Set 
                else{
                    int bright = map(n, 0, MAX_ITERATIONS, 0, 255);
                    if((n == MAX_ITERATIONS) || (bright < 20)){
                        bright = 0;
                    }
                    // Traditional Blue Color Scheme
                    if(color_type.compare(Blue)==0){
                        red = map(bright*bright, 0, 255*255, 0, 255);
                        green = bright;
                        blue = map(sqrt(bright), 0, sqrt(255), 0, 255);
                    }
                    // Traditional Purple Color Scheme
                    else if(color_type.compare(Purple)==0){
                        green = map(bright*bright, 0, 255*255, 0, 255);
                        red = bright;
                        blue = map(sqrt(bright), 0, sqrt(255), 0, 255);
                    }
                    // Traditional Pink Color Scheme
                    else if(color_type.compare(Pink)==0){
                        green = map(bright*bright, 0, 255*255, 0, 255);
                        blue = bright;
                        red = map(sqrt(bright), 0, sqrt(255), 0, 255);
                    }
                    // Traditional Orange Color Scheme
                    else if(color_type.compare(Orange)==0){
                        blue = map(bright*bright, 0, 255*255, 0, 255);
                        green = bright;
                        red = map(sqrt(bright), 0, sqrt(255), 0, 255);
                    }
                    // Traditional Green Color Scheme
                    else{
                        red = map(bright*bright, 0, 255*255, 0, 255);
                        blue = bright;
                        green = map(sqrt(bright), 0, sqrt(255), 0, 255);
                    }
                }

                // Color each point
                SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
        //t = clock() - t;
        //double time = ((double)t)/CLOCKS_PER_SEC;
        //cout << time << endl;
        if(pause){
            count++;
        }
    }
    return 0;
}