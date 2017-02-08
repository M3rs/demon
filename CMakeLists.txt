cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

project(demon)

set(FMOD_LIBS fmod fmodstudio)
set(SDL_LIBS SDL2)
set(LUA_LIBS lua)

include_directories("include", "include/FMOD", "include/Lua", "include/SDL")

link_directories("lib/FMOD", "lib/Lua", "lib/SDL")

file (GLOB SOURCES "src/*.cpp")

add_executable(demon ${SOURCES})

target_link_libraries(demon ${FMOD_LIBS} ${SDL_LIBS} ${LUA_LIBS})
