cmake_minimum_required(VERSION 3.1.3)
project(img_blend)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV 4 REQUIRED)
include_directories( 
    include
    ${OpenCV_INCLUDE_DIRS}  
)
aux_source_directory(src DIR_SRCS)
add_library(SRC ${DIR_SRCS})
add_executable(main main.cpp )
target_link_libraries(main
    ${OpenCV_LIBS}  
    SRC
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})




    