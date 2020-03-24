project(pid CXX)

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

enable_testing()
add_subdirectory(test)

add_library(PID src/PID.cpp)
target_include_directories(PID PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(sources src/main.cpp)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

include_directories(/usr/local/opt/openssl/include)
link_directories(/usr/local/opt/openssl/lib)
link_directories(/usr/local/Cellar/libuv/1*/lib)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 


add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} PID z ssl uv uWS)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
