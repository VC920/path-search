#ifndef RENDERER_H
#define RENDERER_H
#include <SDL3/SDL.h>
#include <ctype.h>

void renderer_init(SDL_Window *window);

void renderer_destroy();

void renderer_clear(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);

void renderer_present();

void renderer_draw_rect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void renderer_draw_text(int x, int y, char *text, size_t length);

#endif//RENDERER_H
