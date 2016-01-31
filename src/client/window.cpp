#include <sstream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <arg3log/log.h>
#include "window.h"
#include "graphics.h"
#include "exception.h"
#include "dungeon.h"

using namespace std;

#define PI 3.141592653589793238463
#define TWOPI (2.0 * PI)
#define DARK_COLOR 0
#define LIGHT_COLOR 1

namespace arg3
{
    namespace graphics
    {
        double deg2rad(double degrees)
        {
            return (degrees * PI / 180);
        }
        double rad2deg(double degrees)
        {
            return (degrees * 180 / PI);
        }
        game_config::game_config_s()
        {
            // viewport
            screen_width = 640;
            screen_height = 480;

            map_width = 32;
            map_height = 24;

            cell_size = 64;

            proj_plane_dist = 277.;
        }

        player::player_s()
        {
            x = 96.;
            y = 130.;
            rot = 30. * PI / 180.;
            rot_dir = 0;
            move_dir = 0;
            move_speed = 18.;
            rot_speed = 6. * PI / 180;
        }

        window::window()
        {
            screen = nullptr;
            renderer_ = nullptr;

            running_ = true;

            config = game_config();

            start_time = 0;
            last_time = 0;
        }

        window::~window()
        {
            cleanup();
        }
        bool window::is_valid() const
        {
            return running_;
        }
        void window::update()
        {
            while (SDL_PollEvent(&event_)) {
                on_event(&event_);
            }

            SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

            SDL_RenderClear(renderer_);

            move_player();

            raycast();

            render();
        }

        void window::cleanup()
        {
            if (renderer_) {
                SDL_DestroyRenderer(renderer_);
            }
            if (screen) {
                SDL_DestroyWindow(screen);
            }

            screen = nullptr;
            renderer_ = nullptr;

            SDL_Quit();
        }

        bool window::init()
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                log::error("%s", SDL_GetError());
                return false;
            }

            uint16_t width = config.screen_width;
            uint16_t height = config.screen_height;

            screen = SDL_CreateWindow("DLM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                      // use opengl??
                                      SDL_WINDOW_RESIZABLE);

            if (screen == nullptr) {
                log::error("%s", SDL_GetError());
                return false;
            }

            renderer_ = SDL_CreateRenderer(screen, -1,
#ifdef __APPLE__
                                           SDL_RENDERER_SOFTWARE
#else
                                           0
#endif
                                           );

            if (renderer_ == nullptr) {
                log::error("%s", SDL_GetError());
                return false;
            }

            load_level();

            start_time = SDL_GetTicks();

