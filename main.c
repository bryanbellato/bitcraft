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

// Function to update game state based on input
void update_game_state(GameState* state, float dt) {
    if (input_is_key_pressed(SDLK_LEFT)) {
        state->rect_x -= 100.0f * dt;
    }
    if (input_is_key_pressed(SDLK_RIGHT)) {
        state->rect_x += 100.0f * dt;
    }
}

// Scheduler structure to manage the game loop
typedef struct {
    GameState* game_state;  // Pointer to the game state
    float last_time;        // Last recorded time for delta calculation
    float accumulator;      // Accumulated time for fixed time-step updates
} Scheduler;

void scheduler_init(Scheduler* scheduler, GameState* game_state) {
    scheduler->game_state = game_state;
    scheduler->last_time = get_current_time();
    scheduler->accumulator = 0.0f;
}


void scheduler_run(Scheduler* scheduler) {
    int frameCount = 0;
    float fpsTimer = 0.0f;

    while (!input_should_quit()) {
        input_poll_events();

        float current_time = get_current_time();
        float delta_time = current_time - scheduler->last_time;
        scheduler->last_time = current_time;

        fpsTimer += delta_time;
        frameCount++;

        scheduler->accumulator += delta_time;
        while (scheduler->accumulator >= TARGET_FRAME_TIME) {
            update_game_state(scheduler->game_state, TARGET_FRAME_TIME);
            scheduler->accumulator -= TARGET_FRAME_TIME;
        }

        render_begin_frame();
        render_draw_rect((int)scheduler->game_state->rect_x,
                         (int)scheduler->game_state->rect_y,
                         200, 200, 255, 0, 0);
        render_end_frame();

        if (fpsTimer >= 1.0f) {
            printf("FPS: %d\n", frameCount);
            frameCount = 0;
            fpsTimer -= 1.0f;
        }
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

    GameState game_state = {100.0f, 100.0f};

    Scheduler scheduler;
    scheduler_init(&scheduler, &game_state);
    scheduler_run(&scheduler);

    render_shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
