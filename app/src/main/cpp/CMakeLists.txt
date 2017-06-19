
cmake_minimum_required(VERSION 3.4.1)

project(libwebsockets)

include_directories(${PROJECT_SOURCE_DIR}/boringssl/include)
include_directories(${PROJECT_SOURCE_DIR}/libwebsockets/include)

set(lib_dir ${PROJECT_SOURCE_DIR}/lib/${ANDROID_ABI})

add_library( # Sets the name of the library.
             native-lib

             SHARED
             register.h
             register.cpp
             native-lib.cpp )


find_library( # Sets the name of the path variable.
              log-lib
              log )

add_library(ssl STATIC IMPORTED)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${lib_dir}/libssl.a)

add_library(crypto STATIC IMPORTED)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${lib_dir}/libcrypto.a)

add_library(websockets STATIC IMPORTED)
set_target_properties(websockets PROPERTIES IMPORTED_LOCATION ${lib_dir}/libwebsockets.a)

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ssl
                       crypto
                       websockets
                       ${log-lib} )