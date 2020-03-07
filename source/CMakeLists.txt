cmake_minimum_required (VERSION 2.6)
project (termfun)

set (CMAKE_CXX_STANDARD 14)
set (LOCAL_HEADERS "/usr/local/include/")
set (ANNIE_HEADERS "painting/")
include_directories ("${LOCAL_HEADERS}", "${ANNIE_HEADERS}")

set (LIB_SRC
  painting/Canvas.cpp)

add_library(annie_lib ${LIB_SRC})

add_executable(moving_dot apps/moving_dot/MovingDot.cpp)
add_executable(mean_guy apps/mean_guy/MeanGuy.cpp apps/mean_guy/main.cpp)

target_link_libraries(moving_dot annie_lib ncurses)
target_link_libraries(mean_guy annie_lib ncurses)
