
// Alternative DrawText() function to use with raylib
// Created by Nighten, using the code from the Raylib source code written by Ramon Santamaria (@raysan5)

/*
Features:

*italic*
**Bold**
~wave animation~
~~crossed~~
__underline__

+ user defined line spacing
*/
void DrawTextStyleEx(Font main_font, Font italic_font, Font bold_font, Font bolditalic_font, const char *text, Vector2 position, float fontSize, float spacing, float linespacing, float time, Color color);


//It is really recommended to use a wrapper function like this :
void DrawTextStyle(const char* text, float posx, float posy, int fontsize, Color color)
{
    //Exemple:
    DrawTextStyleEx(my_main_font, my_italic_font, my_bold_font, my_bolditalic_font, 
                    text, (Vector2){posx, posy}, fontsize,
                    1, 1.1, timer, color);
}


void DrawTextStyleEx(Font main_font, Font italic_font, Font bold_font, Font bolditalic_font, const char *text, Vector2 position, float fontSize, float spacing, float linespacing, float time,Color color)
{
    // DrawTextEx(Text_font, text, (Vector2){posX, posY},fontSize, 1,color);

    Font font = main_font;

    int length = TextLength(text);      // Total length in bytes of the text, scanned by codepoints in loop

    int textOffsetY = 0;            // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    
    float scaleFactor = fontSize/font.baseSize;     // Character quad scaling factor

    //Style flags
    bool flag_bold = false;
    bool flag_italic = false;
    bool flag_wave = false;
    bool flag_crossed = false;
    bool flag_underline = false;

    //Parameters for the waves effect
    float wave_x_range = 1;
    float wave_y_range = 2;
    int wave_x_speed = 4;
    int wave_y_speed = 4;
    float wave_x_offset = 0.5;
    float wave_y_offset = 0.5;


    for (int i = 0; i < length;)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetNextCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);


        if (codepoint == 0x3f) codepointByteCount = 1;

        if (codepoint == '\n')
        {
            textOffsetY += (int)((font.baseSize * linespacing)*scaleFactor);
            textOffsetX = 0.0f;
        }
        else if (codepoint == '*')
        {
            if (GetNextCodepoint(&text[i+1], &codepointByteCount) == '*') // -> **
            {
                flag_bold = !flag_bold;
                codepointByteCount += 1;
            }
            else
            {
                flag_italic = !flag_italic;
            }

            //Font Weight switching
            if (flag_bold && flag_italic) font = bolditalic_font;
            else if (flag_bold)font = bold_font;
            else if (flag_italic) font = italic_font;
            else font = main_font;
        }
        else if (codepoint == '~') // Maybe use a different symbol for wave effect (or use a escape character ?)
        {
            if (GetNextCodepoint(&text[i+1], &codepointByteCount) == '~') // -> ~~
            {
                flag_crossed = !flag_crossed;
                codepointByteCount += 1;
            }
            else
            {
                flag_wave = !flag_wave;
            }
        }
        else if (codepoint == '_' && GetNextCodepoint(&text[i+1], &codepointByteCount) == '_') // -> __
        {
            flag_underline = !flag_underline;
            codepointByteCount += 1;

        }
        else
        {
            if ((codepoint != ' ') && (codepoint != '\t'))
            {
                float position_x;
                float position_y;
                position_x = position.x + textOffsetX;
                position_y = position.y + textOffsetY;

                if (flag_wave) //Apply the wave effect
                {
                    position_x += sin(time*wave_x_speed-i*wave_x_offset)*wave_x_range;
                    position_y += sin(time*wave_y_speed-i*wave_y_offset)*wave_y_range;
                }

                DrawTextCodepoint(font, codepoint, (Vector2){ position_x, position_y }, fontSize, color);

                //Draw the crossed and underline
                //TODO: Draw these lines over spaces when needed
                if (flag_crossed)
                {
                    DrawLine(position_x, position_y+fontSize/2,
                            position_x + ((float)font.chars[index].advanceX*scaleFactor + spacing), position_y+fontSize/2,
                            color);
                }

                if (flag_underline)
                {
                    DrawLine(position_x, position_y+fontSize,
                            position_x + ((float)font.chars[index].advanceX*scaleFactor + spacing), position_y+fontSize,
                            color);
                }

            }

            if (font.chars[index].advanceX == 0) textOffsetX += ((float)font.recs[index].width*scaleFactor + spacing);
            else textOffsetX += ((float)font.chars[index].advanceX*scaleFactor + spacing);
        }

        i += codepointByteCount;   // Move text bytes counter to next codepoint
        
    }
}