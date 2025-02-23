#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>
#include <stdbool.h>

void input_init(void);
void input_poll_events(void);
bool input_should_quit(void);
bool input_is_key_pressed(SDL_Keycode key);

#endif
