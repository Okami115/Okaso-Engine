#include "../../Okaso Engine/Okaso/src/BaseGame/BaseGame.h"

void main()
{
    Okaso_Engine* basegame = new Okaso_Engine();
    basegame->gameLoop();
    delete basegame;
}