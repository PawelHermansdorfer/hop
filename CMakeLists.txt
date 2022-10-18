# Base
cmake_minimum_required(VERSION 3.5)
project(main VERSION 1.0 LANGUAGES C)

# compile_commands for clang lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add project files
file(GLOB PROJECT_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

# project files
add_executable(${PROJECT_NAME} ${PROJECT_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

# OpenGl
find_package(OpenGL REQUIRED)

# SDL
find_package(SDL2 CONFIG REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Linking
target_link_libraries(${PROJECT_NAME} 
                      ${OPENGL_LIBRARY}
                      ${SDL2_LIBRARIES}
                      )

