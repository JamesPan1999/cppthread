cmake_minimum_required(VERSION 3.24)
project(class1)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)

find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS} )

add_executable(thread_basic
        thread_basic.cpp  )

target_link_libraries( thread_basic ${GLOG_LIBRARIES} pthread)

add_executable(smart_ptr_closure
        smart_ptr_closure.cpp)

target_link_libraries(smart_ptr_closure ${GLOG_LIBRARIES} pthread)