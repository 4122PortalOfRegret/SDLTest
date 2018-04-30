#include "block.h"
#include "player.h"
#include "portal.h"
#include "EndZoneWall.h"
#include "utils.h"
using namespace std;

// globals
auto frameStart = sc::high_resolution_clock::now();
auto frameEnd = sc::high_resolution_clock::now();

STATE jump = READY;
bool canJump = false;
bool ground = true;

int level = 1;
bool loadLevel = true;

void level1(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {400,660,50,50};
    SDL_Rect wall6 = {450,610,50,100};
    Block hellowall(400,660,50,50,renderer, wall5, true);
    Block hellowall2(450,610,50,100,renderer, wall6, true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
    blockVec.push_back(hellowall);
    blockVec.push_back(hellowall2);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(710-CHAR_HEIGHT);
    p.setX(20);
    p.setY(640);

    end.draw();
}

void level2(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {10,540,100,170};
    SDL_Rect wall6 = {110,590,100,12};
    SDL_Rect wall7 = {210,640,100,70};
    SDL_Rect wall8 = {310,690,200,20};
    SDL_Rect wall9 = {510,310,100,400};
    SDL_Rect wall10 = {710,10,560,300};
    Block stair1(10,540,100,170,renderer, wall5, true);
    Block stair2(110,590,100,120,renderer, wall6, true);
    Block stair3(210,640,100,70,renderer, wall7, true);
    Block floor1(310,690,200,20,renderer, wall8, false);
    Block bigwall(510,310,100,400,renderer, wall9, true);
    Block topright(710,10,560,300,renderer, wall10, false); 

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);

    blockVec.push_back(stair1);
    blockVec.push_back(stair2);
    blockVec.push_back(stair3);
    blockVec.push_back(floor1);
    blockVec.push_back(bigwall);
    blockVec.push_back(topright);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(710-CHAR_HEIGHT);
    p.setX(240);
    p.setY(500);

    end.draw();
}

void level3(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {10,10,750,200};
    SDL_Rect wall6 = {760,10,20,200};
    SDL_Rect wall7 = {10,660,1000,50};
    SDL_Rect wall8 = {1010,210,260,500};
    Block topleft(10,10,750,200,renderer,wall5,true);
    Block ledge(760,10,20,200,renderer,wall6,false);
    Block floorWall(10,660,1000,50,renderer,wall7,false);
    Block right(1010,210,260,500,renderer,wall8,true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);

    blockVec.push_back(topleft);
    blockVec.push_back(ledge);
    blockVec.push_back(floorWall);
    blockVec.push_back(right);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(210-CHAR_HEIGHT);
    p.setX(20);
    p.setY(600);

    end.draw();
}

void level4(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {10,10,800,20};
    SDL_Rect wall6 = {10,710,1000,200};
    SDL_Rect wall7 = {1010,210,260,500};
    Block topGray(10,10,800,20,renderer,wall5,false);
    Block bottomGray(10,710,1000,200,renderer,wall6,false);
    Block right(1010,210,260,500,renderer,wall7,true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);

    blockVec.push_back(topGray);
    blockVec.push_back(bottomGray);
    blockVec.push_back(right);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(210-CHAR_HEIGHT);
    p.setX(20);
    p.setY(600);

    end.draw();
}   

