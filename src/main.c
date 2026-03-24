#include <stdio.h>
#include <stdbool.h>
#include "./SDL3/SDL.h"
#include "chip8.h"
#include "chip8keyboard.h"

const char keyboard_map[CHIP8_TOTAL_KEYS] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3,
    SDLK_4, SDLK_5, SDLK_6, SDLK_7,
    SDLK_8, SDLK_9, SDLK_A, SDLK_B,
    SDLK_C, SDLK_D, SDLK_E, SDLK_F};

int main(int argc, char **argv)
{
    struct chip8 chip8;
    chip8_init(&chip8);

    chip8_screen_set(&chip8.screen, 10, 5);

    printf("%x\n", chip8_keyboard_map(keyboard_map, 0x0f));
    // Test press
    chip8_keyboard_down(&chip8.keyboard, 0x0f);
    // chip8_keyboard_up(&chip8.keyboard, 0x0f);

    bool is_down = chip8_keyboard_is_down(&chip8.keyboard, 0x0f);
    printf("%i\n", (int)is_down);

    // ------------------------------------------  Test stack
    chip8.registers.SP = 0;

    chip8_stack_push(&chip8, 0xff);
    chip8_stack_push(&chip8, 0xaa);

    printf("%x\n", chip8_stack_pop(&chip8));
    printf("%x\n", chip8_stack_pop(&chip8));
    //-------------------------------------------

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE,
        CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLIER,
        CHIP8_HEIGHT * CHIP8_WINDOW_MULTIPLIER,
        0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0);

    while (1)
    {
        SDL_Event event;
        // Handle events, how we close
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                goto out;
                break;
            case SDL_EVENT_KEY_DOWN:
            {
                SDL_Keycode key = event.key.key;
                int vkey = chip8_keyboard_map(keyboard_map, key);
                printf("Key is down %x\n", vkey);

                if (vkey != -1)
                {
                    chip8_keyboard_down(&chip8.keyboard, vkey);
                }
            }

            break;
            case SDL_EVENT_KEY_UP:
            {
                SDL_Keycode key = event.key.key;
                int vkey = chip8_keyboard_map(keyboard_map, key);
                printf("Key is up %x\n", vkey);

                if (vkey != -1)
                {
                    chip8_keyboard_up(&chip8.keyboard, vkey);
                }
            }
            break;
            }
            if (event.type == SDL_EVENT_QUIT)
            {
                goto out;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        for (int x = 0; x < CHIP8_WIDTH; x++)
        {
            for (int y = 0; y < CHIP8_HEIGHT; y++)
            {
                if (chip8_screen_is_set(&chip8.screen, x, y))
                {
                    SDL_FRect r;
                    r.x = x * CHIP8_WINDOW_MULTIPLIER;
                    r.y = y * CHIP8_WINDOW_MULTIPLIER;
                    r.w = CHIP8_WINDOW_MULTIPLIER;
                    r.h = CHIP8_WINDOW_MULTIPLIER;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

// Goto
out:
    SDL_DestroyWindow(window);
    return 0;
}