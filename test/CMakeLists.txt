cmake_minimum_required(VERSION 3.5)

project(pid_test CXX)

set(sources tests.cc)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  PID
  ${CONAN_LIBS})

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/../include)
