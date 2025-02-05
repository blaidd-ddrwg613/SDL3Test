#include <SDL3/SDL_rect.h>
#include "Game.h"

Game::Game()
{
    isRunning = true;
    window = nullptr;
    renderer = nullptr;

    thickness = 15.0f;
    ballPos = {(float)wWidth / 2, (float)wHeight / 2};
    paddlePos = {10, (float)wHeight / 2};
    ticksCount = 0;
    paddleDir = 0;
    paddleSpeed = 500.0f;
    paddleHeight = 100;
    ballVelocity = {-200.0f, 235.0f};

}

bool Game::Init()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (!sdlResult)
    {
        SDL_Log("Failed to Init SDL: %s", SDL_GetError());
        return false;
    }
    SDL_CreateWindowAndRenderer(wTitle.c_str(), wWidth, wHeight, flags, &window, &renderer);
    if (!window || !renderer)
    {
        SDL_Log("Failed to create SDL window or Renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::RunLoop()
{
    while (isRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Handle Events
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
            isRunning = false;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                SDL_GetWindowSize(window, &wWidth, &wHeight);
                break;
        }
    }

    const bool* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
    }

    paddleDir = 0;
    if (state[SDL_SCANCODE_W])
    {
        paddleDir = -1;
    }
    if (state[SDL_SCANCODE_S])
    {
        paddleDir = 1;
    }
}

void Game::UpdateGame()
{
    float deltaTime = CalculateDeltaTime();

    ballPos.x += ballVelocity.x * deltaTime;
    ballPos.y += ballVelocity.y * deltaTime;

    CalculateCollision();

    // Paddle Movement
    if (paddleDir != 0)
    {
        paddlePos.y += paddleDir * paddleSpeed * deltaTime;
        // Clamp the paddles pos to the screen area
        if (paddlePos.y < (paddleHeight/2.0f + thickness))
        {
            paddlePos.y = paddleHeight/2.0f + thickness;
        }
        else if (paddlePos.y > ((float)wHeight - paddleHeight/2.0f - thickness))
        {
            paddlePos.y = (float)wHeight - paddleHeight/2.0f - thickness;
        }
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(renderer, 120, 0, 150, 255);
    SDL_RenderClear(renderer);

    // Top Wall
    SDL_FRect wall{0,0,(float)wWidth,thickness};
    SDL_SetRenderDrawColor(renderer, 255, 255 , 255, 255);
    SDL_RenderFillRect(renderer, &wall);

    // Bottom Wall
    wall = {0, (float)wHeight - thickness, (float)wWidth, thickness};
    SDL_RenderFillRect(renderer, &wall);

    // Right Wall
    wall = {(float)wWidth - thickness, 0, thickness, (float)wHeight};
    SDL_RenderFillRect(renderer, &wall);

    // Player Paddle
    wall = {paddlePos.x, paddlePos.y - 50, thickness, paddleHeight};
    SDL_RenderFillRect(renderer, &wall);

    // Ball
    SDL_FRect ball {(ballPos.x - thickness/2), (ballPos.y - thickness/2), thickness, thickness};
    SDL_RenderFillRect(renderer, &ball);

    SDL_RenderPresent(renderer);
}

void Game::CalculateCollision()
{
    // Bounce if needed
    // Did we intersect with the paddle?
    float diff = paddlePos.y - ballPos.y;
    // Take absolute value of difference
    diff = (diff > 0.0f) ? diff : -diff;
    if (
        // Our y-difference is small enough
            diff <= paddleHeight / 2.0f &&
            // We are in the correct x-position
            ballPos.x <= 25.0f && ballPos.x >= 20.0f &&
            // The ball is moving to the left
            ballVelocity.x < 0.0f)
    {
        ballVelocity.x *= -1.0f;
    }

    // Top wall collision
    if (ballPos.y <= thickness && ballVelocity.y < 0.0f)
    {
        ballVelocity.y *= -1;
    }

    // Bottom Wall collision
    if (ballPos.y >= (wHeight - thickness) && ballVelocity.y > 0.0f)
    {
        ballVelocity.y *= -1;
    }

    // Right Wall Collision
    if (ballPos.x > (wWidth - thickness) && ballVelocity.x > 0.0f)
    {
        ballVelocity.x *= -1;
    }
}

float Game::CalculateDeltaTime()
{
    while (!SDL_GetTicks() >= ticksCount + 16)
        ;
    // Converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
    ticksCount = SDL_GetTicks();

    // Clamp maximum delta value
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    return deltaTime;
}

void Game::Shutdown()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
