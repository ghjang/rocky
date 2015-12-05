cmake_minimum_required(VERSION 3.3)
project(RockyTest)

set(BOOST_ROOT "../../../boost_1_59_0")
find_package(Boost 1.59.0)
if(Boost_FOUND)
    include_directories(${BOOST_ROOT})
else()
    message(FATAL_ERROR "Could not find boost!")
endif()

set(ROCKY_ROOT "../..")
include_directories(${ROCKY_ROOT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        main.cpp
        TupleSizeTest.cpp
        NthTupleTest.cpp
        HasMemberTest.cpp
        IdentityTest.cpp
        TypeSelectionTest.cpp
        ReverseTupleTest.cpp
        IntegralConstantUtilityTest.cpp
        PowerTest.cpp
        StringNumberConversionTest.cpp
        MultipleInheritance.cpp
        ForEachArgumentTest.cpp
        IntegerSequenceUtilityTest.cpp
        ForEachTupleTest.cpp
        TypeUtilityTest.cpp
        FoldTest.cpp
        TransformTupleTest.cpp
        CountTupleTest.cpp
        ConstExprArrayTest.cpp
        RemoveTupleTest.cpp
        ReplaceTupleTest.cpp
        FindTupleTest.cpp
        UniqueTupleTest.cpp
        VariantUtilityTest.cpp)

add_executable(RockyTest ${SOURCE_FILES})

