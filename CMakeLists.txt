cmake_minimum_required(VERSION 3.8)
project(RPiCameraMultiplexer)

set(CMAKE_CXX_STANDARD 11)

include_directories("include/")
include_directories("/usr/local/include/")
include_directories("/usr/local/include/opencv")
include_directories("/usr/local/include/opencv2")
link_directories("/usr/local/lib")


######################################Include everuthing src##################################
file(GLOB_RECURSE RPiCameraMultiplexer_SOURCES "src/*.cpp")
file(GLOB_RECURSE RPiCameraMultiplexer_HEADERS "src/*.h")

set (RPiCameraMultiplexer_INCLUDE_DIRS "include/")
foreach (_headerFile ${RPiCameraMultiplexer_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND RPiCameraMultiplexer_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES RPiCameraMultiplexer_INCLUDE_DIRS)
##############################################################################################

add_executable(RPiCameraMultiplexer ${RPiCameraMultiplexer_SOURCES})
target_include_directories(RPiCameraMultiplexer PRIVATE ${RPiCameraMultiplexer_INCLUDE_DIRS})

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

### Raspicam
target_link_libraries(RPiCameraMultiplexer opencv_imgcodecs)
target_link_libraries (RPiCameraMultiplexer raspicam)
target_link_libraries (RPiCameraMultiplexer raspicam_cv)
#target_link_libraries (RPiCameraMultiplexer mmal)
#target_link_libraries (RPiCameraMultiplexer mmal_core)
#target_link_libraries (RPiCameraMultiplexer mmal_util)

### WiringPi
target_link_libraries(RPiCameraMultiplexer wiringPi)
