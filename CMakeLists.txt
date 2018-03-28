CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(datamining_brainville_dumontier)

SET(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(include/)

FILE(GLOB data_src src/*)
FILE(GLOB data_h include/*)

ADD_EXECUTABLE(program ${data_src} ${data_h})
