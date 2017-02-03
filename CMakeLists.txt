cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(demon)

set(FMOD_LIBS fmod fmodstudio)
set(SFML_LIBS sfml-graphics sfml-window sfml-system)

include_directories("include", "include/FMOD")

link_directories("lib")

file (GLOB SOURCES "src/*.cpp")

add_executable(demon ${SOURCES})

target_link_libraries(demon ${FMOD_LIBS} ${SFML_LIBS})
