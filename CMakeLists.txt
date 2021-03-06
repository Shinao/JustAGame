cmake_minimum_required (VERSION 2.6)
# C++11 because Vive la Revolution!
# FULL WARNINGS BECAUSE I LIKE PAIN !
add_definitions ("-std=gnu++0x -g -Wall -Wextra")


### Include directories
set (INC_DIR
  include/
  Games/include/
  )


# Specific include Windows/Linux
if (WIN32)
  list (APPEND INC_DIR include/System/Win32)
else (WIN32)
  list (APPEND INC_DIR include/System/Unix)
endif (WIN32)

include_directories (${INC_DIR})


# ### Library Thor
# project (thor)
# file (GLOB_RECURSE THOR_SRC src/Thor/*.cpp) 
# add_library (thor SHARED ${THOR_SRC})
# # Link SFML
# target_link_libraries (thor sfml-system)
# target_link_libraries (thor sfml-graphics)



### Library network
project (network)
file (GLOB_RECURSE NETWORK_SRC src/Network/*.cpp) 
add_library (network SHARED ${NETWORK_SRC})
# Link SFML
target_link_libraries (network sfml-network)
target_link_libraries (network sfml-system)
target_link_libraries (network sfml-graphics)



### Library GUI
project (gui)
file (GLOB_RECURSE GUI_SRC src/GUI/*.cpp) 

# Specific implementation Windows/Linux
if (WIN32)
  file (GLOB_RECURSE SRC_UNIX src/GUI/Unix/*.cpp) 
  list (REMOVE_ITEM GUI_SRC ${SRC_UNIX})
else (WIN32)
  file (GLOB_RECURSE SRC_WIN src/GUI/Win32/*.cpp) 
  list (REMOVE_ITEM GUI_SRC ${SRC_WIN})
endif (WIN32)

add_library (gui SHARED ${GUI_SRC})
# Link SFML
target_link_libraries (gui sfml-graphics)
target_link_libraries (gui sfml-system)
target_link_libraries (gui sfml-window)
target_link_libraries (gui network)



### System
project (system)
file (GLOB SRC_SYSTEM src/System/*.cpp) 
# Specific implementation Windows/Linux
if (WIN32)
  file (GLOB_RECURSE SRC_SPECIFIC src/System/Win32/*.cpp) 
else (WIN32)
  file (GLOB_RECURSE SRC_SPECIFIC src/System/Unix/*.cpp) 
endif (WIN32)
list (APPEND SRC_SYSTEM ${SRC_SPECIFIC})
# list (APPEND SRC_SYSTEM ~/rep/JustAGame/src/System/*.cpp) 
add_library (system SHARED ${SRC_SYSTEM})



### Client - JustAGame
project (justagame)
file (GLOB_RECURSE CLIENT_SRC src/Client/*.cpp) 
add_executable (justagame ${CLIENT_SRC})

# Link libraries
target_link_libraries (justagame gui)
target_link_libraries (justagame network)
target_link_libraries (justagame system)



### Server - JustAGame
project (server)
file (GLOB_RECURSE SERVER_SRC src/Server/*.cpp) 
add_executable (server ${SERVER_SRC})

# Link libraries
target_link_libraries (server network)
target_link_libraries (server system)



### Games
# Search for all CMakeLists.txt in Games and add them to our calling process
FILE (GLOB_RECURSE CMAKEFILES Games/CMakeLists.txt)
FOREACH (file_path ${CMAKEFILES})
  GET_FILENAME_COMPONENT (dir_path ${file_path} PATH)
  add_subdirectory (${dir_path})
ENDFOREACH ()
