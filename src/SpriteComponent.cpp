#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
        :Component(owner)
        ,mTexture(nullptr)
        ,mDrawOrder(drawOrder)
        ,mTexWidth(0)
        ,mTexHeight(0)
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        SDL_FRect r;
        // Scale the width/height by owner's scale
        r.w = (mTexWidth * mOwner->GetScale());
        r.h = (mTexHeight * mOwner->GetScale());
        // Center the rectangle around the position of the owner
        r.x = (mOwner->GetPosition().x - r.w / 2);
        r.y = (mOwner->GetPosition().y - r.h / 2);

        // Draw (have to convert angle from radians to degrees, and clockwise to counter)
        SDL_RenderTextureRotated(renderer, mTexture, NULL, &r, -Math::ToDegrees(mOwner->GetRotation()), NULL, SDL_FLIP_NONE);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;
    // Set width/height
//    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
    SDL_GetTextureSize(texture, &mTexWidth, &mTexHeight);
}