            return true;
        }

        void window::on_event(SDL_Event* event)
        {
            if (event->type == SDL_QUIT) {
                running_ = false;
                return;
            } else if (event->type == SDL_KEYDOWN) {
                switch (event->key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running_ = false;
                        return;
                    case SDLK_a:
                    case SDLK_LEFT:
                        player.rot_dir = 1.;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        player.rot_dir = -1.;
                        break;
                    case SDLK_w:
                    case SDLK_UP:
                        player.move_dir = 1.;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        player.move_dir = -1.;
                        break;
                    default:
                        break;
                }

            } else if (event->type == SDL_KEYUP) {
                switch (event->key.keysym.sym) {
                    case SDLK_a:
                    case SDLK_d:
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        player.rot_dir = 0;
                        break;
                    case SDLK_w:
                    case SDLK_s:
                    case SDLK_UP:
                    case SDLK_DOWN:
                        player.move_dir = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        void window::draw_vert_line(int x, int y, int h, int color_mode)
        {
            if (color_mode) {
                SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer_, x, y, x, y + h);
            }
        }

        float window::cast_single_ray(double ray_angle)
        {
            // first make sure the angle is between 0 and 360 degrees
            ray_angle = fmod(ray_angle, TWOPI);
            if (ray_angle < 0) {
                ray_angle += TWOPI;
            }
            int right = (ray_angle > TWOPI * 0.75) || (ray_angle < TWOPI * 0.25);
            int up = ray_angle < PI;
            double tan_angle = tan(ray_angle);

            float dx, dy;
            float x, y;
            int map_x;
            int map_y;
            float dist = 0;

            // Vertical lines
            if (right) {
                x = floor(player.x / config.cell_size) * config.cell_size + config.cell_size;
            } else {
                x = floor(player.x / config.cell_size) * config.cell_size - 1;
            }
            y = player.y + (player.x - x) * tan_angle;
            map_x = x / config.cell_size;
            map_y = y / config.cell_size;
            dx = right ? config.cell_size : -config.cell_size;
            dy = up ? -config.cell_size * std::abs(tan_angle) : config.cell_size * std::abs(tan_angle);
            while (x >= 0 && x < config.map_width * config.cell_size && y >= 0 && y < config.map_height * config.cell_size) {
                if (map[map_y][map_x] > 0) {
                    break;
                }
                x += dx;
                y += dy;
                map_x = x / config.cell_size;
                map_y = y / config.cell_size;
            }
            dist = sqrt((player.x - x) * (player.x - x) + (player.y - y) * (player.y - y));

            // Horizontal lines
            if (up) {
                y = floor(player.y / config.cell_size) * config.cell_size - 1;
            } else {
                y = floor(player.y / config.cell_size) * config.cell_size + config.cell_size;
            }
            x = player.x + (player.y - y) / tan_angle;
            map_x = x / config.cell_size;
            map_y = y / config.cell_size;
            dy = up ? -config.cell_size : config.cell_size;
            dx = right ? config.cell_size / std::abs(tan_angle) : -config.cell_size / std::abs(tan_angle);
            while (x >= 0 && x < config.map_width * config.cell_size && y >= 0 && y < config.map_height * config.cell_size) {
                if (map[map_y][map_x] > 0) {
                    break;
                }
                x += dx;
                y += dy;
                map_x = x / config.cell_size;
                map_y = y / config.cell_size;
            }

            dist = std::min(dist, sqrt((player.x - x) * (player.x - x) + (player.y - y) * (player.y - y)));
            dist = dist * cos(player.rot - ray_angle);

            return (float)config.cell_size / dist * config.proj_plane_dist;
        }

        void window::raycast()
        {
            float proj_slice_height;
            float dangle = 60.0 * PI / 180.0 / config.screen_width;

            for (int x = 0; x < config.screen_width; x++) {
                float ray_angle = player.rot + 30. * PI / 180. - dangle * x;
                proj_slice_height = cast_single_ray(ray_angle);

                int y1 = config.screen_height / 2 - proj_slice_height / 2;
                int y2 = config.screen_height / 2 + proj_slice_height / 2;

                y1 = std::min(y1, config.screen_height);
                y2 = std::min(y2, config.screen_height);

                if (y1 >= config.screen_height) {
                    y1 = config.screen_height - 1;
                }
                if (y2 >= config.screen_height) {
                    y2 = config.screen_height - 1;
                }
                if (y1 < 0) {
                    y1 = 0;
                }
                if (y2 < 0) {
                    y2 = 0;
                }

                draw_vert_line(x, 0, y1, DARK_COLOR);
                draw_vert_line(x, y1, y2 - y1, LIGHT_COLOR);
                draw_vert_line(x, y2, config.screen_height - y2, DARK_COLOR);
            }
        }

        int window::is_blocking(float x, float y) const
        {
            if (y < 0 || y >= config.map_height * config.cell_size || x < 0 || x >= config.map_width * config.cell_size) {
                return 1;
            }
            if (map[(int)floor(y / config.cell_size)][(int)floor(x / config.cell_size)] != 0) {
                return 1;
            }

            return 0;
        }

        void window::move_player()
        {
            float move_step = player.move_dir * player.move_speed;

            player.rot += player.rot_dir * player.rot_speed;

            while (player.rot < 0) {
                player.rot += TWOPI;
            }
            while (player.rot >= TWOPI) {
                player.rot -= TWOPI;
            }

            float newx = player.x + cos(player.rot) * move_step;
            float newy = player.y - sin(player.rot) * move_step;

            if (is_blocking(newx, newy)) {
                return;
            }

            player.x = newx;
            player.y = newy;
        }

        void window::render()
        {
            SDL_RenderPresent(renderer_);
            SDL_Delay(1000 / 30);
        }

        bool window::load_level()
        {
            game::dungeon d;

            if (!d.generate(config.map_width, config.map_height, 100)) {
                log::error("unable to generate dungeon!");
            }

            map = d.to_map();

            std::fstream f("dungeon.txt");

            f << d.to_string();

            cout << d.to_string();

            f.close();

            player = graphics::player();

            log::debug("level loaded... (%d)", map.size());

            return true;
        }
    }
}
