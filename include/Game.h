#pragma once
#include "SDL3/SDL.h"
#include <iostream>

#define WHITE 255,255,255,255
#define Purple 100,0,175,255

struct Vector2
{
    float x;
    float y;
};

struct Paddle
{
    Vector2 pos;
    int paddleDir;
};

class Game
{
public:
    Game();

    bool Init();
    void RunLoop();
    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    float CalculateDeltaTime();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    int wWidth = 1080;
    int wHeight = 720;
    std::string wTitle = "SDL3 Window";
    const int thickness = 15;
    const int pHeight = 105;
    float paddleSpeed = 500.0f;
//    Vector2 paddlePos;
    Vector2 ballPos;
    Vector2 bVelocity;
    Uint32 tickCount;
    float deltatime;
    // 0 if not moving, -1 up, 1 down
//    int paddleDir;
    Paddle lPaddle;
    Paddle rPaddle;

};