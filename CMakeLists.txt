cmake_minimum_required(VERSION 3.1.3)
project(Kalman)


find_package(OpenCV 4 REQUIRED)
find_package(Ceres REQUIRED)
include_directories( include
                    ${OpenCV_INCLUDE_DIRS} 
                    /usr/local/include/   
                    /usr/include/python3.10
)

aux_source_directory(src DIR_SRCS)
add_library(kalman ${DIR_SRCS})

add_executable(main main.cpp )


target_link_libraries(main
    ${OpenCV_LIBS}  
    ${CERES_LIBRARIES}
    kalman
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})




