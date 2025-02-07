#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game* game)
        :Actor(game)
        ,mRightSpeed(0.0f)
        ,mDownSpeed(0.0f)
{
    // Create an animated sprite component
    AnimSpriteComponent* asc = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> anims = {
            game->GetTexture(RESOURCES_PATH"textures/ship/Ship01.png"),
            game->GetTexture(RESOURCES_PATH"textures/ship/Ship02.png"),
            game->GetTexture(RESOURCES_PATH"textures/ship/Ship03.png"),
            game->GetTexture(RESOURCES_PATH"textures/ship/Ship04.png"),
    };
    asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    // Update position based on speeds and delta time
    Vector2 pos = GetPosition();
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;
    // Restrict position to left half of screen
    if (pos.x < 25.0f)
    {
        pos.x = 25.0f;
    }
    else if (pos.x > 500.0f)
    {
        pos.x = 500.0f;
    }
    if (pos.y < 25.0f)
    {
        pos.y = 25.0f;
    }
    else if (pos.y > 743.0f)
    {
        pos.y = 743.0f;
    }
    SetPosition(pos);
}

void Ship::ProcessKeyboard(const bool* state)
{
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;
    // right/left
    if (state[SDL_SCANCODE_D])
    {
        mRightSpeed += 250.0f;
    }
    if (state[SDL_SCANCODE_A])
    {
        mRightSpeed -= 250.0f;
    }
    // up/down
    if (state[SDL_SCANCODE_S])
    {
        mDownSpeed += 300.0f;
    }
    if (state[SDL_SCANCODE_W])
    {
        mDownSpeed -= 300.0f;
    }
}