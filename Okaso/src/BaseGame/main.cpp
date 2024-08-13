#include <glfw3.h>
#include "baseGame.h"

int main(void)
{
    Okaso_Engine* basegame = new Okaso_Engine();
    basegame->gameLoop();
    delete basegame;
   
    return 0;
}
