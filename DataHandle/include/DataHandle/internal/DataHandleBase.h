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

#include <DataHandle/DataTypes.h>

namespace datarw
{
    class DataHandleBase
    {
    public:
        virtual ~DataHandleBase() {}
        
    protected:
        virtual uint64_t tellPosition() = 0;
        
    private:
        virtual uint64_t getDataSizeImpl() = 0;
        
        /* Some data sources (e.g. streams, files) have native implementation of seeking / reading consistent data.
         * Overriding 'seekPositionOptimized' allows derived classes to ignore range.position in 'peekDataImpl / writeDataImpl' methods.
         * That allows native seek implmenetation to be called only when needed. */
        virtual void seekPositionOptimized(const uint64_t position);
    };
    
    namespace utils
    {
        template<typename T>
        T ReverseValueByteOrder(T value);
    }
}

template<typename T>
T datarw::utils::ReverseValueByteOrder(T value)
{
    uint8_t* valuePtr = reinterpret_cast<uint8_t*>(&value);
    std::reverse(valuePtr, valuePtr + sizeof(value));
    
    return value;
}
