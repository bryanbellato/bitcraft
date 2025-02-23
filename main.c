#include <SDL2/SDL.h>
#include <render.h>
#include <input.h>
#include <utils.h>

#define TARGET_FPS 60
#define TARGET_FRAME_TIME (1.0f / TARGET_FPS)

// Struct to hold game state
typedef struct {
    float rect_x;
    float rect_y;
} GameState;

void update_game_state(GameState* state, float dt) {
    if (input_is_key_pressed(SDLK_LEFT)) {
        state->rect_x -= 100.0f * dt; 
    }
    if (input_is_key_pressed(SDLK_RIGHT)) {
        state->rect_x += 100.0f * dt; 
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 224, 0);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    render_init(renderer);
    input_init();

    // Initialize game state
    GameState game_state = {100.0f, 100.0f};

    // Timing variables
    float last_time = get_current_time();
    float accumulator = 0.0f;

    while (!input_should_quit()) {
        input_poll_events();

        float current_time = get_current_time();
        float delta_time = current_time - last_time;
        last_time = current_time;

        accumulator += delta_time;
        while (accumulator >= TARGET_FRAME_TIME) {
            update_game_state(&game_state, TARGET_FRAME_TIME);
            accumulator -= TARGET_FRAME_TIME;
        }

        render_begin_frame();
        render_draw_rect((int)game_state.rect_x, (int)game_state.rect_y, 200, 200, 255, 0, 0);
        render_end_frame();
    }

    render_shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
