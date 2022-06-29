#
# Copyright 2017 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.4.1)
project(invideo)

### INCLUDE OBOE LIBRARY ###

# Set the path to the Oboe library directory
set (OBOE_DIR ../../../../../)

# Add the Oboe library as a subproject. Since Oboe is an out-of-tree source library we must also
# specify a binary directory
add_subdirectory(${OBOE_DIR} ./oboe)

# Include the Oboe headers and shared sample code
include_directories (${OBOE_DIR}/include ${OBOE_DIR}/samples/shared)

### Include directories of oboe required for building muses module ###
### --- MUSES start --- ###

include_directories (${OBOE_DIR}/src/flowgraph)

### --- MUSES end --- ###

### END OBOE INCLUDE SECTION ###


# Include Muses Library specific sources .cpp files
### --- MUSES start --- ###

set (LIB_SOURCES
    jni_audio_resampler.cpp
)

### --- MUSES end --- ###

# Build the libhello-oboe library
add_library(invideo SHARED ${LIB_SOURCES})

# Specify the libraries needed for muses
target_link_libraries(invideo android log oboe)
