#include <iostream>
#include "SDL.h"
#include "object.h"
#include <ctime>
#include <chrono>
using namespace std;
namespace sc = std::chrono;
// constants
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int GRAVITY = 10;
const int CHAR_WIDTH = 64;
const int CHAR_HEIGHT = 64;
const int FRAMES_PER_SEC = 20;
// globals
enum STATE {BUTTON_PRESS, DECELERATE, DESCEND, FREEFALL, READY1, BUTTON_PRESS2, DECELERATE2, DESCEND2, FREEFALL2, READY};
STATE jump = READY;
bool canJump = false;
bool ground = true;
auto frameStart = sc::high_resolution_clock::now();
auto frameEnd = sc::high_resolution_clock::now();
#define KEY_W 0
#define KEY_A 1
#define KEY_D 2
#define KEY_S 3

// void update(int* xLoc, int* yLoc, int xSpeed, int ySpeed){
//     if ( left1 > right2 || right1 < left2 || top1 > bottom2 || bottom1 < top2)
//     {
//     if (xSpeed == 0 && ySpeed == 0)
//         return;
//     *xLoc = *xLoc + xSpeed;
//     if (*xLoc < 0)
//         *xLoc = 0;
//     if (*xLoc > WINDOW_WIDTH - CHAR_WIDTH)
//         *xLoc = WINDOW_WIDTH - CHAR_WIDTH;
//     *yLoc = *yLoc + ySpeed;
//     if (*yLoc < 0)
//         *yLoc = 0;
//     if (*yLoc > WINDOW_HEIGHT - CHAR_HEIGHT) {
//         *yLoc = WINDOW_HEIGHT - CHAR_HEIGHT;
//         ground = true;
//     }
//     }
// }

void updatex(const SDL_Rect &rect1, const SDL_Rect &rect2,int* xLoc, int* yLoc, int xSpeed, int ySpeed,STATE* lols,bool* prevPlat){
    if (xSpeed == 0)
        return;
    *xLoc = *xLoc + xSpeed;

    if (*xLoc < 0)
        *xLoc = 0;
    if (*xLoc > WINDOW_WIDTH - CHAR_WIDTH)
        *xLoc = WINDOW_WIDTH - CHAR_WIDTH;

    int left1 = rect1.x;                    // playerx
    int right1 = rect1.x + rect1.w;         // playerx+width
    int top1 = rect1.y;                     // playerY
    int bottom1 = rect1.y + rect1.h;        // playerY+height

    // Find edges of rect2
    int left2 = rect2.x;                    // blockX
    int right2 = rect2.x + rect2.w;         // blockX+width
    int top2 = rect2.y;                     // blockY          
    int bottom2 = rect2.y + rect2.h;        // blocky+height


    int oldleft1 = rect1.x - xSpeed;
    int oldright1 = rect1.x + rect1.w - xSpeed;


    if ( left1 > right2 || right1 < left2 || top1 > bottom2 || bottom1 < top2 )// Left 1 is right of right 2
        return; // No collision


    if (oldleft1 < left2 && oldright1 < left2 && (((top1 < top2) || (bottom1 < top1))  || ((top1 < bottom2) || bottom1 < bottom2)))        // left
    {
        *xLoc = *xLoc - xSpeed - 0;
    }

    if (oldleft1 > right2 && oldright1 > right2 && (((top1 < top2) || (bottom1 < top1))  || ((top1 < bottom2) || (bottom1 < bottom2))))  // right
    {
        *xLoc = *xLoc - xSpeed + 0; 
    }

    return;
    
    


}

void updatey(const SDL_Rect &rect1, const SDL_Rect &rect2,int* xLoc, int* yLoc, int xSpeed, int ySpeed,STATE* lols,bool* prevPlat)
    {
    if (ySpeed == 0)
        return;

    *yLoc = *yLoc + ySpeed;
    if (*yLoc < 0)
        *yLoc = 0;
    if (*yLoc > WINDOW_HEIGHT - CHAR_HEIGHT) {
        *yLoc = WINDOW_HEIGHT - CHAR_HEIGHT;
        ground = true;
    }
    
    int left1 = rect1.x;                    // playerx
    int right1 = rect1.x + rect1.w;         // playerx+width
    int top1 = rect1.y;                     // playerY
    int bottom1 = rect1.y + rect1.h;        // playerY+height

    // Find edges of rect2
    int left2 = rect2.x;                    // blockX
    int right2 = rect2.x + rect2.w;         // blockX+width
    int top2 = rect2.y;                     // blockY          
    int bottom2 = rect2.y + rect2.h;        // blocky+height

    int oldtop1 = rect1.y - ySpeed;
    int oldbottom1 = rect1.y + rect1.h - ySpeed;


    if ( left1 > right2 || right1 < left2  || top1 > bottom2 || bottom1 < top2){
        return; // No collision
    }


    if (oldtop1 < top2 && top2 < oldbottom1 && oldbottom1 < bottom2)                // top   
    {
        *yLoc = *yLoc - ySpeed  - 0;
        ground = true;
        *lols = READY;
        *prevPlat = true;
    }            
        // need to change state to free fall

    if  ((top2 < oldtop1 && oldtop1 < bottom2 && bottom2 < oldbottom1))             // bot
    {
        *yLoc = *yLoc - ySpeed + 20;
        if (*lols == BUTTON_PRESS || *lols == DECELERATE || *lols == DESCEND)
            *lols = FREEFALL;

        if (*lols == BUTTON_PRESS2 || *lols == DECELERATE2 || *lols == DESCEND2)
            *lols = FREEFALL2;
    }
    return;
    

}










