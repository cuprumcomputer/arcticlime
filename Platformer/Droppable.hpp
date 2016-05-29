#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Player.hpp"

using namespace std;

class Droppable {
public:
    Droppable(SDL_Renderer * render_target, string file_path, int x, int y);
    
    void Update(SDL_Rect player_position);
    void Draw(SDL_Renderer * render_target, SDL_Rect camera, SDL_Rect player_position);
    
    ~Droppable();
    
private:
    bool CheckCollision(SDL_Rect player_position);
    
    SDL_Rect position;
    SDL_Rect drawing;
    
    SDL_Texture * texture;
    
    bool grabbed;
    
    bool going_up;
    int distance;
};