#include <render.h>

static SDL_Renderer* g_renderer;

void render_init(SDL_Renderer* renderer) {
    g_renderer = renderer;
}

void render_begin_frame(void) {
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);
}

void render_draw_rect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(g_renderer, r, g, b, 255);
    SDL_RenderFillRect(g_renderer, &rect);
}

void render_end_frame(void) {
    SDL_RenderPresent(g_renderer);
}

void render_shutdown(void) {}
