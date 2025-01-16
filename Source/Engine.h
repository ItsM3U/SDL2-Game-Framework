#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    Uint8 R, G, B, A;
} Color;

typedef struct {
    int X, Y;
    bool Left, Right, Middle;
} MouseState;

typedef struct {
    SDL_Window *Window;
    SDL_Renderer *Renderer;
    SDL_Texture *Texture;
    Uint32 *Pixels;
    bool Keys[SDL_NUM_SCANCODES];
    MouseState Mouse;
    bool Focused, Quit;
    int Width, Height;
} EngineType;

extern EngineType Engine;

void Engine_Init(const char *Title, int Width, int Height, bool VSync);
void Engine_UpdateWindowTitle(const char *BaseTitle);
void Engine_Cleanup();

void DrawPixel(int X, int Y, Color Color);

#endif // ENGINE_H
