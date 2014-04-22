cmake_minimum_required (VERSION 2.6)

# C++ 11 because why not
# FULL WARNINGS BECAUSE I LIKE PAIN !
list (APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -pthread -g")

# Include directories
set (INC_DIR
  Client/include
  Network/include
  GUI/include
  SimpleIni/
  )

include_directories (${INC_DIR})

# Library network
project (network)
file (GLOB_RECURSE NETWORK_SRC Network/src/*.cpp) 
add_library(network SHARED ${NETWORK_SRC})
# Link SFML & Posix Thread
target_link_libraries (network sfml-network)
target_link_libraries (network sfml-system)
target_link_libraries (network pthread)

# Library GUI
project (gui)
file (GLOB_RECURSE GUI_SRC GUI/src/*.cpp) 

# Specific implementation Windows/Linux
if (WIN32)
  file (GLOB_RECURSE SRC_UNIX GUI/src/Unix/*.cpp) 
  list (REMOVE_ITEM GUI_SRC ${SRC_UNIX})
else (WIN32)
  file (GLOB_RECURSE SRC_WIN GUI/src/Win32/*.cpp) 
  list (REMOVE_ITEM GUI_SRC ${SRC_WIN})
endif (WIN32)

add_library(gui SHARED ${GUI_SRC})
# Link SFML
target_link_libraries (gui sfml-graphics)
target_link_libraries (gui sfml-system)
target_link_libraries (gui sfml-window)


# Client - JustAGame
project (justagame)
file (GLOB_RECURSE CLIENT_SRC Client/src/*.cpp) 
add_executable (justagame ${CLIENT_SRC})

# Link libraries
target_link_libraries (justagame gui)
target_link_libraries (justagame network)
