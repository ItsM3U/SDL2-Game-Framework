#include "Engine.h"
#include "Input.h"

#define TITLE "Framework"
#define WIDTH 800
#define HEIGHT 600
#define VSYNC true

void DrawShapesBasedOnInput() {
    if (Engine.Keys[SDL_SCANCODE_R]) { // Draw rectangle
        for (int y = 100; y < 200; y++) {
            for (int x = 100; x < 200; x++) {
                DrawPixel(x, y, (Color){255, 0, 0, 255});
            }
        }
    }

    if (Engine.Keys[SDL_SCANCODE_C]) { // Draw circle
        int centerX = 400, centerY = 300, radius = 50;
        for (int y = centerY - radius; y <= centerY + radius; y++) {
            for (int x = centerX - radius; x <= centerX + radius; x++) {
                int dx = x - centerX;
                int dy = y - centerY;
                if (dx * dx + dy * dy <= radius * radius) {
                    DrawPixel(x, y, (Color){0, 255, 0, 255});
                }
            }
        }
    }

    if (Engine.Keys[SDL_SCANCODE_L]) { // Draw line
        int startX = 50, startY = 50, endX = 750, endY = 550;
        int dx = abs(endX - startX), dy = abs(endY - startY);
        int sx = startX < endX ? 1 : -1;
        int sy = startY < endY ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;

        while (true) {
            DrawPixel(startX, startY, (Color){0, 0, 255, 255});
            if (startX == endX && startY == endY) break;
            e2 = err;
            if (e2 > -dx) { err -= dy; startX += sx; }
            if (e2 < dy) { err += dx; startY += sy; }
        }
    }
}

int main(int argc, char *argv[]) {
    Engine_Init(TITLE, WIDTH, HEIGHT, VSYNC);

    SDL_Event Event;
    Uint32 FrameStart, FrameTime;
    int FrameLimit = 60;

    while (!Engine.Quit) {
        FrameStart = SDL_GetTicks();

        while (SDL_PollEvent(&Event) != 0) {
            switch (Event.type) {
                case SDL_QUIT: Engine.Quit = true; break;
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    HandleMouseEvent(&Event);
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    HandleKeyEvent(&Event);
                    break;
                default: break;
            }
        }

        if (Engine.Keys[SDL_SCANCODE_ESCAPE]) {
            Engine.Quit = true;
        }

        memset(Engine.Pixels, 0, Engine.Width * Engine.Height * sizeof(Uint32));

        DrawShapesBasedOnInput();

        SDL_UpdateTexture(Engine.Texture, NULL, Engine.Pixels, Engine.Width * sizeof(Uint32));
        SDL_RenderClear(Engine.Renderer);
        SDL_RenderCopy(Engine.Renderer, Engine.Texture, NULL, NULL);
        SDL_RenderPresent(Engine.Renderer);

        Engine_UpdateWindowTitle(TITLE);

        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameTime < 1000 / FrameLimit) SDL_Delay(1000 / FrameLimit - FrameTime);
    }

    Engine_Cleanup();
    return 0;
}
