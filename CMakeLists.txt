cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project (arg3game) 


find_package(PkgConfig)

pkg_check_modules(WEBSOCKETS libwebsockets)
pkg_check_modules(LUA lua)
pkg_check_modules(ARG3 arg3db arg3format arg3log arg3str arg3net)
pkg_check_modules(OPENSSL openssl)

enable_testing()

add_subdirectory(src)

add_subdirectory(tests)

