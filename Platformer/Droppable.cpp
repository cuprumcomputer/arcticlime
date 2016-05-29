#include "Droppable.hpp"

#define MAX_DISTANCE 20

Droppable::Droppable(SDL_Renderer * render_target, string file_path, int x, int y) {
    texture = nullptr;
    
    SDL_Surface * surface = IMG_Load(file_path.c_str());
    texture = SDL_CreateTextureFromSurface(render_target, surface);
    
    SDL_FreeSurface(surface);
    
    position.x = x;
    position.y = y;
    
    position.w = position.h = 30;

    grabbed = false;
    
    going_up = false;
    distance = 0;
}

void Droppable::Update(SDL_Rect player_position) {
    if (CheckCollision(player_position)) {
        grabbed = true;
    } else {
        if (going_up && distance < MAX_DISTANCE) {
            position.y--;
            distance++;
        } else if (!going_up && distance > 0) {
            position.y++;
            distance--;
        } else if (distance >= MAX_DISTANCE) {
            going_up = false;
            position.y++;
            distance--;
        } else if (distance <= 0) {
            going_up = true;
            position.y--;
            distance++;
        }
    }
}

void Droppable::Draw(SDL_Renderer * render_target, SDL_Rect camera, SDL_Rect player_position) {
    if (!grabbed) {
        drawing = {position.x - camera.x, position.y - camera.y, position.w, position.h};
    } else {
        drawing = {player_position.x - camera.x, player_position.y - camera.y, position.w, position.h};
    }
    
    SDL_RenderCopy(render_target, texture, NULL, &drawing);
}

bool Droppable::CheckCollision(SDL_Rect player_position) {
    if (position.x + position.w < player_position.x || position.x > player_position.x + player_position.w ||
        position.y + position.h < player_position.y || position.y > player_position.y + player_position.h) {
        return false;
    } else {
        return true;
    }
}

Droppable::~Droppable() {
    SDL_DestroyTexture(texture);
}
