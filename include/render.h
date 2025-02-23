#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>

void render_init(SDL_Renderer* renderer);
void render_begin_frame(void);
void render_draw_rect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);
void render_end_frame(void);
void render_shutdown(void);

#endif
