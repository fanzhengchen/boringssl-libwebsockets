
cmake_minimum_required(VERSION 3.4.1)

project(libwebsockets)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(lib_dir ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})

find_library( # Sets the name of the path variable.
              log-lib
              log )

add_library(ssl STATIC IMPORTED)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${lib_dir}/libssl.a)

add_library(crypto STATIC IMPORTED)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${lib_dir}/libcrypto.a)

add_library(websockets SHARED IMPORTED)
set_target_properties(websockets PROPERTIES IMPORTED_LOCATION ${lib_dir}/libwebsockets.so)

add_library(native SHARED register.h register.cpp native.cpp native.h)
target_link_libraries(native ssl crypto websockets log)

#add_library(websocket SHARED websocket.h websocket.cpp register.cpp register.h)
#target_link_libraries(websocket ssl crypto websockets log)