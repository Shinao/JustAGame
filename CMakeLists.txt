cmake_minimum_required (VERSION 2.6)

# C++11 because Vive la Revolution!
# FULL WARNINGS BECAUSE I LIKE PAIN !
list (APPEND CMAKE_CXX_FLAGS "-std=gnu++0x -Wall -Wextra -pthread")


### Include directories
set (INC_DIR
  include/Client
  include/Server
  include/Network
  include/GUI
  include/SimpleIni
  Games/client/include
  Games/server/include
  )


# Specific include Windows/Linux
if (WIN32)
  list (APPEND INC_DIR include/LibraryLoader/Win32)
else (WIN32)
  list (APPEND INC_DIR include/LibraryLoader/Unix)
endif (WIN32)

include_directories (${INC_DIR})



### Library network
project (network)
file (GLOB_RECURSE NETWORK_SRC src/Network/*.cpp) 
add_library (network SHARED ${NETWORK_SRC})
# Link SFML & Posix Thread
target_link_libraries (network sfml-network)
target_link_libraries (network sfml-system)
target_link_libraries (network sfml-graphics)
target_link_libraries (network pthread)



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



### Library Loader
project (libraryloader)
# Specific implementation Windows/Linux
if (WIN32)
  file (GLOB_RECURSE SRC_LIBRARYLOADER src/LibraryLoader/Win32/*.cpp) 
else (WIN32)
  file (GLOB_RECURSE SRC_LIBRARYLOADER src/LibraryLoader/Unix/*.cpp) 
endif (WIN32)
add_library (libraryloader SHARED ${SRC_LIBRARYLOADER})



### Client - JustAGame
project (justagame)
file (GLOB_RECURSE CLIENT_SRC src/Client/*.cpp) 
add_executable (justagame ${CLIENT_SRC})

# Link libraries
target_link_libraries (justagame gui)
target_link_libraries (justagame network)
target_link_libraries (justagame libraryloader)



### Server - JustAGame
project (server)
file (GLOB_RECURSE SERVER_SRC src/Server/*.cpp) 
add_executable (server ${SERVER_SRC})

# Link libraries
target_link_libraries (server network)
target_link_libraries (server libraryloader)



### Games
# Search for all CMakeLists.txt in Games and add them to our calling process
FILE (GLOB_RECURSE CMAKEFILES Games/CMakeLists.txt)
FOREACH (file_path ${CMAKEFILES})
  GET_FILENAME_COMPONENT (dir_path ${file_path} PATH)
  add_subdirectory (${dir_path})
ENDFOREACH ()
