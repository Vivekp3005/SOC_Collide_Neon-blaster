#include"Bodies.h"
#include<vector>
#include"SDL.h"

#define RESET_TIME 200

class Game{
    public:
    Game(SDL_Renderer* renderer);
    void initialize();
    void generateBullet();
    void generateObs();
    void key_down(SDL_KeyboardEvent* event );
    void key_up(SDL_KeyboardEvent* event );
    void move();
    void render(SDL_Renderer* renderer);
    std::vector<Bodies*> listOfBodies;
    std::vector<Bodies*> listOfBullets;
    std::vector<int> angles;
    bool running;
    Bodies* screen;

    private:
    SDL_Renderer* renderer;
    double timer = 0;
};