#include <input.h>

static bool quitting = false;

void input_init(void) {}

void input_poll_events(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitting = true;
        }
       
    }
}

bool input_should_quit(void) {
    return quitting;
}

bool input_is_key_pressed(SDL_Keycode key) {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[SDL_GetScancodeFromKey(key)] != 0;
}
