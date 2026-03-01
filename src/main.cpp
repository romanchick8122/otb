#include <iostream>

#include "raylib.h"

int main()
{
    InitWindow(800, 600, "otb");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();

        const char* text = "Hello, world!";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, 800 / 2 - text_size.x / 2, text_size.y + 10, 20, RAYWHITE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}