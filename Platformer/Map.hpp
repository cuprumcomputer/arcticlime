#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>

#define TILE_SIZE 40
#define MAP_WIDTH 1280
#define MAP_HEIGHT 480

using namespace std;

class Map {
public:
    void InitializeMap(void);
    void SetMap(SDL_Renderer * render_target);
    void Draw(SDL_Renderer * render_target, SDL_Rect camera);
    bool CheckCollision(int x, int y);
    
    void SetBrick(int x, int y, SDL_Renderer * render_target);
    
private:
    struct Tile {
        bool solid;
        SDL_Rect position;
        SDL_Texture * texture;
    };
    
    Tile map[(MAP_WIDTH / TILE_SIZE)][MAP_HEIGHT / TILE_SIZE];
    SDL_Texture * LoadTexture(SDL_Renderer * render_target, string file_path);
};