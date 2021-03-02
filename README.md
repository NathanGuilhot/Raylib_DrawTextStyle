# DrawTextStyle( )

> a stylish markdown-like DrawText function for Raylib!

## Usage

You can use basic markdown syntax to style your text :

````markdown
*italic*
**Bold**
~wave animation~
~~crossed~~
__underline__
````

Of course, you can easily combine these effects with each other; maybe even all at once!

```
DrawTextStyle("~Hellooo~ :D", 100,100, DARKGRAY)
```

You can also use this function to specify the line spacing to use in your multi-line text (something you can't do by default in Raylib)

I really recommend tweaking this function to your liking! I hope I wrote something clear enough. Have fun!

## How to setup

- You need to load your font, with variations (normal, italic, bold, bold+italic)
- Create a timer variable to animate the ~waaave~ (and add the delta-time each frame)
- Include the [header](DrawTextStyle.h) file
- Customize the *DrawTextStyle()* wrapper to use your favorite settings
- **You're good to go!**

Thank Raysan for making such a lovely framework <3