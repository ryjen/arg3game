enable_testing()

include_directories(. vendor/bandit ${CMAKE_SOURCE_DIR}/src)

add_executable(test_game currency.test.cpp db.test.cpp main.test.cpp player.test.cpp script.test.cpp util.test.cpp)

target_link_libraries(test_game arg3game boost_system mongoclient)

add_dependencies(test_game arg3game)

add_test(game_test ${CMAKE_CURRENT_BINARY_DIR}/dlm_test)
