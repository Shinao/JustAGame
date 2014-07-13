cmake_minimum_required (VERSION 2.6)

# The only things you probably want to change is :
# SRC Client/Server if you have an implementation Windows/Linux
# Linked libraries if you have additional libraries (Box2D/...)

# Get the name of the game (FOLDER NAME)
get_filename_component (GAME_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string (REPLACE " " "_" GAME_NAME ${GAME_NAME})



# Include
set (INCLUDES client/include server/include include)
include_directories (${INCLUDES})

set (GAME_CLIENT "${GAME_NAME}_client")
set (GAME_SERVER "${GAME_NAME}_server")



### Project Client
project (${GAME_CLIENT})

# Source
file (GLOB_RECURSE GAME_CLIENT_SRC client/src/*.cpp) 
file (GLOB_RECURSE GAME_CLIENT_BASE_SRC ../client/src/*.cpp)
list (APPEND GAME_CLIENT_SRC ${GAME_CLIENT_BASE_SRC})

# Create Shared Library
add_library (${GAME_CLIENT} SHARED ${GAME_CLIENT_SRC})

# Link Libraries
target_link_libraries (${GAME_CLIENT} sfml-graphics)
target_link_libraries (${GAME_CLIENT} sfml-system)
target_link_libraries (${GAME_CLIENT} sfml-window)
target_link_libraries (${GAME_CLIENT} gui)
target_link_libraries (${GAME_CLIENT} network)
target_link_libraries (${GAME_CLIENT} system)



### Project Server
project (${GAME_SERVER})

# Source
file (GLOB_RECURSE GAME_SERVER_SRC server/src/*.cpp) 
list (APPEND GAME_SERVER_SRC ../server/src/*.cpp) 

# Create Shared Library
add_library (${GAME_SERVER} SHARED ${GAME_SERVER_SRC})

# Link Libraries
target_link_libraries (${GAME_SERVER} network)
target_link_libraries (${GAME_SERVER} system)
