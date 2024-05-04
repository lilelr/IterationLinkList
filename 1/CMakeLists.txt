set(CMAKE_CXX_STANDARD 20)

message( ${CMAKE_CURRENT_SOURCE_DIR})
message(${PROJECT_SOURCE_DIR})
#设置cmake时要include的文件路径
include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

#指定要链接的文件目录(这里并未执行链接)。因为lib下的.a文件都make过了，所以只需要链接一下即可。
link_directories(
        ${PROJECT_SOURCE_DIR}/lib
)


add_executable(index_pq main.cpp index_pq.hpp my_integer.hpp)
target_link_libraries(index_pq gtest)

add_executable(indexed_priority_queue_min_heap indexed_priority_queue_min_heap.cpp)
