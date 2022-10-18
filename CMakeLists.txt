# Base
cmake_minimum_required(VERSION 3.5)
project(main VERSION 1.0 LANGUAGES C)

# compile_commands for clang lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add project files
file(GLOB PROJECT_FILES ${PROJECT_SOURCE_DIRECTORY}/src/*.c)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIRECTORY}/src/*.h )

# project files
add_executable(${PROJECT_NAME} ${PROJECT_FILES} ${HEADER_FILES})

# OpenGl
find_package(OpenGL REQUIRED)

# SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Linking
target_link_libraries(${PROJECT_NAME} 
                      ${OPENGL_LIBRARY}
                      ${SDL2_LIBRARIES}
                      )

