#include <SDL2/SDL.h>

float get_current_time(void) {
    return SDL_GetTicks() / 1000.0f; // Convert milliseconds to seconds
}
