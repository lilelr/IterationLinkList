cmake_minimum_required(VERSION 3.10)
project(IterationLinkList)

set(CMAKE_CXX_STANDARD 20)

message( ${CMAKE_CURRENT_SOURCE_DIR})
#设置cmake时要include的文件路径
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#指定要链接的文件目录(这里并未执行链接)。因为lib下的.a文件都make过了，所以只需要链接一下即可。
link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_subdirectory(1)
add_subdirectory(2)
add_subdirectory(3)

#设置要编译的文件的名称，即src下面所有的.cpp文件都需要编译，他们整体取了个名字叫src_files
#file(GLOB_RECURSE src_files
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
#)

#将上述的src_files添加到可执行文件里，生产的可执行文件叫${PROJECT_NAME}。固定写法
#add_executable(${PROJECT_NAME} ${src_files})

#告诉gcc去gtest这个目录(即link_directories)寻找lib库。(gtest这个名字是gcc取的)

add_executable(IterationLinkList main.cpp myInteger.hpp myList.cpp myList.hpp)
target_link_libraries(IterationLinkList gtest)
