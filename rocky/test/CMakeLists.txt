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
        ../meta/ForEachArgument.h
        ../meta/ForEachTuple.h
        ../meta/HasMember.h
        ../meta/Identity.h
        ../meta/IntegerSequenceUtility.h
        ../meta/IntegralConstantUtility.h
        ../meta/MultipleInheritance.h
        ../meta/NthTuple.h
        ../meta/Remove.h
        ../meta/ReplaceTuple.h
        ../meta/ReverseTuple.h
        ../meta/Transform.h
        ../meta/TupleSize.h
        ../meta/TypeSelection.h
        ../meta/TypeUtility.h
        ../meta/UniqueTuple.h
        ../meta/CharSequenceUtility.h
        ../meta/TransformIntegerSequence.h
        ../meta/ExtractTuple.h
        ../meta/TypeList.h
        ../meta/TypeListJoin.h
        ../meta/TypeAt.h
        ../wolca/StringUtility.h
        ../wolca/Range.h
        ../wolca/IntegerLength.h
        ../wolca/IntegerDigits.h
        ../skull/Head.h
        ../skull/Tail.h
        ../skull/Take.h
        ../skull/Drop.h
        ../skull/Init.h
        ../skull/Map.h
        ../skull/Filter.h
        ../skull/FoldL.h
        ../skull/FoldR.h
        ../skull/Length.h)

set(SOURCE_FILES
        main.cpp
        ConstExprArrayTest.cpp
        StringNumberConversionTest.cpp
        VariantUtilityTest.cpp
        meta/TupleSizeTest.cpp
        meta/NthTupleTest.cpp
        meta/HasMemberTest.cpp
        meta/IdentityTest.cpp
        meta/TypeSelectionTest.cpp
        meta/ReverseTupleTest.cpp
        meta/IntegralConstantUtilityTest.cpp
        meta/MultipleInheritance.cpp
        meta/ForEachArgumentTest.cpp
        meta/IntegerSequenceUtilityTest.cpp
        meta/ForEachTupleTest.cpp
        meta/TypeUtilityTest.cpp
        meta/TransformTest.cpp
        meta/CountTupleTest.cpp
        meta/RemoveTest.cpp
        meta/ReplaceTupleTest.cpp
        meta/FindTupleTest.cpp
        meta/UniqueTupleTest.cpp
        meta/CharSequenceUtilityTest.cpp
        meta/TransformIntegerSequenceTest.cpp
        meta/ExtractTupleTest.cpp
        meta/TypeListTest.cpp
        meta/TypeListJoinTest.cpp
        meta/TypeAtTest.cpp
        math/PowerTest.cpp
        math/AbsTest.cpp
        math/RatioStringTest.cpp
        wolca/StringUtilityTest.cpp
        wolca/RangeTest.cpp
        wolca/IntegerLengthTest.cpp
        wolca/IntegerDigitsTest.cpp
        skull/HeadTest.cpp
        skull/TailTest.cpp
        skull/TakeTest.cpp
        skull/DropTest.cpp
        skull/InitTest.cpp
        skull/MapTest.cpp
        skull/FilterTest.cpp
        skull/FoldLTest.cpp
        skull/FoldRTest.cpp
        skull/LengthTest.cpp)

add_executable(RockyTest ${HEADER_FILES} ${SOURCE_FILES})

