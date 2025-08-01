#include "event.h"
#include "sdl.h"

int main() {
    SDLEnv env("Bouncy");
    game_loop(env);

    return 0;
}
