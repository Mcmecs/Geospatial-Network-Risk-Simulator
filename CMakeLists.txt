cmake_minimum_required(VERSION 3.14)
project(GeospatialNetworkRiskSim CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") 

include_directories(include)

# add_executable(geo_risk_app src/main.cpp src/graph.cpp src/quadtree.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(graphs_tests tests/test_graph.cpp src/graph.cpp) 
target_link_libraries(graphs_tests GTest::gtest_main)

add_executable(quadtree_tests tests/test_quadtree.cpp src/quadtree.cpp) 
target_link_libraries(quadtree_tests GTest::gtest_main)

include(GoogleTest) 
gtest_discover_tests(graphs_tests) 
gtest_discover_tests(quadtree_tests)

# FetchContent_Declare(
#     pybind11
#     GIT_REPOSITORY http://github.com/pybind/pybind11.git
#     GIT_TAG        v2.11.1
# )
# FetchContent_MakeAvailable(pybind11)

# pybind11_add_module(geo_risk_ext src/bindings.cpp)
