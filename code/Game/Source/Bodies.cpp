#include"Bodies.h"
#include"defs.h"
#include<math.h>
#include<iostream>

Bodies::Bodies(double u, double v, double w, double h,int type,SDL_Renderer* renderer ): x(u),y(v),wid(w),hei(h), type(type) {
    r = 0;
    g = 0;
    b = 0;
    o = 255;
    vel_x=0;
    vel_y = 0;
    
    if(type==0){
        image = SDL_LoadBMP("images/gun.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
    }
    else if(type==1){
        image = SDL_LoadBMP("images/bullet.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
    }
    else if(type==3){
        image = SDL_LoadBMP("images/1.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
        health = 1;
    }
    else if(type==4){
        image = SDL_LoadBMP("images/2.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
        health = 2;
    }
    else if(type==5){
        image = SDL_LoadBMP("images/5.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
        health = 3;
    }
    else if(type==6){
        image = SDL_LoadBMP("images/10.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
        health = 4;
    }
    else if(type==7){
        image = SDL_LoadBMP("images/50.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
        health = 6;
    }
    else if(type==8){
        image = SDL_LoadBMP("images/99.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
        health = 8;
    }
    else{
        image = SDL_LoadBMP("images/main_screen.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
    }
    
}

Bodies::~Bodies(){
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}

void Bodies::SetColour(int ri, int gi, int bi){
    r = ri;
    g = gi;
    b = bi;
}

void Bodies::SetVel(double ux, double uy){
    vel_x = ux;
    vel_y = uy;
}


bool Bodies::check_col(Bodies* B){
    if(((x>=B->x && x<=(B->x+B->wid)) || (B->x>=x && B->x<=(x+wid))) && ((y>=B->y && y<=(B->y+B->hei)) || (B->y>=y && B->y<=(y+hei)))) return true;
    return false;  
}

void Bodies::check_col2(Bodies* B){
    if(!(y + hei <= B->y || y >= B->y + B->hei || x + wid <= B->x  || x >= B->x + B->wid)){
        int temp1 = vel_x;
        int temp2 = vel_y;
        int temp3 = B->vel_x;
        int temp4 = B->vel_y;
        SetVel(temp3,temp4);
        B->SetVel(temp1,temp2);
    }
}

void Bodies::display(SDL_Renderer* renderer){
    SDL_Rect fillRect = {x ,y ,wid,hei};
    SDL_RenderCopy(renderer,texture,NULL,&fillRect); 
}

void Bodies::move(){
    if(!(x+vel_x<0 || x+vel_x+wid>WIDTH)) x+=vel_x;
    if(!(y+vel_y<0 || y+vel_y+hei>HEIGHT)) y+=vel_y;
}

void Bodies::moveObs(){
    if(!(x+vel_x<0 || x+vel_x+wid>WIDTH)) x += vel_x;
    else SetVel(-vel_x,vel_y);
    if(!(y+vel_y<0 || y+vel_y+hei>HEIGHT)) y += vel_y;
    else SetVel(vel_x,-vel_y);
}