int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        cout << "Something went wrong! " << SDL_GetError() << endl;
    }

    SDL_Window* window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(window == NULL){
        cout << "Something also went wrong here" << endl;
    }
    bool pastPlat = false;
    int pastPress[] = {0,0,0,0};
    int jumpframes = 0;
    bool quit = false;
    SDL_Event event;
    int x = 288;
    int y = 208;    
    
    SDL_Renderer* renderer;
    SDL_Renderer* wRender;
    SDL_Event events;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect myRect = {600, 100, CHAR_WIDTH, CHAR_HEIGHT};
    int xSpeed = 0; int ySpeed = 0;
    long int delayTime;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &myRect);
    SDL_RenderPresent(renderer);

    clock_t start; clock_t end;

    SDL_Rect platform = {200,670,400,50};
    SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
    SDL_RenderFillRect(renderer, &platform);
    SDL_RenderPresent(renderer);


    while(!quit){
    frameStart = sc::high_resolution_clock::now();
        SDL_PollEvent(&events);
        if(events.type == SDL_QUIT) {
            quit = true;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderFillRect(renderer, &myRect);

        SDL_RenderClear(renderer);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        

        xSpeed = 0;
       // if (event.type == SDL_KEYDOWN) {

//            xSpeed = 0; 
            //ySpeed = -GRAVITY;
            // x direction
            if(state[SDL_SCANCODE_A]) {
                xSpeed -= 5;;
            }
            if(state[SDL_SCANCODE_D]) {
                xSpeed += 5;
            }
            // y direction
            if(state[SDL_SCANCODE_W])
            {
                ++pastPress[KEY_W];
                if(pastPress[KEY_W] == 1)
                {
                  canJump = true;
                }
                if (jump == READY) {
                    start = clock();
                    jump = BUTTON_PRESS;
                    //ySpeed += 10;
                }
                if (jump == READY1){
                    start = clock();
                    jump = BUTTON_PRESS2;
                }
            }
        else {
        pastPress[KEY_W] = 0;
        canJump = true;
        }
            // escape
            if(state[SDL_SCANCODE_ESCAPE]) {
                quit = true;
            }
       // } else if (event.type == SDL_KEYUP) {
            if(!state[SDL_SCANCODE_W]) {
                canJump = true;
            }
       // 
        switch(jump) {
            case BUTTON_PRESS:
//                if (canJump) {
            canJump = false;
            ySpeed = -12;
                    end = clock();
            if (jumpframes > 6)
            {
                jumpframes = 0;
                jump = DECELERATE;
            }
            ++jumpframes;
            ground = false;
            break;
            case DECELERATE  :
            ySpeed += 3;
            if (ySpeed >= 0){
                ySpeed = 0;
                jump = DESCEND;
            }
                break;
            case DESCEND     :
                ySpeed += 5;
                if (ySpeed == GRAVITY) {
                    jump = FREEFALL;
                    start = clock();
                }
                break;
            case FREEFALL    :
                jumpframes = 0;
                ySpeed = GRAVITY;
                if (canJump) {
                    if (canJump) {
                        jump = READY1;
                    }
                }
                break;
            case READY1      :
                jumpframes = 0;
                ySpeed = GRAVITY;
                break;
            case BUTTON_PRESS2:
//                if (canJump) {
            canJump = false;
            ySpeed = -12;
                    end = clock();
            if (jumpframes > 6)
            {
                jumpframes = 0;
                jump = DECELERATE2;
            }
            ++jumpframes;
            ground = false;
            break;
            case DECELERATE2:
            ySpeed += 3;
            if (ySpeed >= 0){
                ySpeed = 0;
                jump = DESCEND2;
            }
            case DESCEND2   :
                ySpeed += 5;
                if (ySpeed == GRAVITY) {
                    jump = FREEFALL2;
                    start = clock();
                }
                break;
            case FREEFALL2    :
                jumpframes = 0;
                ySpeed = GRAVITY;
                if (canJump && ground) {
                    if (canJump) {
                        jump = READY;
                    }
                }
                break;
            case READY      :
                ySpeed = GRAVITY;
                break;
        }


        // are there collisions?
        //CheckCollision(myRect,platform,&myRect.x,&myRect.y,xSpeed,ySpeed);


        // update location based on button press
        updatex(myRect,platform,&myRect.x, &myRect.y, xSpeed, ySpeed,&jump,&pastPlat);
        updatey(myRect,platform,&myRect.x, &myRect.y, xSpeed, ySpeed,&jump,&pastPlat);



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &myRect);

        SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
        SDL_RenderFillRect(renderer, &platform);
        SDL_RenderPresent(renderer);
    frameEnd = sc::high_resolution_clock::now();
    delayTime = 16 - sc::duration_cast<sc::milliseconds>(frameEnd-frameStart).count(); 
    if(delayTime > 0) {
        SDL_Delay(delayTime);
    }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}