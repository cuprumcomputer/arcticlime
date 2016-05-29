#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Map.hpp"

using namespace std;

class Player {
public:
    SDL_Rect position;
    SDL_Rect drawing;
    
    Player(SDL_Renderer * render_target, string file_path, int x, int y);
    
    void Update(float delta_time, const Uint8 * key_state, Map map);
    void Draw(SDL_Renderer * render_target, SDL_Rect camera);
    
    ~Player();
        
private:
    SDL_Texture * texture;
    
    SDL_Scancode keys[4];
    
    bool CheckHorizontalCollision(int x, int y, int &tile_y, Map map);
    bool CheckVerticalCollision(int x, int y, int &tile_x, Map map);
    
    int x_velocity;
    int y_velocity;
    bool jumping;
};