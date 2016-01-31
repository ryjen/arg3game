#include "window.h"
#include <arg3log/log.h>


int main(int argc, char *argv[])
{
    arg3::log::set_min_log_level(arg3::LOG_TRACE);

    arg3::graphics::window window;

    if (!window.init()) {
        arg3::log::error("unable to init window!");
    }

    while (window.is_valid()) {
        window.update();
    }

    window.cleanup();

    return EXIT_SUCCESS;
}
