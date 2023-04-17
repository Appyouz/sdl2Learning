#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {

  SDL_Window *window;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not be initialized." << '\n';
  } else {
    std::cout << "SDL video  system is ready to go." << '\n';
  }

  window = SDL_CreateWindow("SDL2 parallax scrolling", 20, 20, 640, 480,
                            SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = nullptr;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Surface *sky_surface = SDL_LoadBMP("./assets/images/sky.bmp");
  SDL_Surface *road_surface = SDL_LoadBMP("./assets/images/road.bmp");
  SDL_Surface *sidewalk_surface = SDL_LoadBMP("./assets/images/sidewalk.bmp");

  // to make transparency
  SDL_SetColorKey(sky_surface, SDL_TRUE,
                  SDL_MapRGB(sky_surface->format, 0xFF, 0, 0xFF));

  SDL_SetColorKey(road_surface, SDL_TRUE,
                  SDL_MapRGB(road_surface->format, 0xFF, 0, 0xFF));

  SDL_SetColorKey(sidewalk_surface, SDL_TRUE,
                  SDL_MapRGB(sidewalk_surface->format, 0xFF, 0, 0xFF));

  //  create surfaces
  SDL_Texture *sky_texture =
      SDL_CreateTextureFromSurface(renderer, sky_surface);

  SDL_Texture *road_texture =
      SDL_CreateTextureFromSurface(renderer, road_surface);

  SDL_Texture *sidewalk_texture =
      SDL_CreateTextureFromSurface(renderer, sidewalk_surface);

  // clean up memory
  SDL_FreeSurface(sky_surface);
  SDL_FreeSurface(road_surface);
  SDL_FreeSurface(sidewalk_surface);

  SDL_Rect sky1;
  sky1.x = 0;
  sky1.y = 0;
  sky1.w = 640;
  sky1.h = 480;

  SDL_Rect sky2;
  sky2.x = -639;
  sky2.y = 0;
  sky2.w = 640;
  sky2.h = 480;

  SDL_Rect road1;
  road1.x = 0;
  road1.y = 0;
  road1.w = 640;
  road1.h = 480;

  SDL_Rect road2;
  road2.x = -639;
  road2.y = 0;
  road2.w = 640;
  road2.h = 480;

  SDL_Rect sidewalk1;
  sidewalk1.x = 0;
  sidewalk1.y = 0;
  sidewalk1.w = 640;
  sidewalk1.h = 480;

  SDL_Rect sidewalk2;
  sidewalk2.x = -639;
  sidewalk2.y = 0;
  sidewalk2.w = 640;
  sidewalk2.h = 480;

  bool gameIsRunning = true;
  while (gameIsRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      const Uint8 *state = SDL_GetKeyboardState(NULL);
      // handle each specific event
      if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        gameIsRunning = false;
        std::cout << "Escaped key pressed\n";
      }
    }

    SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0xBB, 0xFF);
    SDL_RenderClear(renderer);
    SDL_Delay(20);

    // handle texture scrolling left and right
    sky1.x += 1;
    sky2.x += 1;

    road1.x += 2;
    road2.x += 2;

    sidewalk1.x += 4;
    sidewalk2.x += 4;

    // handle looping of each of the  two textured rectangles
    // as they each  scroll across the screen. When the boundary is
    // reached, then the texture moves back to the start while the second
    // texture continues scrolling
    if (road1.x > 639)
      road1.x = -639;

    if (road2.x > 639)
      road2.x = -639;

    if (sky1.x > 639)
      sky1.x = -639;

    if (sky2.x > 639)
      sky2.x = -639;

    if (sidewalk1.x > 639)
      sidewalk1.x = -639;

    if (sidewalk2.x > 639)
      sidewalk2.x = -639;

    /* SDL_RenderCopy(renderer, sky_texture, NULL, &sky1);
    SDL_RenderCopy(renderer, sky_texture, NULL, &sky2);
*/
    SDL_RenderCopy(renderer, road_texture, NULL, &road1);
    SDL_RenderCopy(renderer, road_texture, NULL, &road2);
/*
    SDL_RenderCopy(renderer, sidewalk_texture, NULL, &sidewalk1);
    SDL_RenderCopy(renderer, sidewalk_texture, NULL, &sidewalk2); */

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(sky_texture);
  SDL_DestroyTexture(road_texture);
  SDL_DestroyTexture(sidewalk_texture);

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
