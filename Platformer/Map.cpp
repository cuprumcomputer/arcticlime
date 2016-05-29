#include "Map.hpp"

void Map::InitializeMap() {
    for (int x = 0; x < (MAP_WIDTH / TILE_SIZE); x++){
        for (int y = 0; y < (MAP_HEIGHT / TILE_SIZE); y++){
            map[x][y].solid = false;
            map[x][y].position = {(x * TILE_SIZE), (y * TILE_SIZE), TILE_SIZE, TILE_SIZE};
            map[x][y].texture = NULL;
        }
    }
}

void Map::SetMap(SDL_Renderer *render_target) {
    for (int x = 0; x < (MAP_WIDTH / TILE_SIZE); x++) {
        SetBrick(x, 11, render_target);
    }
    
    SetBrick(7, 9, render_target);
    SetBrick(7, 8, render_target);
    SetBrick(7, 7, render_target);
    
    SetBrick(12, 10, render_target);
    SetBrick(13, 10, render_target);
    SetBrick(13, 9, render_target);
}

void Map::Draw(SDL_Renderer * render_target, SDL_Rect camera) {
    for (int x = 0; x < (MAP_WIDTH / TILE_SIZE); x++){
        for (int y = 0; y < (MAP_HEIGHT / TILE_SIZE); y++){
            if (map[x][y].texture != NULL) {
                int drawing_x = map[x][y].position.x - camera.x;
                int drawing_y = map[x][y].position.y - camera.y;
                SDL_Rect drawing = {drawing_x, drawing_y, map[x][y].position.w, map[x][y].position.h};
                SDL_RenderCopy(render_target, map[x][y].texture, NULL, &drawing);
            }
        }
    }
}

void Map::SetBrick(int x, int y, SDL_Renderer * render_target) {
    map[x][y].texture = LoadTexture(render_target, "Assets/tile.png");
    map[x][y].solid = true;
}

bool Map::CheckCollision(int x, int y) {
    return(map[x][y].solid);
}

SDL_Texture * Map::LoadTexture(SDL_Renderer * render_target, string file_path) {
    SDL_Texture * texture = nullptr;
    SDL_Surface * surface = IMG_Load(file_path.c_str());
    
    texture = SDL_CreateTextureFromSurface(render_target, surface);
    
    SDL_FreeSurface(surface);
    return(texture);
}










