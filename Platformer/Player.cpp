#include <SDL2_image/SDL_image.h>

#include "Player.hpp"

#define SPEED 200.0f
#define JUMP_VELOCITY 13
#define GRAVITY 1

Player::Player(SDL_Renderer * render_target, string file_path, int x, int y) {
    texture = nullptr;
    SDL_Surface * surface = IMG_Load(file_path.c_str());
    texture = SDL_CreateTextureFromSurface(render_target, surface);
    
    SDL_FreeSurface(surface);
        
    position.x = 100;
    position.y = 30;
    
    position.w = position.h = 30;
    
    jumping = false;
    
    x_velocity = 0;
    y_velocity = 0;
    
    keys[0] = SDL_SCANCODE_LEFT;
    keys[1] = SDL_SCANCODE_RIGHT;
    keys[2] = SDL_SCANCODE_UP;
    keys[3] = SDL_SCANCODE_SPACE;
}

void Player::Update(float delta_time, const Uint8 * key_state, Map map) {
    int tile_position;
    
    bool left_collision;
    bool right_collision;
    
    if (key_state[keys[0]]) {
        x_velocity = -(SPEED * delta_time);
        
        if (!CheckHorizontalCollision(position.x + x_velocity, position.y, tile_position, map))
            position.x += x_velocity;
    }
    
    if (key_state[keys[1]]) {
        x_velocity = SPEED * delta_time;
        
        if (!CheckHorizontalCollision(position.x + x_velocity, position.y, tile_position, map))
            position.x += x_velocity;
    }
    
    if (key_state[keys[2]]) {
        position.y -= 20;
    }
    
    if (key_state[keys[3]] && !jumping){
        y_velocity = -JUMP_VELOCITY;
        jumping = true;
    }
    
    left_collision = CheckVerticalCollision(position.x, position.y + y_velocity, tile_position, map);
    right_collision = CheckVerticalCollision(position.x + position.w, position.y + y_velocity, tile_position, map);

    if (y_velocity < 0) {
        if (left_collision || right_collision) {
            y_velocity = 0;

        } else {
            position.y += y_velocity;
            y_velocity += GRAVITY;
        }
    } else {
        if (left_collision || right_collision) {
            y_velocity = 1;
            
            if (!key_state[3])
                jumping = false;
        } else {
            position.y += y_velocity;
            y_velocity += GRAVITY;
            
            if (y_velocity > TILE_SIZE)
                y_velocity = TILE_SIZE;
            
            jumping = true;
        }
    }
}

void Player::Draw(SDL_Renderer * render_target, SDL_Rect camera) {
    drawing = {position.x - camera.x, position.y - camera.y, position.w, position.h};
    
    SDL_RenderCopy(render_target, texture, NULL, &drawing);
}

bool Player::CheckHorizontalCollision(int x, int y, int &tile_y, Map map) {
    int tile_pixels_x = x - (x % TILE_SIZE);
    int test_end = x + position.w;
    
    tile_y = y / TILE_SIZE;
    
    int tile_x = tile_pixels_x / TILE_SIZE;
    
    while(tile_pixels_x <= test_end){
        if(map.CheckCollision(tile_x, tile_y))
            return true;
        
        tile_x++;
        tile_pixels_x += TILE_SIZE;
    }
    
    return false;
}

bool Player::CheckVerticalCollision(int x, int y, int &tile_x, Map map) {
    int tile_pixels_y = y - (y % TILE_SIZE);
    int test_end = y + position.h;
    
    tile_x = x / TILE_SIZE;
    
    int tile_y = tile_pixels_y / TILE_SIZE;
    
    while(tile_pixels_y <= test_end){
        if(map.CheckCollision(tile_x, tile_y))
            return true;
        
        tile_y++;
        tile_pixels_y += TILE_SIZE;
    }
    
    return false;
}

Player::~Player() {
    SDL_DestroyTexture(texture);
}