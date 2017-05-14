//
//  DataHandleUtilsTest.m
//  DataHandleTests
//
//  Created by Alkenso on 5/7/17.
//
//

#include <DataHandle/DataTypes.h>
#include <DataHandle/DataHandleBase.h>

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
