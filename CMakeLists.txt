cmake_minimum_required(VERSION 3.8)
project(RPiCameraMultiplexer)

set(CMAKE_CXX_STANDARD 11)

include_directories("include/")
include_directories("/usr/local/include/opencv")
include_directories("/usr/local/include/opencv2")
link_directories("/usr/local/lib")

set(SOURCE_FILES main.cpp)
add_executable(RPiCameraMultiplexer ${SOURCE_FILES})

### OpenCV
target_link_libraries(RPiCameraMultiplexer opencv_core)
target_link_libraries(RPiCameraMultiplexer opencv_imgproc)
target_link_libraries(RPiCameraMultiplexer opencv_highgui)
target_link_libraries(RPiCameraMultiplexer opencv_ml)
target_link_libraries(RPiCameraMultiplexer opencv_videoio)
target_link_libraries(RPiCameraMultiplexer opencv_features2d)
target_link_libraries(RPiCameraMultiplexer opencv_calib3d)
target_link_libraries(RPiCameraMultiplexer opencv_objdetect)
target_link_libraries(RPiCameraMultiplexer opencv_stitching)

### WiringPi
target_link_libraries(RPiCameraMultiplexer wiringPi)
