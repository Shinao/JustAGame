cmake_minimum_required (VERSION 2.6)

# C++ 11 because why not
# FULL WARNINGS BECAUSE I LIKE PAIN !
list (APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -pthread")


set (INC_DIR
  include/
  )

include_directories (${INC_DIR})

project (network)
add_library(network SHARED "network/Network.cpp")
target_link_libraries (network sfml-graphics)
target_link_libraries (network sfml-window)
target_link_libraries (network sfml-network)
target_link_libraries (network sfml-system)

# project (plugin)
# add_library(plugin SHARED "plugin/plugin.cpp")
# target_link_libraries (plugin network)

project (client)
add_executable (client "src/client.cpp")

# Link libraries
target_link_libraries (client network)
target_link_libraries (client sfml-graphics)
target_link_libraries (client sfml-window)
target_link_libraries (client sfml-network)
target_link_libraries (client sfml-system)
