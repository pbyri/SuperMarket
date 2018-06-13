
include_directories(../inc)
if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 14)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()


add_library(MyStore Product.cpp Inventory.cpp Store.cpp ShoppingCart.cpp)
add_executable(SuperMarket SuperMarket.cpp) 
target_link_libraries(SuperMarket MyStore)
