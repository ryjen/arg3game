
add_custom_target(external_runtime swig -lua -c++ -external-runtime swig.h)

find_package(swig REQUIRED)
include(${SWIG_USE_FILE})

set( SWIG_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/swig.h" )
set( SWIG_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/swig.cpp" )
set( SWIG_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/swig.i" )

set_source_files_properties(${SWIG_OUTPUT} PROPERTIES GENERATED TRUE)

add_custom_target(generate-swig
    COMMAND ${SWIG_EXECUTABLE} -c++ -lua -external-runtime ${SWIG_HEADER}.tmp
    COMMAND ${SWIG_EXECUTABLE} -c++ -lua -o ${SWIG_OUTPUT}.tmp ${SWIG_INPUT}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SWIG_HEADER}.tmp ${SWIG_HEADER}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SWIG_OUTPUT}.tmp ${SWIG_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E remove ${SWIG_HEADER}.tmp ${SWIG_OUTPUT}.tmp
)

include_directories(${OPENSSL_INCLUDE_DIRS})

add_library(arg3game SHARED account.cpp area.cpp character.cpp connection.cpp connection_state.cpp currency.cpp db.cpp dungeon.cpp entity.cpp exit.cpp location.cpp npc.cpp object.cpp player.cpp script.cpp util.cpp world.cpp swig.cpp server.cpp)

target_link_libraries (arg3game ${LUA_LIBRARIES} ${ARG3_LIBRARIES} mongoclient boost_system ${WEBSOCKETS_LIBRARIES})

add_dependencies(arg3game generate-swig)

add_subdirectory(client)
add_subdirectory(terminal)
