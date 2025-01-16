#include "Input.h"
#include "Engine.h"
#include <stdio.h>

void HandleKeyEvent(const SDL_Event *Event) {
    if (Event->type == SDL_KEYDOWN && !Event->key.repeat) {
        Engine.Keys[Event->key.keysym.scancode] = true;
        printf("Key pressed: %s\n", SDL_GetScancodeName(Event->key.keysym.scancode));
    } else if (Event->type == SDL_KEYUP) {
        Engine.Keys[Event->key.keysym.scancode] = false;
        printf("Key released: %s\n", SDL_GetScancodeName(Event->key.keysym.scancode));
    }
}

void HandleMouseEvent(const SDL_Event *Event) {
    if (Event->type == SDL_MOUSEMOTION) {
        Engine.Mouse.X = Event->motion.x;
        Engine.Mouse.Y = Event->motion.y;
        printf("Mouse position: (%d, %d)\n", Engine.Mouse.X, Engine.Mouse.Y);
    } else if (Event->type == SDL_MOUSEBUTTONDOWN) {
        if (Event->button.button == SDL_BUTTON_LEFT) {
            Engine.Mouse.Left = true;
            printf("Left click pressed\n");
        } else if (Event->button.button == SDL_BUTTON_RIGHT) {
            Engine.Mouse.Right = true;
            printf("Right click pressed\n");
        } else if (Event->button.button == SDL_BUTTON_MIDDLE) {
            Engine.Mouse.Middle = true;
            printf("Middle click pressed\n");
        }
    } else if (Event->type == SDL_MOUSEBUTTONUP) {
        if (Event->button.button == SDL_BUTTON_LEFT) {
            Engine.Mouse.Left = false;
            printf("Left click released\n");
        } else if (Event->button.button == SDL_BUTTON_RIGHT) {
            Engine.Mouse.Right = false;
            printf("Right click released\n");
        } else if (Event->button.button == SDL_BUTTON_MIDDLE) {
            Engine.Mouse.Middle = false;
            printf("Middle click released\n");
        }
    }
}
