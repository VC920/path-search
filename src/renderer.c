#include "renderer.h"
#include <stdio.h>
#include <SDL3_ttf/SDL_ttf.h>

static SDL_Renderer *renderer;
static TTF_Font *font;

SDL_Surface* textSurface;
SDL_Texture* textTexture;

void renderer_init(SDL_Window *window)
{
    TTF_Init();
    font = TTF_OpenFont("third/arial.ttf", 64);
    
    // Init sdl renderer
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        fprintf(stderr, "error: SDL_CreateRenderer()\n");
        return;
    }
}

void renderer_destroy()
{
    SDL_DestroyRenderer(renderer);

    // Clear font
    SDL_DestroySurface(textSurface);
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTexture);
    TTF_Quit();
}

void renderer_clear(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

void renderer_present()
{
    SDL_RenderPresent(renderer);
}

void renderer_draw_rect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_FRect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);
}

void renderer_draw_text(int x, int y, char *text, size_t length)
{
    SDL_Color textColor = {0, 255, 0, 255}; // °×É«
    textSurface = TTF_RenderText_Blended(font, text, length, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FRect dst_rect = { x, y, textSurface->w, textSurface->h};
    SDL_RenderTexture(renderer, textTexture, NULL, &dst_rect);
}
