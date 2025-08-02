#include "game.h"
#include "sdl.h"

int main() {
    const SDLEnv env("Bouncy");
    game_loop(env);

    return 0;
}
