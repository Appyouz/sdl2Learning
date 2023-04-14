#include "../include/Text.hpp"
#include <iostream>
#include <SDL2/SDL.h>

bool Text::m_ttfInitialized = false;
Text::Text() {
  if (!m_ttfInitialized && TTF_Init() == -1) {
    std::cout << "Could not initialize SDL_ttf. Error: " << TTF_GetError()
              << '\n';
  } else {
    std::cout << "SDL_ttf working...\n" << '\n';
    // initialize ttf system only once even if
    // we have multiple Text objects
    m_ttfInitialized = true;
  }
  // load our font file and set the font size
  TTF_Font *ourFont = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf", 32);

  // confirm it was loaded
  if (ourFont == nullptr) {
    std::cout << "Could not load font.\n";
    std::exit(1);
  }

  // pixels from our text
  SDL_Surface *surfaceText =
      TTF_RenderText_Solid(ourFont, "SDL2 learning series", {255, 255, 255});

  SDL_Texture *textureText =
      SDL_CreateTextureFromSurface(renderer, surfaceText);
  SDL_FreeSurface(surfaceText);

  SDL_Rect rectangle;
  rectangle.x = 10;
  rectangle.y = 10;
  rectangle.w = 400;
  rectangle.h = 100;
}

Text::~Text() {

  // Destroy our textured Text
  SDL_DestroyTexture(textureText);

  // Close our font subsystem
  TTF_CloseFont(ourFont);
}

void Text::drawText() {
  // Render our text on a rectangle
  SDL_RenderCopy(renderer, textureText, NULL, &rectangle);
}
