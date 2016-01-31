#include "game.h"
#include "area.h"
#include "server.h"


int main(int argc, char *argv[])
{
    arg3::log::set_min_log_level(arg3::LOG_TRACE);

    return arg3::game::game::instance()->run();
}
