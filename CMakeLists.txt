cmake_minimum_required(VERSION 2.8.3)
project(tf2_segv_reproduce)

find_package(catkin REQUIRED
  COMPONENTS
    roscpp
    tf
)

catkin_package(
  CATKIN_DEPENDS
    roscpp
    tf
)

find_package(Boost REQUIRED COMPONENTS chrono)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O1 -coverage")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1")


include_directories(${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} include)

add_executable(tf_listener_segv src/tf_listener.cpp)
target_link_libraries(tf_listener_segv ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(tf_broadcaster_segv src/tf_broadcaster.cpp)
target_link_libraries(tf_broadcaster_segv ${catkin_LIBRARIES} ${Boost_LIBRARIES})
