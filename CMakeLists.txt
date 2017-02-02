cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rpath ./lib")
endif()

project(demon)

set(FMOD_LIBS fmod fmodstudio)
set(SFML_LIBS sfml-graphics sfml-window sfml-system)

include_directories("include", "include/FMOD")

link_directories("lib")

file (GLOB SOURCES "src/*.cpp")

add_executable(demon ${SOURCES})

target_link_libraries(demon ${FMOD_LIBS} ${SFML_LIBS})
