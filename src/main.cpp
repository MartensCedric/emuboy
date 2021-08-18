#include <iostream>
#include "util/safety.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "cpu/CPU.h"
#include <thread>


int main() {

    CPU cpu;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
    }

    bool running = true;
    bool stopped = false;
    SDL_Window* window = SDL_CreateWindow("EmuBoy",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       800, 800, 0);
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    SDL_Quit();
                    break;
                default:
                    break;
            }
        }

        if(!stopped)
        {
            cpu.fetch_cycle();
        }
    }

    return 0;
}