int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        cout << "Something went wrong! " << SDL_GetError() << endl;
    }
    
    SDL_Window* window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(window == NULL){
        cout << "Something also went wrong here" << endl;
    }
    int pastPress[] = {0,0,0,0};
    int jumpframes = 0;
    bool quit = false;
    SDL_Event event;
    int x = 288;
    int y = 208;
    const int FPS = 60;
    int frameTime;
    
    SDL_Renderer* renderer;
    SDL_Event events;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // player
    SDL_Surface * image = SDL_LoadBMP("lols.bmp");
    SDL_Texture * currentimage = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect playerRect = {600, 100, CHAR_WIDTH, CHAR_HEIGHT};
    // player texture
    SDL_Rect animationRect;
    int framewidth, frameheight;
    int texturewidth, textureheight;
    SDL_QueryTexture(currentimage,NULL,NULL,&texturewidth,&textureheight);
    framewidth = texturewidth/4 ;
    frameheight = textureheight/4;
    animationRect.x = animationRect.y = 0;
    animationRect.w = framewidth;
    animationRect.h = frameheight;
    Player player(600, 100, CHAR_WIDTH, CHAR_HEIGHT, renderer, playerRect, currentimage);
    // player.draw(&animationRect);

    // end zone wall
    SDL_Rect endBlock = {0,0,CHAR_WIDTH/2,CHAR_HEIGHT};
    EndZoneWall endWall(0,0,CHAR_WIDTH/2,CHAR_HEIGHT, renderer, endBlock);

    // portals

    // block vector
    vector<Block> blockVector;

    // call the level function
    level1(renderer, blockVector, endWall, player);
    loadLevel = false;
    player.draw(&animationRect);
    

    long int delayTime;
    clock_t start; clock_t end;
    
    // // test Block
    // SDL_Rect platform = {200,670,400,50};
    // Block block(200, 670, 400, 50, renderer, platform, false);
    // //block.draw();
    // vector<Block> vec;
    // vec.push_back(block);
    // SDL_Rect plat = {600, 620, 300, 100};
    // Block block2(600, 620, 300, 100, renderer, plat, true);
    // vec.push_back(block2);
    // //SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
    // //SDL_RenderFillRect(renderer, &platform);
    
    SDL_RenderPresent(renderer);
    
    while(!quit){
        // level handling
        if (loadLevel == true) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);        
            SDL_RenderClear(renderer);
            blockVector.clear();
            switch(level) {
                case 1:
                    level1(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 2:
                    level2(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 3:
                    level3(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 4:
                    level4(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                default: 
                    level1(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
            }
        }

        frameStart = sc::high_resolution_clock::now();
        SDL_PollEvent(&events);
        if(events.type == SDL_QUIT) {
            quit = true;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);        
        SDL_RenderClear(renderer);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        // use the arrow keys to control the player
        if(state[SDL_SCANCODE_R]) {
            loadLevel = true;
        }
        // if(state[SDL_SCANCODE_LEFT]) {
        //     level--;
        //     loadLevel = true;
        //     if (level < 1)
        //         level = 1;
        // }
        // if(state[SDL_SCANCODE_RIGHT]) {
        //     level++;
        //     loadLevel = true;
        //     if (level > 4)
        //         level = 4;
        // }
        player.setXSpeed(0);
        if(state[SDL_SCANCODE_A]) {
            player.changeXSpeed(-5);
        }
        if(state[SDL_SCANCODE_D]) {
            player.changeXSpeed(5);
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
                player.setYSpeed(-12);
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
                player.changeYSpeed(3);
                if (player.getYSpeed() >= 0){
                    player.setYSpeed(0);
                    jump = DESCEND;
                }
                break;
            case DESCEND     :
                player.changeYSpeed(5);
                if (player.getYSpeed() == GRAVITY) {
                    jump = FREEFALL;
                    start = clock();
                }
                break;
            case FREEFALL    :
                jumpframes = 0;
                player.setYSpeed(GRAVITY);
                if (canJump && ground) {
                    jump = READY;
                }
                break;
            case READY      :
                jumpframes = 0;
                player.setYSpeed(GRAVITY);
                break;
        }

        // move the player to the new position based on current momentum
        // check if the player collides with its environment
        player.updateX(blockVector);
        player.updateY(blockVector, &ground, jump);

        // check if player collides with exit
        if (SDL_HasIntersection(player.getRectangle(), endWall.getRectangle())) {
            loadLevel = true;
            level++;
            if (level > 4)
                level = 4;
        }

        // check it player collides with portal
        
        // update animation if necessary
        ++frameTime;
        if (player.getXSpeed() == 0)
        {
            if (FPS/frameTime == 4)
            {   
                animationRect.y = 0;
                animationRect.x +=framewidth;
                if(animationRect.x >= texturewidth)
                    animationRect.x = 0;
                frameTime = 0;
            }
        }
        else if(state[SDL_SCANCODE_A])
        {
            if (FPS/frameTime == 4){
            animationRect.y = frameheight;
            animationRect.x +=framewidth;
            if(animationRect.x >= texturewidth)
                animationRect.x = 0;
            frameTime = 0;
            }
        }
        else if (state[SDL_SCANCODE_D])
        {
            if (FPS/frameTime == 4){
                animationRect.y = frameheight*2;
                animationRect.x +=framewidth;
                if(animationRect.x >= texturewidth)
                    animationRect.x = 0;
                frameTime = 0;
            }
        }

        // draw the player and its animation
        player.draw(&animationRect);

        // draw the blocks for the level
        vector<Block>::iterator it;
        for (it = blockVector.begin(); it != blockVector.end(); it++) {
            (*it).draw();
        }

        // draw the end zone
        endWall.draw();

        // switch buffer to display
        SDL_RenderPresent(renderer);
        
        frameEnd = sc::high_resolution_clock::now();
        delayTime = 16 - sc::duration_cast<sc::milliseconds>(frameEnd-frameStart).count(); 
        if(delayTime > 0) {
            SDL_Delay(delayTime);
        }
    }
    // vector<Block*>::iterator it;
    // for (it = vec.begin(); it < vec.end(); it++) {
    //     delete *it;
    // }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;

}
