#include "Game.h"

int main()
{
    Game game;
    bool success = game.Init();

    if (success)
    {
        game.RunLoop();
    }

    game.Shutdown();
    return 0;
}
