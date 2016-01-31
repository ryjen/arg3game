#ifndef ARG3_GAME_CLIENT_WINDOW_H
#define ARG3_GAME_CLIENT_WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "graphics.h"

namespace arg3
{
    namespace graphics
    {
        class window
        {
           private:
            SDL_Window* screen;
            SDL_Renderer* renderer_;

            std::vector<std::vector<int> > map;

            uint32_t start_time;
            uint32_t last_time;

            game_config config;
            arg3::graphics::player player;
            bool running_;

            SDL_Event event_;

            int execute();
            bool load_level();
            void on_event(SDL_Event* event);
            void render();

            void raycast();

            int is_blocking(float x, float y) const;

            void draw_vert_line(int x, int y, int h, int color_mode);

            float cast_single_ray(double ray_angle);

            void move_player();

           public:
            window();
            ~window();
            bool init();
            void update();
            bool is_valid() const;
            void cleanup();
        };
    }
}

#endif
