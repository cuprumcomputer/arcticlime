#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

#include "Map.hpp"
#include "Player.hpp"
#include "Droppable.hpp"

#define WIDTH 640
#define HEIGHT 480

using namespace std;

SDL_Texture * LoadTexture(SDL_Renderer * render_target, string file_path);

int main() {
    int previous_time = 0;
    int current_time = 0;
    float delta_time = 0;
    
    bool quit = false;
    
    SDL_Event event;
    
    SDL_Texture * background;
    
    Map map;
    
    int map_width;
    int map_height;
    
    SDL_Window * window = nullptr;
    SDL_Renderer * render_target = nullptr;
    
    SDL_Rect camera = {0, 0, WIDTH, HEIGHT};
    
    const Uint8 * key_state = nullptr;
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    render_target = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    Player player(render_target, "Assets/player.png", 100, 300);
    Droppable helmet(render_target, "Assets/helmet.png", 400, 300);
    
    background = LoadTexture(render_target, "Assets/background.png");
    SDL_QueryTexture(background, NULL, NULL, &map_width, &map_height);
        
    map.InitializeMap();
    map.SetMap(render_target);
    
    while (!quit) {
        previous_time = current_time;
        current_time = SDL_GetTicks();
        
        delta_time = (current_time - previous_time) / 1000.0f;
        
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                quit = true;
        }
        
        key_state = SDL_GetKeyboardState(NULL);
        
        helmet.Update(player.position);
        player.Update(delta_time, key_state, map);
        
        camera.x = player.position.x - (WIDTH / 2);
        camera.y = player.position.y - (HEIGHT / 2);
        
        if (camera.x < 0)
            camera.x = 0;
        
        if (camera.y < 0)
            camera.y = 0;
        
        if (camera.x + camera.w >= map_width)
            camera.x = map_width - WIDTH;
        
        if (camera.y + camera.h >= map_height)
            camera.y = map_height - HEIGHT;
        
        SDL_RenderClear(render_target);
        
        SDL_RenderCopy(render_target, background, &camera, NULL);
        map.Draw(render_target, camera);
        player.Draw(render_target, camera);
        helmet.Draw(render_target, camera, player.position);
        
        SDL_RenderPresent(render_target);
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render_target);
    
    
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

SDL_Texture * LoadTexture(SDL_Renderer * render_target, string file_path) {
    SDL_Texture * texture = nullptr;
    SDL_Surface * surface = IMG_Load(file_path.c_str());
    
    texture = SDL_CreateTextureFromSurface(render_target, surface);
    
    SDL_FreeSurface(surface);
    return(texture);
}



