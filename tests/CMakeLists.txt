
include_directories(../inc)
if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 14)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

add_executable(TestSuperMarket ProductTest.cpp InventoryTest.cpp StoreTest.cpp ShoppingCartTest.cpp main.cpp) 
target_link_libraries(TestSuperMarket MyStore)

enable_testing()
add_test(TestStore TestSuperMarket)

