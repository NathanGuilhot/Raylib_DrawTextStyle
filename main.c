/*******************************************************************************************
*
*   DrawTextStyle() Example by Nighten
*   (Base on the raylib [core] example)
*
********************************************************************************************/

#include "raylib.h"
#include <math.h> //So we can use sin() to animate the ~wave~

Font my_main_font;
Font my_italic_font;
Font my_bold_font;
Font my_bolditalic_font;

float timer; //timer is used to animate the text

//Include the actual header file
#include "DrawTextStyle.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    //Loading our fonts
    my_main_font = LoadFont("font/NotoSans-Regular.ttf");
    my_italic_font = LoadFont("font/NotoSans-Italic.ttf");
    my_bold_font = LoadFont("font/NotoSans-Bold.ttf");
    my_bolditalic_font = LoadFont("font/NotoSans-BoldItalic.ttf");

    char* text_to_display = "**Congrats!** ~You just discovered the *DrawTextStyle*!~\nYou ~~should~~ can include this *function* in **__any project__**,\nand start ~having fun!!!~ ";

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        //Update the timer by adding the delta time
        timer += GetFrameTime();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Style :)
        DrawTextStyle(text_to_display, 20, 100, 32, DARKGRAY);

        //No style :(
        DrawTextEx(my_main_font ,text_to_display, (Vector2){20, 275}, 32, 1, DARKGRAY);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();

    UnloadFont(my_main_font);
    UnloadFont(my_italic_font);
    UnloadFont(my_bold_font);
    UnloadFont(my_bolditalic_font);

    //--------------------------------------------------------------------------------------

    return 0;
}