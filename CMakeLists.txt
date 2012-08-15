CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(crawler)

add_subdirectory(lib)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(
  ${engineworks_SOURCE_DIR}/include
  ${SDL_INCLUDE_DIR}
)

file(GLOB SOURCES src/*.cpp src/util/*.cpp)
list(APPEND CMAKE_CXX_FLAGS -std=c++0x)
add_executable(crawler ${SOURCES})

target_link_libraries(crawler engineworks ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})
