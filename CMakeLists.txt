cmake_minimum_required (VERSION 2.8)
project(cmake_test)

add_definitions( -DLINUX )

include_directories(
  $ENV{BHAND_INCLUDE_DIR}
)

link_directories(
  $ENV{HOME}/BHand/API/lib
)

add_executable(cmake_test 
  src/main.cpp
)

target_link_libraries(cmake_test 
  BHand
)
