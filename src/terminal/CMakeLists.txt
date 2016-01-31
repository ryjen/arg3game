
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(gameterm main.cpp color.cpp command.cpp connection.cpp connection_state.cpp game.cpp interpreter.cpp server.cpp)

target_link_libraries (gameterm arg3game ${LUA_LIBRARIES} ${ARG3_LIBRARIES} mongoclient boost_system)

