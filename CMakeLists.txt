cmake_minimum_required(VERSION 3.17)
project(Image_Proc)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(IMAGES_FOLDER ${CMAKE_SOURCE_DIR}/images)
set(FINAL_IMAGE_FOLDER ${CMAKE_SOURCE_DIR}/finalimage)


file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_BINARY_DIR})

find_package(OpenCV REQUIRED)

add_executable(Image_Proc main.cpp)

target_compile_definitions(Image_Proc PRIVATE IMAGES_FOLDER="${IMAGES_FOLDER}")
target_compile_definitions(Image_Proc PRIVATE FINAL_IMAGE_FOLDER="${FINAL_IMAGE_FOLDER}")
target_link_libraries(Image_Proc PRIVATE ${OpenCV_LIBS})
