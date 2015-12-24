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

set(HEADER_FILES
        ../ConstExprArray.h
        ../StringNumberConversion.h
        ../VariantUtility.h
        ../math/Power.h
        ../math/Abs.h
        ../math/RatioString.h
        ../meta/CountTuple.h
        ../meta/FindTuple.h
        ../meta/Fold.h
        ../meta/ForEachArgument.h
        ../meta/ForEachTuple.h
        ../meta/HasMember.h
        ../meta/Identity.h
        ../meta/IntegerSequenceUtility.h
        ../meta/IntegralConstantUtility.h
        ../meta/MultipleInheritance.h
        ../meta/NthTuple.h
        ../meta/RemoveTuple.h
        ../meta/ReplaceTuple.h
        ../meta/ReverseTuple.h
        ../meta/TransformTuple.h
        ../meta/TupleSize.h
        ../meta/TypeSelection.h
        ../meta/TypeUtility.h
        ../meta/UniqueTuple.h
        ../meta/CharSequenceUtility.h
        ../wolca/StringUtility.h
        ../wolca/Range.h
        ../wolca/IntegerLength.h
        ../wolca/IntegerDigits.h)

set(SOURCE_FILES
        main.cpp
        TupleSizeTest.cpp
        NthTupleTest.cpp
        HasMemberTest.cpp
        IdentityTest.cpp
        TypeSelectionTest.cpp
        ReverseTupleTest.cpp
        IntegralConstantUtilityTest.cpp
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
        VariantUtilityTest.cpp
        CharSequenceUtilityTest.cpp
        math/PowerTest.cpp
        math/AbsTest.cpp
        math/RatioStringTest.cpp
        wolca/StringUtilityTest.cpp
        wolca/RangeTest.cpp
        wolca/IntegerLengthTest.cpp
        wolca/IntegerDigitsTest.cpp)

add_executable(RockyTest ${HEADER_FILES} ${SOURCE_FILES})

