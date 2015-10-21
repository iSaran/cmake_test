cmake_minimum_required (VERSION 2.6)

project(cmake_test)

add_definitions( -DLINUX )

add_executable(cmake_test 
  src/main.cpp
)

include_directories(
  $ENV{BHAND_INCLUDE_DIR}
)

link_directories(
  $ENV{BHAND_INCLUDE_DIR}/lib
)

target_link_libraries(cmake_test
  /home/iason/code/BHand/API/lib/libBHand.a
)


