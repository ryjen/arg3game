#ifndef ARG3_GAME_CLIENT_GRAPHICS_H
#define ARG3_GAME_CLIENT_GRAPHICS_H

#define WINDOW_X 100
#define WINDOW_Y 100
#define WIDTH 800
#define HEIGHT 600
#define DEPTH 32
#define PIXEL_SIZE 4
#define TEXTURE_SIZE WIDTH* HEIGHT
#define TEXTURE_BYTES_COUNT TEXTURE_SIZE* PIXEL_SIZE
#define PIXEL(X, Y) (Y * WIDTH + X)
#define MAX_FPS 60

#define COLOR(R, G, B, A) (R << 24 | G << 16 | B << 8 | A)

#define WINDOW_TITLE_FORMAT "Ray casting ({ENGINE}) FPS:{FPS_COUNT}"
#define FPS_COUNT_KEY "{FPS_COUNT}"
#define ENGINE_KEY "{ENGINE}"
#define ENGINE_CPU "CPU"
#define ENGINE_GPU "GPU"

#ifdef __CUDACC__

#ifndef HAS_GPU
#define HAS_GPU 1
#endif

#else

#ifndef HAS_GPU
#define HAS_GPU 0
#endif

#endif

namespace arg3
{
    namespace graphics
    {
        typedef struct player_s player;
        typedef struct game_config_s game_config;

        // math
        // TODO: move elsewhere
        double rad2deg(double degrees);
        double deg2rad(double degrees);

        template <typename T>
        struct vector2 {
            T x;
            T y;
        };


        template <typename T>
        struct vector3 {
            T x;
            T y;
            T z;
        };


        struct player_s {
            float x;
            float y;
            float rot;
            float move_dir;
            float rot_dir;
            float move_speed;
            float rot_speed;

            player_s();
        };


        struct game_config_s {
            uint8_t cell_size;

            float proj_plane_dist;

            int screen_height;
            int screen_width;

            uint16_t map_width;
            uint16_t map_height;

            game_config_s();
        };
    }
}
#endif