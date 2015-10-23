cmake_minimum_required (VERSION 2.8)
project(cmake_test)

add_definitions(-DLINUX)


## Change these paths if you have installed your software elsewhere
set(BHAND_INCLUDE_DIR $ENV{HOME}/BHand/API)
set(BHAND_LIBS_DIR $ENV{HOME}/BHand/API/lib)



## Find external libraries
find_library(
  BHAND_LIB BHand PATHS ${BHAND_LIBS_DIR}
)

include_directories(
  ${BHAND_INCLUDE_DIR}
)


add_executable(cmake_test
  src/main.cpp
)

message(STATUS ${BHAND_LIB})

target_link_libraries( cmake_test
  ${BHAND_LIB}
  pcan
  ctb-0.14
  PocoFoundation
)
