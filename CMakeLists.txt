cmake_minimum_required (VERSION 2.6)

# 32 bits
# Thor dependencies
list (APPEND CMAKE_CXX_FLAGS "-std=c++0x -m32")

project (justagame)

set (INC_DIR
  include/
  )

include_directories (${INC_DIR})

file (GLOB_RECURSE CLIENT_SRC src/*.cpp) 

add_executable (justagame ${CLIENT_SRC})

target_link_libraries (justagame sfml-window)
target_link_libraries (justagame sfml-graphics)
target_link_libraries (justagame sfml-system)
target_link_libraries (justagame sfml-network)
target_link_libraries (justagame thor)
