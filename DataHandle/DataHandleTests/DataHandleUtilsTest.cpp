//
//  DataHandleUtilsTest.m
//  DataHandleTests
//
//  Created by Alkenso on 5/7/17.
//
//

#include "DataHandleUtils.h"

#include "TestData.h"

TEST(DataHandleUtils, ReverseValueByteOrder)
{
    EXPECT_EQ(datarw::utils::ReverseValueByteOrder<uint32_t>(datarw::testing::g_value0), datarw::testing::g_value0_BE);
    EXPECT_EQ(datarw::utils::ReverseValueByteOrder<uint64_t>(datarw::testing::g_value1), datarw::testing::g_value1_BE);
    
    EXPECT_EQ(datarw::utils::ReverseValueByteOrder<uint32_t>(datarw::testing::g_value0_BE), datarw::testing::g_value0);
    EXPECT_EQ(datarw::utils::ReverseValueByteOrder<uint64_t>(datarw::testing::g_value1_BE), datarw::testing::g_value1);
}

TEST(Range, RangeDefaultCtor)
{
    datarw::Range r;
    EXPECT_EQ(r.position, 0);
    EXPECT_EQ(r.length, 0);
}

TEST(Range, RangeParameterizedCtor)
{
    datarw::Range r(10, 20);
    EXPECT_EQ(r.position, 10);
    EXPECT_EQ(r.length, 20);
}

TEST(DataHandleUtils, RangesIntersects)
{
    const datarw::Range r1(100, 500);
    const datarw::Range r2(300, 50);
    const datarw::Range r3(400, 50);
    
    EXPECT_TRUE(datarw::utils::RangesIntersects(r1, r2));
    EXPECT_TRUE(datarw::utils::RangesIntersects(r1, r3));
    EXPECT_FALSE(datarw::utils::RangesIntersects(r2, r3));
}

TEST(DataHandleUtils, RangesIntersection)
{
    const datarw::Range r1(100, 500);
    const datarw::Range r2(300, 500);
    const datarw::Range r3(700, 100);
    
    const datarw::Range intersection = datarw::utils::RangesIntersection(r1, r2);
    EXPECT_EQ(intersection.position, 300);
    EXPECT_EQ(intersection.length, 300);
    
    const datarw::Range emptyRange = datarw::utils::RangesIntersection(r1, r3);
    EXPECT_EQ(emptyRange.position, -1);
    EXPECT_EQ(emptyRange.length, 0);
}

TEST(DataHandleUtils, RangesAreEqual)
{
    EXPECT_TRUE(datarw::utils::RangesAreEqual(datarw::Range(100, 500), datarw::Range(100, 500)));
    EXPECT_FALSE(datarw::utils::RangesAreEqual(datarw::Range(101, 500), datarw::Range(100, 500)));
}

TEST(DataHandleUtils, RangeWithAdditionalOffset)
{
    const datarw::Range range(100, 500);
    const datarw::Range rangeWithOffset = datarw::utils::RangeWithAdditionalOffset(range, 150);
    
    EXPECT_TRUE(datarw::utils::RangesAreEqual(rangeWithOffset, datarw::Range(250, 500)));
}
