set(CMAKE_CXX_STANDARD 17)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# // 添加库文件，test1，只是个命名，随便取
add_library(add
Astar.cpp
Map.cpp
)

# // 根据上面的命名，把所需库文件添加
link_libraries(add)

SET(CMAKE_BUILD_TYPE "Debug")     #// 固定
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")     #// 固定

# // 添加头文件，注意：PROJECT_SOURCE_DIR 的路径，为最外面的那个 CMakeLists 的路径
include_directories(${PROJECT_SOURCE_DIR}/include/Astar)

# // 需要编译的库文件，第一个参数 runtest 即为最后编译的可执行文件名字
add_executable( runtest ${PROJECT_SOURCE_DIR}/test/runtest.cpp)