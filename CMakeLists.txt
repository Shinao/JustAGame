cmake_minimum_required (VERSION 2.6)

# 32 bits
# C++ 11 because why not
# FULL WARNINGS BECAUSE I LIKE PAIN !
list (APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")

project (justagame)

set (INC_DIR
  include/
  )

include_directories (${INC_DIR})

file (GLOB_RECURSE CLIENT_SRC src/*.cpp) 

if (WIN32)
  file (GLOB_RECURSE SRC_UNIX src/Unix/*.cpp) 
  list (REMOVE_ITEM CLIENT_SRC ${SRC_UNIX})
else (WIN32)
  file (GLOB_RECURSE SRC_WIN src/Win32/*.cpp) 
  list (REMOVE_ITEM CLIENT_SRC ${SRC_WIN})
endif (WIN32)

add_executable (justagame ${CLIENT_SRC})

target_link_libraries (justagame sfml-graphics)
target_link_libraries (justagame sfml-window)
target_link_libraries (justagame sfml-network)
target_link_libraries (justagame sfml-system)
