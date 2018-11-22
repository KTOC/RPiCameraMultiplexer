#!/usr/bin/env bash

cd ../build/
cmake ..
make -j4
./RPiCameraMultiplexer