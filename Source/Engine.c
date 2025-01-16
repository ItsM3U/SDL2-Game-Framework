#include "Engine.h"
#include <stdlib.h>
#include <stdio.h>

EngineType Engine;

static Uint32 LastTime = 0, TitleUpdateTime = 0;
static int FrameCount = 0;

void Engine_Init(const char *Title, int Width, int Height, bool VSync) {
    Uint32 RendererFlags = SDL_RENDERER_ACCELERATED | (VSync ? SDL_RENDERER_PRESENTVSYNC : 0);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    Engine.Width = Width;
    Engine.Height = Height;

    Engine.Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);
    if (!Engine.Window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(1);
    }

    Engine.Renderer = SDL_CreateRenderer(Engine.Window, -1, RendererFlags);
    if (!Engine.Renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        exit(1);
    }

    Engine.Texture = SDL_CreateTexture(Engine.Renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, Width, Height);
    if (!Engine.Texture) {
        fprintf(stderr, "SDL_CreateTexture Error: %s\n", SDL_GetError());
        exit(1);
    }

    Engine.Pixels = malloc(Width * Height * sizeof(Uint32));
    if (!Engine.Pixels) {
        fprintf(stderr, "Memory allocation error for Engine.Pixels\n");
        exit(1);
    }

    LastTime = SDL_GetTicks();
    TitleUpdateTime = LastTime;
}

void Engine_UpdateWindowTitle(const char *BaseTitle) {
    Uint32 CurrentTime = SDL_GetTicks();
    FrameCount++;

    if (CurrentTime > TitleUpdateTime + 500) {
        float ElapsedTime = (CurrentTime - LastTime) / 1000.0f;
        if (ElapsedTime == 0.0f) ElapsedTime = 1.0f;

        int FPS = (int)(FrameCount / ElapsedTime);

        char Title[128];
        snprintf(Title, sizeof(Title), "%s - FPS: %d", BaseTitle, FPS);

        if (Engine.Window) {
            SDL_SetWindowTitle(Engine.Window, Title);
        } else {
            fprintf(stderr, "Error: Engine.Window is NULL\n");
        }

        LastTime = CurrentTime;
        TitleUpdateTime = CurrentTime;
        FrameCount = 0;
    }
}

void Engine_Cleanup() {
    SDL_DestroyTexture(Engine.Texture);
    SDL_DestroyRenderer(Engine.Renderer);
    SDL_DestroyWindow(Engine.Window);
    SDL_Quit();
}

void DrawPixel(int X, int Y, Color Color) {
    if (X < 0 || X >= Engine.Width || Y < 0 || Y >= Engine.Height) return;
    Engine.Pixels[Y * Engine.Width + X] = (Color.A << 24) | (Color.B << 16) | (Color.G << 8) | Color.R;
}
