#include "game.h"
#include "sdl.h"

int main() {
    SDLEnv env("Bouncy");
    game_loop();

    return 0;
}
