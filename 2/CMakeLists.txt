#设置cmake时要include的文件路径
include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

#指定要链接的文件目录(这里并未执行链接)。因为lib下的.a文件都make过了，所以只需要链接一下即可。
link_directories(
        ${PROJECT_SOURCE_DIR}/lib
)


add_executable(graph_main main.cpp graph.hpp)
target_link_libraries(graph_main gtest)
