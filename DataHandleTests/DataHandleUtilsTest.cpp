/*
 * Copyright (c) 2017 Alkenso (Vashurkin Vladimir)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "DataHandleBase.h"

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
