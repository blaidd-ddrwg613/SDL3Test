#pragma once
#include "SDL3/SDL.h"
#include <iostream>

struct Vec2
{
    float x, y;
};

class Game
{
public:
    int wWidth = 1080;
    int wHeight = 720;
    std::string wTitle = "SDL Window";
    SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    Game();
    bool Init();
    void RunLoop();
    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void CalculateCollision();
    float CalculateDeltaTime();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    float thickness;
    Vec2 paddlePos;
    Vec2 ballPos;
    Uint32 ticksCount;
    int paddleDir;
    float paddleSpeed;
    float paddleHeight;
    Vec2 ballVelocity;

};
