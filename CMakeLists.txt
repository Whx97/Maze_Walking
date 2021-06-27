cmake_minimum_required(VERSION 3.11)
project(Astar)

set(CMAKE_CXX_STANDARD 11)

# 编译的可执行文件存放路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 子目录下的所有 CMakeLists 所在路径
add_subdirectory(src)