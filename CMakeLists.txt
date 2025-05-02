cmake_minimum_required(VERSION 3.27)
set(PROJECT kof)
project(${PROJECT})

# Toolchain do vcpkg
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

# Add global definitions
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADER_FILES "src/*.h" "src/*.l" )

add_executable(${PROJECT} ${SOURCE_FILES} ${HEADER_FILES})

message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions("-g -O0 -Wall -Wextra -Wpedantic")
    add_definitions("-fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

find_package(PkgConfig REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(PNG REQUIRED)
find_package(WavPack REQUIRED)
find_package(Vorbis REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

target_compile_options(${PROJECT} PRIVATE -Wall -Wextra -Wpedantic)
include_directories(
    src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_GFX_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_LIBRARY_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLESV2_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
    ${WAVPACK_INCLUDE_DIRS}
    ${VORBIS_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include
)

link_directories(
    ${SDL2_LIBRARY_DIRS}
    ${SDL2_IMAGE_LIBRARY_DIRS}
    ${SDL2_GFX_LIBRARY_DIRS}
    ${SDL2_TTF_LIBRARY_DIRS}
    ${SDL2_MIXER_LIBRARY_DIRS}
    ${GLEW_LIBRARY_DIRS}
    ${GLESV2_LIBRARY_DIRS}
    ${PNG_LIBRARY_DIRS}
    ${WAVPACK_LIBRARY_DIRS}
    ${VORBIS_LIBRARY_DIRS}
    ${FREETYPE_CFLAGS_OTHER}
    ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib
)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf-static
    SDL2_image::SDL2_image-static
    SDL2_mixer::SDL2_mixer-static
    SDL2::SDL2_gfx
    GLEW::glew_s
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()