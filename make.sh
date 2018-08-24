#!/usr/bin/env bash
g++ main.cpp -o bin/camtest \
-I/usr/local/include/opencv \
-I/usr/local/include/opencv2 \
-L/usr/local/lib/ \
-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_videoio -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_stitching \
-lwiringPi
