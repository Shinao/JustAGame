cmake_minimum_required (VERSION 2.6)

# The only things you probably want to change is :
# GAME_CLIENT_SRC if you have an implementation Windows/Linux
# Linked libraries if you have additional libraries (Box2D/...)

# Get the name of the game (FOLDER NAME)
get_filename_component (GAME_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string (REPLACE " " "_" GAME_NAME ${GAME_NAME})

# Include
list (APPEND INCLUDES client/include)
include_directories (${INCLUDES})

### Project
project (${GAME_NAME})

# Source
file (GLOB_RECURSE GAME_CLIENT_SRC client/src/*.cpp) 
list (APPEND GAME_CLIENT_SRC ../client/src/*.cpp) 

# Create Shared Library
add_library (${GAME_NAME} SHARED ${GAME_CLIENT_SRC})

# Link Libraries
target_link_libraries (${GAME_NAME} sfml-graphics)
target_link_libraries (${GAME_NAME} sfml-system)
target_link_libraries (${GAME_NAME} sfml-window)
target_link_libraries (${GAME_NAME} gui)
target_link_libraries (${GAME_NAME} network)
