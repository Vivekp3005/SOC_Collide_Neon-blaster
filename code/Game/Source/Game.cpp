#include"Game.h"
#include"Bodies.h"
#include"defs.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

Game::Game(SDL_Renderer* rendereer){
    running = true;
    timer= 0;
    renderer = rendereer;
    SDL_Texture * text;
    SDL_Surface * imag;
    imag = SDL_LoadBMP("images/neon-blaster-2.bmp"); 	
    text = SDL_CreateTextureFromSurface(renderer, imag);
    SDL_Rect fillRect = {0 ,0 ,WIDTH,HEIGHT};
    SDL_RenderCopy(renderer,text,NULL,&fillRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_DestroyTexture(text);
    SDL_FreeSurface(imag);
    initialize();
}

void Game::initialize(){
    //Clear the list of bodies
    listOfBodies.clear();
    listOfBullets.clear();
    angles.clear();

    //Add player
    Bodies* B = new Bodies(WIDTH/2 - 37.5,HEIGHT-75,75,75,0,renderer);
    listOfBodies.push_back(B);

    //Add Screen
    Bodies* B1 = new Bodies(0,0,WIDTH,HEIGHT,2,renderer);
    screen = B1;
}

void Game::generateBullet(){
    // Add bullets
    Bodies* B = listOfBodies[0];
    Bodies* bul1 = new Bodies(B->x+30.5,B->y,8,8,1,renderer);
    listOfBullets.push_back(bul1);
    bul1->SetVel(0,-4);

    Bodies* bul2 = new Bodies(B->x+42.5,B->y,8,8,1,renderer);
    listOfBullets.push_back(bul2);
    bul2->SetVel(0,-4);
}

void Game::generateObs(){
    //Add obstacle
    if(listOfBodies.size()==1){
        int side = rand()%2;
        if(side == 0){
            int t = rand()%6;
            int h = rand()%(HEIGHT/2);
            Bodies* obs1 = new Bodies(5,h+5,75,75,t+3,renderer);
            int angle = rand()%45;
            obs1->SetVel(3.5*cos(angle*1.57/180),3.5*sin((angle+45)*1.57/180));
            listOfBodies.push_back(obs1);
        }
        else{
            int t = rand()%6;
            int h = rand()%(HEIGHT/2);
            Bodies* obs1 = new Bodies(WIDTH-75,h+5,75,75,t+3,renderer);
            int angle = rand()%45;
            obs1->SetVel(-3.5*cos(angle*1.57/180),3.5*sin((angle+45)*1.57/180));
            listOfBodies.push_back(obs1);
        }
     
        int side2 = rand()%2;
        if(side2 == 0){
            int t2 = rand()%6;
            int h2 = rand()%(HEIGHT/2);
            Bodies* obs2 = new Bodies(5,h2+5,75,75,t2+3,renderer);
            int angle2 = rand()%45;
            obs2->SetVel(3.5*cos((angle2*1.57/180)),3.5*sin((angle2+45)*1.57/180));
            listOfBodies.push_back(obs2);
        }
        else{
            int t2 = rand()%6;
            int h2 = rand()%(HEIGHT/2);
            Bodies* obs2 = new Bodies(WIDTH-75,h2+5,75,75,t2+3,renderer);
            int angle2 = rand()%45;
            obs2->SetVel(-3.5*cos((angle2*1.57/180)),3.5*sin((angle2+45)*1.57/180));
            listOfBodies.push_back(obs2);
        }
        
    }
    else if(listOfBodies.size()==2){
        int side = rand()%2;
        if(side == 0){
            int t2 = rand()%6;
            int h2 = rand()%(HEIGHT/2);
            Bodies* obs2 = new Bodies(5,h2+5,75,75,t2+3,renderer);
            int angle2 = rand()%45;
            obs2->SetVel(3.5*cos((angle2*1.57/180)),3.5*sin((angle2+45)*1.57/180));
            listOfBodies.push_back(obs2);
        }
        else{
            int t2 = rand()%6;
            int h2 = rand()%(HEIGHT/2);
            Bodies* obs2 = new Bodies(WIDTH-75,h2+5,75,75,t2+3,renderer);
            int angle2 = rand()%45;
            obs2->SetVel(-3.5*cos((angle2*1.57/180)),3.5*sin((angle2+45)*1.57/180));
            listOfBodies.push_back(obs2);
        }
    }
}

void Game::key_down(SDL_KeyboardEvent* event ){

    if(event->repeat==0){
        // Press any key to restart game
        if(!running){ 
            running = true;
            initialize();
        }
        switch (event->keysym.scancode){
            case SDL_SCANCODE_SPACE:
                generateBullet();
                break;

            case SDL_SCANCODE_LEFT:
                listOfBodies[0]->vel_x-=5;
                break;

            case SDL_SCANCODE_RIGHT:
                listOfBodies[0]->vel_x+=5;   
                break;
            default:
                break;
        }
    }
}


void Game::key_up(SDL_KeyboardEvent* event ){
    if(event->repeat==0){
        switch (event->keysym.scancode){
            case SDL_SCANCODE_LEFT:
                listOfBodies[0]->vel_x+=5;
                break;
            case SDL_SCANCODE_RIGHT:
                listOfBodies[0]->vel_x-=5;   
                break;
            default:
                break;
        }
    }
}


void Game::move(){
    if(running){    
        //move the bodies
        listOfBodies[0]->move();
        for(int i=1; i<listOfBodies.size();i++){
            listOfBodies[i]->moveObs();
        }

        for(int i=0; i<listOfBullets.size();i++){
            Bodies* temp = listOfBullets[i];
            if(!(temp->x + temp->vel_x<0 || temp->x + temp->vel_x + temp->wid > WIDTH)) temp->x += temp->vel_x;
            else listOfBullets.erase(listOfBullets.begin()+i,listOfBullets.begin()+i+1),i--;
            if(!(temp->y + temp->vel_y < 0 || temp->y + temp->vel_y + temp->hei > HEIGHT)) temp->y += temp->vel_y;
            else listOfBullets.erase(listOfBullets.begin()+i,listOfBullets.begin()+i+1),i--;
        }

        //check for final collision
        for(int i=1; i<listOfBodies.size();i++){
            if(listOfBodies[0]->check_col(listOfBodies[i]))
            {
                running = false;
                break;
            }
        }

        //check for bullet object collision
        for(int i=0;i<listOfBullets.size();i++){
            bool check = false;
            for(int j=1;j<listOfBodies.size();j++){
                if(listOfBullets[i]->check_col(listOfBodies[j])){
                    check = true;
                    if(listOfBodies[j]->health - 1 == 0){
                        listOfBodies.erase(listOfBodies.begin()+j);
                        listOfBullets.erase(listOfBullets.begin()+i);
                        j--;
                    }
                    else{
                        listOfBullets.erase(listOfBullets.begin()+i);
                        listOfBodies[j]->health--;
                    }
                }
            }
            (check)?i--:i += 0;
        }

        //check for object object collision
        for(int i=1;i<listOfBodies.size();i++){
            for(int j=i+1;j<listOfBodies.size();j++){
                listOfBodies[i]->check_col2(listOfBodies[j]);
            }
        }
        timer++;
    }
}

//render
void Game::render(SDL_Renderer* renderer){
    if(running){
        screen->display(renderer);
        for(int i=0; i<listOfBodies.size();i++){
            listOfBodies[i]->display(renderer);
        }
        for(int i=0; i<listOfBullets.size();i++){
            listOfBullets[i]->display(renderer);
        }
    }
}