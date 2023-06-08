cmake_minimum_required(VERSION 3.10)
#项目名：Client
project(rtspServer C CXX)

# set (CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

INCLUDE(FindPkgConfig)
##
# Find FFmpeg include directories and link libraries.
# define FFMPEG_LIBRARIES and FFMPEG_INCLUDE_DIRS
##
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}"/Modules)
# set(SDL2MAIN_LIBRARY "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/Modules)
message("CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

# find_package(SDL2 REQUIRED)
find_package(FFMPEG REQUIRED)
# include_directories(${FFMPEG_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR})
include_directories(${FFMPEG_INCLUDE_DIRS})

message("FFMPEG_INCLUDE_DIRS: " ${FFMPEG_INCLUDE_DIRS})


set(ROOT ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${ROOT}/bin)

# 指定头文件目录
include_directories(${ROOT}/include)

#生成动态库.so文件，默认在lib文件夹中
add_library(rtp SHARED ${ROOT}/src/rtp.cc)
add_library(H264 SHARED ${ROOT}/src/H264.cc)
add_library(AAC SHARED ${ROOT}/src/AAC.cpp)
add_library(Utils SHARED ${ROOT}/src/Utils.cpp)

#添加可执行程序
add_executable(${PROJECT_NAME} ${ROOT}/src/main.cc ${ROOT}/src/rtsp.cc)

#连接，将动态库链接到可执行文件
target_link_libraries(${PROJECT_NAME} rtp H264 AAC Utils ${FFMPEG_LIBRARIES})
# target_link_libraries(FFmpeg_Example PRIVATE ${FFMPEG_LIBRARIES})
