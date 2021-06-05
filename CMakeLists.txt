cmake_minimum_required( VERSION 3.7 )

project( Izola )

set(SDL2_DIR "include/SDL2") #Here put the path to your SDL2
set(SDL2_image_DIR "include/SDL2_image") #Here put the path to your SDL2

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# On MacOS clang complains if this is not set
set (CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(headers)

include_directories(${SDL2_INCLUDE_DIRS}/include)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS}/include)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})