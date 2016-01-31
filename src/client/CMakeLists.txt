
include_directories(${CMAKE_SOURCE_DIR}/src)

pkg_check_modules(SDL2 sdl2)

add_executable(gameclient main.cpp window.cpp)

target_link_libraries (gameclient ${LUA_LIBRARIES} ${ARG3_LIBRARIES} mongoclient boost_system ${SDL2_LIBRARIES})

