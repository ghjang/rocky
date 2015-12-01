cmake_minimum_required(VERSION 3.3)
project(RockyTest)

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
        UniqueTupleTest.cpp)

add_executable(RockyTest ${SOURCE_FILES})

