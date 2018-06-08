
add_definitions(-DTEST_SUPER_MARKET)

include_directories(../inc)
if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 14)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

add_executable(SuperMarket Product.cpp Catalog.cpp Store.cpp SuperMarket.cpp) 
