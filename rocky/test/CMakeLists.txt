cmake_minimum_required(VERSION 3.3)
project(RockyTest)

set(ROCKY_ROOT "../..")
include_directories(${ROCKY_ROOT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        main.cpp
        TupleSizeTest.cpp
        NthTupleTypeTest.cpp
        HasTypeMemberTest.cpp
        IdentityTest.cpp
        TypeSelectionTest.cpp
        ReverseTupleTest.cpp
        IntegralConstantUtilityTest.cpp)

add_executable(RockyTest ${SOURCE_FILES})

