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

#pragma once

#include "DataTypes.h"

namespace datarw
{
    namespace testing
    {
        static const datarw::ByteBuffer g_testData = {
            0x09, 0x76, 0xC6, 0xEE, 0xF6, 0xB3, 0xF3, 0x8F, 0x79, 0xE6, 0x12, 0xCD, 0xE2, 0x8A, 0x8C, 0xFE,
            0x4A, 0x79, 0xC7, 0xB7, 0x20, 0x13, 0x42, 0xF3, 0x98, 0xC6, 0xBE, 0xA0, 0x11, 0x8B, 0x3F, 0xB6
        };
        
        static const datarw::ByteBuffer g_textualTestData = { // ABCDEFGHJKLMNOPQRSTUVWXYZ
            0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51,
            0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a
        };
        
        static const std::string g_testString = "ABCDEFGHJKLMNOPQRSTUVWXYZ";
        
        static const uint32_t g_value0 = 4294901760;
        static const uint32_t g_value0_BE = 65535;
        static const uint64_t g_value1 = 111998173032;
        static const uint64_t g_value1_BE = 7529908707841277952;
        static const datarw::ByteBuffer g_valuesLE = { 0x00, 0x00, 0xff, 0xff, 0x68, 0x7f, 0x9C, 0x13, 0x1A, 0x00, 0x00, 0x00 };
        static const datarw::ByteBuffer g_valuesBE = { 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x13, 0x9C, 0x7f, 0x68 };
        
        static const datarw::ByteBuffer g_fourZeroes = { 0x00, 0x00, 0x00, 0x00 };
    }
}
